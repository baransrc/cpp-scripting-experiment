#include <iostream>
#include <Windows.h>
#include <sstream>
#include <fstream>
#include "Script.h"
#include "Entity.h"

typedef Gameplay::Script* (__cdecl* InstantiateScript)(Gameplay::Entity*, const std::string&);

unsigned int SCRIPTING_DLL_INSTANCE_COUNT = 0;
static const std::wstring SCRIPTING_DLL_NAME = L"scripting_layer";

void RetrieveDllVersion(const wchar_t* dll_name, std::string& version)
{
    // Not used, but provided just in case:
    LPDWORD lpdword_handle_not_used = NULL;
    // Info size of the dll, will be used to allocate buffer memory:
    DWORD file_info_size = GetFileVersionInfoSize(dll_name, lpdword_handle_not_used);
    // Not used, added just in case, it says it is for future use in Win32 api docs:
    DWORD dw_handle_not_used = 0;
    
    LPVOID file_info_buffer = malloc(file_info_size);
    
    if (file_info_buffer == NULL)
    {
        return;
    }

    // Get version information into file_info_buffer and return FALSE if something goes wrong:
    if (GetFileVersionInfo(dll_name, dw_handle_not_used, file_info_size, file_info_buffer))
    {
        // Fixed version info of the file:
        LPBYTE fixed_version_info = NULL;
        // Fixed version info size in bytes, will be returned by VerQueryValue function:
        UINT fixed_version_size = 0;

        // If the specified file info structure exists, returns TRUE:
        if (VerQueryValue(file_info_buffer, L"\\", (VOID FAR * FAR*) &fixed_version_info, &fixed_version_size))
        {
            // If fixed_version_size is not zero:
            if (fixed_version_size)
            {
                // Get fixed_version_info as VS_FIXEDFILEINFO*:
                VS_FIXEDFILEINFO* version_info = (VS_FIXEDFILEINFO*)fixed_version_info;

                // Get the version as XXXX.XXXX.XXXX.XXXX:
                std::stringstream string_stream;
                string_stream << ((version_info->dwFileVersionMS >> 16) & 0xffff) << "."
                              << ((version_info->dwFileVersionMS >> 0) & 0xffff)  << "."
                              << ((version_info->dwFileVersionLS >> 16) & 0xffff) << "."
                              << ((version_info->dwFileVersionLS >> 0) & 0xffff);

                version = string_stream.str();
            }
        }
    }

    free(file_info_buffer);
}

bool IsDllVersionChanged(const wchar_t* dll_file_name, std::string& previous_version)
{
    // This function name is not descriptive enough as it also overwrites previous_version:

    std::string new_version;

    // Get the version of the dll file and write it to new_version:
    RetrieveDllVersion(dll_file_name, new_version);

    bool changed = (new_version != previous_version);

    // Update the supplide previous version to new version:
    previous_version = new_version;

    return changed;
}

void FreePreviousScriptingLayerDll(HMODULE previous_dll)
{
    // Get the previous dll instance number:
    unsigned int previous_dll_instance = SCRIPTING_DLL_INSTANCE_COUNT - 1;

    // Form it's name using the same formula LoadScriptDll uses:
    std::wstringstream wss;
    wss << L"_" << previous_dll_instance << L".dll";
    std::wstring previous_dll_name = SCRIPTING_DLL_NAME + wss.str();

    // Free the dll, and delete it:
    FreeLibrary(previous_dll);
    _wremove(previous_dll_name.c_str());
}

void LoadScriptingLayerDll(HMODULE* loaded_dll)
{
    // Ugly but works for now to visualize how the system will work at the end:
    // Increment this to hold an instance count of the original dll so we delete
    // the previous one when we load the new one:
    ++SCRIPTING_DLL_INSTANCE_COUNT;
    
    // Build the name of the new file that's gonna hold the copy of new dll:
    std::wstringstream wss;
    wss << L"_" << SCRIPTING_DLL_INSTANCE_COUNT << L".dll";
    std::wstring current_dll_name = SCRIPTING_DLL_NAME + wss.str();

    // Open the dll we will copy from, and dll we will use:
    std::ifstream source;
    std::ofstream destination(current_dll_name, std::ios::binary);
    
    // I couldn't solve this problem in a beautiful manner, for now I'm doing this to
    // do other stuff. TODO: Find a robust solution to this.
    // Wait while the file is just created:
    int source_buffer_size = 0;
    while (source_buffer_size <= 0)
    {   
        // Wait for 100ms to be less busy-waiting:
        Sleep(100);

        source.close();
        source.open(SCRIPTING_DLL_NAME + L".dll", std::ios::binary);

        source_buffer_size = source.rdbuf()->pubseekoff(0, source.end, source.in);
    }
    // Go back to initial position:
    source.rdbuf()->pubseekpos(0, source.in);

    // Copy the original dll to the one we will use:
    destination << source.rdbuf();

    // Close streams:
    source.close();
    destination.close();

    // Load the copied library:
    *loaded_dll = LoadLibrary(current_dll_name.c_str());
}

void DllHotReloadingExperiment()
{
    std::string current_version = "";
    // This is the handle to the dll we will use:
    HMODULE current_dll = NULL;

    // Retrieve dll version:
    RetrieveDllVersion(SCRIPTING_DLL_NAME.c_str(), current_version);
    
    // Copy the scripting dll into another file and load that as library:
    LoadScriptingLayerDll(&current_dll);

    InstantiateScript instantiate_script = reinterpret_cast<InstantiateScript>(GetProcAddress(current_dll, "InstantiateScript"));
    if (instantiate_script == NULL)
    {
        std::cout << "Could not find InstantiateScript function inside scripting_layer.dll" << std::endl;
        return;
    }

    Gameplay::Entity* entity = new Gameplay::Entity();
    
    // To simulate scene structure that has multiple entities:
    std::vector<Gameplay::Entity*> entities;
    entities.push_back(entity);

    // Instantiate scripts and add them into entity:
    entity->AddScript(instantiate_script(entity, "PlayerController"));
    entity->AddScript(instantiate_script(entity, "LevelManager"));
    entity->AddScript(instantiate_script(entity, "WinConditionManager"));

    // Run start once (also used to test if serialization works):
    entity->Start();

    while (true)
    {
        // If a different version of the dll is seen:
        if (IsDllVersionChanged(SCRIPTING_DLL_NAME.c_str(), current_version))
        {
            // Load new version of dll:
            HMODULE new_dll = NULL;
            LoadScriptingLayerDll(&new_dll);
            
            // Get the script instantiation function of the new dll:
            InstantiateScript new_instantiate_script = reinterpret_cast<InstantiateScript>(GetProcAddress(new_dll, "InstantiateScript"));
            if (instantiate_script == NULL)
            {
                std::cout << "Could not find InstantiateScript function inside scripting_layer.dll" << std::endl;
                return;
            }

            // Iterate through all the entities:
            for (Gameplay::Entity* current : entities)
            {   
                // Get the scripts of current entity:
                std::vector<Gameplay::Script*> new_scripts;
                for (Gameplay::Script* script : current->GetScripts())
                {
                    // Create an unordered_map of fields that are marked as SERIALIZE_FIELD,
                    // that are held as field name : std::string, copy : SerializedField pairs:
                    std::unordered_map<std::string, SerializedField> serialized_fields;
                    // Serialize fields into serialized_fields:
                    script->SerializeTo(serialized_fields);

                    // Create a new script of the same type in the new dll:
                    Gameplay::Script* new_script = new_instantiate_script(entity, script->GetName());
                    // Deserialize the serialized_fields map into new_script:
                    new_script->DeserializeFrom(serialized_fields);

                    // Clear serialized fields:
                    serialized_fields.clear();

                    // Add the script to new_scripts to be added to the same entity in the following
                    // lines:
                    new_scripts.push_back(new_script);
                }

                // Remove all the scripts that belong to the old dll:
                current->RemoveAllScripts();

                // Iterate through all the new_scripts:
                for (Gameplay::Script* script : new_scripts)
                {
                    // Add new script to the entity:
                    current->AddScript(script);
                }
            }

            // Free the dll, then delete the file which was copied from the original:
            FreePreviousScriptingLayerDll(current_dll);
            // Set new dll handles to the current dll handles:
            current_dll = new_dll;
            instantiate_script = new_instantiate_script;
        }

        // Update All entities:
        for (Gameplay::Entity* current : entities)
        {
            current->Update();
        }

        // Sleep for some time to not spam update logs:
        //Sleep(200);
    }

    // This is never run because of the while loop being an infinite one, but added just in
    // case to show that all the copies of the original dll will be deleted after the exec-
    // ution ends:
    ++SCRIPTING_DLL_INSTANCE_COUNT;
    FreePreviousScriptingLayerDll(current_dll);
}

int main()
{
    DllHotReloadingExperiment();

    std::cin.ignore();

    return 0;
}
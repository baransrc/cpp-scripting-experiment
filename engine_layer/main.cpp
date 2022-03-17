#include <iostream>
#include <Windows.h>
#include "Script.h"
#include "Entity.h"

typedef Gameplay::Script* (__cdecl* InstantiateScript)(Gameplay::Entity*, const std::string&);

void PrintDllVersion(const wchar_t* dll_name)
{
    LPDWORD lpdword_handle_not_used = NULL;
    DWORD file_info_size = GetFileVersionInfoSize(dll_name, lpdword_handle_not_used);
    DWORD dw_handle_not_used = 0;
    
    LPVOID file_info_buffer = malloc(file_info_size);

    if (GetFileVersionInfo(dll_name, dw_handle_not_used, file_info_size, file_info_buffer))
    {
        LPBYTE fixed_version_info = NULL;
        UINT fixed_version_size = 0;

        if (VerQueryValue(file_info_buffer, L"\\", (VOID FAR * FAR*) &fixed_version_info, &fixed_version_size))
        {
            if (fixed_version_size)
            {
                VS_FIXEDFILEINFO* version_info = (VS_FIXEDFILEINFO*)fixed_version_info;

                printf("File Version: %d.%d.%d.%d\n",
                    (version_info->dwFileVersionMS >> 16) & 0xffff,
                    (version_info->dwFileVersionMS >> 0) & 0xffff,
                    (version_info->dwFileVersionLS >> 16) & 0xffff,
                    (version_info->dwFileVersionLS >> 0) & 0xffff
                );
            }
        }
    }

    free(file_info_buffer);
}

void CallDLLByExplicitLinking()
{
    LPCWSTR dll_file_name = L"scripting_layer.dll";

    /*std::cout << "DLL VERSION: " << GetDllVersion(dll_file_name) << std::endl;*/

    PrintDllVersion(dll_file_name);

    HMODULE dll = LoadLibrary(dll_file_name);

    if (!dll)
    {
        std::cout << "Fail load library" << std::endl;
        return;
    }

    InstantiateScript instantiate_script = reinterpret_cast<InstantiateScript>(GetProcAddress(dll, "InstantiateScript"));

    if (!instantiate_script)
    {
        std::cerr << "Unable to load Instanitate Script function from DLL!\n";
        FreeLibrary(dll);
        return;
    }

    Gameplay::Entity* entity = new Gameplay::Entity();
    Gameplay::Script* player_controller = instantiate_script(entity, "PlayerController");
    Gameplay::Script* level_manager = instantiate_script(entity, "LevelManager");
    Gameplay::Script* win_condition_manager = instantiate_script(entity, "WinConditionManager");
    
    entity->AddScript(level_manager);
    entity->AddScript(player_controller);
    entity->AddScript(win_condition_manager);

    // The start method will be called once, in PlayerController::Start, 
    // the vector containing scripts are added to the vector.
    // We will see if the serialization works correctly by not calling
    // Start but only Update after the new created and deserialized script.
    entity->Start();
    entity->Update();

    // This scope is to free any resource in the serialized_fields before FreeLibrary.
    {
        std::cout << "Serializing PlayerController from what Script::Serialize does" << std::endl;
        std::unordered_map<std::string, SerializedField> serialized_fields;

        player_controller->SerializeTo(serialized_fields);

        std::cout << std::endl << "After removing PlayerController script" << std::endl << std::endl;

        entity->RemoveScript(player_controller);
        delete player_controller;

        entity->Update();

        std::cout << std::endl << "Adding new PlayerController script" << std::endl << std::endl;

        Gameplay::Script* new_player_controller = instantiate_script(entity, "PlayerController");

        new_player_controller->DeserializeFrom(serialized_fields);

        entity->AddScript(new_player_controller);

        std::cout << std::endl << "Update after new PlayerController script" << std::endl << std::endl;

        entity->Update();

        delete new_player_controller;
    }
    
    delete level_manager;
    delete win_condition_manager;
    delete entity;

    // Library has to be freed after the serialized fields are deleted,
    // This is gonna be tricky to implement.
    FreeLibrary(dll);
}

int main()
{
    CallDLLByExplicitLinking();

    std::cin.ignore();

    return 0;
}
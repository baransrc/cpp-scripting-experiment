#include <iostream>
#include <Windows.h>
#include "Script.h"
#include "Entity.h"

typedef Gameplay::Script* (__cdecl* InstantiateScript)(Gameplay::Entity*, const std::string&);

void CallDLLByExplicitLinking()
{
    LPCWSTR dll_file_name = L"scripting_layer.dll";

    /*std::cout << "DLL VERSION: " << GetDllVersion(dll_file_name) << std::endl;*/

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
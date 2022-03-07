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
    
    entity->AddScript(level_manager);
    entity->AddScript(player_controller);

    entity->Start();
    entity->Update();

    FreeLibrary(dll);
}

int main()
{
    CallDLLByExplicitLinking();

    std::cin.ignore();

    return 0;
}
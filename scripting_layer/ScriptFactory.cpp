#include "scripting_pch.h"
#include "ScriptFactory.h"
#include "LevelManager.h"
#include "PlayerController.h"


Gameplay::Script* InstantiateScript(Gameplay::Entity* script_owner, const std::string& script_name)
{
	if (script_name == "LevelManager")
	{
		return new Gameplay::LevelManager(script_owner);
	}

	if (script_name == "PlayerController")
	{
		return new Gameplay::PlayerController(script_owner);
	}
}
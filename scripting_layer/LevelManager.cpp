#include "scripting_pch.h"
#include "LevelManager.h"

#define GENERATE_SERIALIZED_FIELD(v) new SerializedField(NAME_OF(v), &std::any(v), typeid(v).name())

Gameplay::LevelManager::LevelManager(Entity* new_owner)
	: Script(owner, "LevelManager")
	, _level(0)
{
}

void Gameplay::LevelManager::LevelUp(int new_level)
{
	_level = new_level;

	const char* deneme = "host";

	std::cout << "Leveled up, new level is: " << _level << std::endl;
}

void Gameplay::LevelManager::Update()
{
	std::cout << "LevelManager::Update level is: " << _level << std::endl;
}

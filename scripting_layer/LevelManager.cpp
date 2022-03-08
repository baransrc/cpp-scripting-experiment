#include "scripting_pch.h"
#include "LevelManager.h"

#define GENERATE_SERIALIZED_FIELD(v) new SerializedField(NAME_OF(v), &std::any(v), typeid(v).name())

Gameplay::LevelManager::LevelManager(Entity* new_owner)
	: Script(owner)
	, _level(0)
{
}

void Gameplay::LevelManager::LevelUp(int new_level)
{
	_level = new_level;

	const char* deneme = "host";

	/*SerializedField* serialized_field_level = GENERATE_SERIALIZED_FIELD(_level);*/

	/*serialized_field_level->Print();*/

	std::cout << "Leveled up, new level is: " << _level << std::endl;

	//serialized_field_level->Print();
}

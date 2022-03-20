#include "scripting_pch.h"
#include "PlayerController.h"
#include "Entity.h"
#include "LevelManager.h"
#include "SerializedField.h"
#include "WinConditionManager.h"

Gameplay::PlayerController::PlayerController(Entity* new_owner)
	: Script(new_owner, "PlayerController")
{
}

void Gameplay::PlayerController::Start()
{
	std::cout << "PlayerController::Start" << std::endl;

	_entity_var = owner;

	_some_struct_var = { 69, "WOWOWOW" };
}

void Gameplay::PlayerController::Update()
{
	owner->IncrementVariable();

	std::cout << "This is working" << std::endl;
	
	std::cout << "Entity::some_variable is now: " << owner->GetVariable() << std::endl;

	owner->GetScript<LevelManager>()->LevelUp(69);

	std::cout << "Calling this from serialized var: " << _entity_var->GetScripts()[2]->GetName().c_str() << std::endl;

	std::cout << "Serialized Struct: " << _some_struct_var.string_field << " " << _some_struct_var.int_field << std::endl;
}
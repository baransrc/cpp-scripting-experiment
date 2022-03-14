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

	_vector_var.push_back(owner->GetScript<LevelManager>());
	_vector_var.push_back(owner->GetScript<WinConditionManager>());
}

void Gameplay::PlayerController::Update()
{
	owner->IncrementVariable();

	std::cout << "PlayerController::Update" << std::endl;
	
	std::cout << "Entity::some_variable is now: " << owner->GetVariable() << std::endl;

	owner->GetScript<LevelManager>()->LevelUp(69);

	for (Script* script : _vector_var)
	{
		std::cout << script->GetName().c_str() << std::endl;
	}
}
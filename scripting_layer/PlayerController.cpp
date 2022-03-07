#include "scripting_pch.h"
#include "PlayerController.h"
#include "Entity.h"
#include "LevelManager.h"
#include "SerializedField.h"

Gameplay::PlayerController::PlayerController(Entity* new_owner)
	: Script(new_owner)
{
}

void Gameplay::PlayerController::Start()
{
	std::cout << "PlayerController::Start" << std::endl;
}

void Gameplay::PlayerController::Update()
{
	owner->IncrementVariable();

	std::cout << "PlayerController::Update" << std::endl;
	
	std::cout << "Entity::some_variable is now: " << owner->GetVariable() << std::endl;

	owner->GetScript<LevelManager>()->LevelUp(69);
}
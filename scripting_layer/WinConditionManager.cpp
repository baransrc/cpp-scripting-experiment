#include "scripting_pch.h"
#include "WinConditionManager.h"
#include "Entity.h"

Gameplay::WinConditionManager::WinConditionManager(Entity* owner)
	: Script(owner, "WinConditionManager")
{

}

void Gameplay::WinConditionManager::Update()
{
	std::cout << "WinConditionManager::Update" << std::endl;
}

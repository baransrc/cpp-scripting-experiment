#include "scripting_pch.h"
#include "WinConditionManager.h"
#include "Entity.h"

Gameplay::WinConditionManager::WinConditionManager(Entity* owner)
	: Script(owner, "WinConditionManager")
{

}

void Gameplay::WinConditionManager::Update()
{
	std::cout << "WE ALL WINNERS MY DUDES" << std::endl;
}

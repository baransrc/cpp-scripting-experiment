#pragma once

#include "Script.h"

namespace Gameplay
{
class LevelManager : public Script
{
public:
	LevelManager(Entity* new_owner);
	~LevelManager() = default;

	void LevelUp(int new_level);

private:
	int _level;
};
}

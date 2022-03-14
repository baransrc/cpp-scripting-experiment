#pragma once

#include "Script.h"

class Deneme
{

};

namespace Gameplay
{
class LevelManager : public Script
{
	SERIALIZATION_METHODS(false)
public:
	LevelManager(Entity* new_owner);
	~LevelManager() = default;

	void LevelUp(int new_level);
	void Update() override;

private:
	int _level;
};
}

#pragma once

#include "Script.h"

namespace Gameplay
{
class WinConditionManager : public Script
{
	SERIALIZATION_METHODS(false)
public:
	WinConditionManager(Entity* owner);

	void Update() override;
};
} // namespace Gameplay

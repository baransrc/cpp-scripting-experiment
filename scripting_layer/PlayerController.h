#pragma once

#include "Script.h"

namespace Gameplay
{
class PlayerController : public Script
{
public:
	PlayerController(Entity* new_owner);
	~PlayerController() override = default;

	void Start() override;
	void Update() override;
};
} // namespace Gameplay

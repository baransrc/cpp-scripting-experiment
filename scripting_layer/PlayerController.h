#pragma once

#include "Script.h"

namespace Gameplay
{
class PlayerController : public Script
{
	SERIALIZATION_METHODS(false)
public:
	PlayerController(Entity* new_owner);
	~PlayerController() override = default;

	void Start() override;
	void Update() override;
private:
	SERIALIZE_FIELD(int, _integer_var);
	SERIALIZE_FIELD(std::vector<Script*>, _vector_var);
};
} // namespace Gameplay
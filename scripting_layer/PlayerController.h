#pragma once

#include "Script.h"

namespace Gameplay
{
struct SomeStruct
{
public:
	int int_field;
	std::string string_field;
};

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
	SERIALIZE_FIELD(Entity*, _entity_var);
	SERIALIZE_FIELD(SomeStruct, _some_struct_var);
};
} // namespace Gameplay
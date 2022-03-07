#pragma once

#include "Globals.h"
#include "SerializedField.h"

#include <string>
#include <vector>
#include <typeinfo>

namespace Gameplay
{
class Entity;

class ENGINE_EXPOSE Script
{
public: 
	virtual ~Script() = default;

	virtual void Start() {};
	virtual void Update() {};
	virtual void Disable() {};
	virtual void Enable() {};

protected:
	explicit Script(Entity* new_owner) : owner(new_owner) {};

protected:
	Entity* owner;

private:
	//std::vector<SerializedField> 
};
}


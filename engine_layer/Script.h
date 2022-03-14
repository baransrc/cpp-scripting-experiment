#pragma once

#include "Globals.h"
#include "SerializedField.h"
#include "ISerializable.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <typeinfo>

#define SERIALIZE_FIELD(type, name) type name

// This needs to be added to all script sub classes:
#define SERIALIZATION_METHODS(is_virtual) SERIALIZATION_METHODS_##is_virtual
#define SERIALIZATION_METHODS_true public: virtual void SerializeTo(std::unordered_map<std::string, SerializedField>& serialized_fields) override; virtual void DeserializeFrom(std::unordered_map<std::string, SerializedField>& serialized_fields) override;
#define SERIALIZATION_METHODS_false public: void SerializeTo(std::unordered_map<std::string, SerializedField>& serialized_fields) override; void DeserializeFrom(std::unordered_map<std::string, SerializedField>& serialized_fields) override;

namespace Gameplay
{
class Entity;

class ENGINE_EXPOSE Script : ISerializable
{
	SERIALIZATION_METHODS(true)
public: 
	virtual ~Script() = default;

	virtual void Start() {};
	virtual void Update() {};
	virtual void Disable() {};
	virtual void Enable() {};

	const std::string& GetName() const { return name; };

protected:
	explicit Script(Entity* new_owner, std::string new_name) : owner(new_owner), name(new_name) {  };

protected:
	Entity* owner;

private:
	std::string name;
};
}
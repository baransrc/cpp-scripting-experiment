#pragma once

#include "Globals.h"
#include "SerializedField.h"
#include <unordered_map>

namespace Gameplay
{
class ENGINE_EXPOSE ISerializable
{
public:
	virtual void SerializeTo(std::unordered_map<std::string, SerializedField>& serialized_fields) = 0;
	virtual void DeserializeFrom(std::unordered_map<std::string, SerializedField>& serialized_fields) = 0;
	virtual void ShowInEditor() {};
};
} // namespace Gameplay
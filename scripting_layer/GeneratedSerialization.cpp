#include <vector>
#include <string>
#include <unordered_map>
#include "scripting_pch.h"
#include "ISerializable.h"
#include "SerializedField.h"
#include "LevelManager.h"
#include "PlayerController.h"
#include "WinConditionManager.h"


void Gameplay::LevelManager::DeserializeFrom(std::unordered_map<std::string, SerializedField>& serialized_fields)
{
	Gameplay::Script::DeserializeFrom(serialized_fields);
}

void Gameplay::LevelManager::SerializeTo(std::unordered_map<std::string, SerializedField>& serialized_fields)
{
	Gameplay::Script::SerializeTo(serialized_fields);
}

void Gameplay::PlayerController::DeserializeFrom(std::unordered_map<std::string, SerializedField>& serialized_fields)
{
	Gameplay::Script::DeserializeFrom(serialized_fields);

	if(serialized_fields.find("_integer_var") != serialized_fields.end())
	{
		const SerializedField& _integer_var_sf = serialized_fields["_integer_var"];
		if (_integer_var_sf.type_name == "int")
		{
			_integer_var = std::any_cast<int>(_integer_var_sf.copy);
		}
	}

	if(serialized_fields.find("_entity_var") != serialized_fields.end())
	{
		const SerializedField& _entity_var_sf = serialized_fields["_entity_var"];
		if (_entity_var_sf.type_name == "Entity*")
		{
			_entity_var = std::any_cast<Entity*>(_entity_var_sf.copy);
		}
	}

	if(serialized_fields.find("_some_struct_var") != serialized_fields.end())
	{
		const SerializedField& _some_struct_var_sf = serialized_fields["_some_struct_var"];
		if (_some_struct_var_sf.type_name == "SomeStruct")
		{
			_some_struct_var = std::any_cast<SomeStruct>(_some_struct_var_sf.copy);
		}
	}
}

void Gameplay::PlayerController::SerializeTo(std::unordered_map<std::string, SerializedField>& serialized_fields)
{
	Gameplay::Script::SerializeTo(serialized_fields);

	serialized_fields["_integer_var"] = SerializedField(std::string("_integer_var"), std::make_any<int>(_integer_var), std::string("int"));

	serialized_fields["_entity_var"] = SerializedField(std::string("_entity_var"), std::make_any<Entity*>(_entity_var), std::string("Entity*"));

	serialized_fields["_some_struct_var"] = SerializedField(std::string("_some_struct_var"), std::make_any<SomeStruct>(_some_struct_var), std::string("SomeStruct"));
}

void Gameplay::WinConditionManager::DeserializeFrom(std::unordered_map<std::string, SerializedField>& serialized_fields)
{
	Gameplay::Script::DeserializeFrom(serialized_fields);
}

void Gameplay::WinConditionManager::SerializeTo(std::unordered_map<std::string, SerializedField>& serialized_fields)
{
	Gameplay::Script::SerializeTo(serialized_fields);
}
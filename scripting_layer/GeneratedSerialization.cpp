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

	if(serialized_fields.find("_vector_var") != serialized_fields.end())
	{
		const SerializedField& _vector_var_sf = serialized_fields["_vector_var"];
		if (_vector_var_sf.type_name == "std::vector<Script*>")
		{
			_vector_var = std::any_cast<std::vector<Script*>>(_vector_var_sf.copy);
		}
	}
}

void Gameplay::PlayerController::SerializeTo(std::unordered_map<std::string, SerializedField>& serialized_fields)
{
	Gameplay::Script::SerializeTo(serialized_fields);

	serialized_fields["_integer_var"] = SerializedField(std::string("_integer_var"), std::make_any<int>(_integer_var), std::string("int"));

	serialized_fields["_vector_var"] = SerializedField(std::string("_vector_var"), std::make_any<std::vector<Script*>>(_vector_var), std::string("std::vector<Script*>"));
}

void Gameplay::WinConditionManager::DeserializeFrom(std::unordered_map<std::string, SerializedField>& serialized_fields)
{
	Gameplay::Script::DeserializeFrom(serialized_fields);
}

void Gameplay::WinConditionManager::SerializeTo(std::unordered_map<std::string, SerializedField>& serialized_fields)
{
	Gameplay::Script::SerializeTo(serialized_fields);
}
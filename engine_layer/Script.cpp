#include "Script.h"

void Gameplay::Script::SerializeTo(std::unordered_map<std::string, SerializedField>& serialized_fields)
{
	serialized_fields["owner"] = SerializedField(std::string("owner"), std::make_any<Entity*>(owner), std::string("Entity*"));
}

void Gameplay::Script::DeserializeFrom(std::unordered_map<std::string, SerializedField>& serialized_fields)
{
	if (serialized_fields.find("owner") != serialized_fields.end())
	{
		const SerializedField& owner_serialized_field = serialized_fields["owner"];
		
		if (owner_serialized_field.type_name == "Entity*")
		{
			owner = std::any_cast<Entity*>(owner_serialized_field.copy);
		}
	}
}
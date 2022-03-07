#include "SerializedField.h"


SerializedField::SerializedField(std::string name, std::any* reference, std::string type_name, std::string former_name)
	: _name(name)
	, _reference(reference)
	, _type_name(type_name)
	, _former_name(former_name)
{
}

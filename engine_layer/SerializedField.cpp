#include "SerializedField.h"


SerializedField::SerializedField(std::string name, std::any copy, std::string type_name)
	: name(name)
	, copy(copy)
	, type_name(type_name)
{
}

SerializedField::SerializedField()
	: name({})
	, copy(std::any::any())
	, type_name({})
{
}
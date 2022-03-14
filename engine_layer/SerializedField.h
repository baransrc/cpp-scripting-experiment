#pragma once

#include "Globals.h"
#include <string>
#include <typeinfo>
#include <iostream>
#include <any>

class ENGINE_EXPOSE SerializedField
{
public:
	explicit SerializedField();
	explicit SerializedField(std::string name, std::any copy, std::string type_name);
	~SerializedField() = default;

public:
	std::string name;
	std::string type_name;
	std::any copy;
};


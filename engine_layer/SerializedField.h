#pragma once

#include "Globals.h"
#include <string>
#include <typeinfo>
#include <iostream>

class ENGINE_EXPOSE SerializedField
{
public:
	SerializedField(std::string name, void* reference, std::string type_name, std::string former_name = "");
	~SerializedField() = default;

	void Print() { 
		using Type = typename std::remove_reference<decltype(_reference)>::type;
		std::cout << "Name: " << _name.c_str() << " Type: " << _type_name.c_str() << " Former Name: " << _former_name <<  " " <<  (Type)_reference << std::endl; }

private:
	//size_t _type_id;
	std::string _name;
	std::string _type_name;
	std::string _former_name;
	void* _reference;
};

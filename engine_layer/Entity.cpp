#include "Entity.h"
#include "Script.h"

Gameplay::Entity::Entity()
	: some_variable(0)
{
}

Gameplay::Entity::~Entity()
{
}

void Gameplay::Entity::Start()
{
	for (Script* script : scripts)
	{
		script->Start();
	}
}

void Gameplay::Entity::Update()
{
	for (Script* script : scripts)
	{
		script->Update();
	}
}

void Gameplay::Entity::Enable()
{
	for (Script* script : scripts)
	{
		script->Enable();
	}
}

void Gameplay::Entity::Disable()
{
	for (Script* script : scripts)
	{
		script->Disable();
	}
}

void Gameplay::Entity::AddScript(Script* script)
{
	scripts.push_back(script);
}

void Gameplay::Entity::RemoveScript(Script* script)
{
	// TODO: Check by unique script id.

	std::vector<Script*>::const_iterator script_index;
	bool found_script = false;

	for (script_index = scripts.begin(); script_index < scripts.end(); ++script_index)
	{
		if (typeid(*(*script_index)) == typeid(*script))
		{
			found_script = true;
			break;
		}
	}

	if (found_script)
	{
		scripts.erase(script_index);
	}
}

void Gameplay::Entity::IncrementVariable()
{
	++some_variable;
}

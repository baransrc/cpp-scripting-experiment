#pragma once

#include <vector>
#include <string>
#include <typeinfo>
#include "Globals.h"

namespace Gameplay
{
class Script;

class ENGINE_EXPOSE Entity
{
public:
	Entity();
	~Entity();

	void Start();
	void Update();
	void Enable();
	void Disable();

	void AddScript(Script* script);
	template <class SCRIPT_T> void RemoveScript();
	void RemoveScript(Script* script);
	template <class SCRIPT_T> SCRIPT_T* GetScript() const;
	Script* GetScript(std::string name);
	void IncrementVariable();
	int GetVariable() const { return some_variable; };

	std::vector<Script*>& GetScripts() { return scripts; }

	void RemoveAllScripts();

private:
	std::vector<Script*> scripts;
	int some_variable;
};

template<class SCRIPT_T>
inline void Entity::RemoveScript()
{
	// TODO: Check by script unique id.

	std::vector<Script*>::const_iterator script_index;
	bool found_script = false;

	for (script_index = scripts.begin(); script_index < scripts.end(); ++script_index)
	{
		if (typeid(*(*script_index)) == typeid(SCRIPT_T))
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

template<class SCRIPT_T>
inline SCRIPT_T* Entity::GetScript() const
{
	for (Script* script : scripts)
	{
		if (typeid(*script) == typeid(SCRIPT_T))
		{
			return (SCRIPT_T*) script;
		}
	}

	return nullptr;
}
} // namespace Gameplay
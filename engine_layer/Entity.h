#pragma once

#include <vector>
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
	template <class SCRIPT_T> SCRIPT_T* GetScript() const;
	void IncrementVariable();
	int GetVariable() const { return some_variable; };

private:
	std::vector<Script*> scripts;
	int some_variable;
};

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
#pragma once

#include "Script.h"
#include "Entity.h"
#include "scripting_pch.h"


extern "C" SCRIPTING_API Gameplay::Script * __cdecl InstantiateScript(Gameplay::Entity * script_owner, const std::string & script_name);
#pragma once

// Exposes a method/function/class to other modules in .lib
// so that they can be used:
#define ENGINE_EXPOSE __declspec(dllexport) 

// Stringizes the name of a variable/class at runtime:
#define NAME_OF( v ) ((void) sizeof(v), #v) 
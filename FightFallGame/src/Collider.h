#pragma once
#include "SDL.h"

class Collider
{
public:
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
};
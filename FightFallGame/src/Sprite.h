#pragma once
#include "SDL_image.h"
#include "./Window/Window.h"

class Sprite
{
public:
	Window* window;

public:
	Sprite(const char* path, Window* window);
	Sprite() = default;
	~Sprite();

	void ChangeSprite(const char* path);

	const char* path;
private:

public:
	SDL_Surface* surface;
	SDL_Texture* tex;
};
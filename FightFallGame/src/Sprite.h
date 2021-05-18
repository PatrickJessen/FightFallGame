#pragma once
#include "SDL_image.h"
#include "./Window/Window.h"

class Sprite
{
public:
	Window* window;

public:
	Sprite(const char* path, Window* window);
	~Sprite();

	void ChangeSprite(const char* path);

private:
	const char* path;

public:
	SDL_Surface* surface;
	SDL_Texture* tex;
};
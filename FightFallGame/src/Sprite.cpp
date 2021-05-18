#include "Sprite.h"

Sprite::Sprite(const char* path, Window* window)
{
	this->window = window;
	this->path = path;
	surface = IMG_Load(path);
	tex = SDL_CreateTextureFromSurface(window->GetRender(), surface);
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(tex);
	SDL_FreeSurface(surface);
}

void Sprite::ChangeSprite(const char* path)
{
	this->path = path;
	SDL_DestroyTexture(tex);
	SDL_FreeSurface(surface);
	surface = IMG_Load(path);
	tex = SDL_CreateTextureFromSurface(window->GetRender(), surface);
}
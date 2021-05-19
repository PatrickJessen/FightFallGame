#pragma once
#include "../Window/Window.h"
#include <unordered_map>
#include "../Sprite.h"
#include "../Server/Common.h"


class Character : public client_interface<GameMsg>
{
public:
	virtual ~Character() = default;

	virtual void OnPlayerCreate() = 0;
	virtual void OnPlayerUpdate() = 0;

protected:
	std::unordered_map<uint32_t, sPlayerDescription> object;
	uint32_t playerID = 0;
	sPlayerDescription playerDesc;

	bool waitingForConnection = true;

	SDL_Rect transform;
	Sprite* sprite;
	Window* window;
};
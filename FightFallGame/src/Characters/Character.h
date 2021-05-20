#pragma once
#include "../Window/Window.h"
#include <unordered_map>
#include "../Sprite.h"
#include "../Server/Common.h"

class Character : public client_interface<GameMsg>
{
public:
	virtual ~Character() = default;

	void Update();
	void ConnectToServer();

	virtual void OnPlayerCreate() = 0;
	virtual void OnPlayerUpdate() = 0;

protected:
	uint32_t nPlayerID = 0;
	std::unordered_map<uint32_t, sPlayerDescription> mapObjects;
	sPlayerDescription descPlayer;

	SDL_Rect rect;

	Sprite* sprite;
	Window* window;

private:
	bool waitingForConnection = true;

};
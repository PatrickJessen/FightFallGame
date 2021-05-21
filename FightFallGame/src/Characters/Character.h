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
	void Gravity();
	void Collision();

	virtual void OnPlayerCreate() = 0;
	virtual void OnPlayerUpdate() = 0;

protected:
	uint32_t nPlayerID = 0;
	std::unordered_map<uint32_t, sPlayerDescription> mapObjects;
	sPlayerDescription descPlayer;

	SDL_Rect rect;
	SDL_Rect srcRect;
	SDL_Rect platform;

	Sprite* sprite;
	Window* window;

	int spriteNr = 0;

	std::string pathNr = "Assets/run" + spriteNr;

private:
	bool waitingForConnection = true;

};
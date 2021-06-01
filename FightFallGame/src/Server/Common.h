#pragma once
#include <cstdint>
#include "Network.h"
#include "../Sprite.h"
#include "../Vector/Vec2D.h"

enum class KeyPress
{
	STALL,
	JUMP,
	LEFT,
	RIGHT,
	HITLEFT,
	HITRIGHT,
	HITUP
};

enum class GameMsg : uint32_t
{
	Server_GetStatus,
	Server_GetPing,

	Client_Accepted,
	Client_AssignID,
	Client_RegisterWithServer,
	Client_UnregisterWithServer,

	Game_AddPlayer,
	Game_RemovePlayer,
	Game_UpdatePlayer,
};

struct sPlayerDescription
{
	uint32_t nUniqueID = 0;
	uint32_t nAvatarID = 0;

	uint32_t nHealth = 100;
	uint32_t nAmmo = 20;

	float fRadius = 0.5f;

	float xPos;
	float yPos;
	int width;
	int height;

	int animX;
	int animY;

	float velocityX;
	float velocityY;

	bool canJump = false;

	KeyPress keyPress;
	Sprite* sprite;
	SDL_RendererFlip flip;
	SDL_Rect punchHitbox;
	SDL_Rect playerHitbox;

	sPlayerDescription() {}
};
#pragma once
#include <cstdint>
#include "Network.h"
#include "../Sprite.h"
#include "../Vector/Vec2D.h"
#include "../Characters/Abillities/Projectile.h"

enum class KeyPress
{
	STALL,
	JUMP,
	LEFT,
	RIGHT,
	HITLEFT,
	HITRIGHT,
	HITUP,
	BLOCK,
	DIZZY,
	HURT,
	KO,
	SHOOT,
	SLIDE
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

	float hsp = 2.0f;
	float vsp = 2.0f;
	float bulletPosX;
	float bulletPosY;
	int bulletWidth = 32;
	int bulletHeight = 32;
	SDL_RendererFlip bulletFlip;
	int projectileSize;

	int animX;
	int animY;

	float velocityX;
	float velocityY;

	bool canJump = false;

	KeyPress keyPress;
	Sprite* sprite;
	Sprite* sprBullet;
	SDL_RendererFlip flip;
	SDL_Rect punchHitbox;
	SDL_Rect playerHitbox;

	const char* path;
	const char* bulletPath;

	sPlayerDescription() {}
};
#pragma once
#include "Character.h"
#include "Abillities/Projectile.h"

class Robot : public Character
{
public:
	Robot(Window* window, Sprite* sprite);
	~Robot();

public:
	virtual void OnPlayerCreate() override;
	virtual void OnPlayerUpdate() override;

private:
	void Movement(std::pair<const uint32_t, sPlayerDescription>& object);

	Sprite* sprBullet;
	std::vector<Projectile> projectiles;

	float posX = 450;
	float posY = 300;
	float hsp = 2.0f;
	float vsp = 2.0f;

	SDL_Rect test;

private:
	const char* run[8] = { "Assets/Robot/Run (1).png", "Assets/Robot/Run (2).png", "Assets/Robot/Run (3).png", "Assets/Robot/Run (4).png", "Assets/Robot/Run (5).png", "Assets/Robot/Run (6).png", "Assets/Robot/Run (7).png", "Assets/Robot/Run (8).png" };

	const char* idle[10] = { "Assets/Robot/Idle (1).png", "Assets/Robot/Idle (2).png", "Assets/Robot/Idle (3).png", "Assets/Robot/Idle (4).png", "Assets/Robot/Idle (5).png", "Assets/Robot/Idle (6).png", "Assets/Robot/Idle (7).png", "Assets/Robot/Idle (8).png", "Assets/Robot/Idle (9).png", "Assets/Robot/Idle (10).png" };

	const char* attack[10] = { "Assets/Robot/Attack (1).png", "Assets/Robot/Attack (2).png", "Assets/Robot/Attack (3).png", "Assets/Robot/Attack (4).png", "Assets/Robot/Attack (5).png", "Assets/Robot/Attack (6).png", "Assets/Robot/Attack (7).png", "Assets/Robot/Attack (8).png", "Assets/Robot/Attack (9).png", "Assets/Robot/Attack (10).png" };

	const char* throwKnife[10] = { "Assets/Robot/Throw (1).png", "Assets/Robot/Throw (2).png", "Assets/Robot/Throw (3).png", "Assets/Robot/Throw (4).png", "Assets/Robot/Throw (5).png", "Assets/Robot/Throw (6).png", "Assets/Robot/Throw (7).png", "Assets/Robot/Throw (8).png", "Assets/Robot/Throw (9).png", "Assets/Robot/Throw (10).png" };

	const char* slide[10] = { "Assets/Robot/Slide (1).png", "Assets/Robot/Slide (2).png", "Assets/Robot/Slide (3).png", "Assets/Robot/Slide (4).png", "Assets/Robot/Slide (5).png", "Assets/Robot/Slide (6).png", "Assets/Robot/Slide (7).png", "Assets/Robot/Slide (8).png", "Assets/Robot/Slide (9).png", "Assets/Robot/Slide (10).png" };

	const char* block[10] = { "Assets/Robot/Run (1).png", "Assets/Robot/Run (2).png", "Assets/Robot/Run (3).png", "Assets/Robot/Run (4).png", "Assets/Robot/Run (5).png", "Assets/Robot/Run (6).png", "Assets/Robot/Run (7).png", "Assets/Robot/Run (8).png", "Assets/Robot/Run (9).png", "Assets/Robot/Run (10).png" };

	const char* bullet[5] = { "Assets/Robot/Objects/Bullet_000.png", "Assets/Robot/Objects/Bullet_001.png", "Assets/Robot/Objects/Bullet_002.png", "Assets/Robot/Objects/Bullet_003.png", "Assets/Robot/Objects/Bullet_004.png" };

	const char* shoot[4] = { "Assets/Robot/Shoot (1).png", "Assets/Robot/Shoot (2).png", "Assets/Robot/Shoot (3).png", "Assets/Robot/Shoot (4).png" };
};
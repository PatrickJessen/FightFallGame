#pragma once
#include "Character.h"

class Ninja : public Character
{
public:
	Ninja(Window* window, Sprite* sprite);
	~Ninja();

public:
	virtual void OnPlayerCreate() override;
	virtual void OnPlayerUpdate() override;

private:
	const char* run[10] = { "Assets/Ninja/Run (1).png", "Assets/Ninja/Run (2).png", "Assets/Ninja/Run (3).png", "Assets/Ninja/Run (4).png", "Assets/Ninja/Run (5).png", "Assets/Ninja/Run (6).png", "Assets/Ninja/Run (7).png", "Assets/Ninja/Run (8).png", "Assets/Ninja/Run (9).png", "Assets/Ninja/Run (10).png" };

	const char* idle[10] = { "Assets/Ninja/Idle (1).png", "Assets/Ninja/Idle (2).png", "Assets/Ninja/Idle (3).png", "Assets/Ninja/Idle (4).png", "Assets/Ninja/Idle (5).png", "Assets/Ninja/Idle (6).png", "Assets/Ninja/Idle (7).png", "Assets/Ninja/Idle (8).png", "Assets/Ninja/Idle (9).png", "Assets/Ninja/Idle (10).png" };

	const char* attack[10] = { "Assets/Ninja/Attack (1).png", "Assets/Ninja/Attack (2).png", "Assets/Ninja/Attack (3).png", "Assets/Ninja/Attack (4).png", "Assets/Ninja/Attack (5).png", "Assets/Ninja/Attack (6).png", "Assets/Ninja/Attack (7).png", "Assets/Ninja/Attack (8).png", "Assets/Ninja/Attack (9).png", "Assets/Ninja/Attack (10).png" };

	const char* throwKnife[10] = { "Assets/Ninja/Throw (1).png", "Assets/Ninja/Throw (2).png", "Assets/Ninja/Throw (3).png", "Assets/Ninja/Throw (4).png", "Assets/Ninja/Throw (5).png", "Assets/Ninja/Throw (6).png", "Assets/Ninja/Throw (7).png", "Assets/Ninja/Throw (8).png", "Assets/Ninja/Throw (9).png", "Assets/Ninja/Throw (10).png" };

	const char* slide[10] = { "Assets/Ninja/Slide (1).png", "Assets/Ninja/Slide (2).png", "Assets/Ninja/Slide (3).png", "Assets/Ninja/Slide (4).png", "Assets/Ninja/Slide (5).png", "Assets/Ninja/Slide (6).png", "Assets/Ninja/Slide (7).png", "Assets/Ninja/Slide (8).png", "Assets/Ninja/Slide (9).png", "Assets/Ninja/Slide (10).png" };

	const char* block[10] = { "Assets/Ninja/Run (1).png", "Assets/Ninja/Run (2).png", "Assets/Ninja/Run (3).png", "Assets/Ninja/Run (4).png", "Assets/Ninja/Run (5).png", "Assets/Ninja/Run (6).png", "Assets/Ninja/Run (7).png", "Assets/Ninja/Run (8).png", "Assets/Ninja/Run (9).png", "Assets/Ninja/Run (10).png" };
};
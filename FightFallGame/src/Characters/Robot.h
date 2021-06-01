#pragma once
#include "Character.h"

class Robot : public Character
{
public:
	Robot(Window* window, Sprite* sprite);
	~Robot();

public:
	virtual void OnPlayerCreate() override;
	virtual void OnPlayerUpdate() override;

private:
	const char* run[8] = { "Assets/Robot/Run (1).png", "Assets/Robot/Run (2).png", "Assets/Robot/Run (3).png", "Assets/Robot/Run (4).png", "Assets/Robot/Run (5).png", "Assets/Robot/Run (6).png", "Assets/Robot/Run (7).png", "Assets/Robot/Run (8).png" };

	const char* idle[10] = { "Assets/Robot/Idle (1).png", "Assets/Robot/Idle (2).png", "Assets/Robot/Idle (3).png", "Assets/Robot/Idle (4).png", "Assets/Robot/Idle (5).png", "Assets/Robot/Idle (6).png", "Assets/Robot/Idle (7).png", "Assets/Robot/Idle (8).png", "Assets/Robot/Idle (9).png", "Assets/Robot/Idle (10).png" };

	const char* attack[10] = { "Assets/Robot/Attack (1).png", "Assets/Robot/Attack (2).png", "Assets/Robot/Attack (3).png", "Assets/Robot/Attack (4).png", "Assets/Robot/Attack (5).png", "Assets/Robot/Attack (6).png", "Assets/Robot/Attack (7).png", "Assets/Robot/Attack (8).png", "Assets/Robot/Attack (9).png", "Assets/Robot/Attack (10).png" };

	const char* throwKnife[10] = { "Assets/Robot/Throw (1).png", "Assets/Robot/Throw (2).png", "Assets/Robot/Throw (3).png", "Assets/Robot/Throw (4).png", "Assets/Robot/Throw (5).png", "Assets/Robot/Throw (6).png", "Assets/Robot/Throw (7).png", "Assets/Robot/Throw (8).png", "Assets/Robot/Throw (9).png", "Assets/Robot/Throw (10).png" };

	const char* slide[10] = { "Assets/Robot/Slide (1).png", "Assets/Robot/Slide (2).png", "Assets/Robot/Slide (3).png", "Assets/Robot/Slide (4).png", "Assets/Robot/Slide (5).png", "Assets/Robot/Slide (6).png", "Assets/Robot/Slide (7).png", "Assets/Robot/Slide (8).png", "Assets/Robot/Slide (9).png", "Assets/Robot/Slide (10).png" };

	const char* block[10] = { "Assets/Robot/Run (1).png", "Assets/Robot/Run (2).png", "Assets/Robot/Run (3).png", "Assets/Robot/Run (4).png", "Assets/Robot/Run (5).png", "Assets/Robot/Run (6).png", "Assets/Robot/Run (7).png", "Assets/Robot/Run (8).png", "Assets/Robot/Run (9).png", "Assets/Robot/Run (10).png" };
};
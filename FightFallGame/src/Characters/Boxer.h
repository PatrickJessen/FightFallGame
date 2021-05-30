#pragma once
#include "Character.h"

class Boxer : public Character
{
public:
	Boxer(Window* window, Sprite* sprite);
	~Boxer();

public:
	virtual void OnPlayerCreate() override;
	virtual void OnPlayerUpdate() override;


private:
	const char* punchRightPath[6] = { "Assets/boxer/PunchRight1.png", "Assets/boxer/PunchRight2.png", "Assets/boxer/PunchRight3.png", "Assets/boxer/PunchRight4.png", "Assets/boxer/PunchRight5.png", "Assets/boxer/PunchRight6.png" };
	const char* punchLeftPath[6] = { "Assets/boxer/PunchLeft1.png", "Assets/boxer/PunchLeft2.png", "Assets/boxer/PunchLeft3.png", "Assets/boxer/PunchLeft4.png", "Assets/boxer/PunchLeft5.png", "Assets/boxer/PunchLeft6.png" };
	const char* boxerIdle[10] = { "Assets/boxer/Idle1.png", "Assets/boxer/Idle2.png", "Assets/boxer/Idle3.png", "Assets/boxer/Idle4.png", "Assets/boxer/Idle5.png", "Assets/boxer/Idle6.png", "Assets/boxer/Idle7.png", "Assets/boxer/Idle8.png", "Assets/boxer/Idle9.png", "Assets/boxer/Idle10.png" };

	const char* boxerWalk[10] = { "Assets/boxer/Walk (1).png", "Assets/boxer/Walk (2).png", "Assets/boxer/Walk (3).png", "Assets/boxer/Walk (4).png", "Assets/boxer/Walk (5).png", "Assets/boxer/Walk (6).png", "Assets/boxer/Walk (7).png", "Assets/boxer/Walk (8).png", "Assets/boxer/Walk (9).png", "Assets/boxer/Walk (10).png" };
};
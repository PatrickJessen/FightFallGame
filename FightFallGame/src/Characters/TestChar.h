#pragma once
#include "Character.h"

class TestChar : public Character
{
public:
	TestChar(Sprite* sprite, Window* window, int posX, int posY, int width, int height);
	~TestChar();

public:
	virtual void OnPlayerCreate() override;
	virtual void OnPlayerUpdate() override;
};
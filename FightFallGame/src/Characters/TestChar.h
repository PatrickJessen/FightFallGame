#pragma once
#include "Character.h"
#include <asio.hpp>

class TestChar : public Character
{
public:
	TestChar(Window* window, Sprite* sprite)
	{
		this->window = window;
		this->sprite = sprite;
	}
	~TestChar();

public:
	virtual void OnPlayerCreate() override;
	virtual void OnPlayerUpdate() override;

private:
	void SetMovement();
	bool test = true;
};


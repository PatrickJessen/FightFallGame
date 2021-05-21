#include "TestChar.h"
#include "../Input.h"

TestChar::~TestChar()
{
}

void TestChar::OnPlayerCreate()
{
	descPlayer.xPos = 300;
	descPlayer.yPos = 300;
	descPlayer.width = 200;
	descPlayer.height = 200;
}

void TestChar::OnPlayerUpdate()
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 seconds = ticks / 1000;
	Uint32 spriteTick = (ticks / 150) % 8;
	if (Input::KeyState(Key::W))
	{
		mapObjects[nPlayerID].yPos -= 6;
		//srcRect = { ((int)spriteTick % 12) * 84, -1, 42, 73 };
	}
	if (Input::KeyState(Key::S))
	{
		mapObjects[nPlayerID].yPos += 6;
	}
	if (Input::KeyState(Key::A))
	{
		mapObjects[nPlayerID].xPos -= 6;
	}
	if (Input::KeyState(Key::D))
	{
		mapObjects[nPlayerID].xPos += 6;
		sprite->ChangeSprite("Assets/sprite1walk.png");
		mapObjects[nPlayerID].animX = ((int)spriteTick % 4) * 40;
		
	}
}

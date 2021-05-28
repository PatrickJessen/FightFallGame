#include "TestChar.h"
#include "../Input.h"

TestChar::~TestChar()
{

}

void TestChar::OnPlayerCreate()
{
	descPlayer.xPos = 300;
	descPlayer.yPos = 300;
	descPlayer.width = 100;
	descPlayer.height = 100;
}

void TestChar::OnPlayerUpdate()
{
	SetMovement();
}

void TestChar::SetMovement()
{
	if (Input::KeyPressed(Key::SPACE))
	{

		if (mapObjects[nPlayerID].canJump)
		{
			mapObjects[nPlayerID].keyPress = KeyPress::JUMP;
			speed = 0;
			mapObjects[nPlayerID].velocityY = 0;
			speed += 15;
			mapObjects[nPlayerID].velocityY -= speed;
			mapObjects[nPlayerID].canJump = false;
		}
	}
	else if (Input::KeyState(Key::S))
	{
		mapObjects[nPlayerID].yPos += 3;
	}
	else if (Input::KeyState(Key::A))
	{
		mapObjects[nPlayerID].xPos -= 3;
		mapObjects[nPlayerID].keyPress = KeyPress::LEFT;
	}
	else if (Input::KeyState(Key::D))
	{
		mapObjects[nPlayerID].xPos += 3;
		mapObjects[nPlayerID].keyPress = KeyPress::RIGHT;
	}
	else
	{
		mapObjects[nPlayerID].keyPress = KeyPress::STALL;
	}

	if (Input::KeyState(Key::L))
	{
		mapObjects[nPlayerID].keyPress = KeyPress::HITLEFT;
	}
	if (Input::KeyState(Key::J))
	{
		mapObjects[nPlayerID].keyPress = KeyPress::HITRIGHT;
	}
}

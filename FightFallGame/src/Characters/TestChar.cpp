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

	if (canJump)
	{
		mapObjects[nPlayerID].yPos -= 6;
	}
}

void TestChar::SetMovement()
{
	if (Input::KeyPressed(Key::SPACE))
	{
		if (IsOnGround())
		{
			canJump = true;
			mapObjects[nPlayerID].keyPress = KeyPress::JUMP;
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
		//mapObjects[nPlayerID].xPos += 3;
		////sprite->ChangeSprite("Assets/BoxerWalkRight.png");
		////std::cout << descPlayer.animX << "\n";
		//sprite->ChangeSprite("Assets/BoxerWalkRight.png");
		//mapObjects[nPlayerID].keyPress = KeyPress::RIGHT;
		////mapObjects[nPlayerID].animX = ((int)spriteTick % 10) * 55;
	}
	if (!AirTime())
	{
		//sprite->ChangeSprite("Assets/BoxerIdle.png");
		mapObjects[nPlayerID].keyPress = KeyPress::STALL;
		currentTime = 0;
		canJump = false;
	}

}

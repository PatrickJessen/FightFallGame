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
	if (Input::KeyPressed(Key::W))
	{
		mapObjects[nPlayerID].yPos -= 5;
	}
	if (Input::KeyPressed(Key::S))
	{
		mapObjects[nPlayerID].yPos += 5;
	}
	if (Input::KeyPressed(Key::A))
	{
		mapObjects[nPlayerID].xPos -= 5;
	}
	if (Input::KeyPressed(Key::D))
	{
		mapObjects[nPlayerID].xPos += 5;
	}
}

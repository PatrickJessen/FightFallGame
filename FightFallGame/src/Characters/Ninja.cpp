#include "Ninja.h"

Ninja::Ninja(Window* window, Sprite* sprite)
{
	this->window = window;
	this->sprite = sprite;
}

Ninja::~Ninja()
{
}

void Ninja::OnPlayerCreate()
{
	descPlayer.xPos = 300;
	descPlayer.yPos = 300;
	descPlayer.width = 100;
	descPlayer.height = 120;
}

void Ninja::OnPlayerUpdate()
{
	for (auto& object : mapObjects)
	{
		DrawSprite(object, (int)object.second.xPos, (int)object.second.yPos, (int)object.second.width, (int)object.second.height);

		if (object.second.keyPress == KeyPress::JUMP)
		{

		}
		if (object.second.keyPress == KeyPress::RIGHT)
		{
			mapObjects[nPlayerID].playerHitbox = { (int)mapObjects[nPlayerID].xPos, (int)mapObjects[nPlayerID].yPos, mapObjects[nPlayerID].width - 20, mapObjects[nPlayerID].height };
			HandleObjectInput(object, 70, 10, run, SDL_RendererFlip::SDL_FLIP_NONE);
			object.second.xPos += 10;
			object.second.velocityX = 0.0f;
		}
		if (object.second.keyPress == KeyPress::LEFT)
		{
			mapObjects[nPlayerID].playerHitbox = { (int)mapObjects[nPlayerID].xPos + 20, (int)mapObjects[nPlayerID].yPos, mapObjects[nPlayerID].width - 20, mapObjects[nPlayerID].height };
			HandleObjectInput(object, 70, 10, run, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
			object.second.xPos -= 10;
			object.second.velocityX = 0.0f;
		}
		if (object.second.keyPress == KeyPress::STALL)
		{
			HandleObjectInput(object, 70, 8, idle);
		}

		if (object.second.nUniqueID == nPlayerID)
		{
			CollisionAndGravity(object);
		}
		if (object.second.path != NULL)
		{
			object.second.sprite->ChangeSprite(object.second.path);
		}
	}
}

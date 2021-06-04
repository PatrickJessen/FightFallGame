#include "Boxer.h"

Boxer::Boxer(Window* window, Sprite* sprite)
{
	this->window = window;
	this->sprite = sprite;
}

Boxer::~Boxer()
{
}

void Boxer::OnPlayerCreate()
{
	descPlayer.xPos = 300;
	descPlayer.yPos = 300;
	descPlayer.width = 100;
	descPlayer.height = 120;
}

void Boxer::OnPlayerUpdate()
{
	for (auto& object : mapObjects)
	{
		if (object.second.path != NULL)
		{
			object.second.sprite->ChangeSprite(object.second.path);
		}

		DrawSprite(object, (int)object.second.xPos, (int)object.second.yPos, (int)object.second.width, (int)object.second.height);

		if (object.second.nUniqueID == nPlayerID)
		{
			CollisionAndGravity(object);
			Movement(object);
		}
	}
}

void Boxer::Movement(std::pair<const uint32_t, sPlayerDescription>& object)
{
	if (Input::KeyPressed(Key::SPACE) && mapObjects[nPlayerID].canJump)
	{
		speed = 0;
		mapObjects[nPlayerID].velocityY = 0;
		speed += 15;
		mapObjects[nPlayerID].velocityY -= speed;
		mapObjects[nPlayerID].canJump = false;
	}
	else if (Input::KeyState(Key::A))
	{
		mapObjects[nPlayerID].playerHitbox = { (int)mapObjects[nPlayerID].xPos + 20, (int)mapObjects[nPlayerID].yPos, mapObjects[nPlayerID].width - 20, mapObjects[nPlayerID].height };
		HandleObjectInput(object, 70, 10, run, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
		object.second.xPos -= 10;
		object.second.velocityX = 0.0f;
	}
	else if (Input::KeyState(Key::D))
	{
		mapObjects[nPlayerID].playerHitbox = { (int)mapObjects[nPlayerID].xPos, (int)mapObjects[nPlayerID].yPos, mapObjects[nPlayerID].width - 20, mapObjects[nPlayerID].height };
		HandleObjectInput(object, 70, 10, run, SDL_RendererFlip::SDL_FLIP_NONE);
		object.second.xPos += 10;
		object.second.velocityX = 0.0f;
	}
	else if (Input::KeyState(Key::L))
	{

	}
	else if (Input::KeyState(Key::K))
	{

	}
	else if (Input::KeyState(Key::J))
	{

	}
	else if (Input::KeyState(Key::N))
	{

	}
	else
	{
		HandleObjectInput(object, 70, 8, idle);
	}
}
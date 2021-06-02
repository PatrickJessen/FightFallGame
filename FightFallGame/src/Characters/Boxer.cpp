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
		DrawSprite(object, (int)object.second.xPos, (int)object.second.yPos, (int)object.second.width, (int)object.second.height, 200, 128, 300, 290);

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
			isBlocking = false;
			HandleObjectInput(object, 70, 10, idle);
		}

		if (object.second.keyPress == KeyPress::HITLEFT)
		{
			if (object.second.flip == SDL_RendererFlip::SDL_FLIP_HORIZONTAL)
			{
				object.second.punchHitbox = { (int)object.second.xPos, (int)object.second.yPos + 55, 40, 20 };
			}
			else if (object.second.flip == SDL_RendererFlip::SDL_FLIP_NONE)
			{
				object.second.punchHitbox = { (int)object.second.xPos + 60, (int)object.second.yPos + 55, 40, 20 };
			}
			HandleObjectInput(object, 50, 6, punchLeftPath);
		}
		if (object.second.keyPress == KeyPress::HITRIGHT)
		{
			if (object.second.flip == SDL_RendererFlip::SDL_FLIP_NONE)
			{
				object.second.punchHitbox = { (int)object.second.xPos + 60, (int)object.second.yPos + 55, 40, 20 };
			}
			else if (object.second.flip == SDL_RendererFlip::SDL_FLIP_HORIZONTAL)
			{
				object.second.punchHitbox = { (int)object.second.xPos, (int)object.second.yPos + 55, 40, 20 };
			}
			HandleObjectInput(object, 50, 6, punchRightPath);
		}
		if (object.second.keyPress == KeyPress::HITUP)
		{
			if (object.second.flip == SDL_RendererFlip::SDL_FLIP_NONE)
			{
				object.second.punchHitbox = { (int)object.second.xPos + 70, (int)object.second.yPos + 35, 20, 40 };
			}
			else if (object.second.flip == SDL_RendererFlip::SDL_FLIP_HORIZONTAL)
			{
				object.second.punchHitbox = { (int)object.second.xPos + 10, (int)object.second.yPos + 35, 20, 40 };
			}
			HandleObjectInput(object, 60, 7, punchUp);
		}
		if (object.second.keyPress == KeyPress::BLOCK)
		{
			isBlocking = true;
			HandleObjectInput(object, 80, 10, block, SDL_RendererFlip::SDL_FLIP_NONE);
		}

		//SDL_Rect punchHitbox;
		if (object.second.nUniqueID == nPlayerID)
		{
			CollisionAndGravity(object);
		}
		else
		{
			if (Collider::AABB(object.second.punchHitbox, mapObjects[nPlayerID].playerHitbox))
			{
				if (!isBlocking)
				{
					if (object.second.flip == SDL_RendererFlip::SDL_FLIP_NONE && object.second.keyPress == KeyPress::HITLEFT || object.second.flip == SDL_RendererFlip::SDL_FLIP_NONE && object.second.keyPress == KeyPress::HITRIGHT)
					{
						VelBounceXPositive();
					}
					if (object.second.flip == SDL_RendererFlip::SDL_FLIP_HORIZONTAL && object.second.keyPress == KeyPress::HITLEFT || object.second.flip == SDL_RendererFlip::SDL_FLIP_HORIZONTAL && object.second.keyPress == KeyPress::HITRIGHT)
					{
						VelBounceXNegative();
					}
				}
				if (object.second.flip == SDL_RendererFlip::SDL_FLIP_HORIZONTAL && object.second.keyPress == KeyPress::HITUP || object.second.flip == SDL_RendererFlip::SDL_FLIP_NONE && object.second.keyPress == KeyPress::HITUP)
				{
					VelBounceY();
				}
			}
			mapObjects[nPlayerID].playerHitbox = { (int)mapObjects[nPlayerID].xPos, (int)mapObjects[nPlayerID].yPos, mapObjects[nPlayerID].width - 20, mapObjects[nPlayerID].height };

			if (object.second.path != NULL)
			{
				object.second.sprite->ChangeSprite(object.second.path);
			}
		}
		object.second.punchHitbox = { -345345,-345345,0,0 };
	}
}
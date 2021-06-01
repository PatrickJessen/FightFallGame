#include "Robot.h"

Robot::Robot(Window* window, Sprite* sprite)
{
	this->window = window;
	this->sprite = sprite;
}

Robot::~Robot()
{
}

void Robot::OnPlayerCreate()
{
	descPlayer.xPos = 300;
	descPlayer.yPos = 300;
	descPlayer.width = 100;
	descPlayer.height = 130;
}

void Robot::OnPlayerUpdate()
{
	for (auto& object : mapObjects)
	{
		srcRect = { 200, 128, 300, 290 };
		rect = { (int)object.second.xPos, (int)object.second.yPos, descPlayer.width, descPlayer.height };
		SDL_RenderCopyEx(window->GetRender(), object.second.sprite->tex, NULL, &rect, NULL, NULL, object.second.flip);

		Uint32 ticks = SDL_GetTicks();
		Uint32 seconds = ticks / 1000;
		if (object.second.keyPress == KeyPress::JUMP)
		{

		}
		if (object.second.keyPress == KeyPress::RIGHT)
		{
			mapObjects[nPlayerID].playerHitbox = { (int)mapObjects[nPlayerID].xPos, (int)mapObjects[nPlayerID].yPos, mapObjects[nPlayerID].width - 20, mapObjects[nPlayerID].height };
			Uint32 spriteTick = (ticks / 70) % 6;
			//mapObjects[nPlayerID].run[spriteTick] = run[spriteTick];
			object.second.run[spriteTick] = run[spriteTick];
			mapObjects[nPlayerID].sprite->ChangeSprite(object.second.run[spriteTick]);
			object.second.sprite->ChangeSprite(mapObjects[nPlayerID].run[spriteTick]);
			object.second.flip = SDL_RendererFlip::SDL_FLIP_NONE;
		}
		if (object.second.keyPress == KeyPress::LEFT)
		{
			mapObjects[nPlayerID].playerHitbox = { (int)mapObjects[nPlayerID].xPos + 20, (int)mapObjects[nPlayerID].yPos, mapObjects[nPlayerID].width - 20, mapObjects[nPlayerID].height };
			Uint32 spriteTick = (ticks / 70) % 6;
			//mapObjects[nPlayerID].run[spriteTick] = run[spriteTick];
			object.second.run[spriteTick] = run[spriteTick];
			mapObjects[nPlayerID].sprite->ChangeSprite(object.second.run[spriteTick]);
			object.second.sprite->ChangeSprite(mapObjects[nPlayerID].run[spriteTick]);
			object.second.flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		}
		if (object.second.keyPress == KeyPress::STALL)
		{
			Uint32 spriteTick = (ticks / 70) % 6;
			//mapObjects[nPlayerID].idle[spriteTick] = idle[spriteTick];
			object.second.idle[spriteTick] = idle[spriteTick];
			mapObjects[nPlayerID].sprite->ChangeSprite(object.second.idle[spriteTick]);
			object.second.sprite->ChangeSprite(mapObjects[nPlayerID].idle[spriteTick]);
		}

		if (object.second.nUniqueID == nPlayerID)
		{
			// Platform Collision //	
			if (Collider::AABB(platform, rect))
			{
				mapObjects[nPlayerID].yPos = platform.y - rect.h;
				object.second.yPos = platform.y - rect.h;
				object.second.velocityY = 0.0f;
				object.second.velocityX = 0.0f;
				mapObjects[nPlayerID].canJump = true;
			}
			else
			{
				// Gravity //
				object.second.velocityY += 0.5f;
			}
		}
	}
}

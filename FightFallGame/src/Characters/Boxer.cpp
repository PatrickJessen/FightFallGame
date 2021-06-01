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
	descPlayer.height = 100;
}

void Boxer::OnPlayerUpdate()
{
	for (auto& object : mapObjects)
	{
		srcRect = { 200, 128, 300, 290 };
		rect = { (int)object.second.xPos, (int)object.second.yPos, descPlayer.width, descPlayer.height };
		SDL_RenderCopyEx(window->GetRender(), object.second.sprite->tex, &srcRect, &rect, NULL, NULL, object.second.flip);

		Uint32 ticks = SDL_GetTicks();
		Uint32 seconds = ticks / 1000;
		if (object.second.keyPress == KeyPress::JUMP)
		{
			
		}
		else if (object.second.keyPress == KeyPress::RIGHT)
		{

			mapObjects[nPlayerID].playerHitbox = { (int)mapObjects[nPlayerID].xPos, (int)mapObjects[nPlayerID].yPos, mapObjects[nPlayerID].width - 20, mapObjects[nPlayerID].height };
			Uint32 spriteTick = (ticks / 70) % 10;
			object.second.sprite->ChangeSprite(boxerWalk[spriteTick]);
			object.second.flip = SDL_RendererFlip::SDL_FLIP_NONE;
		}
		else if (object.second.keyPress == KeyPress::LEFT)
		{
			mapObjects[nPlayerID].playerHitbox = { (int)mapObjects[nPlayerID].xPos + 20, (int)mapObjects[nPlayerID].yPos, mapObjects[nPlayerID].width - 20, mapObjects[nPlayerID].height };
			Uint32 spriteTick = (ticks / 70) % 10;
			object.second.sprite->ChangeSprite(boxerWalk[spriteTick]);
			object.second.flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		}
		else if (object.second.keyPress == KeyPress::STALL)
		{
			Uint32 spriteTick = (ticks / 70) % 10;
			object.second.sprite->ChangeSprite(boxerIdle[spriteTick]);
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
			Uint32 spriteTick = (ticks / 50) % 6;
			object.second.sprite->ChangeSprite(punchLeftPath[spriteTick]);
		}
		else if (object.second.keyPress == KeyPress::HITRIGHT)
		{
			if (object.second.flip == SDL_RendererFlip::SDL_FLIP_NONE)
			{
				object.second.punchHitbox = { (int)object.second.xPos + 60, (int)object.second.yPos + 55, 40, 20 };
			}
			else if (object.second.flip == SDL_RendererFlip::SDL_FLIP_HORIZONTAL)
			{
				object.second.punchHitbox = { (int)object.second.xPos, (int)object.second.yPos + 55, 40, 20 };
			}
			Uint32 spriteTick = (ticks / 50) % 6;
			object.second.sprite->ChangeSprite(punchRightPath[spriteTick]);
		}
		else if (object.second.keyPress == KeyPress::HITUP)
		{
			if (object.second.flip == SDL_RendererFlip::SDL_FLIP_NONE)
			{
				object.second.punchHitbox = { (int)object.second.xPos + 70, (int)object.second.yPos + 35, 20, 40 };
			}
			else if (object.second.flip == SDL_RendererFlip::SDL_FLIP_HORIZONTAL)
			{
				object.second.punchHitbox = { (int)object.second.xPos + 10, (int)object.second.yPos + 35, 20, 40 };
			}
			Uint32 spriteTick = (ticks / 60) % 7;
			object.second.sprite->ChangeSprite(punchUp[spriteTick]);
		}

		//SDL_Rect punchHitbox;
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
		else
		{
			if (Collider::AABB(object.second.punchHitbox, mapObjects[nPlayerID].playerHitbox))
			{
				std::cout << object.second.punchHitbox.x << " , " << mapObjects[nPlayerID].playerHitbox.x << "\n";
				if (object.second.flip == SDL_RendererFlip::SDL_FLIP_NONE && object.second.keyPress == KeyPress::HITLEFT || object.second.flip == SDL_RendererFlip::SDL_FLIP_NONE && object.second.keyPress == KeyPress::HITRIGHT)
				{
					VelBounceXPositive();
				}
				else if (object.second.flip == SDL_RendererFlip::SDL_FLIP_HORIZONTAL && object.second.keyPress == KeyPress::HITLEFT || object.second.flip == SDL_RendererFlip::SDL_FLIP_HORIZONTAL && object.second.keyPress == KeyPress::HITRIGHT)
				{
					VelBounceXNegative();
				}
				else if (object.second.flip == SDL_RendererFlip::SDL_FLIP_HORIZONTAL && object.second.keyPress == KeyPress::HITUP || object.second.flip == SDL_RendererFlip::SDL_FLIP_NONE && object.second.keyPress == KeyPress::HITUP)
				{
					VelBounceY();
				}
			}
			mapObjects[nPlayerID].playerHitbox = { (int)mapObjects[nPlayerID].xPos, (int)mapObjects[nPlayerID].yPos, mapObjects[nPlayerID].width - 20, mapObjects[nPlayerID].height };
		}

		object.second.punchHitbox = { -345345,-345345,0,0 };
	}
}
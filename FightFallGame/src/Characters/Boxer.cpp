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
		SDL_Rect punchHitbox;
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

			playerHitbox = { rect.x, rect.y, rect.w - 20, rect.h };
			Uint32 spriteTick = (ticks / 70) % 10;
			object.second.sprite->ChangeSprite(boxerWalk[spriteTick]);
			object.second.flip = SDL_RendererFlip::SDL_FLIP_NONE;
		}
		else if (object.second.keyPress == KeyPress::LEFT)
		{
			playerHitbox = { rect.x + 20, rect.y, rect.w - 20, rect.h };
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
				punchHitbox = { rect.x, rect.y + 55, 40, 20 };
			}
			else if (object.second.flip == SDL_RendererFlip::SDL_FLIP_NONE)
			{
				punchHitbox = { rect.x + 60, rect.y + 55, 40, 20 };
			}
			SDL_SetRenderDrawColor(window->GetRender(), 0, 255, 255, 255);
			SDL_RenderDrawRect(window->GetRender(), &punchHitbox);
			Uint32 spriteTick = (ticks / 50) % 6;
			object.second.sprite->ChangeSprite(punchLeftPath[spriteTick]);
		}
		else if (object.second.keyPress == KeyPress::HITRIGHT)
		{
			if (object.second.flip == SDL_RendererFlip::SDL_FLIP_NONE)
			{
				punchHitbox = { rect.x + 60, rect.y + 55, 40, 20 };
			}
			else if (object.second.flip == SDL_RendererFlip::SDL_FLIP_HORIZONTAL)
			{
				punchHitbox = { rect.x, rect.y + 55, 40, 20 };
			}
			SDL_SetRenderDrawColor(window->GetRender(), 0, 255, 255, 255);
			SDL_RenderDrawRect(window->GetRender(), &punchHitbox);
			Uint32 spriteTick = (ticks / 50) % 6;
			object.second.sprite->ChangeSprite(punchRightPath[spriteTick]);
		}

		if (object.second.nUniqueID == nPlayerID)
		{
			if (Collider::AABB(punchHitbox, playerHitbox))
			{
				std::cout << "collision!\n";
				if (object.second.flip == SDL_RendererFlip::SDL_FLIP_NONE)
				{
					mapObjects[nPlayerID].velocityX = 2.5f;
				}
				else if (object.second.flip == SDL_RendererFlip::SDL_FLIP_HORIZONTAL)
				{
					mapObjects[nPlayerID].velocityX = -2.5f;
				}
			}
		}
	}
}
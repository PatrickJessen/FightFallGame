#include "Character.h"
#include "../Input.h"

bool Character::Update()
{
	if (IsConnected())
	{
		SDL_Delay(5);
		while (!Incoming().empty())
		{
			auto msg = Incoming().pop_front().msg;

			switch (msg.header.id)
			{
				case(GameMsg::Client_Accepted):
				{
					std::cout << "Server accepted client - you're in!\n";
					message<GameMsg> msg;
					msg.header.id = GameMsg::Client_RegisterWithServer;
					msg << descPlayer;
					Send(msg);
					break;
				}

				case(GameMsg::Client_AssignID):
				{
					// Server is assigning us OUR id
					msg >> nPlayerID;
					std::cout << "Assigned Client ID = " << nPlayerID << "\n";
					break;
				}

				case(GameMsg::Game_AddPlayer):
				{
					sPlayerDescription desc;
					msg >> desc;
					desc.sprite = new Sprite("Assets/BoxerIdle.png", window);
					mapObjects.insert_or_assign(desc.nUniqueID, desc);
					if (desc.nUniqueID == nPlayerID)
					{
						// Now we exist in game world
						waitingForConnection = false;
					}
					break;
				}

				case(GameMsg::Game_RemovePlayer):
				{
					uint32_t nRemovalID = 0;
					msg >> nRemovalID;
					mapObjects.erase(nRemovalID);
					break;
				}

				case(GameMsg::Game_UpdatePlayer):
				{
					sPlayerDescription desc;
					msg >> desc;
					desc.sprite = mapObjects[desc.nUniqueID].sprite;
					mapObjects.insert_or_assign(desc.nUniqueID, desc);
					break;
				}
			}

		}
		if (waitingForConnection)
		{
			std::cout << "Waiting for Connection....\n";
			return true;
		}


		OnPlayerUpdate();
		UpdateVelocity();
		//Uint32 ticks = SDL_GetTicks();
		//Uint32 seconds = ticks / 1000;
		//Uint32 spriteTick = (ticks / 150) % 10;
		//mapObjects[nPlayerID].animX = ((int)spriteTick % 10) * 55;


		SDL_SetRenderDrawColor(window->GetRender(), 200, 150, 100, 200);
		platform = { 150, 600, 900, 50 };
		SDL_RenderFillRect(window->GetRender(), &platform);
		for (auto& object : mapObjects)
		{
			Uint32 ticks = SDL_GetTicks();
			Uint32 seconds = ticks / 1000;
			srcRect = { 200, 128, 300, 290 };
			rect = { (int)object.second.xPos, (int)object.second.yPos, descPlayer.width, descPlayer.height };
			SDL_RenderCopyEx(window->GetRender(), object.second.sprite->tex, &srcRect, &rect, NULL, NULL, object.second.flip);

			SDL_Rect testing = { rect.x, rect.y, srcRect.w - 50, srcRect.h };

			SDL_RenderDrawRect(window->GetRender(), &testing);

			SDL_Rect currentPos = rect;

			if (object.second.keyPress == KeyPress::RIGHT)
			{
				object.second.sprite->ChangeSprite("Assets/BoxerWalkRight.png");
				object.second.flip = SDL_RendererFlip::SDL_FLIP_NONE;
			}
			else if (object.second.keyPress == KeyPress::STALL)
			{
				Uint32 spriteTick = (ticks / 70) % 9;
				object.second.sprite->ChangeSprite(boxerIdle[spriteTick]);
			}
			else if (object.second.keyPress == KeyPress::LEFT)
			{
				object.second.sprite->ChangeSprite("Assets/BoxerWalkRight.png");
				object.second.flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
			}


			if (object.second.keyPress == KeyPress::HITLEFT)
			{
				Uint32 spriteTick = (ticks / 50) % 6;
				object.second.sprite->ChangeSprite(punchLeftPath[spriteTick]);
			}
			if (object.second.keyPress == KeyPress::HITRIGHT)
			{
				Uint32 spriteTick = (ticks / 50) % 6;
				object.second.sprite->ChangeSprite(punchRightPath[spriteTick]);
			}

			// Collision //
			if (object.second.nUniqueID == nPlayerID)
			{

				if (Collider::AABB(platform, rect))
				{
					mapObjects[nPlayerID].yPos = platform.y - rect.h;
					object.second.yPos = platform.y - rect.h;
					object.second.velocityY = 0.0f;
					mapObjects[nPlayerID].canJump = true;
				}
				else
				{
					// Gravity //
					object.second.velocityY += 0.5f;

				}
			}

		}

		message<GameMsg> msg;
		msg.header.id = GameMsg::Game_UpdatePlayer;
		msg << mapObjects[nPlayerID];
		Send(msg);
		return true;
	}
}

void Character::ConnectToServer()
{
	Connect("127.0.0.1", 60000);
}

void Character::UpdateVelocity()
{
	mapObjects[nPlayerID].xPos += mapObjects[nPlayerID].velocityX;
	mapObjects[nPlayerID].yPos += mapObjects[nPlayerID].velocityY;
}

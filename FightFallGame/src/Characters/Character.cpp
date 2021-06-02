#include "Character.h"
#include "../Input.h"

bool Character::Update()
{
	if (IsConnected())
	{
		SDL_Delay(1);
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
					desc.sprite = new Sprite("", window);
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

		UpdateMovement();
		UpdateVelocity();
		OnPlayerUpdate();

		SDL_SetRenderDrawColor(window->GetRender(), 200, 150, 100, 200);
		platform = { 150, 600, 900, 50 };
		SDL_RenderFillRect(window->GetRender(), &platform);


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

void Character::HandleObjectInput(std::pair<const uint32_t, sPlayerDescription> &object, int tickSpeed, int tickTimes, const char* path[], SDL_RendererFlip flip)
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 seconds = ticks / 1000;
	Uint32 spriteTick = (ticks / tickSpeed) % tickTimes;

	object.second.path = path[spriteTick];
	//mapObjects[object.second.nUniqueID].sprite->ChangeSprite(mapObjects[object.second.nUniqueID].path);
	object.second.flip = flip;
}

void Character::HandleObjectInput(std::pair<const uint32_t, sPlayerDescription>& object, int tickSpeed, int tickTimes, const char* path[])
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 seconds = ticks / 1000;
	Uint32 spriteTick = (ticks / tickSpeed) % tickTimes;
	object.second.path = path[spriteTick];
	//mapObjects[object.second.nUniqueID].sprite->ChangeSprite(mapObjects[object.second.nUniqueID].path);
}

void Character::DrawSprite(std::pair<const uint32_t, sPlayerDescription>& object, int x, int y, int w, int h)
{
	rect = { x, y, w, h };
	SDL_RenderCopyEx(window->GetRender(), object.second.sprite->tex, NULL, &rect, NULL, NULL, object.second.flip);
}

void Character::DrawSprite(std::pair<const uint32_t, sPlayerDescription>& object, int x, int y, int h, int w, int srcX, int srcY, int srcW, int srcH)
{
	rect = { x, y, w, h };
	srcRect = { srcX, srcY, srcW, srcH };
	SDL_RenderCopyEx(window->GetRender(), object.second.sprite->tex, &srcRect, &rect, NULL, NULL, object.second.flip);
}

void Character::CollisionAndGravity(std::pair<const uint32_t, sPlayerDescription>& object)
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

void Character::UpdateMovement()
{
	if (Input::KeyPressed(Key::SPACE) && mapObjects[nPlayerID].canJump)
	{
		speed = 0;
		mapObjects[nPlayerID].velocityY = 0;
		speed += 15;
		mapObjects[nPlayerID].velocityY -= speed;
		mapObjects[nPlayerID].canJump = false;
		mapObjects[nPlayerID].keyPress = KeyPress::JUMP;
	}
	else if (Input::KeyState(Key::A))
	{
		/*mapObjects[nPlayerID].xPos -= 10;
		mapObjects[nPlayerID].velocityX = 0.0f;*/
		mapObjects[nPlayerID].keyPress = KeyPress::LEFT;
	}
	else if (Input::KeyState(Key::D))
	{
		/*mapObjects[nPlayerID].xPos += 10;
		mapObjects[nPlayerID].velocityX = 0.0f;*/
		mapObjects[nPlayerID].keyPress = KeyPress::RIGHT;
	}
	else if (Input::KeyState(Key::L))
	{
		mapObjects[nPlayerID].keyPress = KeyPress::HITLEFT;
	}
	else if (Input::KeyState(Key::K))
	{
		mapObjects[nPlayerID].keyPress = KeyPress::HITRIGHT;
	}
	else if (Input::KeyState(Key::J))
	{
		mapObjects[nPlayerID].keyPress = KeyPress::HITUP;
	}
	else if (Input::KeyState(Key::N))
	{
		mapObjects[nPlayerID].keyPress = KeyPress::BLOCK;
	}
	else
	{
		mapObjects[nPlayerID].keyPress = KeyPress::STALL;
	}
}

void Character::VelBounceXPositive()
{
	while (mapObjects[nPlayerID].velocityX <= 7.0f)
	{
		mapObjects[nPlayerID].velocityX += 1.5f;
	}

}

void Character::VelBounceXNegative()
{
	while (mapObjects[nPlayerID].velocityX >= -7.0f)
	{
		mapObjects[nPlayerID].velocityX -= 1.5f;
	}
}

void Character::VelBounceY()
{
	mapObjects[nPlayerID].velocityY = -10.5f;
	mapObjects[nPlayerID].playerHitbox = { (int)mapObjects[nPlayerID].xPos, (int)mapObjects[nPlayerID].yPos - (int)mapObjects[nPlayerID].velocityY, mapObjects[nPlayerID].width - 20, mapObjects[nPlayerID].height };
}

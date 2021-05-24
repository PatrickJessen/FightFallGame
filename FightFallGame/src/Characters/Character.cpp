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
					descPlayer.xPos = 200;
					descPlayer.yPos = 200;
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

		if (mapObjects[nPlayerID].nUniqueID == nPlayerID)
		{
			OnPlayerUpdate();
			Uint32 ticks = SDL_GetTicks();
			Uint32 seconds = ticks / 1000;
			Uint32 spriteTick = (ticks / 150) % 10;
			mapObjects[nPlayerID].animX = ((int)spriteTick % 10) * 55;
			srcRect = { mapObjects[nPlayerID].animX, mapObjects[nPlayerID].animY, 50, 60 };
		}



		SDL_SetRenderDrawColor(window->GetRender(), 200, 150, 100, 200);
		platform = { 150, 600, 900, 50 };
		SDL_RenderFillRect(window->GetRender(), &platform);
		for (auto& object : mapObjects)
		{
			if (object.second.nUniqueID != 0)
			{
				rect = { (int)object.second.xPos, (int)object.second.yPos, descPlayer.width, descPlayer.height };
				SDL_RenderCopy(window->GetRender(), sprite->tex, &srcRect, &rect);

				// Gravity //
				object.second.yPos += 2.0f;

				// Collision //
				if (IsOnGround())
				{
					object.second.yPos = platform.y - rect.h;
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

bool Character::IsOnGround()
{
	if (platform.y - rect.h <= rect.y && rect.x + rect.w > platform.x && rect.x < platform.x + platform.w && rect.y < platform.y)
	{
		return true;
	}
	return false;
}

bool Character::AirTime()
{
	currentTime += 1.0f;
	if (currentTime < airTime)
	{
		return true;
	}
	return false;
}
#include "Character.h"

void Character::Update()
{
	if (IsConnected())
	{
		SDL_Delay(10);
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
		}

		OnPlayerUpdate();

		for (auto& object : mapObjects)
		{
			if (object.second.nUniqueID != 0)
			{
				rect = { (int)object.second.xPos, (int)object.second.yPos, descPlayer.width, descPlayer.height };
				SDL_RenderCopy(window->GetRender(), sprite->tex, NULL, &rect);
			}
		}

		message<GameMsg> msg;
		msg.header.id = GameMsg::Game_UpdatePlayer;
		msg << mapObjects[nPlayerID];
		Send(msg);
	}
}

void Character::ConnectToServer()
{
	Connect("10.109.162.46", 60000);
}

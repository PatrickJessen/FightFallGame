#include "TestChar.h"
#include "../Input.h"

TestChar::TestChar(Sprite* sprite, Window* window, int posX, int posY, int width, int height)
{
	this->sprite = sprite;
	this->window = window;

	playerDesc.vPos = { posX, posY, width, height };
}

TestChar::~TestChar()
{
}

void TestChar::OnPlayerCreate()
{
	Connect("127.0.0.1", 60000);
}

void TestChar::OnPlayerUpdate()
{
	SDL_RenderCopy(window->GetRender(), sprite->tex, NULL, &playerDesc.vPos);

	auto msg = Incoming().pop_front().msg;

	switch (msg.header.id)
	{
		case(GameMsg::Client_Accepted):
		{
			std::cout << "Server accepted client - you're in!\n";
			message<GameMsg> msg;
			msg.header.id = GameMsg::Client_RegisterWithServer;
			playerDesc.vPos.x = 100;
			playerDesc.vPos.y = 100;
			msg << playerDesc;
			Send(msg);
			break;
		}

		case(GameMsg::Client_AssignID):
		{
			// Server is assigning us OUR id
			msg >> playerID;
			std::cout << "Assigned Client ID = " << playerID << "\n";
			break;
		}

		case(GameMsg::Game_AddPlayer):
		{
			sPlayerDescription desc;
			msg >> desc;
			object.insert_or_assign(desc.nUniqueID, desc);

			if (desc.nUniqueID == playerID)
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
			object.erase(nRemovalID);
			break;
		}

		case(GameMsg::Game_UpdatePlayer):
		{
			sPlayerDescription desc;
			msg >> desc;
			object.insert_or_assign(desc.nUniqueID, desc);
			break;
		}

	}

	if (waitingForConnection)
	{
		std::cout << "waiting to connect...\n";
	}

	if (Input::KeyPressed(Key::W))
	{
		playerDesc.vPos.y--;
	}
	if (Input::KeyPressed(Key::S))
	{
		playerDesc.vPos.y++;
	}
	if (Input::KeyPressed(Key::A))
	{
		playerDesc.vPos.x--;
	}
	if (Input::KeyPressed(Key::D))
	{
		playerDesc.vPos.x++;
	}

	message<GameMsg> msg1;
	msg1.header.id = GameMsg::Game_UpdatePlayer;
	msg1 << object[playerID];
	Send(msg1);
}

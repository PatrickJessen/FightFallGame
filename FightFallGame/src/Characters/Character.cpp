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

		for (auto& object : mapObjects)
		{
			if (object.second.nUniqueID == nPlayerID)
			{
				// Platform Collision //	
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
			else
			{
				if (Collider::AABB(punchHitbox, rect))
				{
					if (mapObjects[nPlayerID].velocityX > 0)
					{
						std::cout << "test1\n";
						mapObjects[nPlayerID].velocityX -= 2.0f;
					}
					else
					{
						std::cout << "test2\n";
						mapObjects[nPlayerID].velocityX += 2.0f;
					}
				}
			}
		}
		OnPlayerUpdate();
		UpdateMovement();
		UpdateVelocity();

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

void Character::UpdateMovement()
{
	if (Input::KeyPressed(Key::SPACE))
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
		mapObjects[nPlayerID].xPos -= 3;
		mapObjects[nPlayerID].keyPress = KeyPress::LEFT;
	}
	else if (Input::KeyState(Key::D))
	{
		mapObjects[nPlayerID].xPos += 3;
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
	else
	{
		mapObjects[nPlayerID].keyPress = KeyPress::STALL;
	}
}

#include "Robot.h"

Robot::Robot(Window* window, Sprite* sprite)
{
	this->window = window;
	this->sprite = sprite;
	//sprBullet = new Sprite(bullet[0], window);
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
		if (object.second.path != NULL)
		{
			object.second.sprite->ChangeSprite(object.second.path);
		}
		if (object.second.bulletPath != NULL)
		{
			object.second.sprBullet->ChangeSprite(object.second.bulletPath);
		}

		DrawSprite(object, (int)object.second.xPos, (int)object.second.yPos, (int)object.second.width, (int)object.second.height);

		for (int i = 0; i < object.second.projectileSize; i++)
		{
			if (object.second.nUniqueID != nPlayerID)
			{
				if (projectiles.size() <= 3)
				{
					projectiles.push_back(Projectile(object.second.sprBullet, object.second.hsp, object.second.vsp, object.second.xPos + object.second.width / 2, object.second.yPos + object.second.height / 2, 1.5f));
					object.second.projectileSize = projectiles.size();
				}
			}
			if (projectiles[i].CheckTimeToDestroy())
			{
				projectiles.erase(projectiles.begin() + i);
				object.second.projectileSize = projectiles.size();
			}
			else
			{
				//test = { (int)object.second.bulletPosX, (int)object.second.bulletPosY, object.second.bulletWidth, object.second.bulletHeight };
				//hitRect = { (int)projectiles[i].x, (int)projectiles[i].y, 120, 120 };		
				projectiles[i].x += projectiles[i].hsp * 2.0f;
				object.second.bulletPosX = projectiles[i].x;
				object.second.bulletPosY = projectiles[i].y;
				test = { (int)object.second.bulletPosX, (int)object.second.bulletPosY, object.second.bulletWidth, object.second.bulletHeight };
				SDL_SetRenderDrawColor(window->GetRender(), 0, 255, 255, 255);
				SDL_RenderDrawRect(window->GetRender(), &test);
				SDL_RenderCopyEx(window->GetRender(), object.second.sprBullet->tex, NULL, &test, 0, 0, object.second.flip);
			}
		}


		if (object.second.nUniqueID == nPlayerID)
		{
			CollisionAndGravity(object);
			Movement(object);
			HandleBulletInput(object, 70, 5, bullet);		
		}
	}
}

void Robot::Movement(std::pair<const uint32_t, sPlayerDescription>& object)
{
	if (Input::KeyPressed(Key::SPACE) && mapObjects[nPlayerID].canJump)
	{
		speed = 0;
		mapObjects[nPlayerID].velocityY = 0;
		speed += 15;
		mapObjects[nPlayerID].velocityY -= speed;
		mapObjects[nPlayerID].canJump = false;
	}
	else if (Input::KeyState(Key::A))
	{
		mapObjects[nPlayerID].playerHitbox = { (int)mapObjects[nPlayerID].xPos + 20, (int)mapObjects[nPlayerID].yPos, mapObjects[nPlayerID].width - 20, mapObjects[nPlayerID].height };
		HandleObjectInput(object, 70, 8, run, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
		object.second.xPos -= 10;
		object.second.velocityX = 0.0f;
	}
	else if (Input::KeyState(Key::D))
	{
		mapObjects[nPlayerID].playerHitbox = { (int)mapObjects[nPlayerID].xPos, (int)mapObjects[nPlayerID].yPos, mapObjects[nPlayerID].width - 20, mapObjects[nPlayerID].height };
		HandleObjectInput(object, 70, 8, run, SDL_RendererFlip::SDL_FLIP_NONE);
		object.second.xPos += 10;
		object.second.velocityX = 0.0f;
	}
	else if (Input::KeyPressed(Key::L))
	{
		if (projectiles.size() <= 3)
		{
			HandleObjectInput(object, 70, 4, shoot);
			projectiles.push_back(Projectile(object.second.sprBullet, object.second.hsp, object.second.vsp, object.second.xPos + object.second.width / 2, object.second.yPos + object.second.height / 2, 1.5f));
			object.second.projectileSize = projectiles.size();
			/*projectiles.push_back(Projectile(object.second.sprBullet, object.second.hsp, object.second.vsp, object.second.xPos + object.second.width / 2, object.second.yPos + object.second.height / 2, 1.5f));*/

		}
	}
	else if (Input::KeyState(Key::K))
	{

	}
	else if (Input::KeyState(Key::J))
	{

	}
	else if (Input::KeyState(Key::N))
	{

	}
	else
	{
		HandleObjectInput(object, 70, 10, idle);
	}
}

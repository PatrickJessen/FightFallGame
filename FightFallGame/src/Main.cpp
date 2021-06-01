#include "Window/Window.h"
#include "Sprite.h"
#include <asio.hpp>
#include <string>
#include "Characters/Boxer.h"
#include "Characters/Robot.h"
#include "Characters/Ninja.h"
#include "CharacterSelection.h"

int main()
{
	Window* window = new Window("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 750, false);
	Sprite* sprite = new Sprite("", window);
	CharacterSelection* selection = new CharacterSelection(window);

	Character* character;

	const int FPS = 60;
	const int frameDelay = 500 / FPS;

	Uint32 frameStart;
	int frameTime;

	selection->SelectCharacter();

	if (selection->boxerSelected)
	{
		character = new Boxer(window, sprite);
	}
	else if (selection->robotSelected)
	{
		character = new Robot(window, sprite);
	}
	else
	{
		character = new Ninja(window, sprite);
	}

	character->OnPlayerCreate();
	character->ConnectToServer();
	while (true)
	{
		frameStart = SDL_GetTicks();
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
		character->Update();
		window->Update();
		window->Clear();
	}

	window->Clean();
}
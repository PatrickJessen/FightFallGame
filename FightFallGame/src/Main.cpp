#include "Window/Window.h"
#include "Sprite.h"
#include <asio.hpp>
#include <string>
#include "Characters/Boxer.h"

int main()
{
	Window* window = new Window("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 750, false);
	Sprite* sprite = new Sprite("Assets/BoxerIdle.png", window);
	Character* tester = new Boxer(window, sprite);

	const int FPS = 60;
	const int frameDelay = 500 / FPS;

	Uint32 frameStart;
	int frameTime;

	tester->OnPlayerCreate();
	tester->ConnectToServer();
	while (true)
	{
		frameStart = SDL_GetTicks();
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
		tester->Update();
		window->Update();
		window->Clear();
	}

	window->Clean();
}
#include "Window/Window.h"
#include "Sprite.h"
#include <asio.hpp>
#include <string>
#include "Characters/TestChar.h"

int main()
{
	Window* window = new Window("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 750, false);
	Sprite* sprite = new Sprite("test.png", window);
	TestChar* testchar = new TestChar(sprite, window, 100, 100, 100, 100);

	testchar->OnPlayerCreate();
	while (true)
	{
		while (!testchar->Incoming().empty())
		{
			testchar->OnPlayerUpdate();
			window->Update();
			window->Clear();

			SDL_Delay(1);
		}
	}

	window->Clean();
}
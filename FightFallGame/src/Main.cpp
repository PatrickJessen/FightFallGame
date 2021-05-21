#include "Window/Window.h"
#include "Sprite.h"
#include <asio.hpp>
#include <string>
#include "Characters/TestChar.h"

int main()
{
	Window* window = new Window("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 750, false);
	Sprite* sprite = new Sprite("Assets/stall.png", window);
	Character* tester = new TestChar(window, sprite);

	tester->OnPlayerCreate();
	tester->ConnectToServer();
	while (true)
	{
		tester->Update();
		window->Update();
		window->Clear();
	}

	window->Clean();
}
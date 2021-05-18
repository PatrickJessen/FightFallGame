#include "Window/Window.h"

int main()
{
	Window* window = new Window("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 750, false);

	while (window->Running())
	{
		window->Update();
		window->Clear();

		SDL_Delay(1);
	}

	window->Clean();
}
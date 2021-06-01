#include "CharacterSelection.h"
#include "Input.h"

CharacterSelection::CharacterSelection(Window* window)
{
	this->window = window;
	boxer = new Sprite("Assets/boxer/Idle1.png", window);
	robot = new Sprite("Assets/robot/Idle (1).png", window);
	ninja = new Sprite("Assets/ninja/Idle (1).png", window);
}

CharacterSelection::~CharacterSelection()
{
}

void CharacterSelection::SelectCharacter()
{
	while (!IsSelected())
	{
		SDL_Rect boxerPos = { 200, 300, 100, 100 };
		SDL_Rect robotPos = { 500, 300, 100, 100 };
		SDL_Rect ninjaPos = { 700, 300, 100, 100 };
		DrawSprite(boxerPos.x, boxerPos.y, boxerPos.w, boxerPos.h, boxer);
		DrawSprite(robotPos.x, robotPos.y, robotPos.w, robotPos.h, robot);
		DrawSprite(ninjaPos.x, ninjaPos.y, ninjaPos.w, ninjaPos.h, ninja);

		if (XYInRect(boxerPos, Input::MouseX(), Input::MouseY()))
		{
			if (Input::MousePressed(MouseButton::LEFT))
			{
				boxerSelected = true;
				isSelected = true;
			}
		}

		if (XYInRect(robotPos, Input::MouseX(), Input::MouseY()))
		{
			if (Input::MousePressed(MouseButton::LEFT))
			{
				robotSelected = true;
				isSelected = true;
			}
		}

		if (XYInRect(ninjaPos, Input::MouseX(), Input::MouseY()))
		{
			if (Input::MousePressed(MouseButton::LEFT))
			{
				ninjaSelected = true;
				isSelected = true;
			}
		}
		window->Update();
		window->Clear();
	}
}

void CharacterSelection::DrawSprite(int x, int y, int w, int h, Sprite* sprite)
{
	SDL_Rect spritePos = { x, y, w, h };
	SDL_RenderCopyEx(window->GetRender(), sprite->tex, NULL, &spritePos, NULL, NULL, SDL_FLIP_NONE);
}

bool CharacterSelection::IsSelected()
{
	return isSelected;
}

bool CharacterSelection::XYInRect(const SDL_Rect& rect, int x, int y)
{
	return ((x >= rect.x && x <= rect.x + rect.w) && (y >= rect.y && y <= rect.y + rect.h));
}
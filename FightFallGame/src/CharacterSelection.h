#pragma once
#include "Window/Window.h"
#include "Sprite.h"

class CharacterSelection
{
public:
	CharacterSelection(Window* window);
	~CharacterSelection();

public:
	void SelectCharacter();
	void DrawSprite(int x, int y, int w, int h, Sprite* sprite);

	bool IsSelected();
	bool boxerSelected = false;
	bool ninjaSelected = false;
	bool robotSelected = false;

private:
	Window* window;
	Sprite* boxer;
	Sprite* ninja;
	Sprite* robot;
	bool isSelected = false;

	bool XYInRect(const SDL_Rect& rect, int x, int y);
};
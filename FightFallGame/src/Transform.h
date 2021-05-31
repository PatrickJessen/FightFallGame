#pragma once
#include "Vector/Vec2D.h"

class Transform
{
public:
	Transform();
	Transform(int x, int y);
	Transform(int x, int y, int w, int h);

public:
	void Init();
	void Update();

	Vec2D BounceBack();

public:
	Vec2D position;
	Vec2D velocity;

	int width = 32;
	int height = 32;
};
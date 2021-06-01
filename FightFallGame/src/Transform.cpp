#include "Transform.h"

Transform::Transform()
{
	//velocity.Zero();
}

Transform::Transform(int x, int y)
{
	position.x = x;
	position.y = y;
}

Transform::Transform(int x, int y, int w, int h)
{
	position.x = x;
	position.y = y;
	width = w;
	height = h;
}

void Transform::Init()
{
	velocity.Zero();
}

void Transform::Update()
{
	position.x += velocity.x;
	position.y += velocity.y;
}

Vec2D Transform::BounceBack()
{
	return position -= velocity;
}

#include "Vec2D.h"

Vec2D::Vec2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vec2D::Vec2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vec2D& Vec2D::Add(const Vec2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}

Vec2D& Vec2D::Subtract(const Vec2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}

Vec2D& Vec2D::Multiply(const Vec2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}

Vec2D& Vec2D::Divide(const Vec2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}

Vec2D& Vec2D::operator+=(const Vec2D& vec)
{
	return this->Add(vec);
}

Vec2D& Vec2D::operator-=(const Vec2D& vec)
{
	return this->Subtract(vec);
}

Vec2D& Vec2D::operator*=(const Vec2D& vec)
{
	return this->Multiply(vec);
}

Vec2D& Vec2D::operator/=(const Vec2D& vec)
{
	return this->Divide(vec);
}


Vec2D& operator+(Vec2D v1, const Vec2D& v2)
{
	return v1.Add(v2);
}

Vec2D& operator-(Vec2D v1, const Vec2D& v2)
{
	return v1.Subtract(v2);
}

Vec2D& operator*(Vec2D v1, const Vec2D& v2)
{
	return v1.Multiply(v2);
}

Vec2D& operator/(Vec2D v1, const Vec2D& v2)
{
	return v1.Divide(v2);
}

Vec2D& Vec2D::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}

Vec2D& Vec2D::Zero()
{
	this->x = 0;
	this->y = 0;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vec2D vec)
{
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}
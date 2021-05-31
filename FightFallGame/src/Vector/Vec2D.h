#pragma once
#include <iostream>

class Vec2D
{
public:
	float x;
	float y;

	Vec2D();
	Vec2D(float x, float y);

	Vec2D& Add(const Vec2D& vec);
	Vec2D& Subtract(const Vec2D& vec);
	Vec2D& Multiply(const Vec2D& vec);
	Vec2D& Divide(const Vec2D& vec);

	friend Vec2D& operator+(Vec2D v1, const Vec2D& v2);
	friend Vec2D& operator-(Vec2D v1, const Vec2D& v2);
	friend Vec2D& operator*(Vec2D v1, const Vec2D& v2);
	friend Vec2D& operator/(Vec2D v1, const Vec2D& v2);

	Vec2D& operator+=(const Vec2D& vec);
	Vec2D& operator-=(const Vec2D& vec);
	Vec2D& operator*=(const Vec2D& vec);
	Vec2D& operator/=(const Vec2D& vec);

	Vec2D& operator*(const int& i);
	Vec2D& Zero();

	friend std::ostream& operator<<(std::ostream& stream, const Vec2D vec);
};
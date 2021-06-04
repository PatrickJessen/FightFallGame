#pragma once
#include "Projectile.h"
#include <vector>

class IShoot
{
public:
	IShoot();
	~IShoot();

public:
	Sprite* spell;
	std::vector<Projectile> casterSpells;
};
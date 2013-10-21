#include "Bullet.h"
#include "Thing.h"
#include <iostream>

Bullet::Bullet(Thing *parent):
	parent(parent)
{
	
}

Bullet::~Bullet()
{
	
}

void Bullet::tick()
{
	this->x += this->vx;
	this->y += this->vy;
}

void Bullet::draw()
{
	oslDrawFillRect(
		this->x - 5, this->y - 1,
		this->x + 5, this->y + 1,
		RGB(255,0,0)
	);
}

#include "Bullet.h"
#include "Thing.h"
#include <iostream>

Bullet::Bullet(Thing *parent):
	parent(parent),
	x(0), y(0), vx(0), vy(0),
	usedUp(false)
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
		this->x, this->y,
		this->x + width(), this->y + height(),
		RGB(255,0,0)
	);
}

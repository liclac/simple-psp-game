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
		this->x - width()/2, this->y - height()/2,
		this->x + width()/2, this->y + height()/2,
		RGB(255,0,0)
	);
}

int Bullet::width() { return 10; }
int Bullet::height() { return 2; }

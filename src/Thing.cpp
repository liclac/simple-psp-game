#include "Thing.h"
#include <iostream>
#include <climits>
#include "common.h"

Thing::Thing(App *app, OSL_IMAGE *image, OSL_IMAGE *bulletImage):
	x(0), y(0), vx(0), vy(0), hp(INT_MAX),
	image(image), bulletImage(bulletImage),
	color(RGBA(0,0,0,255)),
	_width(20), _height(20),
	app(app)
{
	
}

Thing::~Thing()
{
	
}

void Thing::tick()
{
	this->x += this->vx;
	this->y += this->vy;
	
	std::deque<Bullet>::iterator it = this->ownedBullets.begin();
	while(it != this->ownedBullets.end())
	{
		Bullet &bullet = *it;
		bullet.tick();
		
		if(bullet.usedUp || bullet.x + it->width() < 0 || bullet.x - it->width() > SCREEN_WIDTH)
			it = ownedBullets.erase(it);
		else ++it;
	}
}

void Thing::draw()
{
	this->drawBullets();
	this->drawSelf();
}

void Thing::fire(float vx, float vy, float xoff, float yoff)
{
	Bullet bullet(this);
	bullet.x = this->x + (xoff == -1 ? this->width()/2 : xoff);
	bullet.y = this->y + (yoff == -1 ? this->height()/2 : yoff);
	bullet.vx = vx;
	bullet.vy = vy;
	//bullet.image = (imageOverride ? imageOverride : this->bulletImage);
	
	ownedBullets.push_back(bullet);
}

void Thing::move(float x, float y) { this->x = x; this->y = y; }
void Thing::moveBy(float dx, float dy) { this->x += dx; this->y += dy; }

void Thing::putInMotion(float vx, float vy) { this->vx = vx; this->vy = vy; }

void Thing::resize(int width, int height) { this->_width = width; this->_height = height; }
void Thing::resizeBy(int dwidth, int dheight) { this->_width += dwidth; this->_height += dheight; }

bool Thing::collidesWith(Thing &thing)
{
	if(this->hp == 0 || thing.hp == 0)
		return false;
	
	return this->_collissionCheck(
		this->x, this->y, this->x + this->width(), this->y + this->height(),
		thing.x, thing.y, thing.x + thing.width(), thing.y + thing.height()
	);
}

bool Thing::collidesWith(Bullet &bullet)
{
	if(this->hp == 0 || bullet.parent->hp == 0)
		return false;
	
	return this->_collissionCheck(
		this->x, this->y, this->x + this->width(), this->y + this->height(),
		bullet.x, bullet.y, bullet.x + bullet.width(), bullet.y + bullet.height()
	);
}

bool Thing::_collissionCheck(const float& aMinX, const float& aMinY, const float& aMaxX, const float& aMaxY,
						const float& bMinX, const float& bMinY, const float& bMaxX, const float& bMaxY) const
{
	// Use the AABB (Aligned Axis Bounding Box) algorithm to collission check
	// Basically, if we can draw a line between the two bounding boxes, that
	// means they logically can't be overlapping.
	if(aMaxX < bMinX || aMinX > bMaxX) return false;
	if(aMaxY < bMinY || aMinY > bMaxY) return false;
	
	// We can't draw a line between them, so that means they must be overlapping!
	// (or in a weird angle, that works too)
	return true;
}

void Thing::drawBullets()
{
	for(std::deque<Bullet>::iterator it = this->ownedBullets.begin(); it != this->ownedBullets.end(); it++)
		it->draw();
}

void Thing::drawSelf()
{
	if(hp <= 0) return;
	
	if(image)
	{
		oslDrawImageXY(this->image, this->x, this->y);
	}
	else
	{
		oslDrawFillRect(
			this->x, this->y,
			this->x + this->width(), this->y + this->height(),
			this->color
		);
	}
}

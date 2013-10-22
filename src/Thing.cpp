#include "Thing.h"
#include <iostream>

Thing::Thing(App *app, OSL_IMAGE *image, OSL_IMAGE *bulletImage):
	x(0), y(0), vx(0), vy(0),
	image(image), bulletImage(bulletImage),
	color(RGBA(0,0,0,255)),
	_width(20), _height(20),
	app(app)
{
	
}

void Thing::tick()
{
	this->x += this->vx;
	this->y += this->vy;
	
	for(std::deque<Bullet>::iterator it = this->ownedBullets.begin(); it != this->ownedBullets.end(); it++)
		it->tick();
}

void Thing::draw()
{
	// Draw Bullets
	for(std::deque<Bullet>::iterator it = this->ownedBullets.begin(); it != this->ownedBullets.end(); it++)
		it->draw();
	
	// Draw the thing, either as an image or a small dot
	if(image)
	{
		oslDrawImageXY(
			this->image,
			this->x - (this->width()/2),
			this->y - (this->width()/2)
		);
	}
	else
	{
		oslDrawFillRect(
			this->x - (this->width()/2), this->y - (this->height()/2),
			this->x + (this->width()/2), this->y + (this->height()/2),
			this->color
		);
	}
}

void Thing::fire(float vx, float vy, OSL_IMAGE *imageOverride)
{
	Bullet bullet(this);
	bullet.x = this->x;
	bullet.y = this->y;
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

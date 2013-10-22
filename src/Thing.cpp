#include "Thing.h"
#include <iostream>

Thing::Thing(App *app, OSL_IMAGE *image, OSL_IMAGE *bulletImage):
	x(0), y(0), vx(0), vy(0),
	image(image), bulletImage(bulletImage),
	width(2), height(2),
	color(RGBA(0,0,0,255)),
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
	// Draw the thing...
	if(image)
	{
		oslDrawImageXY(
			this->image,
			this->x - (this->image->sizeX/2),
			this->y - (this->image->sizeY/2)
		);
	}
	else
	{
		oslDrawFillRect(
			this->x - (this->width/2), this->y - (this->height/2),
			this->x + (this->width/2), this->y + (this->height/2),
			this->color
		);
	}
	
	//...and then its bullets.
	for(std::deque<Bullet>::iterator it = this->ownedBullets.begin(); it != this->ownedBullets.end(); it++)
		it->draw();
}

void Thing::fire(int vx, int vy, OSL_IMAGE *imageOverride)
{
	Bullet bullet(this);
	bullet.x = this->x;
	bullet.y = this->y;
	bullet.vx = vx;
	bullet.vy = vy;
	//bullet.image = (imageOverride ? imageOverride : this->bulletImage);
	
	ownedBullets.push_back(bullet);
}

void Thing::move(int x, int y) { this->x = x; this->y = y; }
void Thing::moveBy(int dx, int dy) { this->x += dx; this->y += dy; }

void Thing::resize(int width, int height) { this->width = width; this->height = height; }
void Thing::resizeBy(int dwidth, int dheight) { this->width += dwidth; this->height += dheight; }

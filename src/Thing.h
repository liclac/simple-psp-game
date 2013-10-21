#ifndef _THING_H_
#define _THING_H_

#include <deque>
#include <oslib/oslib.h>
#include "Bullet.h"

class App;
class Thing
{
public:
	
	Thing(App *app, OSL_IMAGE *image = 0, OSL_IMAGE *bulletImage = 0);
	virtual ~Thing() {};
	
	virtual void tick();
	virtual void draw();
	virtual void fire(int vx, int vy, OSL_IMAGE *imageOverride = 0);
	
	void move(int x, int y);
	void moveBy(int dx, int dy);
	
	void resize(int width, int height);
	void resizeBy(int dwidth, int dheight);
	
	int x, y;
	int vx, vy;
	OSL_IMAGE *image, *bulletImage;
	
	// Ignored if an image is present
	int width, height;
	OSL_COLOR color;
	
protected:
	std::deque<Bullet> ownedBullets;
	
	App *app;
};

#endif

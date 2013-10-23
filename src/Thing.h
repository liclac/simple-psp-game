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
	virtual void fire(float vx, float vy, OSL_IMAGE *imageOverride = 0);
	
	void move(float x, float y);
	void moveBy(float dx, float dy);
	
	void putInMotion(float vx, float vy);
	
	void resize(int width, int height);
	void resizeBy(int dwidth, int dheight);
	
	bool collidesWith(Thing &thing);
	bool collidesWith(Bullet &bullet);
	
	float x, y;
	float vx, vy;
	
	inline int width() { return (this->image ? this->image->sizeX : this->_width); };
	inline int height() { return (this->image ? this->image->sizeY : this->_height); };
	
	OSL_IMAGE *image, *bulletImage;
	OSL_COLOR color;
	
protected:
	bool _collissionCheck(const float& aMinX, const float& aMinY, const float& aMaxX, const float& aMaxY, const float& bMinX, const float& bMinY, const float& bMaxX, const float& bMaxY) const;
	
	std::deque<Bullet> ownedBullets;
	
	int _width, _height;
	
	App *app;
};

#endif

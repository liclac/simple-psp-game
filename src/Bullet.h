#ifndef _BULLET_H_
#define _BULLET_H_

#include <oslib/oslib.h>

class Thing;
class Bullet
{
public:
	Bullet(Thing *parent);
	virtual ~Bullet();
	
	virtual void tick();
	virtual void draw();
	
	Thing *parent;
	float x, y;
	float vx, vy;
	
	bool usedUp;
	
	//inline int width() const { return 10; };
	//inline int height() const { return 2; };
	int width();
	int height();
	//OSL_IMAGE *image;
};

#endif

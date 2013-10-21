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
	int x, y;
	int vx, vy;
	//OSL_IMAGE *image;
};

#endif

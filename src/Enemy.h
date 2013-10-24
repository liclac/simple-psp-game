#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Thing.h"

class Enemy : public Thing
{
public:
	Enemy(App *app, OSL_IMAGE *image = 0, OSL_IMAGE *bulletImage = 0);
	virtual ~Enemy();
	virtual void tick();
	
	int collissionDamage;
};

#endif

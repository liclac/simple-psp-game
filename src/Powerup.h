#ifndef _POWERUP_H_
#define _POWERUP_H_

#include "Thing.h"

class Powerup : public Thing
{
public:
	Powerup(App *app, OSL_IMAGE *image = 0, OSL_IMAGE *bulletImage = 0);;
	virtual ~Powerup();
};

#endif

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Thing.h"
#include <oslib/oslib.h>

class Player : public Thing
{
public:
	Player(App *app, OSL_IMAGE *image = 0, OSL_IMAGE *bulletImage = 0);
	virtual ~Player();
	
	virtual void tick();
	
protected:
	void checkMoveControls();
	void checkActionControls();
	void checkBounds();
};

#endif

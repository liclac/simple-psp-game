#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Thing.h"
#include <oslib/oslib.h>

typedef enum {
	WeaponTypeStandard,
	WeaponTypeTriple,
	_WeaponTypeMax
} WeaponType;

class Player : public Thing
{
public:
	Player(App *app, OSL_IMAGE *image = 0, OSL_IMAGE *bulletImage = 0);
	virtual ~Player();
	
	virtual void tick();
	virtual void drawSelf();
	
	int weaponType;
	int invincibilityCountdown;
	
protected:
	void checkMoveControls();
	void checkActionControls();
	void checkBounds();
	
	void die();
};

#endif

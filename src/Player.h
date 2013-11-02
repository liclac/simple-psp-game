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
	
	// Reimplement these to allow for a custom hitbox
	virtual bool collidesWith(Thing &thing);
	virtual bool collidesWith(Bullet &bullet);
	
	virtual void drawSelf();
	
	int weaponType;
	int invincibilityCountdown;
	float cX, cY, cWidth, cHeight;
	
	bool strafing;
	
protected:
	void checkMoveControls();
	void checkActionControls();
	void checkBounds();
	
	void die();
};

#endif

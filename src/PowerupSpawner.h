#ifndef _POWERUPSPAWNER_H_
#define _POWERUPSPAWNER_H_

#include <oslib/oslib.h>

class App;
class PowerupSpawner
{
public:
	PowerupSpawner(App *app);
	virtual ~PowerupSpawner();
	
	float spawnRate;
	float minSpeed, maxSpeed;
	
	OSL_IMAGE *image;
	
	void tick();
	void spawn();
	
protected:
	App *app;
};

#endif

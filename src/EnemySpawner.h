#ifndef _ENEMYSPAWNER_H_
#define _ENEMYSPAWNER_H_

#include <oslib/oslib.h>

class App;
class EnemySpawner
{
public:
	EnemySpawner(App *app);
	virtual ~EnemySpawner();
	
	float spawnRate, fireRate;
	float minSpeed, maxSpeed;
	float bulletSpeed;
	
	int speedupDelay;
	float speedupAmount;
	
	OSL_IMAGE *image, *bulletImage;
	
	void tick();
	void spawn();
	
protected:
	App *app;
	int speedupCountdown;
};

#endif

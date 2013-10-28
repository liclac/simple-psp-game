#include "PowerupSpawner.h"
#include "Powerup.h"
#include "App.h"
#include "common.h"
#include "util.h"

PowerupSpawner::PowerupSpawner(App *app):
	app(app)
{
	
}

PowerupSpawner::~PowerupSpawner()
{
	
}

void PowerupSpawner::tick()
{
	if(uRandomBool(this->spawnRate))
		this->spawn();
}

void PowerupSpawner::spawn()
{
	Powerup powerup(this->app, this->image);
	powerup.move(SCREEN_WIDTH + powerup.width(), uRandomUIntBetween(0, SCREEN_HEIGHT - powerup.height()));
	powerup.putInMotion(-uRandomFloatBetween(this->minSpeed, this->maxSpeed), 0);
	this->app->powerups.push_back(powerup);
}

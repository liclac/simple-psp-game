#include "EnemySpawner.h"
#include "App.h"
#include "common.h"
#include "util.h"
#include <iostream>

EnemySpawner::EnemySpawner(App *app):
	app(app),
	spawnSpeedupCountdown(0),
	firstTick(true)
{
	
}

EnemySpawner::~EnemySpawner()
{
	
}

void EnemySpawner::tick()
{
	if(uRandomBool(this->spawnRate))
		this->spawn();
	
	if(this->firstTick)
	{
		this->spawnSpeedupCountdown = this->spawnSpeedupDelay;
		this->firstTick = false;
	}
	else if(--this->spawnSpeedupCountdown <= 0)
	{
		this->spawnRate += this->spawnSpeedupAmount;
		this->spawnSpeedupCountdown = this->spawnSpeedupDelay;
	}
}

void EnemySpawner::spawn()
{
	Enemy enemy(this->app, this->image, this->bulletImage);
	enemy.move(SCREEN_WIDTH + enemy.width(), uRandomUIntBetween(0, SCREEN_HEIGHT - enemy.height()));
	enemy.putInMotion(-uRandomFloatBetween(this->minSpeed, this->maxSpeed), 0);
	this->app->enemies.push_back(enemy);
}

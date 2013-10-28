#include "EnemySpawner.h"
#include "App.h"
#include "common.h"
#include "util.h"
#include <iostream>

EnemySpawner::EnemySpawner(App *app):
	app(app),
	speedupCountdown(0)
{
	
}

EnemySpawner::~EnemySpawner()
{
	
}

void EnemySpawner::tick()
{
	if(uRandomBool(this->spawnRate))
		this->spawn();
	
	--this->speedupCountdown;
	if(this->speedupCountdown <= 0)
	{
		this->spawnRate += this->speedupAmount;
		this->speedupCountdown = this->speedupDelay;
	}
}

void EnemySpawner::spawn()
{
	Enemy enemy(this->app, this->image, this->bulletImage);
	enemy.move(SCREEN_WIDTH + enemy.width(), uRandomUIntBetween(0, SCREEN_HEIGHT - enemy.height()));
	enemy.putInMotion(-uRandomFloatBetween(this->minSpeed, this->maxSpeed), 0);
	this->app->enemies.push_back(enemy);
}

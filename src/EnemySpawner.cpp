#include "EnemySpawner.h"
#include "App.h"
#include "common.h"
#include "util.h"

EnemySpawner::EnemySpawner(App *app):
	app(app)
{
	
}

EnemySpawner::~EnemySpawner()
{
	
}

void EnemySpawner::tick()
{
	if(uRandomBool(this->spawnRate))
		this->spawn();
}

void EnemySpawner::spawn()
{
	Enemy *enemy = new Enemy(this->app, this->image, this->bulletImage);
	enemy->move(SCREEN_WIDTH + enemy->width(), uRandomUIntBetween(0, SCREEN_HEIGHT - enemy->height()));
	enemy->putInMotion(-uRandomFloatBetween(this->minSpeed, this->maxSpeed), 0);
	this->app->enemies.push_back(enemy);
}

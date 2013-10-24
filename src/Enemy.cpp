#include "Enemy.h"
#include "common.h"
#include "util.h"

Enemy::Enemy(App *app, OSL_IMAGE *image, OSL_IMAGE *bulletImage):
	Thing(app, image, bulletImage)
{
	this->hp = 1;
}

Enemy::~Enemy()
{
	
}

void Enemy::tick()
{
	Thing::tick();
	
	if(this->hp > 0)
	{
		if(uRandomBool(kEnemyFireRate))
		{
			this->fire(kEnemyBulletSpeed, 0);
		}
	}
}

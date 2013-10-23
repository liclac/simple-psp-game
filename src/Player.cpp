#include "Player.h"
#include "App.h"

Player::Player(App *app, OSL_IMAGE *image, OSL_IMAGE *bulletImage):
	Thing(app, image, bulletImage)
{
	
}

Player::~Player()
{
	
}

void Player::tick()
{
	this->checkMoveControls();
	this->checkBounds();
	this->checkActionControls();
	
	// Call this /afterwards/, otherwise we get a frame where a newly
	// fired bullet won't get collission checked properly!
	// (nobody cares, but still...)
	Thing::tick();
	
	for(std::deque<Bullet>::iterator it = this->ownedBullets.begin(); it != this->ownedBullets.end(); it++)
	{
		for(std::deque<Enemy *>::iterator eit = this->app->enemies.begin(); eit != this->app->enemies.end(); eit++)
		{
			Enemy *enemy = *eit;
			Bullet &bullet = *it;
			if(enemy->collidesWith(bullet))
			{
				enemy->hp -= 1;
				bullet.usedUp = true;
			}
		}
	}
}

void Player::checkMoveControls()
{
	int speed = kPlayerSpeed;
	
	// Halve speed if L or R is held down
	if(osl_pad.held.L || osl_pad.held.R)
		speed = speed/2;
	
	if(osl_pad.held.up) this->y -= speed;
	if(osl_pad.held.down) this->y += speed;
	if(osl_pad.held.left) this->x -= speed;
	if(osl_pad.held.right) this->x += speed;
}

void Player::checkActionControls()
{
	if(osl_pad.pressed.square)
		this->fire(kPlayerBulletSpeed, 0);
}

void Player::checkBounds()
{
	int xMin = 0;
	int xMax = SCREEN_WIDTH - width();
	int yMin = 0;
	int yMax = SCREEN_HEIGHT - height();
	
	if(this->x < xMin) this->x = xMin;
	else if(this->x > xMax) this->x = xMax;
	
	if(this->y < yMin) this->y = yMin;
	else if(this->y > yMax) this->y = yMax;
}

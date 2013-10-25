#include "Player.h"
#include "App.h"

Player::Player(App *app, OSL_IMAGE *image, OSL_IMAGE *bulletImage):
	Thing(app, image, bulletImage),
	weaponType(WeaponTypeStandard),
	invincibilityCountdown(0)
{
	this->hp = 3;
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
	
	// Collission check bullets
	for(std::deque<Bullet>::iterator it = this->ownedBullets.begin(); it != this->ownedBullets.end(); it++)
	{
		Bullet &bullet = *it;
		
		for(std::deque<Enemy>::iterator eit = this->app->enemies.begin(); eit != this->app->enemies.end(); eit++)
		{
			Enemy &enemy = *eit;
			if(enemy.collidesWith(bullet))
			{
				enemy.hp -= 1;
				bullet.usedUp = true;
				this->app->score += 1;
			}
		}
	}
	
	// If we're not currently invincible, collission check the player too
	if(invincibilityCountdown <= 0)
	{
		for(std::deque<Enemy>::iterator it = this->app->enemies.begin(); it != this->app->enemies.end(); it++)
		{
			Enemy &enemy = *it;
			if(this->collidesWith(enemy))
				this->die();
			
			for(std::deque<Bullet>::iterator bit = enemy.ownedBullets.begin(); bit != enemy.ownedBullets.end(); bit++)
			{
				Bullet &bullet = *bit;
				if(this->collidesWith(bullet))
					this->die();
			}
		}
	}
	else
	{
		this->invincibilityCountdown--;
	}
}

void Player::drawSelf()
{
	if(invincibilityCountdown > 0)
		oslSetAlpha(OSL_FX_ALPHA, 128);
	
	Thing::drawSelf();
}

void Player::checkMoveControls()
{
	int speed = kPlayerSpeed;
	
	// Halve speed if L or R is held down
	if(osl_pad.held.L || osl_pad.held.R)
		speed = speed/2;
	
	if(osl_pad.pressed.triangle)
	{
		this->weaponType++;
		if(weaponType >= _WeaponTypeMax)
			weaponType = 0;
	}
	
	if(osl_pad.held.up) this->y -= speed;
	if(osl_pad.held.down) this->y += speed;
	if(osl_pad.held.left) this->x -= speed;
	if(osl_pad.held.right) this->x += speed;
}

void Player::checkActionControls()
{
	if(osl_pad.pressed.square)
	{
		switch(this->weaponType)
		{
			case WeaponTypeStandard:
				this->fire(kPlayerBulletSpeed, 0);
				break;
			case WeaponTypeTriple:
				this->fire(kPlayerBulletSpeed, 0, 0, 0);
				this->fire(kPlayerBulletSpeed, 0, this->width(), this->height()/2);
				this->fire(kPlayerBulletSpeed, 0, 0, this->height());
				break;
		}
	}
	
	if(osl_pad.pressed.select)
	{
		this->app->unloadAllImages();
		this->app->newGame();
	}
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

void Player::die()
{
	this->hp--;
	if(this->hp <= 0)
	{
		this->app->state = AppStateGameOver;
	}
	else
	{
		this->invincibilityCountdown = kPlayerDeathInvFrames;
		this->x = 0;
		this->y = (SCREEN_HEIGHT - this->height())/2;
	}
}

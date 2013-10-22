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
	Thing::tick();
	
	this->checkMoveControls();
	this->checkBounds();
	this->checkActionControls();
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
		this->fire(1, 0);
}

void Player::checkBounds()
{
	int xMin = (width()/2);
	int xMax = (SCREEN_WIDTH - width()/2);
	int yMin = (height()/2);
	int yMax = (SCREEN_HEIGHT - height()/2);
	
	if(this->x < xMin) this->x = xMin;
	else if(this->x > xMax) this->x = xMax;
	
	if(this->y < yMin) this->y = yMin;
	else if(this->y > yMax) this->y = yMax;
}

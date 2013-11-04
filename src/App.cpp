#include "App.h"
#include <iostream>
#include <sstream>
#include "util.h"
#include "Enemy.h"

App::App(int argc, const char **argv):
	score(0),
	player(0),
	enemySpawner(0), powerupSpawner(0)
{
	uRandomInit(time(NULL));
	srand(time(NULL)); // In case I need it... I sure hope not.
	
	this->parseArgs(argc, argv);
	this->initOSL();
	
	this->loadFonts();
	this->loadResources();
	this->newGame();
}

App::~App()
{
	
}

void App::parseArgs(int argc, const char **argv)
{
	// Extract the pathname from the executable name in argv[0]
	{
		int len = strrchr(argv[0], '/') - argv[0];
		char *cpy = strndup(argv[0], len);
		this->appDir = cpy;
		free(cpy);
	}
}

void App::initOSL()
{
	// -- OSLib
	// Init OSLib with default callbacks
	oslInit(0);
	// Don't crash if we can't load a resource
	//oslSetQuitOnLoadFailure(1);
	
	// -- Input
	// We want the D-Pad to repeat if you hold it down, makes it easier to scroll through stuff
	// Start repeating after 40 frames, then repeat every 10th
	oslSetKeyAutorepeatMask(OSL_KEYMASK_UP|OSL_KEYMASK_RIGHT|OSL_KEYMASK_DOWN|OSL_KEYMASK_LEFT);
	oslSetKeyAutorepeatInit(40);
	oslSetKeyAutorepeatInterval(10);
	// Map the analog stick to the D-Pad with 80/127 sensitivty
	// This is oslib's recommended default, considering the analog stick's dead zone
	oslSetKeyAnalogToDPad(80);
	
	// -- Graphics
	// Init graphics with 16bit (for now) and double buffering
	// Might bump it up to 32bit later if it looks too bad
	oslInitGfx(OSL_PF_5650, true);
	
	// -- Fonts
	oslIntraFontInit(INTRAFONT_CACHE_MED);
	
	// -- Synchronization
	oslSetFrameskip(1);
	oslSetMaxFrameskip(4);
}

void App::loadResources()
{
	bgImage = this->loadImagePNG("img/bg.png");
	bgImage->x = 0;
	bgImage->y = 0;
	
	hpImage = this->loadImagePNG("img/heart.png", OSL_PF_4444);
}

void App::loadFonts()
{
	bigFont = oslLoadFontFile(FONT_PATH_BIG_SANS);
	smallFont = oslLoadFontFile(FONT_PATH_SMALL_SANS);
}

void App::newGame()
{
	if(player != 0) delete player;
	player = new Player(this, this->loadImagePNG("img/ship.png"), this->loadImagePNG("img/beam.png"));
	player->move((SCREEN_WIDTH - player->width())/2, (SCREEN_HEIGHT - player->height())/2);
	player->cX = 10;
	player->cY = 8;
	player->cWidth = 6;
	player->cHeight = 4;
	
	this->enemies.clear();
	this->powerups.clear();
	
	if(enemySpawner != 0) delete enemySpawner;
	enemySpawner = new EnemySpawner(this);
	enemySpawner->image = this->loadImagePNG("img/enemy1.png");
	enemySpawner->bulletImage = this->loadImagePNG("img/rocket.png");
	enemySpawner->spawnRate = kEnemySpawnRate;
	enemySpawner->spawnSpeedupDelay = kEnemySpawnSpeedupDelay;
	enemySpawner->spawnSpeedupAmount = kEnemySpawnSpeedupAmount;
	enemySpawner->fireRate = kEnemyFireRate;
	enemySpawner->minSpeed = kEnemyMinSpeed;
	enemySpawner->maxSpeed = kEnemyMaxSpeed;
	enemySpawner->bulletSpeed = kEnemyBulletSpeed;
	
	if(powerupSpawner != 0) delete powerupSpawner;
	powerupSpawner = new PowerupSpawner(this);
	powerupSpawner->image = this->loadImagePNG("img/bulle.png");
	powerupSpawner->spawnRate = kPowerupSpawnRate;
	powerupSpawner->minSpeed = kPowerupMinSpeed;
	powerupSpawner->maxSpeed = kPowerupMaxSpeed;
	
	score = 0;
	state = AppStatePlaying;
}

void App::run()
{
	// True if the last frame was in late, in which case we should drop the next frame
	bool lastFrameWasLate = false;
	
	while(!osl_quit)
	{
		// Update state
		this->tick();
		
		// If the last frame was /not/ late, draw the next one
		// Otherwise, drop frames until we catch up
		if(!lastFrameWasLate)
			this->draw();
		
		// This takes care of timing and determining when to drop a frame
		oslEndFrame();
		lastFrameWasLate = oslSyncFrame();
	}
}

void App::reset()
{
	std::cout << "Resetting..." << std::endl;
	
	this->unloadAllImages();
	this->loadResources();
	this->newGame();
	
	std::cout << "Reset Finished!" << std::endl;
}

void App::tick()
{
	// Check the controller for new inputs; this updates osl_pad
	oslReadKeys();
	
	if(this->state == AppStatePlaying)
	{
		if(osl_pad.pressed.start)
			this->state = AppStatePaused;
		else
		{
			if(osl_pad.pressed.select)
			{
				this->reset();
				this->tick();
				return;
			}
			
			// Let objects update their states
			player->tick();
			std::deque<Enemy>::iterator eit = enemies.begin();
			while(eit != enemies.end())
			{
				Enemy &enemy = *eit;
				enemy.tick();
				
				if(enemy.x + enemy.width() < 0)
					eit = enemies.erase(eit);
				else
					++eit;
			}
			
			std::deque<Powerup>::iterator pit = powerups.begin();
			while(pit != powerups.end())
			{
				Powerup &powerup = *pit;
				powerup.tick();
				
				if(powerup.x + powerup.width() < 0)
					pit = powerups.erase(pit);
				else
					++pit;
			}
			
			// Occasionally spawn enemies and powerups
			enemySpawner->tick();
			powerupSpawner->tick();
		}
	}
	else if(this->state == AppStatePaused)
	{
		if(osl_pad.pressed.start)
			this->state = AppStatePlaying;
		else if(osl_pad.pressed.select)
			this->newGame();
	}
	else if(this->state == AppStateGameOver)
	{
		if(osl_pad.pressed.start)
			this->newGame();
	}
}

void App::draw()
{
	// Prepare to draw
	oslStartDrawing();
	
	// Clear the buffer to prevent ghosting
	oslClearScreen(RGB(0, 0, 0));
	
	// Draw a background
	oslDrawImage(bgImage);
	
	// Let objects draw themselves
	for(std::deque<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++)
		it->draw();
	for(std::deque<Powerup>::iterator it = powerups.begin(); it != powerups.end(); it++)
		it->draw();
	player->draw();
	
	// Draw HUD
	this->drawHUD();
	
	// Draw overlays for certain states
	if(state == AppStatePaused)
	{
		const char *msg1 = "PAUSED";
		const char *msg2 = "START = Resume";
		const char *msg3 = "SELECT = Restart";
		
		oslSetFont(this->bigFont);
		oslDrawString((SCREEN_WIDTH - oslGetStringWidth(msg1))/2, SCREEN_HEIGHT/2 - this->bigFont->charHeight - 2, msg1);
		
		oslSetFont(this->smallFont);
		oslDrawString((SCREEN_WIDTH - oslGetStringWidth(msg2))/2, (SCREEN_HEIGHT/2) + 2, msg2);
		oslDrawString((SCREEN_WIDTH - oslGetStringWidth(msg3))/2, (SCREEN_HEIGHT/2) + 2 + osl_curFont->charHeight + 5, msg3);
	}
	else if(state == AppStateGameOver)
	{
		const char *msg1 = "Game Over";
		const char *msg2 = "Press START to try again";
		
		oslSetFont(this->bigFont);
		oslDrawString((SCREEN_WIDTH - oslGetStringWidth(msg1))/2, SCREEN_HEIGHT/2 - this->bigFont->charHeight - 2, msg1);
		
		oslSetFont(this->smallFont);
		oslDrawString((SCREEN_WIDTH - oslGetStringWidth(msg2))/2, (SCREEN_HEIGHT/2) + 2, msg2);
	}
	
	// Release resources grabbed in oslStartDrawing()
	oslEndDrawing();
}

void App::drawHUD()
{
	oslSetFont(this->bigFont);
	
	// Score
	{
		std::stringstream scoreStream;
		scoreStream << score;
		std::string scoreString = scoreStream.str();
		oslDrawString(SCREEN_WIDTH - oslGetStringWidth(scoreString.c_str()) - 10, 10, scoreString.c_str());
	}
	
	// Lives
	{
		for(int i = 0; i < player->hp; i++)
		{
			int x = 5 + (15 + 10)*i;
			int y = 0;
			oslDrawImageXY(this->hpImage, x, y);
		}
	}
}

OSL_IMAGE* App::loadImagePNG(std::string filename, int format, int flags)
{
	std::map<std::string, OSL_IMAGE*>::iterator it = images.find(filename);
	if(it == images.end())
	{
		std::cout << "Loading image '" << filename << "'... (" << std::hex << flags << std::dec << ", " << format << ")" << std::endl;
		char *filenameCStrDup = strdup(filename.c_str());
		OSL_IMAGE *img = oslLoadImageFilePNG(filenameCStrDup, flags, format);
		free(filenameCStrDup);
		
		images.insert(std::pair<std::string, OSL_IMAGE*>(filename, img));
		return img;
	}
	
	return it->second;
}

void App::unloadImage(std::string filename)
{
	std::map<std::string, OSL_IMAGE*>::iterator it = images.find(filename);
	if(it != images.end())
	{
		std::cout << "Unloading image '" << filename << "'..." << std::endl;
		oslDeleteImage(it->second);
		images.erase(it);
	}
}

void App::unloadAllImages()
{
	std::cout << "Unloading all images... Total: " << images.size() << std::endl;
	for(std::map<std::string, OSL_IMAGE*>::iterator it = images.begin(); it != images.end(); it++)
	{
		std::cout << "-> " << it->first << std::endl;
		oslDeleteImage(it->second);
	}
	images.clear();
	std::cout << "Done." << std::endl;
}

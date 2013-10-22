#include "App.h"
#include <iostream>
#include "util.h"
#include "Enemy.h"

App::App(int argc, const char **argv)
{
	this->parseArgs(argc, argv);
	this->initOSL();
	
	sceKernelUtilsMt19937Init(&mt_ctx, time(NULL));
	
	OSL_IMAGE *shipSprite = this->loadImagePNG("img/ship.png");
	
	player = new Player(this, shipSprite);
	player->move(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
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
	oslInitGfx(OSL_PF_5551, true);
	
	// -- Fonts
	oslIntraFontInit(INTRAFONT_CACHE_MED);
	
	// -- Synchronization
	oslSetFrameskip(1);
	oslSetMaxFrameskip(4);
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

void App::tick()
{
	// Check the controller for new inputs; this updates osl_pad
	oslReadKeys();
	
	// Let objects update their states
	player->tick();
	for(std::deque<Thing*>::iterator it = enemies.begin(); it != enemies.end(); it++)
		(*it)->tick();
	
	// Occasionally spawn enemies
	if(uRandomBool(&mt_ctx, kEnemySpawnRate))
	{
		Enemy *enemy = new Enemy(this, this->loadImagePNG("img/enemy1.png"));
		enemy->move(uRandomUIntBetween(&mt_ctx, SCREEN_WIDTH*0.75, SCREEN_WIDTH), uRandomUIntBetween(&mt_ctx, 0, SCREEN_HEIGHT));
		enemies.push_back(enemy);
	}
}

void App::draw()
{
	// Prepare to draw
	oslStartDrawing();
	
	// Clear the buffer to prevent ghosting
	oslClearScreen(RGB(128, 0, 0));
	
	// Let objects draw themselves
	player->draw();
	for(std::deque<Thing*>::iterator it = enemies.begin(); it != enemies.end(); it++)
		(*it)->draw();
	
	// Release stuff grabbed in oslStartDrawing()
	oslEndDrawing();
}

OSL_IMAGE* App::loadImagePNG(std::string filename, int flags, int format)
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
	std::cout << "Unloading all images... size=" << images.size() << std::endl;
	for(std::map<std::string, OSL_IMAGE*>::iterator it = images.begin(); it != images.end(); it++)
	{
		std::cout << "-> " << it->first << std::endl;
		oslDeleteImage(it->second);
	}
	images.clear();
	std::cout << "Done." << std::endl;
}

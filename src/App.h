#ifndef _APP_H_
#define _APP_H_

#include <oslib/oslib.h>
#include <string>
#include <deque>
#include <map>
#include "common.h"
#include "Player.h"

class App
{
public:
	App(int argc, const char **argv);
	virtual ~App();
	
	void run();
	
	OSL_IMAGE* loadImagePNG(std::string filename, int flags = OSL_IN_VRAM | OSL_SWIZZLED, int format = OSL_PF_5551);
	void unloadImage(std::string filename);
	void unloadAllImages();
	
protected:
	void parseArgs(int argc, const char **argv);
	void initOSL();
	
	void tick();
	void draw();
	
protected:
	std::string appDir;
	
	Player *player;
	std::deque<Thing *> enemies;
	
	std::map<std::string, OSL_IMAGE*> images;
	
	SceKernelUtilsMt19937Context mt_ctx;
};

#endif

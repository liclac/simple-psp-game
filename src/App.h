#ifndef _APP_H_
#define _APP_H_

#include <oslib/oslib.h>
#include <string>
#include <deque>
#include <map>
#include "common.h"
#include "Player.h"
#include "Enemy.h"

typedef enum {
	AppStatePlaying,
	AppStatePaused,
	AppStateGameOver
} AppState;

class App
{
public:
	App(int argc, const char **argv);
	virtual ~App();
	
	void run();
	
	OSL_IMAGE* loadImagePNG(std::string filename, int flags = OSL_IN_VRAM | OSL_SWIZZLED, int format = OSL_PF_5551);
	void unloadImage(std::string filename);
	void unloadAllImages();
	
	Player *player;
	std::deque<Enemy *> enemies;
	OSL_IMAGE *bgImage;
	OSL_FONT *bigFont, *smallFont;
	
	AppState state;
	
	int score;
	
protected:
	void parseArgs(int argc, const char **argv);
	void initOSL();
	
	void tick();
	void draw();
	void drawHUD();
	
protected:
	std::string appDir;
	
	std::map<std::string, OSL_IMAGE*> images;
};

#endif

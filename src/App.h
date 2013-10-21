#ifndef _APP_H_
#define _APP_H_

#include <oslib/oslib.h>
#include <string>
#include <deque>
#include "common.h"
#include "Player.h"

class App
{
public:
	App(int argc, const char **argv);
	virtual ~App();
	
	void run();
	
protected:
	void parseArgs(int argc, const char **argv);
	void initOSL();
	
	void tick();
	void draw();
	
	bool stringsEqual;
	
protected:
	std::string appDir;
	
	Player *player;
	std::deque<Thing *> enemies;
	
	SceKernelUtilsMt19937Context mt_ctx;
};

#endif

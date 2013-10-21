#include <pspkernel.h>
#include <oslib/oslib.h>
#include "common.h"
#include "App.h"

PSP_MODULE_INFO("Simple Game", USE_KERNEL_MODE, VERSION_MAJOR, VERSION_MINOR);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_MAX();

int main(int argc, const char **argv)
{
	srand(time(NULL));
	
	App *app = new App(argc, argv);
	app->run();
	delete app;
	
	sceKernelExitGame();
	return 0;
}
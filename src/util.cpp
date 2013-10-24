#include "util.h"
#include <climits>

static SceKernelUtilsMt19937Context ctx;

void uRandomInit(int seed)
{
	sceKernelUtilsMt19937Init(&ctx, seed);
}

u32 uRandomUIntBetween(int min, int max)
{
	return (sceKernelUtilsMt19937UInt(&ctx) % max) + min;
}

float uRandomFloatBetween(float min, float max)
{
	return min + (float)sceKernelUtilsMt19937UInt(&ctx)/((float)UINT_MAX/(max-min));
}

bool uRandomBool(int percent)
{
	return (sceKernelUtilsMt19937UInt(&ctx) % 100) < percent;
}

#include "util.h"
#include <climits>
#include <iostream>

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

bool uRandomBool(float probability)
{
	if(probability == 1)
		return true;
	return (sceKernelUtilsMt19937UInt(&ctx) / (float)UINT_MAX) < probability;
}

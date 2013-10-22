#include "util.h"
#include <climits>

u32 uRandomUIntBetween(SceKernelUtilsMt19937Context *ctx, int min, int max)
{
	return (sceKernelUtilsMt19937UInt(ctx) % max) + min;
}

float uRandomFloatBetween(SceKernelUtilsMt19937Context *ctx, float min, float max)
{
	return min + (float)sceKernelUtilsMt19937UInt(ctx)/((float)UINT_MAX/(max-min));
}

bool uRandomBool(SceKernelUtilsMt19937Context *ctx, int percent)
{
	return (sceKernelUtilsMt19937UInt(ctx) % 100) < percent;
}

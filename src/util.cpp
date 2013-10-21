#include "util.h"

u32 uRandomUIntBetween(SceKernelUtilsMt19937Context *ctx, int min, int max)
{
	return (sceKernelUtilsMt19937UInt(ctx) % max) + min;
}

bool uRandomBool(SceKernelUtilsMt19937Context *ctx, int percent)
{
	return (sceKernelUtilsMt19937UInt(ctx) % 100) < percent;
}

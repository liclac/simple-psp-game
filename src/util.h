#ifndef _UTIL_H_
#define _UTIL_H_

#include <string>
#include <psputils.h>

u32 uRandomUIntBetween(SceKernelUtilsMt19937Context *ctx, int min, int max);
bool uRandomBool(SceKernelUtilsMt19937Context *ctx, int percent = 50);

#endif

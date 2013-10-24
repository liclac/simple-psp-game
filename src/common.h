#ifndef _COMMON_H_
#define _COMMON_H_

/*
 * -- Module Info
 */
#define USE_KERNEL_MODE 0	//< Run in Kernel Mode?
#define VERSION_MAJOR 0		//< Major Version
#define VERSION_MINOR 1		//< Minor Version

/*
 * -- Hardware Info
 */
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

/*
 * -- Font Paths
 * These follow an obvious and regular pattern, but memorizing
 * it would be an unnecessary headache.
 */
#define FONT_PATH_BIG_SANS "flash0:/font/ltn0.pgf"
#define FONT_PATH_BIG_SERIF "flash0:/font/ltn1.pgf"
#define FONT_PATH_BIG_SANS_I "flash0:/font/ltn2.pgf"
#define FONT_PATH_BIG_SERIF_I "flash0:/font/ltn3.pgf"
#define FONT_PATH_BIG_SANS_B "flash0:/font/ltn4.pgf"
#define FONT_PATH_BIG_SERIF_B "flash0:/font/ltn5.pgf"
#define FONT_PATH_BIG_SANS_BI "flash0:/font/ltn6.pgf"
#define FONT_PATH_BIG_SERIF_BI "flash0:/font/ltn7.pgf"

#define FONT_PATH_SMALL_SANS "flash0:/font/ltn8.pgf"
#define FONT_PATH_SMALL_SERIF "flash0:/font/ltn9.pgf"
#define FONT_PATH_SMALL_SANS_I "flash0:/font/ltn10.pgf"
#define FONT_PATH_SMALL_SERIF_I "flash0:/font/ltn11.pgf"
#define FONT_PATH_SMALL_SANS_B "flash0:/font/ltn12.pgf"
#define FONT_PATH_SMALL_SERIF_B "flash0:/font/ltn13.pgf"
#define FONT_PATH_SMALL_SANS_BI "flash0:/font/ltn14.pgf"
#define FONT_PATH_SMALL_SERIF_BI "flash0:/font/ltn15.pgf"

/*
 * -- Game Configuration
 */
#define kPlayerSpeed 4
#define kPlayerSize 5
#define kPlayerBulletSpeed 2

#define kEnemySpawnRate 1
#define kEnemyFireRate 1
#define kEnemyMinSpeed 1.0
#define kEnemyMaxSpeed 2.0
#define kEnemyBulletSpeed -2.5

#endif

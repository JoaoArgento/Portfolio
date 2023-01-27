#ifndef G_EXPLOSION_H
#define G_EXPLOSION_H

#include "G_DECS.h"
#include "G_TYPES.h"
#include "G_IMG_HANDLE.h"
#include "G_SHIELDS.h"

#define EXPLO_IMG_X 63
#define EXPLO_IMG_Y 63
#define EXPLO_SS_SIZEX 447
#define EXPLO_SS_SIZEY 127
#define EXPLO_IMG_AMOUNT 14

typedef struct Effect
{
	float x, y;
	int animIndex;
	
}explosion;

static imgtype **exploTextures;
static imgtype **exploMskTextures;
static explosion  *explosions;


void HandleExploImg();
void drawExplosion();
void UpdateEffects();
void AnimControl();
void RemoveEffect(int target);
void AllocObj(float x, float y);
explosion CreateEffect(float x, float y);
#endif

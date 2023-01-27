#ifndef G_SHIELDS_H
#define G_SHIELDS_H
#include "G_TYPES.h"
#include "G_DECS.h"

#define s_imgX 63
#define s_imgY 63
#define SS_sizeX 319
#define SHIELD_AMNT 5

typedef struct 
{
	int hp;
	int sizex, sizey;
	float x, y;
	int animIndex;

} objtype;

static imgtype **shieldTextures;
static imgtype **shieldMskTextures;

void InitializeArray(Shield Array[], int size);
Shield CreateObj(int x, int y, int hp);
void DrawObj(Shield shield[], int size);
void UpdateObj(Shield shield[], int size);
void VerifyLife(Shield shield[], int i);
void HandleShieldImg();

#endif

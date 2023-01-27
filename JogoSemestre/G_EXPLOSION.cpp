#include "G_EXPLOSION.h"


int explosionSize = 0;
int explo_AnimIndex = 0;

void HandleExploImg()
{
	int i = 0;
	int exploImgSize = GetImgSize(EXPLO_IMG_X, EXPLO_IMG_Y);
	exploTextures = NULL;
	exploMskTextures = NULL;
	
	exploTextures = MallocImg(exploTextures, exploImgSize, EXPLO_IMG_AMOUNT);
	exploMskTextures = MallocImg(exploMskTextures, exploImgSize, EXPLO_IMG_AMOUNT);
	
	ReadImg((char*)"./Sprites/Effects/explo.bmp", EXPLO_IMG_X, EXPLO_IMG_Y, 0, EXPLO_SS_SIZEX, EXPLO_SS_SIZEY, exploTextures, exploMskTextures, EXPLO_IMG_AMOUNT);
	
	for(i = 0; i < EXPLO_IMG_AMOUNT; i++)
	{
		removeImgBG(exploMskTextures[i], exploTextures[i], exploImgSize);
	}
}
void AllocObj(float x, float y)
{
	explosionSize++;
	explosions = (explosion*)realloc(explosions, (sizeof(explosion)*(explosionSize)));
	explosions[explosionSize - 1] = CreateEffect(x, y);
}

explosion CreateEffect(float x, float y)
{
	explosion obj;
	obj.x = x;
	obj.y = y;
	obj.animIndex = 0;
	mciSendString("seek explo to start", NULL, 0, 0);
	mciSendString("play explo", NULL, 0, 0);
	
	
	return obj;
}

void UpdateEffects()
{
	drawExplosion();
	AnimControl();

}

void AnimControl()
{
	int i = 0;
	for(i = 0; i < explosionSize; i++)
	{
		if(explosions[i].animIndex < EXPLO_IMG_AMOUNT - 1)
		{
			explosions[i].animIndex++;
		}
		else
		{	
			explosions[i].animIndex = 0;
			RemoveEffect(i);
		}
	}
}

void RemoveEffect(int target)
{
	int i = 0;
	int j = 0;
	
	while (i < explosionSize)
	{
		if(i == target)
		{
			for(j = i; j < explosionSize - 1; j++)
			{
				explosions[j] = explosions[j+1];
			}
			explosionSize--;
			explosions = (explosion*)realloc(explosions, sizeof(explosion)*explosionSize);
		}
		i++;
	}
}

void drawExplosion()
{
	int i = 0;
	for(i = 0; i < explosionSize; i++)
	{	
		putimg(explosions[i].x, explosions[i].y, exploTextures, exploMskTextures, explosions[i].animIndex);
	}
}

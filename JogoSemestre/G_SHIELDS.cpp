#include "G_SHIELDS.h"
#include "G_DECS.h"
#include "G_IMG_HANDLE.h"

void InitializeArray(Shield Array[], int size)
{
	int i;
	int posX = 10 + gameScreenX/10.0;
	int posY = gameScreenY - 200;
	
	for(i = 0; i < size; i++)
	{
		Array[i] = CreateObj(posX, posY, 5);
		posX += gameScreenX/3.0;
	}
}

Shield CreateObj(int x, int y, int hp)
{
	Shield obj;
	obj.animIndex = 0;
	obj.hp = hp;
	obj.death = false;
	obj.x = x;
	obj.y = y;
	obj.sizex = 64;
	obj.sizey = 64;
	
	return obj;
}

void HandleShieldImg()
{
	int sImgSize = GetImgSize(s_imgX, s_imgY);
	int i = 0;
	shieldTextures = NULL;
	shieldMskTextures = NULL;
	
	shieldTextures = MallocImg(shieldTextures, sImgSize, SHIELD_AMNT);
	shieldMskTextures = MallocImg(shieldMskTextures, sImgSize, SHIELD_AMNT);
	ReadImg((char*)"./Sprites/Shields/shield.bmp",s_imgX, s_imgY, 0, SS_sizeX, s_imgY, shieldTextures, shieldMskTextures, SHIELD_AMNT);

	for(i = 0; i < SHIELD_AMNT; i++)
	{
		removeImgBG(shieldMskTextures[i], shieldTextures[i], sImgSize);
	
	}
	
}

void DrawObj(Shield shield[], int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		
		if(!shield[i].death && shield[i].animIndex < SHIELD_AMNT)
		{
			putimg(shield[i].x, shield[i].y, shieldTextures, shieldMskTextures, shield[i].animIndex);
		}
		else
		{
			shield[i].animIndex = 0;
		}
			
		VerifyLife(shield, i);
	}
} 
void UpdateObj(Shield shield[], int size)
{
	DrawObj(shield, size);
}
void VerifyLife(Shield shield[], int i)
{
	if(shield[i].hp <= 0)
	{
		shield[i].death = true;
	}
}

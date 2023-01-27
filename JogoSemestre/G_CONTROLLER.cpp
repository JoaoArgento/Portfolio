#include "G_CONTROLLER.h"
#include "G_ENEMY.h"
#include "G_SHIELDS.h"
#include "G_BULLET.h"


extern int kills;
extern Enemy *enemies;
extern Meteor *meteors;
extern Bullet *bullets;

int bulletIndex = 0;
int e_BulletIndex = 0;
int shieldIndex = 0;
int meteorIndex = 0;

void VerifyKeyReleased(char key, bool *k_Pressed)
{	
	if((GetKeyState(key) & 0x8000) && !(*k_Pressed))
	{	
		*k_Pressed = true;
	}
	
	if(!(GetKeyState(key) & 0x8000) && !(*k_Pressed))
	{
		*k_Pressed = true;			
	}
}

void InitializeVetor() 
{ 
	int x, y;
	
	for(x = 0; x < enemyRows; x++)
	{
		for(y = 0; y < enemyCols; y++)
		{
			printf("%5d",enemyGrid[x][y]);
		}
		printf("\n");
	}
}
void LoadSounds()
{
	mciSendString("open ./SFX/Soundtrack.mp3 type MPEGVideo alias level1", NULL, 0, 0); 
	mciSendString("open ./SFX/Soundtrack3.mp3 type MPEGVideo alias level2", NULL, 0, 0); 
	mciSendString("open ./SFX/soundtrack1.mp3 type MPEGVideo alias boss", NULL, 0, 0);  
  	mciSendString("open ./SFX/explo.mp3 type MPEGVideo alias explo", NULL, 0, 0); 
  	waveOutSetVolume(0,0x333333);
}
 
void BubbleSort(float *positions, int size)
{   
	int x, y, i;
	float aux; 
	
	for(x = 0; x < size; x++)
	{
		for(y = x + 1; y < size; y++)
		{
			if(positions[x] > positions[y])
			{
				aux = positions[x];
				positions[x] = positions[y];
				positions[y] = aux;
			}
		} 
	}
}

Obj *RemoveObj(Player *player, Obj *objs, int *size, int entityCollided, obj_t type)
{
	int i = 0, j = 0;
	
	while(i < (*size))
	{
		if(i == entityCollided)
		{	
			
			for(j = i; j < *size - 1; j++)
			{
				objs[j] = objs[j+1]; 
			}			
			(*size)--;
			objs = (Obj*)realloc(objs, sizeof(Obj) * (*size));
				
			if(type == ENEMY)
			{
				kills++;
				player->points++;
				
				if(!player->tripleshot)
					player->TS_Points++;
			}
		}
		i++;
	}
	return objs;
}

void StopSounds()
{
	mciSendString("stop level1", NULL, 0, 0);	
	mciSendString("seek level1 to start", NULL, 0, 0);
	mciSendString("stop level2", NULL, 0, 0);	
	mciSendString("seek level2 to start", NULL, 0, 0);
	mciSendString("stop boss", NULL, 0, 0);	
	mciSendString("seek boss to start", NULL, 0, 0);	
}	

bool DetectCollision(Player *player, Obj *v1, Obj *v2, int v1_size,  int *v2_size, obj_t type, int targetSize)
{ 
	int i = 0; 
	int j = 0; 
	float distance;   
	bool collided = false;
	float x;  
	float y;
	
	while(i < v1_size) 
	{ 
		for(j = 0; j < *v2_size; j++)
		{
			if(type == ENEMY)
			{
				x = pow((v1[i].x - v2[j].x), 2);
				y = pow((v1[i].y - v2[j].y), 2);
				
				distance = sqrt(x + y);
				
				if(distance <= targetSize)
				{
					bulletIndex = i;
					AllocObj(v2[j].x, v2[j].y);
					enemies = (Enemy*)RemoveObj(player, v2, v2_size, j, ENEMY);
					collided = true;
				}	 
			} 	
			else if(type == PLAYER)
			{
				x = pow((v1[i].x - player->x), 2);
				y = pow((v1[i].y - player->y), 2);
				
				distance = sqrt(x + y);
				
				if(distance <= targetSize && player->hp > 0)
				{	
					collided = true;
				}			
			}
			else if(type == SHIELD)
			{
				x = pow((v1[j].x - v2[i].x), 2);
				y = pow((v1[j].y - v2[i].y), 2);
				
				distance = sqrt(x + y);
				
				if(distance <= targetSize && v2[i].hp > 0)
				{
					e_BulletIndex = j;
					shieldIndex = i;
				    collided = true;
					v2[i].animIndex += 1;				
				}
			}
			else if(type == METEORS)
			{
				x = pow((v1[i].x - v2[j].x), 2);
				y = pow((v1[i].y - v2[j].y), 2);
				
				distance = sqrt(x + y);
				
				if(distance <= targetSize)
				{
					meteorIndex = i;
					if(*v2_size > 0)
					{
						bullets = (Bullet*) RemoveObj(player, (Obj*)v2, v2_size, j, BULLET);
					}	
				    collided = true;				
				}
			}		
		}	
		i++; 
	} 
	return collided;
}

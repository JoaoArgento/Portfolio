#if 1
#include "G_ENEMY.h"
#include "G_DECS.h"
#include "G_ENEMY_BULLET.h"
#include <math.h>


extern LEVEL level;

int e_animIndices[E_VariantAmount] = {0, 40, 44};
int e_SS_sizeX[E_VariantAmount] = {639, 255, 639};

float enemySpeed = 50.0;
float e_FallSpeed = 200.0;
float directionX = 1.0;
float e_animSpeed = 1;

int   killsCount = 10;
int   increaseKillCount = 10;
int   kills = 0;
int bossIndex = 0;
double changeSprite;
Obj *enemies;

void HandleEnemyImg()
{ 
	//lida com as imagens do enemy.
 	int e_imgSize = GetImgSize(enemyImgsizeX,enemyImgsizeY); 
	int i = 0;  
    
    enemyTextures = MallocImg(enemyTextures, e_imgSize, IMG_AMOUNT);
    enemyMskTextures = MallocImg(enemyMskTextures, e_imgSize, IMG_AMOUNT);
    
	ReadImg((char*)"./Sprites/Enemies/enemy1.bmp", enemyImgsizeX, enemyImgsizeY, 0, e_SS_sizeX[0], SS_sizeY, enemyTextures, enemyMskTextures, IMG_AMOUNT - E2_AMOUNT - E3_AMOUNT);
	ReadImg((char*)"./Sprites/Enemies/enemy2.bmp", enemyImgsizeX, enemyImgsizeY, E1_AMOUNT, e_SS_sizeX[1], enemyImgsizeY, enemyTextures, enemyMskTextures, IMG_AMOUNT- E3_AMOUNT);
	ReadImg((char*)"./Sprites/Enemies/enemy3.bmp", enemyImgsizeX, enemyImgsizeY, E1_AMOUNT + E2_AMOUNT, e_SS_sizeX[2], SS_sizeY, enemyTextures, enemyMskTextures, IMG_AMOUNT);

	for(i = 0; i < IMG_AMOUNT; i++)
		removeImgBG(enemyMskTextures[i], enemyTextures[i], e_imgSize);
}


void EnemyAnimController(float animDelay, Obj *enemy, gt_type gt2, int size, double dt)
{
	//controle de tempo de mudança entre um frame e outro
	
	if(gt2 > changeSprite)
	{
		changeSprite = gt2 + (animDelay * e_animSpeed);
		
		if(level == LEVEL_1)
		{
				EnemyAnimStream(&e_animIndices[2], IMG_AMOUNT, METEOR);
		}
		else if(level == LEVEL_2)
		{
			EnemyAnimStream(&e_animIndices[0], IMG_AMOUNT - E2_AMOUNT - E3_AMOUNT, NORMAL);
			EnemyAnimStream(&e_animIndices[1], IMG_AMOUNT - E3_AMOUNT, OCTOPUS);
		}
		else if(level == FINAL_LEVEL)
		{
			EnemyAnimStream(&bossIndex, 40, BOSS);
		}
	}	
}
void EnemyAnimStream(int *e_animIndex, int amount, enemy_t type)
{
	//trata o fluxo de animação do enemy, nesse caso, como há dois tipos, ele irá mudar frame dos enemies indicados
	//pelo tipo.

	if(*e_animIndex < amount - 1)
	{	
		(*e_animIndex)++;
	}
			
	else
	{
		if(type == NORMAL)
			(*e_animIndex) = 0;	
			
		else if(type == OCTOPUS)
			(*e_animIndex) = amount - E2_AMOUNT;
		
		else if(type == METEOR)
			(*e_animIndex) = E1_AMOUNT + E2_AMOUNT;	
		else if(type == BOSS)
		{
			(*e_animIndex) = 0;
		}	
	}
}

void EnemyUpdate(Enemy *enemy, Player *player,int size, gt_type gt2, double dt)
{
	//trata a animação, desenho e movimento do enemy.
	EnemyAnimController(200.0, enemy, gt2, size, dt);
	DrawEnemies(enemy, size);
	EnemyMovement(enemy, size, dt);
	//trata o tiro do enemy
	VerifyKills();
	
}

void VerifyKills()
{
	if(kills >= killsCount)
	{
		IncreaseSpeed();
	}
}

void IncreaseSpeed()
{
	killsCount += increaseKillCount;
	enemySpeed += 0.5;
	e_animSpeed -= 0.05;
	e_FallSpeed += 2.0;
}

Enemy *AllocEnemyPos(Enemy *enemy, int gridSizeX, int gridSizeY, int size)
{
	//lida com a alocacao de memoria
    int x = 0, y = 0;
    int i = 0, j = 0;
    int aux_size = 0;
	int spacingY = enemyImgsizeY;
	int spacingX = 32;
	
	enemy = (Enemy*)malloc(sizeof(Enemy) * size);
	
    for(x = 0; x < enemyRows; x++)
    {
        for(y = 0; y < enemyCols; y++)
        {
			if(enemyGrid[x][y] == 1)
			{
				aux_size++;
				enemy[aux_size - 1].x = (float) gridSizeX*y + spacingX;
				enemy[aux_size - 1].y = (float) gridSizeY*x;
				enemy[aux_size - 1].y -= spacingY;
				enemy[aux_size - 1].type = x % 2 == 0 ? NORMAL : OCTOPUS;				
			}					
        }
		spacingY -= 4;	
    }
    return enemy;
}

void DrawEnemies(Obj *enemy, int size)
{	
	int i = 0;

	for(i = 0; i < size; i++)
	{	
		if(level == LEVEL_1)
		{
			putimg(enemy[i].x, enemy[i].y, enemyTextures, enemyMskTextures, e_animIndices[2]);
		}
		else if(level == LEVEL_2)
		{
			if(enemy[i].type == NORMAL)
			{
				putimg(enemy[i].x, enemy[i].y, enemyTextures, enemyMskTextures, e_animIndices[0]);
			}
			else if(enemy[i].type == OCTOPUS)
			{
				putimg(enemy[i].x, enemy[i].y, enemyTextures, enemyMskTextures, e_animIndices[1]);
			}
		}	
	}
}		

void EnemyMovement(Enemy *enemy, int size, double dt)
{
	Move(enemy, size, dt);
	DetectWall(enemy,size, dt);
}
void Move(Enemy *enemy, int size, double dt)
{
	int i = 0, j = 0;
	
	//movimenta os enemies na vertical
	
	for(i = 0; i < size; i++)
	{
		enemy[i].x += round(directionX * enemySpeed * dt);
	}		
}

void VerticalMove(Enemy *enemy, int size, double dt)
{	
	int i = 0;
	for(i = 0; i < size; i++)
	{
		enemy[i].y += round(e_FallSpeed * dt);
	}
}
void DetectWall(Enemy *enemy, int size, double dt)
{
	int i = 0;
	float positions[size];
	
	for(i = 0; i < size; i++ )
	{
		positions[i] = enemy[i].x;
	}
	
	BubbleSort(positions, size);
	VerifyPos(enemy, positions, size, dt);
	
}
void VerifyPos(Enemy *enemy, float *positions, int size, double dt)
{
	if(positions[0] <= (float) enemyImgsizeX || positions[size -1] >= (float)gameScreenX - enemyImgsizeX)
	{
		VerticalMove(enemy, size, dt);
		directionX *= -1.0;
	}
}

#endif



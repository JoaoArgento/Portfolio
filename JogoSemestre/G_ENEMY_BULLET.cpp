#if 1 
#include "G_ENEMY_BULLET.h"
#include "G_BOSS.h"

Obj *e_Bullets;

extern int e_BulletIndex;
extern int shieldIndex;
extern LEVEL level;
extern double bossX, bossY;


gt_type E_shootingDelay;
gt_type dmgTimer;
bool E_canShot = true;

void ES_Routine(Player *player, gt_type gt2, Enemy *enemies, int enemySize, int *size, Shield shields[], int s_size, double dt)
{
	int enemyChoosed = 0;

	if(enemySize > 1 && level == LEVEL_2)
	{
		enemyChoosed = ChoosingEnemy(enemySize);
		EnemyShoting(enemies, enemyChoosed, gt2, size);
		
			
	}
	E_UpdateBullet(enemies, player, size, shields, s_size, gt2, dt);
	
	
}
Bullet CreateBossShot()
{
	Bullet B;
	B.x = (float)bossX + 64.0;
	B.y = (float)bossY + 128.0;
	B.speed = 400;
	return B;
}

void B_AllocMem(int *size)
{
	(*size)++;
	e_Bullets = (Bullet*)realloc(e_Bullets, sizeof(Bullet)*(*size));
	e_Bullets[(*size) - 1] = CreateBossShot();
}
void E_UpdateBullet(Enemy *enemies, Player *player, int *size, Shield shields[], int s_size, gt_type gt2, double dt)
{
	bool playerCollided = false;
	bool shieldCollided = false;
	int playersize = 1;

	if(*size > 0)
	{
		playerCollided = DetectCollision(player, e_Bullets, enemies, *size, &playersize,  PLAYER, DEFAULT_SIZE);
		shieldCollided = DetectCollision(player, e_Bullets, shields, s_size, size, SHIELD, DEFAULT_SIZE);
	
		Draw(e_Bullets, size, 5, 10);
		MovementBehavior(e_Bullets, size, dt);
		
		if(playerCollided)
		{	
			e_Bullets = (Bullet*)RemoveObj(player, e_Bullets, size, e_BulletIndex, BULLET);
			DecreaseHealth(player, PLAYER, 0,  gt2);
			
		}
		else if(shieldCollided)
		{
			e_Bullets = (Bullet*)RemoveObj(player, e_Bullets, size, e_BulletIndex, BULLET);
			DecreaseHealth(shields, SHIELD, shieldIndex, gt2);
		}
		e_Bullets = VerifyObjPos(player, e_Bullets, size, BULLET);
	}
}

Obj *VerifyObjPos(Player *player, Obj *objs, int *size,  obj_t type)
{
	int i = 0;

	for(i = 0; i < *size; i++)
	{
		if(objs[i].y >= gameScreenY)
		{
			AllocObj(objs[i].x, gameScreenY - 50);
			objs = (Bullet*)RemoveObj(player, objs, size, i, BULLET);
			if(type == ENEMY)
			{
				(player->hp)--;
			}
		}
	}
	return objs;
}


void DecreaseHealth(void *obj, obj_t type, int index, gt_type gt2)
{
	int dmgDelay = 300;
	
	if(gt2 > dmgTimer)
	{
		dmgTimer = gt2 + dmgDelay;
		
		if(type == PLAYER)
			((Player*)obj)->hp -= 1;
			
		else if(type == SHIELD)
			((Obj*)obj)[index].hp -= 1;	
	}
}

void EnemyShoting(Enemy * enemies, int enemyChoosed, gt_type gt2, int *size)
{
	int delay = 500 + rand() % 500;
	
	if(E_canShot)
	{
		E_shootingDelay = gt2 + delay;
		if(level == FINAL_LEVEL)
		{
			B_AllocMem(size);
		}
		else if(level == LEVEL_2)
		{
			E_AllocMem(enemies, enemyChoosed, size);
		}
	
		E_canShot = false;
		
	}
	if(!E_canShot && gt2 > E_shootingDelay)
	{
		
		E_shootingDelay = gt2 + delay;
		E_canShot = true;	
	}
	
}

void E_AllocMem(Enemy *enemies, int enemyChoosed, int *size)
{
	(*size)++;
	e_Bullets = (Bullet*)realloc(e_Bullets, sizeof(Bullet)*(*size));
	e_Bullets[(*size) - 1] = E_CreateBullet(enemies,enemyChoosed);
}

int ChoosingEnemy(int enemySize)
{
	int enemy_choosed = 0;
	
	srand(time(NULL));
	enemy_choosed = rand() % (enemySize - 1);

	return enemy_choosed;
}

Bullet E_CreateBullet(Enemy *enemies, int e_Choosed)
{
	Bullet e_b;
	e_b.x = enemies[e_Choosed].x + 16;
	e_b.y = enemies[e_Choosed].y + 32;
	e_b.speed = 300;
	return e_b;
}

void Draw(Bullet *obj, int *size, int width, int height)
{
	int i = 0;

	for(i = 0; i < *size; i++)
	{
		setfillstyle(1, RGB(255,0,0));
		bar(obj[i].x, obj[i].y, obj[i].x + width, obj[i].y + height);
	}
}
void MovementBehavior(Bullet *obj, int *size, double dt)
{
	int i = 0;

	for(i = 0; i < *size; i++)
	{
		obj[i].y += obj[i].speed * dt;
	}	
}
#endif



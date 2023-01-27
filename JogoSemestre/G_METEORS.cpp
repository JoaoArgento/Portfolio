#include "G_METEORS.h"
#include "G_ENEMY_BULLET.h"
#include "G_ENEMY.h"


extern Player *player;
extern Bullet *bullets;
extern int bulletIndex;
extern int meteorIndex;
extern int e_animIndices;
extern int kills;
int m_killsCount = 10;
float m_speed = 0;

Meteor *meteors;


gt_type M_SpawnDelay;
float delayToCreate = 1000;
float frameDelay = 150.0;
bool M_canSpawn = true;

Bullet* M_AllocMem(int *size)
{
	(*size)++;
	meteors = (Bullet*)realloc(meteors, sizeof(Bullet) * (*size));
	meteors[(*size) - 1] = M_CreateMeteors();
	
	return meteors;
}

Bullet M_CreateMeteors()
{
	Bullet m;
	m.hp = 3;
	m.x = DEFAULT_SIZE + rand() % (gameScreenX - DEFAULT_SIZE * 2);
	m.y = 0;
	m.speed = 200 + rand() % 150;
	m.frameDelay = 150;
	return m;
}

void M_Spawner(gt_type gt2, int *size)
{ 	
	if(M_canSpawn)
	{
		M_SpawnDelay= gt2 + delayToCreate;
		meteors = M_AllocMem(size);
		M_canSpawn = false;
		
		
	}
	if(!M_canSpawn && gt2 > M_SpawnDelay)
	{
		
		M_SpawnDelay = gt2 + delayToCreate;
		M_canSpawn = true;
		
	}
}
void MeteorUpdate(Player *player, gt_type gt2, int *size, int *v2_size, double dt)
{
	M_Spawner(gt2, size);
	m_speed = 100 + rand() % 50;

	
	if(*size > 0)
	{
		//Draw(meteors, size, 64, 64);
		DrawEnemies(meteors, *size);
		MovementBehavior(meteors, size, dt);
		CollisionControl(player, size, v2_size, gt2);
		meteors = VerifyObjPos(player, meteors, size, ENEMY);
		EnemyAnimController(frameDelay, meteors, gt2, *size, dt);
		IncreaseDifficulty(meteors, m_speed, size, dt);
			
	}
}

void IncreaseDifficulty(Obj *objs, float speed, int *size, double dt)
{
	for(int i = 0; i < *size; i++)
	{
		meteors[i].speed += speed * dt;
		meteors[i].frameDelay--;
		frameDelay = meteors[i].frameDelay;
	}
	
	if(kills >= m_killsCount)
	{
		m_killsCount += 10;
		delayToCreate -= 150;
	}
	
}
void CollisionControl(Player *player, int *size, int *v2_size, gt_type gt2)
{
	bool bulletCollided = false;
	bool playerCollided = false;
	int playersize = 1;
	
	bulletCollided = DetectCollision(player, meteors, bullets, (*size), v2_size, METEORS, DEFAULT_SIZE);
	playerCollided = DetectCollision(player, meteors, bullets, (*size), &playersize, PLAYER, DEFAULT_SIZE);
	
	if(bulletCollided)
	{
		AllocObj(meteors[meteorIndex].x, meteors[meteorIndex].y);
		meteors = (Bullet*)RemoveObj(player, meteors, size, meteorIndex, ENEMY);	
	}
	else if(playerCollided)
	{
		DecreaseHealth(player, PLAYER, 0, gt2);
		AllocObj(meteors[meteorIndex].x, meteors[meteorIndex].y);
		meteors = (Bullet*)RemoveObj(player, meteors, size, meteorIndex, ENEMY);
	}
}


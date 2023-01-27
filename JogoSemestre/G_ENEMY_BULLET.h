#ifndef G_ENEMY_BULLET_H
#define G_ENEMY_BULLET_H
#include "G_BULLET.h"
#include "G_PLAYER.h"
#include <windows.h>
 
typedef struct 
{
	float x, y, speed;
}e_Bullet;

//ES - ENEMY SHOT
//E - ENEMY
int ChoosingEnemy(int enemySize);
void ES_Routine(Player *player, gt_type gt2, Enemy *enemies, int enemySize, int *size, Shield shields[], int s_size, double dt);
void Draw(Bullet *obj, int *size, int width, int height);
void EnemyShoting(Enemy * enemies, int enemyChoosed, gt_type gt2, int *size);
void E_UpdateBullet(Enemy * enemies, Player *player, int *size, Shield shields[], int s_size, gt_type gt2, double dt);
void MovementBehavior(Bullet *obj, int *size, double dt);
void DecreaseHealth(void *obj, obj_t type, int index, gt_type gt2);
Obj *VerifyObjPos(Player *player, Obj *objs, int *size, obj_t type);
void B_AllocMem(int *size);


void E_AllocMem(Enemy *enemies, int enemyChoosed, int *size);
Bullet E_CreateBullet(Enemy *enemies, int enemyChoosed);

#endif

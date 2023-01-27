#ifndef G_METEORS_H
#define G_METEORS_H
#include "G_DECS.h"
#include "G_TYPES.h"
#include "G_BULLET.h" 

#define AMNT_METEOR 50

Bullet* M_AllocMem(int *size);
Bullet M_CreateMeteors();
void M_Spawner(gt_type gt2, int *size);
void MeteorUpdate(Player *player, gt_type gt2, int *size, int *v2_size, double dt);
void CollisionControl(Player *player, int *size, int *v2_size, gt_type gt2);
void IncreaseDifficulty(Obj *objs, float speed, int *size, double dt);
#endif

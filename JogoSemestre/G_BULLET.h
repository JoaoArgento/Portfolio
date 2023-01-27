#ifndef G_BULLET_H
#define G_BULLET_H
#include "G_TYPES.h"
#include "G_SHIELDS.h" 
#include "G_DECS.h"
#include "G_EXPLOSION.h"
#include "G_CONTROLLER.h"
#include "G_PLAYER.h"


#define BULLET_IMG_X 63
#define BULLET_IMG_Y 63
#define B_SS_SIZEX 191
#define B_IMG_AMOUNT 3


//direcoes que a bala pode ir.

//tipos de tiro
typedef enum{
	NORMAL_SHOT = 1, TRIPLE_SHOT = 2, RICOCHETING_SHOT = 3
}b_type;

//vetor da bala

//vetor das imagens da bala.
static imgtype **bulletTextures;
static imgtype **bulletMskTextures;

//variaveis de controle da bullet
//funcoes da bullet
// TS - TRIPLE SHOT
Bullet* AllocMem(Bullet *vector, int *size, Player *player);
Bullet CreateBullet(Player *player, float x, float y, float angle);
void   Shooting(bool *canShoot, Player *player, gt_type gt2, int *size, HWND window);
void   ShootingDelay(bool *canShoot, gt_type gt2);
void   VerifyCursorPos(bool *canShoot, Player *player, gt_type gt2, int *size, HWND window);
void   DrawBullet(Player *player, int size, double dt);
void   BulletUpdate(Enemy* enemies, bool *canShoot, Player *player, gt_type gt2, int *size, HWND window, int *enemysize, Shield shields[], int s_size, double dt);
void   ChangeBulletType(Player *player);
void   CollisionControl(Enemy* enemies,Player *player, gt_type gt2, int *size, int *enemysize, Shield shields[], int s_size);
void   ApplyChanges(b_type type, int amount, bool ricochet);
void   HandleBulletImg();
void   TS_Routine(int i, double dt);
#endif 

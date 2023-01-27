#ifndef G_ENEMY_H
#define G_ENEMY_H
#include "G_TYPES.h"
#include "G_CONTROLLER.h"
#include "G_PLAYER.h"
#include "G_DECS.h"

#define ROWS 5
#define COLS 11
#define IMG_AMOUNT 84
#define E1_AMOUNT 40
#define E2_AMOUNT 4
#define E3_AMOUNT 40
#define E_VariantAmount 3

#define enemyRows 15
#define enemyCols 15
//tamanho do sprite do enemy
#define enemyImgsizeX 63
#define enemyImgsizeY 63
#define SS_sizeY 255

static int enemyGrid[enemyRows][enemyCols] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

};


typedef enum{
	NORMAL = 0, OCTOPUS = 1, METEOR = 2, BOSS = 3
}enemy_t;

//matriz que irá guardar as imagens do enemy
static imgtype **enemyTextures;
static imgtype **enemyMskTextures;


//funções do enemy
void IncreaseSpeed(void);
void VerifyKills(void);
void HandleEnemyImg();
void VerticalMove(Enemy *enemy, int tam, double dt);
void VerifyPos(Enemy *enemy, float *positions, int size, double dt);
void EnemyAnimController(float delay, Obj *enemy, gt_type gt2, int size, double dt);
void EnemyUpdate(Enemy *enemy, Player *player, int size, gt_type gt2, double dt);
void DrawEnemies(Obj *enemy, int size);
void EnemyMovement(Enemy *enemy, int size, double dt);
void DetectWall(Enemy *enemy, int size, double dt);
void Move(Enemy *enemy, int size, double dt);
void EnemyAnimStream(int *e_animIndex, int amount, enemy_t type);
Enemy *AllocEnemyPos(Enemy *enemy, int gridSizeX, int gridSizeY, int size);
#endif

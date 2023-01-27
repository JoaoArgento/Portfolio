#ifndef G_PLAYER_H
#define G_PLAYER_H
#include "G_TYPES.h"
#include "G_DECS.h"
#include "G_IMG_HANDLE.h"

#define playerImgX 64
#define playerImgY 64
#define AMNT_ENEMY 55

typedef struct
{
	int hp;
    int sizeX, sizeY;
    float x, y;
    float speed;
    int points;
    int TS_Points;
    bool tripleshot;
    
}Player;

static imgtype **playerTextures;
static imgtype **playerMskTextures;

void MovementPlayer(Player *player, double dt);
void PlayerSetup(Player *player);
void DrawPlayer(Player *player);
void UpdatePlayer(Player *player, gt_type gt2, double dt);
void HandlePlayerImg();
void PointsToTS(Player *player);
void DrawBar(Player *player);
void DecreaseBar(Player *player, gt_type gt2,  double dt);
void ActiveTS(Player *player);
void textInitialize();
void ShowStatus(Player *player);
void IncreaseSpeed(Player *player);
#endif

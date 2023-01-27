#if 1
#include "G_PLAYER.h"


int pointsToReach = AMNT_ENEMY;
int decreaseDelay = 500;
gt_type decreaseTimer;
float p_speed = 0;
char *pointstxt;
char *healthtxt;
char points[20];
char health[20];

void textInitialize()
{
	pointstxt = NULL;
	healthtxt = NULL;
	pointstxt = (char*)malloc(strlen("Points: 000"));
	healthtxt = (char*)malloc(strlen("Health: 000"));
	
}

void ShowStatus(Player *player)
{
	pointstxt = (char*)realloc(pointstxt,strlen("Points: 000"));
	healthtxt = (char*)realloc(healthtxt,strlen("Health: 000"));
	
	sprintf(points, "%d", player->points);
	sprintf(health, "%d", player->hp);
	
	strcpy(pointstxt, "Points: ");
	strcpy(healthtxt, "Health: ");
	strcat(pointstxt, points);
	strcat(healthtxt, health);
	
	outtextxy(10, 10, pointstxt);
	outtextxy(gameScreenX - 300, 10, healthtxt);
	
	settextstyle(0, HORIZ_DIR, 3);
}	

void UpdatePlayer(Player *player, gt_type gt2, double dt)
{
	MovementPlayer(player, dt);
	DrawPlayer(player);
	DrawBar(player);
	ShowStatus(player);

	if(player->tripleshot && gt2 > decreaseTimer)
	{
		decreaseTimer = gt2 + decreaseDelay;
		DecreaseBar(player, gt2, dt);	
	}	
	if(GetKeyState(VK_SHIFT) & 0x800)
	{
		IncreaseSpeed(player);
	}
	else 
	{
		player->speed = p_speed;
	}
}

void DrawPlayer(Player *player)
{
	putimg(player->x, player->y, playerTextures, playerMskTextures, 0);
}

void DrawBar(Player *player)
{
	if(player->TS_Points > 10)
		player->TS_Points = 10;
	
	if(player->TS_Points > 0)
		bar(5, (gameScreenY - 100 - (player->TS_Points * 16)), 20, gameScreenY - 100);

}

void DecreaseBar(Player *player, gt_type gt2, double dt)
{
	if(player->TS_Points >= 0)
	{
		player->TS_Points -= dt;
	}
	
	if(player->TS_Points <= 0)
		player->tripleshot = false;
}

void PlayerSetup(Player *player)
{
	player->points = 0;
	player->TS_Points = 0;
	player->tripleshot = false;
	player->hp = 50;
	player->sizeX = 63;
    player->sizeY = 63;
    player->x = gameScreenX/2;
    player->y = gameScreenY - player->sizeY;
    player->speed = 400;
    p_speed = player->speed;
}

void IncreaseSpeed(Player *player)
{
	player->speed = 600;
}

void MovementPlayer(Player *player, double dt)
{
    //tratando entrada do usuario
    if((GetKeyState(A) & 0x8000) && player->x > 0)
    {
        player->x -= player->speed * dt;
    }
    if((GetKeyState(D) & 0x8000) && player->x + player->sizeX < gameScreenX)
    {
        player->x += player->speed * dt;        
    }
}
void HandlePlayerImg()
{
	playerTextures = NULL;
	playerMskTextures = NULL;
	
	int playerImgSize = GetImgSize(playerImgX, playerImgY);
	playerTextures = MallocImg(playerTextures, playerImgSize, 2);
	playerMskTextures = MallocImg(playerMskTextures, playerImgSize, 2);
	
	ReadImg((char*)"./Sprites/Player/player.bmp", playerImgX, playerImgY, 0, playerImgX, playerImgY, playerTextures, playerMskTextures, 1);
	removeImgBG(playerMskTextures[0], playerTextures[0], playerImgSize);
} 
#endif




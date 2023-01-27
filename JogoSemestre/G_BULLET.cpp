#if 1
#include "G_BULLET.h"


extern int bulletIndex;
extern int enemyIndex;
Bullet   *bullets;

int delayBetShoots = 300;
int shotType = 1;
int shotAmount = 1;
gt_type shootingDelay;
bool ricochetingShot = false;
float bulletAngle = 180;
int TS_PointsToReach = 10;

Bullet *AllocMem(Bullet *vector, int *size, Player *player)
{
	//guardando a posicao do player.
	float playerPosX = (float)(player->x + player->sizeX) - 63.0;
	float playerPosY = (float)player->y - player->sizeY;
	int i;
	
	for(i = 0; i < shotAmount; i++)
	{
		(*size)++;
   		vector = (Bullet*)realloc(vector, (sizeof(Bullet)*(*size)));
    	vector[(*size) - 1] = CreateBullet(player, playerPosX, playerPosY, bulletAngle);	
    	bulletAngle+= 90.0;
	}
	bulletAngle = 180;  
	
	return vector;   
}

void BulletUpdate(Enemy* enemies, bool *canShoot, Player *player, gt_type gt2, int *size, HWND window, int *enemysize, Shield shields[], int s_size, double dt)
{
	Shooting(canShoot, player, gt2, size, window);
	ChangeBulletType(player);	  
	 
   //só detecta colisao e afins caso exista uma bullet no jogo
	if(*size > 0)
	{
    	CollisionControl(enemies, player, gt2, size, enemysize, shields, s_size);
    	DrawBullet(player, *size, dt);
	}
	
}
void CollisionControl(Enemy* enemies,Player *player, gt_type gt2, int *size, int *enemysize, Shield shields[], int s_size)
{
	bool bulletCollided = false;
	
	int i = 0;
	
	bulletCollided = DetectCollision(player, bullets, enemies, *size, enemysize, ENEMY, DEFAULT_SIZE);
		
		//se colidiu, remove a bala.
		if(bulletCollided)
	    {	
	    	bullets = (Bullet*)RemoveObj(player, bullets, size, bulletIndex, BULLET);
		}
	    for(i = 0; i < *size; i++)
	    {
	    	if(bullets[i].y <= 0)
	    	{
	    		bullets = (Bullet*)RemoveObj(player, bullets, size, i, BULLET);
			}
		}
}

void ChangeBulletType(Player *player)
{	
	if(GetKeyState('1') & 0x8000 && shotType != NORMAL_SHOT)
	{
		ApplyChanges(NORMAL_SHOT, 1, false);
	}
	else if(GetKeyState('2') & 0x8000 && shotType != TRIPLE_SHOT)
	{
		if(player->TS_Points >= TS_PointsToReach)
		{
			player->tripleshot = true;
			ApplyChanges(TRIPLE_SHOT, 3, false);
		}	
	}
	
	else if(GetKeyState('3') & 0x8000 && shotType != RICOCHETING_SHOT)
	{
		ApplyChanges(RICOCHETING_SHOT, 1, true);
	
	}	
	if(!player->tripleshot)
	{
		ApplyChanges(NORMAL_SHOT, 1, false);	
	}			
}
void ApplyChanges(b_type type, int amount, bool ricochet)
{
	shotType = type;
	shotAmount = amount;
	ricochetingShot = ricochet;
}

void Shooting(bool *canShoot, Player *player, gt_type gt2, int *size, HWND window)
{
	VerifyCursorPos(canShoot, player, gt2, size, window);
	ShootingDelay(canShoot, gt2);
}

void VerifyCursorPos(bool *canShoot, Player *player, gt_type gt2, int *size, HWND window)
{
	POINT P;
	
	bool CursorPosInScreen = GetCursorPos(&P) && ScreenToClient(window, &P);
	bool CursorPosInGame = 10 <= P.x && P.x <= gameScreenX && 10 <= P.y && P.y <= gameScreenY;
	bool mouseState = (GetKeyState(VK_LBUTTON) & 0x8000) && *canShoot;
	
	if(CursorPosInScreen && CursorPosInGame) 
	{
		
		if (mouseState)
		{
			shootingDelay = gt2 + delayBetShoots;
            bullets = AllocMem(bullets, size, player);
            sndPlaySound("./SFX/laser.wav", SND_ASYNC);
            *canShoot = false;	
        }		  
	}	
}

void ShootingDelay(bool *canShoot, gt_type gt2)
{
	if(!(*canShoot) && gt2 > shootingDelay)
	{
		
        shootingDelay = gt2 + delayBetShoots;
        *canShoot = true;
 	}	
}
Bullet CreateBullet(Player *player, float x, float y, float angle)
{
    Bullet b;

    b.x = x;
    b.y = y;
    b.speed = 400;
    b.angle = angle * M_PI/180.0;
    b.dir = cos(b.angle);
    b.type = shotType;
    
    if(player->tripleshot)
    {
    	if(round(b.angle) == 3.0)
    		b.imgstyle = b_RIGHT;
    	else if(round(b.angle) == 5.0)
    		b.imgstyle = b_NORMAL;
    	else if(round(b.angle) == 6.0)
    		b.imgstyle = b_LEFT;
	}
	else
		b.imgstyle = b_NORMAL;	
		
    b.collided = false;
    
    return b;
}

void DrawBullet(Player *player, int size, double dt)
{
    int i = 0;
    for(i = 0; i < size; i++)
    {    	
    	putimg(bullets[i].x, bullets[i].y, bulletTextures, bulletMskTextures, bullets[i].imgstyle);
        bullets[i].y -= bullets[i].speed * dt;
        TS_Routine(i, dt);		
    }   
}

void HandleBulletImg()
{
	int i = 0;
	int bulletImgSize = GetImgSize(BULLET_IMG_X, BULLET_IMG_Y);
	
	bulletTextures = NULL;
	bulletMskTextures = NULL;
	
	bulletTextures = MallocImg(bulletTextures, bulletImgSize, B_IMG_AMOUNT);
	bulletMskTextures = MallocImg(bulletMskTextures, bulletImgSize, B_IMG_AMOUNT);
	
	ReadImg((char*)"./Sprites/Bullet/bullet.bmp", BULLET_IMG_X, BULLET_IMG_Y, 0, B_SS_SIZEX, BULLET_IMG_Y, bulletTextures, bulletMskTextures, B_IMG_AMOUNT);
	
	for(i = 0; i < B_IMG_AMOUNT; i++)
	{
		removeImgBG(bulletMskTextures[i], bulletTextures[i], bulletImgSize);
	}
	
}

void TS_Routine(int i, double dt)
{
	if(bullets[i].type == TRIPLE_SHOT)
    { 	
    	if(bullets[i].x <= 0 || bullets[i].x >= gameScreenX - BULLET_IMG_X)
		{
			bullets[i].collided = true;
			bullets[i].dir = -(cos(bullets[i].angle));	
			bullets[i].imgstyle = bullets[i].imgstyle == b_LEFT ? bullets[i].imgstyle = b_RIGHT :  bullets[i].imgstyle = b_LEFT;
		}
    	bullets[i].x = bullets[i].x - bullets[i].dir * bullets[i].speed * dt;
	}
}

#endif




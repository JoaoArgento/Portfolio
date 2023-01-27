#include "G_PLAYER.h"
#include "G_SHIELDS.h"
#include "G_CONTROLLER.h"   
#include "G_ENEMY.h"         
#include "G_BULLET.h"    
#include "G_TYPES.h" 
#include "G_ENEMY_BULLET.h" 
#include "G_IMG_HANDLE.h"
#include "G_EXPLOSION.h"
#include "G_METEORS.h"
#include "G_MENU.h"
#include "G_BOSS.h"

imgtype **bgs;
//variaveis externas que estão em outra unidade de tradução
extern Bullet *bullets;
extern Meteor *meteors;
extern Bullet *e_Bullets;
extern Obj *enemies;
extern int kills;
extern int explosionSize;
int enemySize = 55;
int bulletSize = 0;
int enemyBulletSize = 0;

//variaveis do player.
Player player;
int initialPlayerHP = 50;
int bossHp = 100;
int b_MeteorSize = 0;
//setup inicial do grid de enemies
int gridSizeX = gameScreenX/enemyRows;
int gridSizeY = gameScreenY/enemyCols;

//variaveis de controle de audio e level
LEVEL level = MENU;
gt_type changingLevelDelay;
int levelDelay = 300;
bool canChangeLevel = false;

bool running = true;



double bossX = widht/2 - imgWidht, bossY = 50;

int main()
{
	Game();
    return 0;
}

 
void Game()
{
	//instancia das structs;
	Shield shields[3];
	//dt - controle de tempo
    double dt;
    
    //variaveis
    int page = 1;
    //variaveis de controle
    int i, j, k;
    char key = 0;
    
    //variaveis de controle com o mouse
    POINT P; 
    HWND window; 

    //variaveis de controle de tamanho
   
    int v_ShieldSize = 3; 
   
    //variaveis do tiro
    bool canShoot = true;
    bool canPlayAudio1 = true;
    bool canPlayAudio2 = true;
    bool canPlayAudio3 = true;
    //controle o background
    int BG_Sprite = 4;
    int BG_Delay = 500;
    

    //variaveis do enemy
    bool canMove = true;
    bool canChangeBG = true;
    bool bossCollided = false;
   
    //variaveis de colisao
    float distance = 0;   
 
 

    // FPS
    gt_type gt1, gt2, shootingDelay, changeBGdelay;

    //inicializando os objetos da fase.
   	SetupObjects();
     
    //adquirindo o  tamanho da tela. 
    screenSizeX = GetSystemMetrics(SM_CXSCREEN); 
    screenSizeY = GetSystemMetrics(SM_CYSCREEN);  

    //setando a posicao inicial do player
    PlayerSetup(&player);

    //alocando a posição dos enemies antes do jogo iniciar
    enemies = AllocEnemyPos(enemies, gridSizeX, gridSizeY, enemySize);
    
   	InitializeArray(shields, v_ShieldSize);
  
    //inicialiizando a tela grafica
    initwindow(gameScreenX, gameScreenY, "teste", (int)(screenSizeX - gameScreenX)/2, (int)(screenSizeY - gameScreenY)/2);
  	
  	handleBossImage();
  	LoadSounds();
  	
  	int bgSize = GetImgSize(gameScreenX, gameScreenY);
  	bgs = MallocImg(bgs, bgSize, BG_AMOUNT);
  	
  	LoadBGImg();
  	
	//setando as imagens padrões do player e enemy
	HandleImgs(); 
	textInitialize();

    gt1 = GetTickCount();
	window = GetForegroundWindow();
	

    while(running)  
    {
			
        gt2 = GetTickCount();
        
        dt = (double)(gt2 - gt1)/1000.0;
 
        if(gt2 - gt1 > 1000/FPS)
        {
   
            //altera o valor da page entre 1 e 2
            page = page == 1 ? page = 2 : page = 1;

            //resolve o problema do flickering
            setactivepage(page);
            cleardevice();
            		
			if(player.hp > 0)
			{
			
				if(level == MENU)
				{
					menu();
					
				}
				else if(level == SELECAO)
				{
					selecao();
					
				}
				
				else if(level == CREDITOS)
				{
					ComoJogar();
				}
				
				else if(level == LEVEL_1)
				{
					PlayMusic("play level1 repeat","seek level1 to start", &canPlayAudio1);
					putimage(0,0, bgs[2], COPY_PUT);
					enemySize = 0;
					MeteorUpdate(&player, gt2, &b_MeteorSize, &bulletSize, dt);
					NextLevel(AMNT_METEOR, LEVEL_2, &enemySize, 55);
							
				}
				else if(level == LEVEL_2)
				{

					PlayMusic("play level2 repeat","seek level2 to start", &canPlayAudio2);
					putimage(0,0, bgs[1], COPY_PUT);
					UpdateObj(shields, v_ShieldSize);
					NextLevel(AMNT_ENEMY, SELECAO, &enemySize, 0);
					EnemyUpdate(enemies, &player, enemySize, gt2, dt);
					ES_Routine(&player, gt2, enemies, enemySize, &enemyBulletSize, shields, v_ShieldSize, dt);		
				}
				
				else if(level == FINAL_LEVEL)
				{
					
					PlayMusic("play boss repeat","seek boss to start", &canPlayAudio3);
					putimage(0,0, bgs[3], COPY_PUT);
					enemySize = 0;
					
					if(bossHp > 0)
					{
						EnemyAnimController(100.0, enemies, gt2, 1, dt);
						ES_Routine(&player, gt2, enemies, 1, &enemyBulletSize, shields, v_ShieldSize, dt);
						EnemyShoting(enemies, 0, gt2, &enemyBulletSize);
						bossBehaviour(&bossX, &bossY);
					
						bossCollided = BossCollision(bullets, &bulletSize, bossX, bossY);
						
						if(bossCollided)
						{
							bossHp -= 10;
							AllocObj(bossX, bossY);
						
						}
						bar(gameScreenX/3, 20,gameScreenX/3.0 + bossHp * 3, 40);
					
					}
					else
					{
						return;	
					}				
							
				}
				else if(level == SAIR)
				{
					return;
				}
				//else if()
				if(level != MENU && level != SELECAO && level != CREDITOS && level != COMO_JOGAR)
				{
					BulletUpdate(enemies, &canShoot, &player, gt2, &bulletSize, window, &enemySize, shields, v_ShieldSize, dt);
					UpdatePlayer(&player, gt2, dt);				
					UpdateEffects();	
				}		
			}	
			else
			{
				StopSounds();
        		
        		canPlayAudio1 = true;
        		canPlayAudio2 = true;
        		canPlayAudio3 = true;
        		canShoot = true;
        		
				if(canChangeBG)
				{
					changeBGdelay = gt2 + BG_Delay;
					BG_Sprite = BG_Sprite == 4 ? BG_Sprite = 5 : BG_Sprite = 4;
					canChangeBG = false;
					
				}
				if(!canChangeBG && gt2 > changeBGdelay)
				{
					changeBGdelay = gt2 + BG_Delay;
					canChangeBG = true;
				}
				putimage(0, 0, bgs[BG_Sprite], COPY_PUT);
				
				if(GetKeyState(VK_SPACE) & 0x800)
				{
					
					changingLevelDelay = gt2 + levelDelay;
					canChangeLevel = true;
				}	
	
				if(canChangeLevel && gt2 > changingLevelDelay)
				{
					player.hp = 1;
					player.TS_Points = 0;
					kills = 0;
					if(level == LEVEL_1)
					{
						
						b_MeteorSize = 0;
					}
					
					else if(level == LEVEL_2)
					{
						
						enemySize = 55;
						enemyBulletSize = 0;
						InitializeArray(shields, v_ShieldSize);
						enemies = AllocEnemyPos(enemies, gridSizeX, gridSizeY, enemySize);
					}
					
					bulletSize = 0;
					explosionSize = 0;	
					changingLevelDelay = gt2 + levelDelay;
					canChangeLevel = false;
				}
					
			}
				  
            setvisualpage(page);
             
            fflush(stdin);
            if(kbhit())
            {  
            	key = getch();
			}   
			 
			gt1 = gt2;
		
        }
    }
    
    
    running = false;
    free(bullets);
    free(enemies);
    free(e_Bullets);
    //FreePointer(enemypaths, STRING_SIZE);
    //FreePointer(playerpaths, STRING_SIZE);
    free(playerTextures);
    free(playerMskTextures);
    free(shieldTextures);
    free(shieldMskTextures);
    free(enemyTextures);
    free(enemyMskTextures);
}

void NextLevel(int amount, LEVEL l, int *enemySize, int e_amount)
{
	if(kills >= amount)
	{
		kills = 0;
		level = l;
		*enemySize = e_amount;
	}
		
}

void PlayMusic(const char *music, const char*seek, bool *canPlayAudio)
{
	if(*canPlayAudio)
	{
		mciSendString(seek, NULL, 0, 0);
		mciSendString(music, NULL, 0, 0);	
		*canPlayAudio = false;
	}
	
}
bool BossCollision(Bullet * bullets, int *bulletSize, double bossX, double bossY)
{
	int i = 0;
	float distance, x, y;
	bool collided = false;

	for(i=0; i < *bulletSize; i++)
	{
			x = pow((bullets[i].x - bossX), 2);
			y = pow((bullets[i].y - bossY), 2);
				
			distance = sqrt(x + y);
			
			if(distance <= DEFAULT_SIZE)
			{
				collided = true;
				bullets = RemoveObj(&player, bullets, bulletSize, i, BULLET);
			}
				
	}
	return collided;
}
void SetupObjects()
{
	bullets = NULL;
    enemies = NULL;
 	explosions = NULL;
 	meteors = NULL;
 
    //bullets = (Bullet *)malloc(sizeof(Bullet) * 1);
    //enemies = (Enemy *)malloc(sizeof(Enemy) * 1); 
    //explosions = (explosion *)malloc(sizeof(explosion) * 1);
}


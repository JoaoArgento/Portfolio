#ifndef G_CONTROLLER_H
#define G_CONTROLLER_H
#include "G_DECS.h"
#include "G_PLAYER.h"



typedef struct
{
	float x, y;	
	
} Vector2;


void InitialScreen(void);
void Credits(void);
void LoadingScreen(void);
void HowToPlay(void);
void LevelOne(void);
void Game(void);
void LevelThree(void);
void FinalLevel(void);

void InitializeVetor(void);
void BubbleSort(float *positions, int size);
void VerifyKeyReleased(char key, bool *k_Pressed);
void FreePointer(char *pointer[], int size);
bool DetectCollision(Player *player, Obj *v1, Obj *v2, int v1_size,  int *v2_size, obj_t type, int targetSize);
bool BossCollision(Bullet * bullets, int *bulletSize, double bossX, double bossY);
Obj *RemoveObj(Player *player, Obj *objs,  int *size, int entityCollided, obj_t type);
void SetupObjects();
void NextLevel(int amount, LEVEL l, int *enemySize, int amnt_enemy);
void ResetLevel(int *enemySize, gt_type gt2, int gridSizeX, int gridSizeY);
void LoadSounds();
void PlayMusic(const char *music, const char*seek, bool *canPlayAudio);
void StopSounds();

#endif

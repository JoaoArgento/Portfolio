#ifndef G_DEF_H
#define G_DEF_H

#include <stdio.h>
#include <time.h>
#include <graphics.h>
#include <math.h>

//constantes
#define FPS 30
//constants de imgs
#define STRING_SIZE 3
#define DEFAULT_SIZE 64
#define BG_AMOUNT 6

//global variables
//constantes das keys
#define A 0x41
#define D 0x44
#define W 0x57
#define S 0x53

typedef enum 
{
	b_NORMAL = 0, b_LEFT = 1, b_RIGHT = 2
	
}bulletImg_t;

typedef struct Obj
{
	float x, y, speed, angle, dir, frameDelay;
	int type, hp, animIndex, sizex, sizey; 
	bool collided, death;
	bulletImg_t imgstyle;

}Bullet, Meteor, Enemy, Shield, Boss;

/*E = ENEMY*/
#define E 1

//carregando os audios .mp3

//mciSendString("open .\\sons\\led.mp3 type MPEGVideo alias fundo", NULL, 0, 0);   
//mciSendString("open .\\sons\\my.mp3 type MPEGVideo alias fundo2", NULL, 0, 0); 

//definindo a resolucao padrao da tela
/*TODO
implementar a resolucao dinamica da tela.
*/
static int gameScreenX = 1024;
static int gameScreenY = 896;
static int screenSizeX = 0; 
static int screenSizeY = 0;


#endif

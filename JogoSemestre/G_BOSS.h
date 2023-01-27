#pragma once
#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <cmath>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "G_TYPES.h"
#include "G_IMG_HANDLE.h"
#include "G_DECS.h"

#define BOSS_IMG_AMOUNT 40
static int widht = 1024, height = 800;
static int imgWidht = 210, imgHeight = 290;
static int passoX = 5, passoY = 5;
static double ang = 0, angC = 0, sinBehaviour = rand()%3, sinBehaviourFactor = 0;
static double circX = widht/2 - 20, circY = 50, circdX = widht/2 - 20, circdY = 50, circddX = widht/2 - 20, circddY = 50;
static void *imgBoss;
static int bossSize = 0;
static int timer = 0;
static imgtype **bossTextures;
static imgtype **bossMskTextures;
extern int bossIndex;



static void handleBossImage(){
	bossTextures = NULL;
	bossMskTextures = NULL;
	int bossSize = GetImgSize(127, 127);
	int i = 0;
	
	bossTextures = MallocImg(bossTextures,bossSize, BOSS_IMG_AMOUNT);
	bossMskTextures = MallocImg(bossTextures,bossSize, BOSS_IMG_AMOUNT);
	
    ReadImg((char*)"./Sprites/Enemies/boss.bmp", 127, 127, 0, 1023, 639,bossTextures, bossMskTextures, 40);
    
    for(i = 0; i < 40; i++)
    {
		removeImgBG(bossMskTextures[i], bossTextures[i], bossSize);
	}
}

static void bossBehaviour(double *bossX, double *bossY){
	//Alternancia entre comporbossSizeentos
	sinBehaviour = rand()%3;
            if(timer == 0)
            {
                timer = 180;
                if(sinBehaviour == 0)
                {
                    sinBehaviourFactor = 5;
                }

                else if(sinBehaviour == 1)
                {
                    sinBehaviourFactor = 10;
                }

                else if(sinBehaviour == 2)
                {
                    sinBehaviourFactor = 15;
                }
            }
    
    //Efeito de teleporte entre cantos
    if(*bossX <= 0 - imgWidht){
                *bossX = widht;
            }else if(*bossX >= widht){
                *bossX = 0 - imgWidht;
            }else{
                ang += 0.05;
            }
            
    //Movimento de seno
    angC += 0.2;
    *bossX += sin(ang)*sinBehaviourFactor;
    
    if(ang == 360){ang = 0;}
    if(angC == 360){angC = 0;}
    
    putimage(*bossX,*bossY, bossTextures[bossIndex], AND_PUT);
    putimage(*bossX,*bossY, bossMskTextures[bossIndex], OR_PUT);
    
    //Timer dos behaviours
    timer--;
}


#define G_BOSS

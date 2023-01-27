#pragma once
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include"G_MENU3D.h"
#include "G_TYPES.h"

int Width = 1024, Height = 896;
int ButtonW = 117 , ButtonH = 57;
int page = 1;
unsigned long long gt2, gt1;

extern LEVEL level;
extern bool running;
int tela = 1;
void Home();
void Creditos();
void SelecaoFases();
void ComoJogar();

int menu() {
  Home();
}

void Home(){
	StopSounds();
    bool jogando = TRUE;
    int tam;
    void *imgHome, *btnSelecao, *btnCreditos, *btnSair, *btnComoJogar;
    POINT MousePos;
    HWND screen;
    char teste[50];
    strcpy(teste, "Teste");

    tam = imagesize(0, 0, Width-1, Height-1);
    imgHome = malloc(tam);
    readimagefile(".\\Sprites\\Menu\\homescreen.bmp", 0, 0, Width-1, Height-1);
    getimage(0, 0, Width-1, Height-1, imgHome);

    tam = imagesize(0, 0, ButtonW, ButtonH);
    btnSelecao = malloc(tam);
    readimagefile(".\\Sprites\\Menu\\selecao.bmp", 0, 0, ButtonW, ButtonH);
    getimage(0, 0, ButtonW, ButtonH, btnSelecao);

    tam = imagesize(0, 0, ButtonW, ButtonH);
    btnSair = malloc(tam);
    readimagefile(".\\Sprites\\Menu\\sair.bmp", 0, 0, ButtonW, ButtonH);
    getimage(0, 0, ButtonW, ButtonH, btnSair);

    tam = imagesize(0, 0, ButtonW, ButtonH);
    btnCreditos = malloc(tam);
    readimagefile(".\\Sprites\\Menu\\creditos.bmp", 0, 0, ButtonW, ButtonH);
    getimage(0, 0, ButtonW, ButtonH, btnCreditos);

    tam = imagesize(0, 0, ButtonW, ButtonH);
    btnComoJogar = malloc(tam);
    readimagefile(".\\Sprites\\Menu\\comojogar.bmp", 0, 0, ButtonW, ButtonH);
    getimage(0, 0, ButtonW, ButtonH, btnComoJogar);

    gt1 = GetTickCount();

    screen = GetForegroundWindow();
    while(jogando){
        gt2 = GetTickCount();

        if(gt2 - gt1 > 1000/60){
            gt1 = gt2;

            setactivepage(page);
            setvisualpage(1-page);
            cleardevice();

            setbkcolor(COLOR(33,33,33));

            putimage(0, 0, imgHome, COPY_PUT);
            putimage(Width/2-ButtonW/2, 100, btnSelecao, COPY_PUT);
            putimage(Width/2-ButtonW/2 + 400, 50, btnSair, COPY_PUT);
            putimage(Width/2-ButtonW/2, 700, btnComoJogar, COPY_PUT);
            

            if (GetCursorPos(&MousePos))
            {			
	                if (ScreenToClient(screen, &MousePos)) {
	                	
	                if(GetKeyState(VK_LBUTTON)&0x80) {
	                  if (Width/2-ButtonW/2 <= MousePos.x && MousePos.x <= Width/2-ButtonW/2+ButtonW && 100 <= MousePos.y && MousePos.y <= 100+ButtonH)
	                  {
	                  	level = SELECAO;
	                    break;
					  }   
	                }
	
	                if(GetKeyState(VK_LBUTTON)&0x80) {
	                  if (Width/2-ButtonW/2+400 <= MousePos.x && MousePos.x <= Width/2-ButtonW/2+ButtonW+400 && 50 <= MousePos.y && MousePos.y <= 50+ButtonH)
	                  {
	                  	jogando = FALSE;
	                  	level = SAIR;
	              
	         
					  }
	     
	                }
	
	                if(GetKeyState(VK_LBUTTON)&0x80) {
	                  if (Width/2-ButtonW/2 <= MousePos.x && MousePos.x <= Width/2-ButtonW/2+ButtonW && 700 <= MousePos.y && MousePos.y <= 700+ButtonH)
	                    ComoJogar();
                	}
            	}
			}
            page = 1 - page;
        }
    }
}

void Creditos(){
    bool jogando = TRUE;
    int tam;
    void *imgCreditos, *btnMenu;
    POINT MousePos;
    HWND screen;

    tam = imagesize(0, 0, Width-1, Height-1);
    imgCreditos = malloc(tam);
    readimagefile(".\\Sprites\\Menu\\telacreditos.bmp", 0, 0, Width-1, Height-1);
    getimage(0, 0, Width-1, Height-1, imgCreditos);

    tam = imagesize(0, 0, ButtonW, ButtonH);
    btnMenu = malloc(tam);
    readimagefile(".\\Sprites\\Menu\\menu.bmp", 0, 0, ButtonW, ButtonH);
    getimage(0, 0, ButtonW, ButtonH, btnMenu);

    gt1 = GetTickCount();

    screen = GetForegroundWindow();
    while(jogando){
        gt2 = GetTickCount();

        if(gt2 - gt1 > 1000/60){
            gt1 = gt2;

            setactivepage(page);
            setvisualpage(1-page);
            cleardevice();

            putimage(0, 0, imgCreditos, COPY_PUT);
            putimage(Width/2-ButtonW/2+200, 700, btnMenu, COPY_PUT);

            if (GetCursorPos(&MousePos))
                if (ScreenToClient(screen, &MousePos)) {

                if(GetKeyState(VK_LBUTTON)&0x80) {
                  if (Width/2-ButtonW/2+200 <= MousePos.x && MousePos.x <= Width/2-ButtonW/2+200+ButtonW && 700 <= MousePos.y && MousePos.y <= 700+ButtonH)
                  {
                  	jogando = FALSE;
                    closegraph();
				  }
                    
                }
            }

            page = 1 - page;
        }
    }
}

void ComoJogar(){
    bool jogando = TRUE;
    int tam;
    void *imgComoJoga, *btnMenu;
    POINT MousePos;
    HWND screen;

    tam = imagesize(0, 0, Width-1, Height-1);
    imgComoJoga = malloc(tam);
    readimagefile(".\\Sprites\\Menu\\telacomojoga.bmp", 0, 0, Width-1, Height-1);
    getimage(0, 0, Width-1, Height-1, imgComoJoga);

    tam = imagesize(0, 0, ButtonW, ButtonH);
    btnMenu = malloc(tam);
    readimagefile(".\\Sprites\\Menu\\menu.bmp", 0, 0, ButtonW, ButtonH);
    getimage(0, 0, ButtonW, ButtonH, btnMenu);

    gt1 = GetTickCount();

    screen = GetForegroundWindow();
    while(jogando){
        gt2 = GetTickCount();

        if(gt2 - gt1 > 1000/60){
            gt1 = gt2;

            setactivepage(page);
            setvisualpage(1-page);
            cleardevice();

            putimage(0, 0, imgComoJoga, COPY_PUT);
            putimage(Width/2-ButtonW/2+200, 700, btnMenu, COPY_PUT);

            if (GetCursorPos(&MousePos))
	        {
	                if (ScreenToClient(screen, &MousePos)) {
	
	                if(GetKeyState(VK_LBUTTON)&0x80) {
	                  if (Width/2-ButtonW/2+200 <= MousePos.x && MousePos.x <= Width/2-ButtonW/2+200+ButtonW && 700 <= MousePos.y && MousePos.y <= 700+ButtonH)
	                  {
	                  	jogando = FALSE;
	                  	level = MENU;
					  }
	                    
                	}
            }

            	page = 1 - page;
       	 }
    	}
	}
}
#define G_MENU

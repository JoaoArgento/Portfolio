#pragma once
#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <cmath>
#include<stdio.h>
#include<conio.h>
#include"G_MENU.h"
#include "G_DECS.h"



//constantes.
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define TEXTURE_WIDTH 128
#define TEXTURE_HEIGHT 128
#define MAP_WIDTH 13
#define MAP_HEIGHT 11

const int SCREEN_RESX = 1024; //GetSystemMetrics(SM_CXSCREEN);
const int SCREEN_RESY = 896; //GetSystemMetrics(SM_CYSCREEN);

extern LEVEL level;
extern int enemySize;
extern Obj* enemies;
extern int gridSizeX;
extern int gridSizeY;
extern int b_MeteorSize;
extern int enemyBulletSize;


//Img que será desenhada na tela.
unsigned char *img;
unsigned tam;
int tamX = 127, tamY = 127;

//posição do player
double playerX = 8.0, playerY = 6.5;
double dirX = -1.0, dirY = 0; // direção que o player está olhando
double planeX = 0, planeY = 0.66; // angulo que irá ser criado os raios
char textoportal[50];
char textoteste[50];
POINT MousePos;
HWND screen;
//matriz de texturas.


//matriz que contem o mapa do game.
int map[MAP_WIDTH][MAP_HEIGHT] =
{
  {1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,5,6,7,1,1,1,1},
  {1,1,1,0,0,0,0,0,1,1,1},
  {1,1,0,0,0,0,0,0,0,1,1},
  {1,1,0,0,0,0,0,0,0,1,1},
  {1,1,1,0,0,0,0,0,1,1,1},
  {1,1,0,0,0,0,0,0,0,1,1},
  {1,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,1,1},
  {1,1,1,0,0,0,0,0,1,1,1},
  {1,1,1,2,1,1,1,4,1,1,1},
};

void ReadImgs(unsigned int texture[8][TEXTURE_WIDTH * TEXTURE_HEIGHT]);
void DrawMap(unsigned int texture[8][TEXTURE_WIDTH * TEXTURE_HEIGHT]);


int selecao()
{
	StopSounds();
	//printf("%d\n", factorScale);

	//variaveis de controle
	int page = 1;
	unsigned long long gt2, gt1;
	//matriz que guarda as texturas.
	unsigned int texture[8][TEXTURE_WIDTH * TEXTURE_HEIGHT];

	//inicializando a tela grafica.
	strcpy(textoportal, "Aperte espa�o para entrar na fase");
	strcpy(textoteste, "Funcionou");

	//lendo as imagens
	ReadImgs(texture);

	gt1 = GetTickCount();

	while(true)
	{
		gt2 = GetTickCount();

		if(gt2 - gt1 > 1000/60)
		{
			gt1 = gt2;
			page = page == 1 ? page = 2 : page = 1;
			setactivepage(page);
			cleardevice();

			DrawMap(texture);
                	
            if(playerX >=11 && playerX <= 12 && playerY >= 3 && playerY <= 4){
			outtextxy(SCREEN_RESX/3, 300, textoportal);
				
			if(GetKeyState(VK_SPACE)&0x80) {
				StopSounds();
               	level = LEVEL_1;  
				break;	
                }
			}
			
			if(playerX >=11 && playerX <= 12 && playerY >= 7 && playerY <= 8){
			outtextxy(SCREEN_RESX/3, 300, textoportal);
				
			if(GetKeyState(VK_SPACE)&0x80) {
				StopSounds();
				enemyBulletSize = 0;
				level = LEVEL_2;
                break;
                }
			}
			
			if(playerX >=1 && playerX <= 3 && playerY >= 4 && playerY <= 7){
			outtextxy(SCREEN_RESX/4, 300, textoportal);
				
			if(GetKeyState(VK_SPACE)&0x80) {
				StopSounds();
				enemyBulletSize = 0;
				level = FINAL_LEVEL;
				break;
                }
			}
            
    	
			setvisualpage(page);

			double speed = 0.1;
			double rotationSpeed = 0.1;

			if(GetKeyState(W) &	0x8000)
			{
				if(map[int(playerX + dirX * speed)][int(playerY)] == 0)
				{
					playerX += dirX * speed;
				}


				if(map[int(playerX)][int(playerY + dirY * speed)] == 0)
				{
					playerY += dirY * speed;
				}

				if(map[int(playerX + dirX * speed)][int(playerY)] != 0)
				{
					playerX -= dirX * speed;
					playerY -= dirY * speed;
				}

			}
			if(GetKeyState(S) & 0x8000)
			{
				if(map[int(playerX - dirX * speed)][int(playerY)] == 0)
				{
					playerX -= dirX * speed;
				}
				if(map[int(playerX)][int(playerY - dirY * speed)] == 0)
				{
					playerY -= dirY * speed;
				}
				if(map[int(playerX + dirX * speed)][int(playerY)] != 0)
				{
					playerX += dirX * speed;
					playerY += dirY * speed;
				}
			}

			if(GetKeyState(D) & 0x8000)
			{
				double oldDirX = dirX;
				dirX = dirX * cos(-rotationSpeed) - dirY * sin(-rotationSpeed);
				dirY = oldDirX *sin(-rotationSpeed) + dirY * cos(-rotationSpeed);
				double oldPlaneX = planeX;
				planeX = planeX * cos(-rotationSpeed) - planeY * sin(-rotationSpeed);
				planeY = oldPlaneX * sin(-rotationSpeed) + planeY * cos(-rotationSpeed);
			}
			if(GetKeyState(A) & 0x8000)
			{
				double oldDirX = dirX;
				dirX = dirX * cos(rotationSpeed) - dirY * sin(rotationSpeed);
				dirY = oldDirX *sin(rotationSpeed) + dirY * cos(rotationSpeed);
				double oldPlaneX = planeX;
				planeX = planeX * cos(rotationSpeed) - planeY * sin(rotationSpeed);
				planeY = oldPlaneX * sin(rotationSpeed) + planeY * cos(rotationSpeed);
			}

		}
	}

}

void ReadImgs(unsigned int texture[8][TEXTURE_WIDTH * TEXTURE_HEIGHT])
{
	readimagefile(".\\Sprites\\Menu\\ShipWall2.bmp", 0, 0, tamX, tamY);
	getimage(0,0, tamX, tamY, texture[0]);
	cleardevice();
	
	readimagefile(".\\Sprites\\Menu\\Portal1BMP.bmp", 0, 0, tamX, tamY);
	getimage(0,0, tamX, tamY, texture[1]);
	cleardevice();
	
	readimagefile(".\\Sprites\\Menu\\Portal2BMP.bmp", 0, 0, tamX, tamY);
	getimage(0,0, tamX, tamY, texture[2]);
	cleardevice();
	
	readimagefile(".\\Sprites\\Menu\\Portal3BMP.bmp", 0, 0, tamX, tamY);
	getimage(0,0, tamX, tamY, texture[3]);
	cleardevice();
	
	readimagefile(".\\Sprites\\Menu\\Buraco_Negro_Direita_BMP.bmp", 0, 0, tamX, tamY);
	getimage(0,0, tamX, tamY, texture[4]);
	cleardevice();
	
	readimagefile(".\\Sprites\\Menu\\Buraco_Negro_Centro_BMP.bmp", 0, 0, tamX, tamY);
	getimage(0,0, tamX, tamY, texture[5]);
	cleardevice();
	
	readimagefile(".\\Sprites\\Menu\\Buraco_Negro_Esquerda_BMP.bmp", 0, 0, tamX, tamY);
	getimage(0,0, tamX, tamY, texture[6]);
	cleardevice();
}

void DrawMap(unsigned int texture[8][TEXTURE_WIDTH * TEXTURE_HEIGHT])
{
	int scaleFactor = SCREEN_RESX / SCREEN_WIDTH;
	int scaleFactorY = SCREEN_RESY / SCREEN_HEIGHT;

	for(int r = 0; r < SCREEN_WIDTH; r++)
	{
		//criando o campo de visualização do player
		double cameraX = 2 * r /double(SCREEN_WIDTH) - 1;
		//definindo as direções do raio.
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		//definindo a posição do player no map
		int mapX = int(playerX);
		int mapY = int(playerY);

		//distancia do player entre a primeira reta vertical e horizontal
		double sideDistX;
		double sideDistY;

		//distancia entre duas retas verticais / horizontais
		double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1/rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1/rayDirY);
		//distancia entre a parede encontrada e a camera que está atrás do player
		double perpWallDist;

		//incrementa no X ou no Y, de acordo de qual reta é a menor
		int stepX;
		int stepY;

		//variavel de controle de quando hittar uma parede
		bool hit = false;
		//variavel que guarda o lado que bateu.
		int side;

		//se for menor que 0, quer dizer que o raio está indo para esq
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (playerX - mapX) * deltaDistX;

		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - playerX) * deltaDistX;
		}
		// mesma coisa com o y.
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY  = (playerY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - playerY) * deltaDistY;
		}

		//enquanto não encontrar uma parede, roda o algoritimo DDA.
		while(!hit)
		{
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;

			}
			//se for maior que 0, quer dizer que foi encontrado uma parede
			if(map[mapX][mapY] > 0)
			{
				hit = true;
			}
		}
		if(side == 0)
		{
			perpWallDist = (sideDistX - deltaDistX);
		}
		else
		{
			perpWallDist = (sideDistY - deltaDistY);
		}

		//define o tamanho da linha, inicio de onde se deve desenhar e o fim.
		int lineHeight = (int)(SCREEN_HEIGHT/perpWallDist);
		int drawStart = -lineHeight/2 + SCREEN_HEIGHT/2;
		int drawEnd = lineHeight/2 + SCREEN_HEIGHT/2;

		//texturizando as paredes
		int textureIndex = map[mapX][mapY] - 1;
		double wallX;

		if(side == 0)
		{
			wallX = playerY + perpWallDist * rayDirY;
		}
		else
		{
			wallX = playerX + perpWallDist * rayDirX;
		}
		wallX -= floor(wallX);

		int textureX = int(wallX * double(TEXTURE_WIDTH));

		if(side == 0 && rayDirX > 0) textureX = (TEXTURE_WIDTH - textureX - 1) + 6;
		if(side == 0 && rayDirX < 0) textureX = (TEXTURE_WIDTH - textureX - 1) + 6;
		if(side == 1 && rayDirY < 0) textureX = (TEXTURE_WIDTH - textureX - 1) + 6;
		if(side == 1 && rayDirY > 0) textureX = (TEXTURE_WIDTH - textureX - 1) + 6;

		//0.12 - FULL HD;
		// 0.25 - 640x480
		//0.5 - 320x200
		//0.165 - 1280x720

		double step = 0.165 * (double)TEXTURE_HEIGHT / lineHeight;
		double texturePos = (drawStart - SCREEN_HEIGHT/2 + lineHeight/2) * step;

		//desenhando as paredes

		tam = imagesize(r*scaleFactor, drawStart*scaleFactorY, r*scaleFactor + 1,  drawEnd*scaleFactorY);
		img = (unsigned char*)realloc(img, tam);
		getimage(r*scaleFactor, drawStart*scaleFactorY, r*scaleFactor + 1, drawEnd*scaleFactorY, img);

		for(int y = 24; y < tam; y+=4)
		{
			int textureY = (int)texturePos & (TEXTURE_HEIGHT - 1);
			texturePos += step;
			unsigned color = texture[textureIndex][TEXTURE_HEIGHT * textureY + textureX];

			img[y] = RED_VALUE(color);
			img[y+1] = GREEN_VALUE(color);
			img[y+2] = BLUE_VALUE(color);
		}
		putimage(r*scaleFactor, drawStart*scaleFactorY, img, COPY_PUT);

	}
}
#define G_MENU3D


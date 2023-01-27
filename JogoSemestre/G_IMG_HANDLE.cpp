#include "G_IMG_HANDLE.h"
#include "G_TYPES.h"
#include "G_PLAYER.h"
#include "G_ENEMY.h"
#include "G_SHIELDS.h"
#include "G_BULLET.h"
#include "G_EXPLOSION.h"

extern imgtype **bgs;

int GetImgSize(int x, int y)
{

	return imagesize(0, 0, x, y);
}

imgtype **MallocImg(imgtype **img, int tam, int amount)
{
    int i = 0;
    img = (imgtype**)malloc(sizeof(imgtype*) * amount);
 
    for(i = 0; i < amount; i++)
    {
    	img[i] = (imgtype*)malloc(tam);
	}
	return img; 
     
}

void HandleImgs()
{
	//essa funcao lida com o carregamento das imagens.
	HandlePlayerImg();
    HandleEnemyImg();   
    HandleShieldImg();
    HandleBulletImg();
    HandleExploImg();
}

void putimg(int x, int y, imgtype **img, imgtype **msk, int index)
{
	putimage(x, y, img[index], AND_PUT);
    putimage(x, y, msk[index], OR_PUT);
    
}

void ReadImg(char path[], int x, int y, int index, int sizeX, int sizeY, imgtype **imgTarget, imgtype **mskTarget, int amount)
{
	//essa funcao lida com o carregamento das imagens, seja um SS ou uma imagem pequena.
	int i = 0;
	int posY = 0;
	int j = 0;
	readimagefile(path, 0, 0, sizeX, sizeY);

	for(i = index; i < amount; i++)
	{
		if(x + (x+1) * j < sizeX)
		{
			getimage((x+1)*j, posY, x + (x+1)*j, posY + y, imgTarget[i]);
	    	getimage((x+1)*j, posY, x + (x+1)*j, posY + y, mskTarget[i]);
			j++;    	
		}
		else
		{
			getimage((x+1)*j, posY, x + (x+1)*j, posY + y, imgTarget[i]);
	    	getimage((x+1)*j, posY, x + (x+1)*j, posY + y, mskTarget[i]);
			j = 0;
			posY += y;
		}	
	}
	bar(0, 0, gameScreenX, gameScreenY);
}

void LoadBGImg()
{
	int i = 0;
	char *path;
	char *num;
	path = NULL;
	num = NULL;
	
	num = (char*)malloc(sizeof(char));
	path = (char*)malloc(strlen("./Sprites/BG/1.bmp"));
	
	for(i = 0; i < BG_AMOUNT; i++)
	{
		strcpy(path,"./Sprites/BG/");
		sprintf(num, "%d", i + 1);
		strcat(path, num);
		strcat(path, ".bmp");
		
		readimagefile(path, 0,0, gameScreenX, gameScreenY);
  		getimage(0,0, gameScreenX, gameScreenY, bgs[i]);
  		cleardevice();
	}
}

void removeImgBG(imgtype *img, imgtype *msk, int tam)
{

	int i = 0, j = 0;
	unsigned char R, G, B;
	B = img[24];
	G = img[25];
	R = img[26];

	for(i = 24; i < tam; i += 4)
	{
		if(img[i] == B && img[i+1] == G && img[i+2] == R)
		{
			img[i] = 0;
			img[i+1] = 0;
			img[i+2] = 0;
			msk[i] = 255; 
			msk[i+1] = 255;
			msk[i+2] = 255;	
		}
		else
		{
			msk[i] = 0;
			msk[i + 1] = 0;
			msk[i + 2] = 0;
		}
	}
}

void ReadFile(char *paths[], const char *pathname)
{
	int r, i;
	int rows = 0;

	FILE *arq;
	
	arq = fopen(pathname, "r");
	
	if(arq != NULL)
	{
		fscanf(arq, "%d", &rows);
		
		for(r = 0; r < rows + 1; r++)
		{
			//aloca memoria para colocar a string.
			paths[r] = (char*)malloc(rows);
			
			//coloca a string no ponteiro de arrays.
			fgets(paths[r], STRING_SIZE, arq);
			
			//guarda o tamanho a string usando a funcao strlen.
			int pathSize = strlen(paths[r]);
			
			//verfica se ao fim da string ha um \n
			if(pathSize > 0 && paths[r][pathSize-1] == '\n')
			{
				//so houver, substitue por um \0, que indica o fim de uma linha.
				paths[r][pathSize-1] = '\0';
			}
		}
	}
	else
	{
		printf("Nao foi possivel carregar o arquivo, verifique se ele esta na pasta informada.\n");
		exit(1);
	}
	fclose(arq);
}


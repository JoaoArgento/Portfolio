#ifndef G_IMG_HANDLE_H
#define G_IMG_HANDLE_H
#include "G_DECS.h"
#include "G_TYPES.h"
 

void HandleImgs();
void ReadImg(char path[], int x, int y, int index, int sizeX, int sizeY, imgtype **imgTarget, imgtype **mskTarget, int amount);
void removeImgBG(imgtype *img, imgtype *msk, int tam);
void ReadFile(char *paths[], const char *pathname);
void putimg(int x, int y, imgtype **img, imgtype **msk, int index);
imgtype **MallocImg(imgtype **img, int tam, int amount);
int GetImgSize(int x, int y);
void LoadBGImg();

#endif 

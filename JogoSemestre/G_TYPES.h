#ifndef G_TYPES_H
#define G_TYPES_H

typedef unsigned long long gt_type;
typedef unsigned char imgtype;

typedef enum {
	PLAYER, ENEMY, BULLET, SHIELD, EFFECTS, METEORS
} obj_t;

typedef enum {
	MENU = 0,
	LEVEL_1 = 1,
	LEVEL_2 = 2,
	SELECAO = 4,
	CREDITOS = 5,
	COMO_JOGAR = 6,
	FINAL_LEVEL = 7,
	SAIR = 8
	
}LEVEL;

#endif

#pragma once

#include "collision.h"

#define MAX_EXPLOSION (16)
#define EXPLOSION_W (4)
#define EXPLOSION_H (4)

typedef struct Explosion
{
	float PosX;
	float PosY;

	bool  enable;
	int   cnt;
	int   frame;

	CIRCLE	col_circle;
}Explosion;

void Explosion_Initialize(void);
void Explosion_Update(void);
void Explosion_Draw(void);

void Explosion_Create(float x, float y);
void Friend_Destroy(int index);
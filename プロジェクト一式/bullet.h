#pragma once

#include "collision.h"

#define BULLET_MAX (1024)

void Bullet_Initialize(void);
void Bullet_Update(void);
void Bullet_Draw(void);

void Bullet_Create(float x, float y, int pattern);

void Bullet_Destroy(int index);
bool Bullet_IsEnable(int index);

CIRCLE* Bullet_GetCircle(int index);

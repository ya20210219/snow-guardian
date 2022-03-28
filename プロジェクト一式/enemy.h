#pragma once

#include "collision.h"

#define ENEMY_MAX (256)

void Enemy_Initialize(void);
void Enemy_Update(void);
void Enemy_Draw(void);

void Enemy_Create(float x, float y);

void Enemy_Destroy(int index);
bool Enemy_IsEnable(int index);

CIRCLE* Enemy_GetCircle(int index);


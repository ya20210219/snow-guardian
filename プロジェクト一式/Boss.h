#pragma once

#include "collision.h"

#define BOSS_MAX (10)

void Boss_Initialize(void);
void Boss_Update(void);
void Boss_Draw(void);

void Boss_Create(float x, float y);

void Boss_Destroy(int index);
bool Boss_IsEnable(int index);

CIRCLE* Boss_GetCircle(int index);


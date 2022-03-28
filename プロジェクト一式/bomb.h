#pragma once

#include "collision.h"

#define BOMB_MAX (50)

void Bomb_Initialize(void);
void Bomb_Update(void);
void Bomb_Draw(void);

void Bomb_Create(float x, float y);

bool Bomb_IsEnable(int index);

CIRCLE* Bomb_GetCircle(int index);

void AddDrawNum(int add);

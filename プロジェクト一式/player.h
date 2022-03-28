#pragma once

#include "collision.h"

#define MAX_PLAYER (1)


// プレイヤー座標
typedef struct Player
{
	float PlayerX;
	float PlayerY;
	D3DXVECTOR2 PlayerSpeed;
	bool	enable;
	int  Life;

	CIRCLE	col_circle;
}Player;

void Player_Initialize(void);
void Player_Update(void);
void Player_Draw(void);

void Player_Create(float x, float y);
void Player_Destroy(int index);
bool  Player_IsEnable(int index);
CIRCLE* Player_GetCircle(int index);
Player* GetPlayer();
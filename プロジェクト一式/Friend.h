#pragma once

#include "collision.h"

#define MAX_FRIEND (3)
#define FRIEND_W (40)
#define FRIEND_H (60)
	
typedef struct Friend
{
	float FriendX;
	float FriendY;
	D3DXVECTOR2 FriendSpeed;
	bool	enable;
	int  Life;
	int  LifeTimer;
	int  LifeColor;
	int  HpDrawNum;
	bool LifeCntDown;
	int  CntDownBlinking;

	CIRCLE	col_circle;
}Friend;

void Friend_Initialize(void);
void Friend_Update(void);
void Friend_Draw(void);

void Friend_Create(float x, float y);
void Friend_Destroy(int index);
bool  Friend_IsEnable(int index);
CIRCLE* Friend_GetCircle(int index);
#pragma once

#include "collision.h"

#define MAX_SHOP (1)
#define SHOP_W (100.0f)
#define SHOP_H (80.0f)

typedef struct Shop
{
	float posx;
	float posy;

	bool  enable;
	bool  Shopflg; 

	CIRCLE	col_circle;
}SHOP;

void Shop_Initialize(void);
void Shop_Update(void);
void Shop_Draw(void);

void Shop_Create(float x, float y);
bool Shop_IsEnable(int index);
bool  Shop_IsActivate(int index);
CIRCLE* Shop_GetCircle(int index);
SHOP* GetShop();
void Shop_Activate(int index);

int Shop_FriendLifespan();
int Shop_BombLifespan();
int Shop_BulletRate();
bool Shop_BulletDual();

int Shop_List1Value();
int Shop_List2Value();
int Shop_List3Value();
int Shop_List4Value();

bool Shop_List1SoldOut();
bool Shop_List2SoldOut();
bool Shop_List3SoldOut();
bool Shop_List4SoldOut();
#pragma once

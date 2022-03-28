#pragma once

#include <d3dx9.h>

typedef struct
{
	D3DXVECTOR2 pos;	//位置(中心)
	float       r;		//半径

}CIRCLE;

typedef struct
{
	D3DXVECTOR2 pos;	//位置(中心)
	D3DXVECTOR2 size;	//サイズ
}BOX;

float GetFloatCircle(CIRCLE* cA, CIRCLE* cB);
void Collision_Bullet_vs_Enemy();
void Collision_Bullet_vs_Boss();
void Collision_Bomb_vs_Enemy();
void Collision_Bomb_vs_Boss();
void Collision_SnowJewel_vs_Enemy();
void Collision_SnowJewel_vs_Boss();
void Collision_Player_vs_Enemy();
void Collision_Player_vs_Boss();
void Collision_Friend_vs_Enemy();
void Collision_Friend_vs_Boss();
void Collision_Player_vs_Shop();

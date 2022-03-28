#pragma once

#include <d3dx9.h>

typedef struct
{
	D3DXVECTOR2 pos;	//�ʒu(���S)
	float       r;		//���a

}CIRCLE;

typedef struct
{
	D3DXVECTOR2 pos;	//�ʒu(���S)
	D3DXVECTOR2 size;	//�T�C�Y
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

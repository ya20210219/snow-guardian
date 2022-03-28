
#include "collision.h"
#include "enemy.h"
#include "bullet.h"
#include "SnowJewel.h"
#include "player.h"
#include "Friend.h"
#include "sound.h"
#include "Boss.h"
#include "bomb.h"
#include "shop.h"


bool HitCheckCircle(CIRCLE* cA, CIRCLE* cB)
{
	//ベクトルを計算する
	D3DXVECTOR2 dist;	//距離

	//BからAに向かうベクトルを計算する
	dist = cA->pos - cB->pos;

	//ベクトルdistの大きさを計算する
	float length = D3DXVec2Length(&dist);

	//cAの半径とcBの半径を足した値を計算する
	float size = cA->r + cB->r;

	//lengthとsizeの比較をしてsizeの方が大きければヒットしているという判定
	if (length < size)
		return true;

	//ヒットしていない
	return false;
}

float GetFloatCircle(CIRCLE* cA, CIRCLE* cB)
{
	//ベクトルを計算する
	D3DXVECTOR2 dist;	//距離

	//BからAに向かうベクトルを計算する
	dist = cA->pos - cB->pos;

	//ベクトルdistの大きさを計算する
	float length = D3DXVec2Length(&dist);

	return length;
}

bool HitCheckBox(BOX* bA, BOX* bB)
{
	//Aの上下左右
	float bA_left;
	float bA_right;
	float bA_top;
	float bA_bottom;

	//Bの上下左右
	float bB_left;
	float bB_right;
	float bB_top;
	float bB_bottom;

	//Aの矩形を設定
	bA_left = bA->pos.x - (bA->size.x / 2);
	bA_right = bA->pos.x + (bA->size.x / 2);
	bA_top = bA->pos.y - (bA->size.y / 2);
	bA_bottom = bA->pos.y + (bA->size.y / 2);

	//Bの矩形を設定
	bB_left = bB->pos.x - (bB->size.x / 2);
	bB_right = bB->pos.x + (bB->size.x / 2);
	bB_top = bB->pos.y - (bB->size.y / 2);
	bB_bottom = bB->pos.y + (bB->size.y / 2);

	//Aの左よりBの右が大きい時当たってる可能性がある
	if (bA_left < bB_right)
	{
		//Aの右よりBの左が小さい時当たってる可能性がある
		if (bA_right > bB_left)
		{
			//Aの上よりBの下が大きい時当たってる可能性がある
			if (bA_top < bB_bottom)
			{
				//Aの下よりBの上が小さい時当たってる可能性がある
				if (bA_bottom > bB_top)
				{
					//全ての判定を通った場合当たり判定になる
					return true;
				}

			}
		}
	}

	//ヒットしていない
	return false;
}

void Collision_Bullet_vs_Enemy()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		//弾の有効フラグチェック(trueでない場合)
		if (!Bullet_IsEnable(i))
			continue;

		for (int j = 0; j < ENEMY_MAX; j++)
		{
			//敵の有効フラグチェック(trueでない場合)
			if (!Enemy_IsEnable(j))
				continue;

			if (HitCheckCircle(Bullet_GetCircle(i), Enemy_GetCircle(j)))
			{
				//ヒットしている
				Enemy_Destroy(j);
				Bullet_Destroy(i);
				AddDrawNum(1);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_Bullet_vs_Boss()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		//弾の有効フラグチェック(trueでない場合)
		if (!Bullet_IsEnable(i))
			continue;

		for (int j = 0; j < BOSS_MAX; j++)
		{
			//敵の有効フラグチェック(trueでない場合)
			if (!Boss_IsEnable(j))
				continue;

			if (HitCheckCircle(Bullet_GetCircle(i), Boss_GetCircle(j)))
			{
				//ヒットしている
				Boss_Destroy(j);
				Bullet_Destroy(i);
				AddDrawNum(1);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_Bomb_vs_Enemy()
{
	for (int i = 0; i < BOMB_MAX; i++)
	{
		//弾の有効フラグチェック(trueでない場合)
		if (!Bomb_IsEnable(i))
			continue;

		for (int j = 0; j < ENEMY_MAX; j++)
		{
			//敵の有効フラグチェック(trueでない場合)
			if (!Enemy_IsEnable(j))
				continue;

			if (HitCheckCircle(Bomb_GetCircle(i), Enemy_GetCircle(j)))
			{
				//ヒットしている
				Enemy_Destroy(j);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_Bomb_vs_Boss()
{
	for (int i = 0; i < BOMB_MAX; i++)
	{
		//弾の有効フラグチェック(trueでない場合)
		if (!Bomb_IsEnable(i))
			continue;

		for (int j = 0; j < BOSS_MAX; j++)
		{
			//敵の有効フラグチェック(trueでない場合)
			if (!Boss_IsEnable(j))
				continue;

			if (HitCheckCircle(Bomb_GetCircle(i), Boss_GetCircle(j)))
			{
				//ヒットしている
				Boss_Destroy(j);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_SnowJewel_vs_Enemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//敵の有効フラグチェック(trueでない場合)
		if (!Enemy_IsEnable(i))
			continue;

		for (int j = 0; j < MAX_SNOW_JEWEL; j++)
		{
			if (!SnowJewel_IsEnable(j))
				continue;

			if (HitCheckCircle(Enemy_GetCircle(i), SnowJewel_GetCircle(j)))
			{
				//ヒットしている
				SnowJewel_Destroy(j);
				Enemy_Destroy(i);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_SnowJewel_vs_Boss()
{
	for (int i = 0; i < BOSS_MAX; i++)
	{
		//敵の有効フラグチェック(trueでない場合)
		if (!Boss_IsEnable(i))
			continue;

		for (int j = 0; j < MAX_SNOW_JEWEL; j++)
		{
			if (!SnowJewel_IsEnable(j))
				continue;

			if (HitCheckCircle(Boss_GetCircle(i), SnowJewel_GetCircle(j)))
			{
				//ヒットしている
				SnowJewel_Delete(j);
				Boss_Destroy(i);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_Player_vs_Enemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//敵の有効フラグチェック(trueでない場合)
		if (!Enemy_IsEnable(i))
			continue;

		for (int j = 0; j < MAX_PLAYER; j++)
		{
			if (!Player_IsEnable(j))
				continue;

			if (HitCheckCircle(Enemy_GetCircle(i), Player_GetCircle(j)))
			{
				//ヒットしている
				Player_Destroy(j);
				Enemy_Destroy(i);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_Friend_vs_Enemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//敵の有効フラグチェック(trueでない場合)
		if (!Enemy_IsEnable(i))
			continue;

		for (int j = 0; j < MAX_FRIEND; j++)
		{
			if (!Friend_IsEnable(j))
				continue;

			if (HitCheckCircle(Enemy_GetCircle(i), Friend_GetCircle(j)))
			{
				//ヒットしている
				Friend_Destroy(j);
				Enemy_Destroy(i);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_Player_vs_Boss()
{
	for (int i = 0; i < BOSS_MAX; i++)
	{
		//敵の有効フラグチェック(trueでない場合)
		if (!Boss_IsEnable(i))
			continue;

		for (int j = 0; j < MAX_PLAYER; j++)
		{
			if (!Player_IsEnable(j))
				continue;

			if (HitCheckCircle(Boss_GetCircle(i), Player_GetCircle(j)))
			{
				//ヒットしている
				Player_Destroy(j);
				Boss_Destroy(i);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_Friend_vs_Boss()
{
	for (int i = 0; i < BOSS_MAX; i++)
	{
		//敵の有効フラグチェック(trueでない場合)
		if (!Boss_IsEnable(i))
			continue;

		for (int j = 0; j < MAX_FRIEND; j++)
		{
			if (!Friend_IsEnable(j))
				continue;

			if (HitCheckCircle(Boss_GetCircle(i), Friend_GetCircle(j)))
			{
				//ヒットしている
				Friend_Destroy(j);
				Boss_Destroy(i);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_Player_vs_Shop()
{
	for (int i = 0; i < MAX_SHOP; i++)
	{
		//敵の有効フラグチェック(trueでない場合)
		if (!Shop_IsEnable(i))
			continue;

		for (int j = 0; j < MAX_PLAYER; j++)
		{
			if (!Player_IsEnable(j))
				continue;

			if (HitCheckCircle(Shop_GetCircle(i), Player_GetCircle(j)))
			{
				//ヒットしている
				Shop_Activate(i);

				StopSound(SOUND_LABEL_BGM001);
				PlaySound(SOUND_LABEL_SHOP_BGM);
			}
		}
	}
}
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include <d3dx9.h>
#include "Friend.h"
#include "sound.h"
#include "explosion.h"

static Explosion g_Explosion[MAX_EXPLOSION];

void Explosion_Initialize(void)
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		g_Explosion[i].enable = false;
	}
}

void Explosion_Update(void)
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		if (g_Explosion[i].enable == true)
		{
			g_Explosion[i].frame += 1;
			if (g_Explosion[i].frame >= 3)
			{
				g_Explosion[i].cnt += 1;
				g_Explosion[i].frame = 0;
			}

			if (g_Explosion[i].cnt == 3 && g_Explosion[i].frame == 3)
			{
				g_Explosion[i].enable = false;
				g_Explosion[i].cnt = 0;
				g_Explosion[i].frame = 0;
			}
		}
	}

}

void Explosion_Draw(void)
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		// もし爆破がすでに有効だったら？
		if (!g_Explosion[i].enable)
		{
			continue;
		}	

		//爆発描画
		Sprite_Draw(TEXTURE_INDEX_EXPLOSION,					//テクスチャ管理番号
			g_Explosion[i].PosX,								//描画座標x
			g_Explosion[i].PosY,								//描画座標y
			60 * g_Explosion[i].frame,
			60 * g_Explosion[i].cnt,							//テクスチャ切り取り座標x,y
			60, 60,												//テクスチャ切り取り幅x,y
			60 * 0.5f,											//中心座標x
			60 * 0.5f,											//中心座標y
			1.0f,												//拡大率x方向
			1.0f,												//拡大率y方向
			0.0f,												//回転角度(ラジアン)
			0);													//描画の色
	}

}

void Explosion_Create(float x, float y)
{

	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		// もし爆発がすでに有効だったら？
		if (g_Explosion[i].enable)
		{
			continue;
		}

		// 爆発の座標に引数の値を代入する
		g_Explosion[i].PosX = x;
		g_Explosion[i].PosY = y;

		//爆発を有効にする
		g_Explosion[i].enable = true;

		break;
	}
}
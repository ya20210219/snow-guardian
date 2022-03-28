#include "main.h"
#include "texture.h"
#include "sprite.h"
#include <math.h>
#include "SnowJewel.h"



static SNOWJEWEL g_SnowJewel[MAX_SNOW_JEWEL];

void SnowJewel_Initialize(void)
{
	for (int i = 0; i < MAX_SNOW_JEWEL; i++) {
		g_SnowJewel[i].enable = false;
	}
}

void SnowJewel_Update(void)
{
	for (int i = 0; i < MAX_SNOW_JEWEL; i++) {

		if (!SnowJewel_IsEnable(i))
		{
			continue;
		}

		if (g_SnowJewel[i].Life >= 7)
		{
			g_SnowJewel[i].HpColor = 3;
		}

		if (g_SnowJewel[i].Life <= 6)
		{
			g_SnowJewel[i].HpColor = 2;
		}

		if (g_SnowJewel[i].Life <= 3)
		{
			g_SnowJewel[i].HpColor = 1;
		}
	}


}

void SnowJewel_Draw(void)
{
	for (int i = 0; i < MAX_SNOW_JEWEL; i++) {

		if (!SnowJewel_IsEnable(i))
		{
			continue;
		}

		int tw = Texture_GetWidth(TEXTURE_INDEX_SNOW_JEWEL);
		int th = Texture_GetHeight(TEXTURE_INDEX_SNOW_JEWEL);
		Sprite_Draw(TEXTURE_INDEX_SNOW_JEWEL,					//テクスチャ管理番号
			g_SnowJewel[i].posx,									//描画座標x
			g_SnowJewel[i].posy,									//描画座標y
			0, 0,												//テクスチャ切り取り座標x,y
			tw, th,												//テクスチャ切り取り幅x,y
			tw * 0.5f,											//中心座標x
			th * 0.5f,											//中心座標y
			1.0f,												//拡大率x方向
			1.0f,												//拡大率y方向
			0.0f,												//回転角度(ラジアン)
			0);

		//HPバー
		Sprite_Draw(TEXTURE_INDEX_HPBAR,									//テクスチャ管理番号
			g_SnowJewel[i].posx - SNOW_JEWEL_W / 2 + 20.0f,					//描画座標x
			g_SnowJewel[i].posy - SNOW_JEWEL_H / 2 - 20.0f,					//描画座標y
			0, 0,															//テクスチャ切り取り座標x,y
			10 * g_SnowJewel[i].Life, 10,									//テクスチャ切り取り幅x,y
			10.0f * 0.5f,													//中心座標x
			10.0f * 0.5f,													//中心座標y
			1.0f,															//拡大率x方向
			1.0f,															//拡大率y方向
			0.0f,															//回転角度(ラジアン)
			g_SnowJewel[i].HpColor);										//描画する色
	}
}


void SnowJewel_Create(float x, float y)
{
	for (int i = 0; i < MAX_SNOW_JEWEL; i++)
	{
		// もし結晶がすでに有効だったら？
		if (g_SnowJewel[i].enable)
		{
			continue;
		}

		// 結晶の座標に引数の値を代入する
		g_SnowJewel[i].posx = x;
		g_SnowJewel[i].posy = y;
		g_SnowJewel[i].Life = 9;

		//ポジションの位置更新
		g_SnowJewel[i].col_circle.pos.x = g_SnowJewel[i].posx;
		g_SnowJewel[i].col_circle.pos.y = g_SnowJewel[i].posy;
		g_SnowJewel[i].col_circle.r = SNOW_JEWEL_W / 2;

		//結晶を有効にする
		g_SnowJewel[i].enable = true;

		break;
	}
}


void SnowJewel_Destroy(int index)
{
	g_SnowJewel[index].Life += -3;
	if (g_SnowJewel[index].Life <= 0)
	{
		g_SnowJewel[index].enable = false;
	}
}

void SnowJewel_Delete(int index)
{
	g_SnowJewel[index].Life += -99;
	if (g_SnowJewel[index].Life <= 0)
	{
		g_SnowJewel[index].enable = false;
	}
}

bool  SnowJewel_IsEnable(int index)
{
	return  g_SnowJewel[index].enable;
}

SNOWJEWEL* GetSnowJewel()
{
	return g_SnowJewel;
}

CIRCLE* SnowJewel_GetCircle(int index)
{
	return (&g_SnowJewel[index].col_circle);
}

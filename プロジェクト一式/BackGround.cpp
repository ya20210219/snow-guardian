#include "main.h"
#include "texture.h"
#include "sprite.h"
#include <math.h>
#include "BackGround.h"

void BackGround_Initialize(void)
{

}

void BackGround_Update(void)
{

}

void BackGround_Draw(void)
{
	int tw = Texture_GetWidth(TEXTURE_INDEX_BACKGROUND);
	int th = Texture_GetHeight(TEXTURE_INDEX_BACKGROUND);
	Sprite_Draw(TEXTURE_INDEX_BACKGROUND,					//テクスチャ管理番号
		SCREEN_WIDTH * 0.5f,								//描画座標x
		SCREEN_HEIGHT * 0.5f,								//描画座標y
		0, 0,												//テクスチャ切り取り座標x,y
		tw, th,												//テクスチャ切り取り幅x,y
		tw * 0.5f,											//中心座標x
		th * 0.5f,											//中心座標y
		1.0f,												//拡大率x方向
		1.0f,												//拡大率y方向
		0.0f,												//回転角度(ラジアン)
		0);
}

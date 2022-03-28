//-------------------------------------------------//
//[score.cpp]スコア
//                      author:俺   date:2020/06/09
//-------------------------------------------------//

#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "windows.h"
#include "Score.h"
#include "player.h"
#include "SnowJewel.h"
#include "shop.h"
#include <d3dx9.h>


//マクロ-------------------------------------------------//



//グローバル変数-------------------------------------------------//

static int g_Score;
static bool g_ShopCheck;

static Score g_ScorePos[MAX_SCORE];
static Value g_ValuePos[4][MAX_SCORE];



//初期化-------------------------------------------------//
void Score_Initialize()
{
	g_Score = 0;

	for (int i = 0; i < MAX_SCORE; i++)
	{
		g_ScorePos[i].ScorePosX = SCORE_POS_X; 
		g_ScorePos[i].ScorePosY = SCORE_POS_Y;
		g_ScorePos[i].DrawScoreNumX = 0;
		g_ScorePos[i].DrawScoreNumY= 0;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < MAX_SCORE; j++)
		{
			g_ValuePos[i][j].ValuePosX = SCORE_POS_X;
			if (i == 0)
			{
				g_ValuePos[i][j].ValuePosY = 155.0f;
			}
			if (i == 1)
			{
				g_ValuePos[i][j].ValuePosY = 280.0f;
			}
			if (i == 2)
			{
				g_ValuePos[i][j].ValuePosY = 420.0f;
			}
			if (i == 3)
			{
				g_ValuePos[i][j].ValuePosY = 555.0f;
			}

			g_ValuePos[i][j].DrawValueNumX = 0;
			g_ValuePos[i][j].DrawValueNumY = 0;
		}
	}
}

//更新-------------------------------------------------//
void Score_Update()
{
	Player* pPlayer = GetPlayer();
	SNOWJEWEL* pSnowJewel = GetSnowJewel();

	//ゲームオーバーになったら、リザルト時のポジションへ移動させる
	if (pPlayer->enable == false ||  pSnowJewel->enable == false)
	{
		for (int i = 0; i < MAX_SCORE; i++)
		{
			g_ScorePos[i].ScorePosX = SCORE_POS_X - ((SCREEN_WIDTH / 4) + (NUM_SIZE_X / 2));
			g_ScorePos[i].ScorePosY = SCORE_POS_Y + (SCREEN_HEIGHT / 3);
			g_ScorePos[i].DrawScoreNumX = 0;
			g_ScorePos[i].DrawScoreNumY = 0;	
		}
	}
}

//描画-------------------------------------------------//
void Score_Draw()
{
	//計算用変数にスコアを入れる
	int score = g_Score;  //計算用変数

	for (int i = 0; i < MAX_SCORE; i++)
	{
		int num = 0;				    //分割した値を入れ
		g_ScorePos[i].DrawScoreNumY = 0;

		num = score % 10;				//スコアの1の位を抜き出す
		score /= 10;					//スコアを1の位ずらしている

		if (num >= 5)
		{
			g_ScorePos[i].DrawScoreNumY = 1;
			num -= 5;
		}

		g_ScorePos[i].DrawScoreNumX = num;

		int tw = Texture_GetWidth(TEXTURE_INDEX_NUMBER) / 5;
		int th = Texture_GetHeight(TEXTURE_INDEX_NUMBER) / 2;

		Sprite_Draw(TEXTURE_INDEX_NUMBER,						//テクスチャ管理番号
			g_ScorePos[i].ScorePosX - (NUM_SIZE_X * i),			//描画座標x
			g_ScorePos[i].ScorePosY,							//描画座標y
			g_ScorePos[i].DrawScoreNumX * NUM_SIZE_X,			//テクスチャ切り取り座標x
			(int)(NUM_SIZE_Y * g_ScorePos[i].DrawScoreNumY),	//テクスチャ切り取り座標y
			(int)(NUM_SIZE_X), (int)(NUM_SIZE_Y),			//テクスチャ切り取り幅x,y
			tw * 0.5f,											//中心座標x
			th * 0.5f,											//中心座標y
			1.0f,												//拡大率x方向
			1.0f,												//拡大率y方向
			0.0f,												//回転角度(ラジアン)
			0);
	}

	g_ShopCheck = Shop_IsActivate(0);
	if (g_ShopCheck == true)
	{
		//値段表示用
		for (int i = 0; i < 4; i++)
		{
			int value;
			bool SoldOut;

			//計算用変数にスコアを入れる
			if(i == 0)
			{
				value = Shop_List1Value();  //計算用変数
				SoldOut = Shop_List1SoldOut();
			}
			if(i == 1)
			{
				value = Shop_List2Value();  //計算用変数
				SoldOut = Shop_List2SoldOut();
			}
			if(i == 2)
			{
				value = Shop_List3Value();  //計算用変数
				SoldOut = Shop_List3SoldOut();
			}
			if(i == 3)
			{
				value = Shop_List4Value();  //計算用変数
				SoldOut = Shop_List4SoldOut();
			}


			for (int j = 0; j < MAX_SCORE; j++)
			{
				int Vnum = 0;				    //分割した値を入れ
				g_ValuePos[i][j].DrawValueNumY = 0;

				Vnum = value % 10;				//スコアの1の位を抜き出す
				value /= 10;					//スコアを1の位ずらしている

				if (Vnum >= 5)
				{
					g_ValuePos[i][j].DrawValueNumY = 1;
					Vnum -= 5;
				}

				g_ValuePos[i][j].DrawValueNumX = Vnum;

				int tw = Texture_GetWidth(TEXTURE_INDEX_NUMBER) / 5;
				int th = Texture_GetHeight(TEXTURE_INDEX_NUMBER) / 2;

				if (SoldOut == false)
				{
					Sprite_Draw(TEXTURE_INDEX_NUMBER,							//テクスチャ管理番号
						g_ValuePos[i][j].ValuePosX - ((VALUE_SIZE_X / 2) * j),	//描画座標x
						g_ValuePos[i][j].ValuePosY,								//描画座標y
						g_ValuePos[i][j].DrawValueNumX * VALUE_SIZE_X,			//テクスチャ切り取り座標x
						VALUE_SIZE_Y * g_ValuePos[i][j].DrawValueNumY,			//テクスチャ切り取り座標y
						(int)VALUE_SIZE_X, (int)VALUE_SIZE_Y,					//テクスチャ切り取り幅x,y
						tw * 0.5f,												//中心座標x
						th * 0.5f,												//中心座標y
						0.5f,													//拡大率x方向
						0.5f,													//拡大率y方向
						0.0f,													//回転角度(ラジアン)
						0);
				}
			}
		}
	}
			  
	//上限上回った時
	if (g_Score > 99999)
	{
		g_Score = 99999;
	}
}

//スコアの増加関数
void AddScore(int add)
{
	g_Score += add;
}

//スコアの設定関数
void SetScore(int set)
{
	g_Score += set;
}

int ScoreCount()
{
	return g_Score;
}

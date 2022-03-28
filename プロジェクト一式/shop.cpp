#include "main.h"
#include "texture.h"
#include "sprite.h"
#include <math.h>
#include "Shop.h"
#include "input.h"
#include "player.h"
#include "Friend.h"
#include "bomb.h"
#include "Score.h"
#include "sound.h"

#define TEXT_POSX
#define TEXT_POSY

static Shop g_Shop[MAX_SHOP];
static float g_WitchPosX;
static float g_WitchPosY;
static int g_F_LifeSpanPlus;
static int g_B_LifeSpanPlus;
static int g_B_Rate;
static bool g_B_Dual;
static int g_ShopListNum;
static bool g_ShopStay;
static int g_ShopStayCnt;
static float g_ShopArrowPosX;
static float g_ShopArrowPosY;
static int g_ShopTxtNum;

static int g_ShopList1Value;
static int g_ShopList2Value;
static int g_ShopList3Value;
static int g_ShopList4Value;

static bool g_ShopList1Soldout;
static bool g_ShopList2Soldout;
static bool g_ShopList3Soldout;
static bool g_ShopList4Soldout;

static bool g_ShopNewflg;
static bool g_ShopNotEnough;

void Shop_Initialize(void)
{
	for (int i = 0; i < MAX_SHOP; i++) {
		g_Shop[i].enable = false;
		g_Shop[i].Shopflg = false;
	}

	g_WitchPosX = 300.0f;
	g_WitchPosY = SCREEN_HEIGHT / 3;

	g_F_LifeSpanPlus = 0;
	g_ShopArrowPosX = 635.0f;
	g_ShopArrowPosY = 90.0f;
	g_ShopTxtNum = 0;
	g_ShopList1Value = 200;
	g_ShopList2Value = 3600;
	g_ShopList3Value = 500;
	g_ShopList4Value = 200;
	g_ShopList1Soldout = false;
	g_ShopList2Soldout = false;
	g_ShopList3Soldout = false;
	g_ShopList4Soldout = false;
	g_ShopNotEnough = false;
	g_ShopNewflg = true;
}

void Shop_Update(void)
{
	Player* pPlayer = GetPlayer();
	int nScore = ScoreCount();

	for (int i = 0; i < MAX_SHOP; i++) {

		if (!Shop_IsActivate(i))
		{
			continue;
		}

		if (Keyboard_IsPress(DIK_BACK))
		{
			g_Shop[i].Shopflg = false;
			g_Shop[i].enable = true;
			pPlayer[i].PlayerX = SCREEN_WIDTH * 0.25f;
			pPlayer[i].PlayerY = SCREEN_HEIGHT * 0.5f;


			StopSound(SOUND_LABEL_SHOP_BGM);
			PlaySound(SOUND_LABEL_BGM001);
		}

		if (Keyboard_IsPress(DIK_1))
		{
			g_ShopListNum = 1;
			g_ShopTxtNum = 1;
			g_ShopArrowPosY = 90.0f;
		}
		if (Keyboard_IsPress(DIK_2))
		{
			g_ShopListNum = 2;
			g_ShopTxtNum = 2;
			g_ShopArrowPosY = 220.0f;
		}
		if (Keyboard_IsPress(DIK_3))
		{
			g_ShopListNum = 3;
			g_ShopTxtNum = 3;
			g_ShopArrowPosY = 350.0f;
		}
		if (Keyboard_IsPress(DIK_4))
		{
			g_ShopListNum = 4;
			g_ShopTxtNum = 4;
			g_ShopArrowPosY = 490.0f;
		}


		//攻撃速度UP
		if (g_ShopListNum == 1 && nScore >= g_ShopList1Value && g_ShopStay == false && Keyboard_IsPress(DIK_RETURN))
		{
			g_B_Rate += 1;
			if (g_B_Rate >= 8)
			{
				g_B_Rate = 8;
				g_ShopList1Soldout = true;
			}
			AddScore(-g_ShopList1Value);
			g_ShopStay = true;
			PlaySound(SOUND_LABEL_SE_SHOP_BUY);
			g_ShopList1Value += (g_ShopList1Value / 2);
		}
				
		//攻撃2列化
		if (g_ShopListNum == 2 && nScore >= g_ShopList2Value && g_ShopStay == false && Keyboard_IsPress(DIK_RETURN))
		{
			g_B_Dual = true;
			g_ShopList2Soldout = true;
			AddScore(-g_ShopList2Value);
			PlaySound(SOUND_LABEL_SE_SHOP_BUY);
		}

		//結晶ボム効果時間延長
		if (g_ShopListNum == 3 && nScore >= g_ShopList3Value && g_ShopStay == false && Keyboard_IsPress(DIK_RETURN))
		{
			g_B_LifeSpanPlus += 120;
			if (g_B_LifeSpanPlus >= 600)
			{
				g_B_LifeSpanPlus = 600;
				g_ShopList3Soldout = true;
			}
			AddScore(-g_ShopList3Value);
			g_ShopStay = true;
			PlaySound(SOUND_LABEL_SE_SHOP_BUY);
			g_ShopList3Value += (g_ShopList3Value / 2);
		}

		//仲間召喚時間延長
		if (g_ShopListNum == 4 && nScore >= g_ShopList4Value && g_ShopStay == false && Keyboard_IsPress(DIK_RETURN))
		{
			g_F_LifeSpanPlus += 300;
			if (g_F_LifeSpanPlus >= 1800)
			{
				g_F_LifeSpanPlus = 1800;
				g_ShopList4Soldout = true;
			}
			AddScore(-g_ShopList4Value);
			g_ShopStay = true;
			PlaySound(SOUND_LABEL_SE_SHOP_BUY);
			g_ShopList4Value += (g_ShopList4Value / 2);
		}

		//ショップ1のスコアが足りてなかった
		if (g_ShopListNum == 1 && nScore < g_ShopList1Value && g_ShopStay == false && Keyboard_IsPress(DIK_RETURN))
		{
			g_ShopNotEnough = true;
		}
		//ショップ2のスコアが足りてなかった
		if (g_ShopListNum == 2 && nScore < g_ShopList2Value && g_ShopStay == false && Keyboard_IsPress(DIK_RETURN))
		{
			g_ShopNotEnough = true;
		}
		//ショップ3のスコアが足りてなかった
		if (g_ShopListNum == 3 && nScore < g_ShopList3Value && g_ShopStay == false && Keyboard_IsPress(DIK_RETURN))
		{
			g_ShopNotEnough = true;
		}
		//ショップ4のスコアが足りてなかった
		if (g_ShopListNum == 4 && nScore < g_ShopList4Value && g_ShopStay == false && Keyboard_IsPress(DIK_RETURN))
		{
			g_ShopNotEnough = true;
		}
	}

	//まいどあり～の描画および連打阻止
	if (g_ShopStay == true)
	{
		g_ShopStayCnt++;
		if (g_ShopStayCnt >= 90)
		{
			g_ShopStay = false;
			g_ShopTxtNum = 0;
			g_ShopStayCnt = 0;
		}
	}

	//初期メッセージ消去
	if (g_ShopTxtNum == 5)
	{
		g_ShopStayCnt++;
		if (g_ShopStayCnt >= 120 || Keyboard_IsPress(DIK_1) || Keyboard_IsPress(DIK_2) || Keyboard_IsPress(DIK_3) || Keyboard_IsPress(DIK_4))
		{
			g_ShopTxtNum = 0;
			g_ShopNewflg = false;
			g_ShopStayCnt = 0;
		}
	}

	//スコアが足りない
	if (g_ShopNotEnough == true)
	{
		g_ShopStayCnt++;
		if (g_ShopStayCnt >= 60)
		{
			g_ShopNotEnough = false;
			g_ShopStayCnt = 0;
		}
	}
}

void Shop_Draw(void)
{
	for (int i = 0; i < MAX_SHOP; i++) {

		if (!Shop_IsEnable(i))
		{
			continue;
		}

		if (g_Shop[i].enable == true)
		{
			int tw = Texture_GetWidth(TEXTURE_INDEX_SHOP);
			int th = Texture_GetHeight(TEXTURE_INDEX_SHOP);

			//店(魔法陣)
			Sprite_Draw(TEXTURE_INDEX_SHOP,							//テクスチャ管理番号
				g_Shop[i].posx,										//描画座標x
				g_Shop[i].posy,										//描画座標y
				0, 0,												//テクスチャ切り取り座標x,y
				tw, th,												//テクスチャ切り取り幅x,y
				tw * 0.5f,											//中心座標x
				th * 0.5f,											//中心座標y
				1.0f,												//拡大率x方向
				1.0f,												//拡大率y方向
				0.0f,												//回転角度(ラジアン)
				0);
		}		
	}

	for (int i = 0; i < MAX_SHOP; i++)
	{
		//店内部
		if (g_Shop[i].Shopflg == true)
		{
			int tw = Texture_GetWidth(TEXTURE_INDEX_SHOP_BG);
			int th = Texture_GetHeight(TEXTURE_INDEX_SHOP_BG);

			//店背景
			Sprite_Draw(TEXTURE_INDEX_SHOP_BG,							//テクスチャ管理番号
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

			//魔女描画
			Sprite_Draw(TEXTURE_INDEX_WITCH,						//テクスチャ管理番号
				g_WitchPosX,										//描画座標x
				g_WitchPosY,										//描画座標y
				0, 0,												//テクスチャ切り取り座標x,y
				350, 300,											//テクスチャ切り取り幅x,y
				350 * 0.5f,											//中心座標x
				300 * 0.5f,											//中心座標y
				1.0f,												//拡大率x方向
				1.0f,												//拡大率y方向
				0.0f,												//回転角度(ラジアン)
				0);

			//アイテム選択矢印
			Sprite_Draw(TEXTURE_INDEX_SHOP_ARROW,						//テクスチャ管理番号
				g_ShopArrowPosX,										//描画座標x
				g_ShopArrowPosY,										//描画座標y
				0, 0,												//テクスチャ切り取り座標x,y
				80, 80,											//テクスチャ切り取り幅x,y
				80 * 0.5f,											//中心座標x
				80 * 0.5f,											//中心座標y
				1.0f,												//拡大率x方向
				1.0f,												//拡大率y方向
				0.0f,												//回転角度(ラジアン)
				0);

			//初期メッセージ
			if (g_ShopTxtNum == 5)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_TXT_WELCOME,				//テクスチャ管理番号
					320,												//描画座標x
					SCREEN_HEIGHT - 100,								//描画座標y
					0, 0,												//テクスチャ切り取り座標x,y
					625, 200,											//テクスチャ切り取り幅x,y
					625 * 0.5f,											//中心座標x
					200 * 0.5f,											//中心座標y
					1.0f,												//拡大率x方向
					1.0f,												//拡大率y方向
					0.0f,												//回転角度(ラジアン)
					0);
			}

			//基本メッセージ
			if (g_ShopTxtNum == 0 && g_ShopStay == false)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_TXT_DEFAULT,				//テクスチャ管理番号
					320,												//描画座標x
					SCREEN_HEIGHT - 100,								//描画座標y
					0, 0,												//テクスチャ切り取り座標x,y
					625, 200,											//テクスチャ切り取り幅x,y
					625 * 0.5f,											//中心座標x
					200 * 0.5f,											//中心座標y
					1.0f,												//拡大率x方向
					1.0f,												//拡大率y方向
					0.0f,												//回転角度(ラジアン)
					0);
			}


			//アイテム１のメッセージ
			if (g_ShopTxtNum == 1 && g_ShopStay == false)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_TXT_LIST1,				//テクスチャ管理番号
					320,												//描画座標x
					SCREEN_HEIGHT - 100,								//描画座標y
					0, 0,												//テクスチャ切り取り座標x,y
					625, 200,											//テクスチャ切り取り幅x,y
					625 * 0.5f,											//中心座標x
					200 * 0.5f,											//中心座標y
					1.0f,												//拡大率x方向
					1.0f,												//拡大率y方向
					0.0f,												//回転角度(ラジアン)
					0);
			}

			if (g_ShopTxtNum == 2 && g_ShopStay == false)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_TXT_LIST2,				//テクスチャ管理番号
					320,												//描画座標x
					SCREEN_HEIGHT - 100,								//描画座標y
					0, 0,												//テクスチャ切り取り座標x,y
					625, 200,											//テクスチャ切り取り幅x,y
					625 * 0.5f,											//中心座標x
					200 * 0.5f,											//中心座標y
					1.0f,												//拡大率x方向
					1.0f,												//拡大率y方向
					0.0f,												//回転角度(ラジアン)
					0);
			}

			if (g_ShopTxtNum == 3 && g_ShopStay == false)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_TXT_LIST3,				//テクスチャ管理番号
					320,												//描画座標x
					SCREEN_HEIGHT - 100,								//描画座標y
					0, 0,												//テクスチャ切り取り座標x,y
					625, 200,											//テクスチャ切り取り幅x,y
					625 * 0.5f,											//中心座標x
					200 * 0.5f,											//中心座標y
					1.0f,												//拡大率x方向
					1.0f,												//拡大率y方向
					0.0f,												//回転角度(ラジアン)
					0);
			}

			if (g_ShopTxtNum == 4 && g_ShopStay == false)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_TXT_LIST4,				//テクスチャ管理番号
					320,												//描画座標x
					SCREEN_HEIGHT - 100,								//描画座標y
					0, 0,												//テクスチャ切り取り座標x,y
					625, 200,											//テクスチャ切り取り幅x,y
					625 * 0.5f,											//中心座標x
					200 * 0.5f,											//中心座標y
					1.0f,												//拡大率x方向
					1.0f,												//拡大率y方向
					0.0f,												//回転角度(ラジアン)
					0);
			}

			//アイテム1が売り切れの場合表示
			if (g_ShopList1Soldout == true)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_SOLDOUT,					//テクスチャ管理番号
					SCREEN_WIDTH - (350 / 2),							//描画座標x
					88.0f,													//描画座標y
					0, 0,												//テクスチャ切り取り座標x,y
					350, 95,											//テクスチャ切り取り幅x,y
					350 * 0.5f,											//中心座標x
					95 * 0.5f,											//中心座標y
					1.0f,												//拡大率x方向
					1.0f,												//拡大率y方向
					0.0f,												//回転角度(ラジアン)
					0);
			}

			if (g_ShopList2Soldout == true)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_SOLDOUT,					//テクスチャ管理番号
					SCREEN_WIDTH - (350 / 2),							//描画座標x
					218.0f,												//描画座標y
					0, 0,												//テクスチャ切り取り座標x,y
					350, 95,											//テクスチャ切り取り幅x,y
					350 * 0.5f,											//中心座標x
					95 * 0.5f,											//中心座標y
					1.0f,												//拡大率x方向
					1.0f,												//拡大率y方向
					0.0f,												//回転角度(ラジアン)
					0);
			}

			if (g_ShopList3Soldout == true)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_SOLDOUT,					//テクスチャ管理番号
					SCREEN_WIDTH - (350 / 2),							//描画座標x
					348.0f,												//描画座標y
					0, 0,												//テクスチャ切り取り座標x,y
					350, 95,											//テクスチャ切り取り幅x,y
					350 * 0.5f,											//中心座標x
					95 * 0.5f,											//中心座標y
					1.0f,												//拡大率x方向
					1.0f,												//拡大率y方向
					0.0f,												//回転角度(ラジアン)
					0);
			}

			if (g_ShopList4Soldout == true)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_SOLDOUT,					//テクスチャ管理番号
					SCREEN_WIDTH - (350 / 2),							//描画座標x
					488.0f,												//描画座標y
					0, 0,												//テクスチャ切り取り座標x,y
					350, 95,											//テクスチャ切り取り幅x,y
					350 * 0.5f,											//中心座標x
					95 * 0.5f,											//中心座標y
					1.0f,												//拡大率x方向
					1.0f,												//拡大率y方向
					0.0f,												//回転角度(ラジアン)
					0);
			}

			//スコア不足メッセージ
			if (g_ShopNotEnough == true)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_NOT_ENOUGH,				//テクスチャ管理番号
					320,												//描画座標x
					SCREEN_HEIGHT - 100,								//描画座標y
					0, 0,												//テクスチャ切り取り座標x,y
					625, 200,											//テクスチャ切り取り幅x,y
					625 * 0.5f,											//中心座標x
					200 * 0.5f,											//中心座標y
					1.0f,												//拡大率x方向
					1.0f,												//拡大率y方向
					0.0f,												//回転角度(ラジアン)
					0);
			}
		}
	}

	//まいどあり～の描画
	if (g_ShopStay == true && g_Shop[0].Shopflg == true)
	{
		Sprite_Draw(TEXTURE_INDEX_SHOP_TXT_THX,					//テクスチャ管理番号
			320,												//描画座標x
			SCREEN_HEIGHT - 100,								//描画座標y
			0, 0,												//テクスチャ切り取り座標x,y
			625, 200,											//テクスチャ切り取り幅x,y
			625 * 0.5f,											//中心座標x
			200 * 0.5f,											//中心座標y
			1.0f,												//拡大率x方向
			1.0f,												//拡大率y方向
			0.0f,												//回転角度(ラジアン)
			0);
	}
}


void Shop_Create(float x, float y)
{
	for (int i = 0; i < MAX_SHOP; i++)
	{
		// もし店がすでに有効だったら？
		if (g_Shop[i].enable)
		{
			continue;
		}

		// 店の座標に引数の値を代入する
		g_Shop[i].posx = x;
		g_Shop[i].posy = y;

		//ポジションの位置更新
		g_Shop[i].col_circle.pos.x = g_Shop[i].posx;
		g_Shop[i].col_circle.pos.y = g_Shop[i].posy;
		g_Shop[i].col_circle.r = SHOP_W / 2;

		//店を有効にする
		g_Shop[i].enable = true;

		break;
	}
}

void Shop_Activate(int index)
{
	g_Shop[index].enable = false;
	g_Shop[index].Shopflg = true;
	if (g_ShopNewflg == true)
	{
		g_ShopTxtNum = 5;
	}

	if (g_ShopNewflg == false)
	{
		g_ShopTxtNum = 0;
	}

}

bool  Shop_IsEnable(int index)
{
	return  g_Shop[index].enable;
}

bool  Shop_IsActivate(int index)
{
	return  g_Shop[index].Shopflg;
}

CIRCLE* Shop_GetCircle(int index)
{
	return (&g_Shop[index].col_circle);
}

int Shop_FriendLifespan()
{
	return g_F_LifeSpanPlus;
}

int Shop_BombLifespan()
{
	return g_B_LifeSpanPlus;
}

int Shop_BulletRate()
{
	return g_B_Rate;
}

bool Shop_BulletDual()
{
	return g_B_Dual;
}

int Shop_List1Value()
{
	return g_ShopList1Value;
}

int Shop_List2Value()
{
	return g_ShopList2Value;
}

int Shop_List3Value()
{
	return g_ShopList3Value;
}

int Shop_List4Value()
{
	return g_ShopList4Value;
}

bool Shop_List1SoldOut()
{
	return g_ShopList1Soldout;
}

bool Shop_List2SoldOut()
{
	return g_ShopList2Soldout;
}

bool Shop_List3SoldOut()
{
	return g_ShopList3Soldout;
}

bool Shop_List4SoldOut()
{
	return g_ShopList4Soldout;
}

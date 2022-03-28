#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "Bomb.h"
#include "player.h"
#include "sound.h"
#include "input.h"
#include "shop.h"
#include <d3dx9.h>


#define BOMB_WIDTH   (300)
#define BOMB_HEIGHT  (300)


/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/
typedef struct Bomb_tag
{
	float	x, y;
	float	rotation;
	int		time;
	bool	enable;

	CIRCLE  col_circle;
}BOMB;

typedef struct BombSkill
{
	float PosX;
	float PosY;
}BombSkill;

/*------------------------------------------------------------------------------
   グローバル変数宣言
------------------------------------------------------------------------------*/
static BOMB g_Bombs[BOMB_MAX];
static BombSkill g_BombSkill[2];
static int  g_BombsDirection = 0;

static bool  g_BombSkillflg;
static int  g_BombSkillDrawNum;
static int  g_BombLifeSpan;


/*------------------------------------------------------------------------------
   関数定義
------------------------------------------------------------------------------*/

//初期化
void Bomb_Initialize(void)
{
	for (int i = 0; i < BOMB_MAX; i++) {
		g_Bombs[i].enable = false;
	}

	g_BombSkillflg = false;
	g_BombLifeSpan = 300;
	g_BombSkillDrawNum = 0;
}

//更新処理
void Bomb_Update(void)
{
	Player* pPlayer = GetPlayer();


	g_BombLifeSpan = 300;
	g_BombLifeSpan = g_BombLifeSpan + Shop_BombLifespan();

	for (int i = 0; i < BOMB_MAX; i++) {

		if (g_Bombs[i].enable) {
			g_Bombs[i].rotation += 2.0f;

			if (g_Bombs[i].enable)
			{
				g_Bombs[i].time++;
			}

			if (g_Bombs[i].time >= g_BombLifeSpan && g_Bombs[i].enable)
			{
				g_Bombs[i].enable = false;
				g_Bombs[i].time = 0;
			}
			
			//当たり判定用のCIRCLEも座標を更新
			g_Bombs[i].col_circle.pos.x = g_Bombs[i].x;
			g_Bombs[i].col_circle.pos.y = g_Bombs[i].y;

		}
	}

	for (int i = 0; i < 2; i++)
	{
		g_BombSkill[i].PosX = SCREEN_WIDTH - SCREEN_WIDTH + 150;
		g_BombSkill[i].PosY = SCREEN_HEIGHT - 50;
	}

	//ボム(でか氷)
	if (Keyboard_IsTrigger(DIK_2) && g_BombSkillDrawNum >= 10 && g_BombSkillflg == true)
	{
		Bomb_Create((pPlayer + 0)->PlayerX + 100.0f, (pPlayer + 0)->PlayerY);
		g_BombSkillflg = false;
		g_BombSkillDrawNum = 0;
	}

	if (g_BombSkillflg == false && g_BombSkillDrawNum >= 30)
	{
		g_BombSkillflg = true;
		PlaySound(SOUND_LABEL_SE_SKILLRECHARGE);
	}
}

//描画処理
void Bomb_Draw(void)
{
	for (int i = 0; i < BOMB_MAX; i++)
	{
		if (g_Bombs[i].enable)
		{
			int tw = Texture_GetWidth(TEXTURE_INDEX_BOMB);
			int th = Texture_GetHeight(TEXTURE_INDEX_BOMB);

			Sprite_Draw(TEXTURE_INDEX_BOMB,
				g_Bombs[i].x, g_Bombs[i].y,
				0, 0, tw, th, tw * 0.5f, th * 0.5f, 1.0f, 1.0f, g_Bombs[i].rotation, 0);
		}

		//ボムスキル描画
		Sprite_Draw(TEXTURE_INDEX_BOMB_SKILL,					//テクスチャ管理番号
			g_BombSkill[1].PosX,								//描画座標x
			g_BombSkill[1].PosY,								//描画座標y
			0, 0,												//テクスチャ切り取り座標x,y
			64, 80,												//テクスチャ切り取り幅x,y
			64 * 0.5f,											//中心座標x
			80 * 0.5f,											//中心座標y
			1.0f,												//拡大率x方向
			1.0f,												//拡大率y方向
			0.0f,												//回転角度(ラジアン)
			4);													//描画の色

		//ボムスキルクールダウン描画
		if (g_BombSkillflg == false)
		{
			Sprite_Draw(TEXTURE_INDEX_BOMB_SKILL,					//テクスチャ管理番号
				g_BombSkill[0].PosX,								//描画座標x
				g_BombSkill[0].PosY,								//描画座標y
				0, 0,												//テクスチャ切り取り座標x,y
				64, (8 * (g_BombSkillDrawNum / 3)),					//テクスチャ切り取り幅x,y
				64 * 0.5f,											//中心座標x
				80 * 0.5f,											//中心座標y
				1.0f,												//拡大率x方向
				1.0f,												//拡大率y方向
				0.0f,												//回転角度(ラジアン)
				0);													//描画の色
		}

		if (g_BombSkillflg == true)
		{
			Sprite_Draw(TEXTURE_INDEX_BOMB_SKILL,					//テクスチャ管理番号
				g_BombSkill[0].PosX,								//描画座標x
				g_BombSkill[0].PosY,								//描画座標y
				0, 0,												//テクスチャ切り取り座標x,y
				64, 80,												//テクスチャ切り取り幅x,y
				64 * 0.5f,											//中心座標x
				80 * 0.5f,											//中心座標y
				1.0f,												//拡大率x方向
				1.0f,												//拡大率y方向
				0.0f,												//回転角度(ラジアン)
				0);													//描画の色
		}
	}
}

void Bomb_Create(float x, float y)
{
	for (int i = 0; i < BOMB_MAX; i++)
	{
		// もしボムがすでに有効だったら？
		if (g_Bombs[i].enable)
		{
			continue;
		}

		// ボムの座標に引数の値を代入する
		g_Bombs[i].x = x;
		g_Bombs[i].y = y;


		g_Bombs[i].col_circle.pos.x = g_Bombs[i].x;
		g_Bombs[i].col_circle.pos.y = g_Bombs[i].y;

		g_Bombs[i].col_circle.r = 100.0f;

		// ボムを有効にする
		g_Bombs[i].enable = true;

		PlaySound(SOUND_LABEL_SE_MAGICSKILL);

		break;
	}
}

bool Bomb_IsEnable(int index)
{
	return g_Bombs[index].enable;
}

CIRCLE* Bomb_GetCircle(int index)
{
	return (&g_Bombs[index].col_circle);
}

//g_BombSkillDrawNumの増加関数
void AddDrawNum(int add)
{
	g_BombSkillDrawNum += add;
}


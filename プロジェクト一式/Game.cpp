#include "Game.h"
#include "main.h"
#include "MyDirect3D.h"
#include "input.h"
#include "sprite.h"
#include <time.h>
#include "fade.h"
#include "scene.h"
#include "player.h"
#include "Friend.h"
#include "enemy.h"
#include "Boss.h"
#include "bullet.h"
#include "bomb.h"
#include "collision.h"
#include "BackGround.h"
#include "SnowJewel.h"
#include "sound.h"
#include "Score.h"
#include "explosion.h"
#include "shop.h"

#define MAX_PARTICLE 128

static bool Game_EndCheck(void);
double frand(void);
static int g_EnemyBirthCount;
static int g_BossBirthCount;
static int g_EnemyBirthNumber;
static int g_BossBirthNumber;
static int g_BossBirthTime;
static int g_BossBirthCnt;
static int g_BossBirthIntervalCnt;
static int g_BossBirthInterval;

// ２Dポリゴン頂点構造体
typedef struct Vertex2D_tag
{
	D3DXVECTOR4 position; // 頂点座標（座標変換済み頂点）
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
} Vertex2D;
#define FVF_VERTEX2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) // ２Dポリゴン頂点フォーマット


enum PHASE_INDEX
{
	PHASE_INDEX_FADE,
	PHASE_INDEX_PLAYER_NORMAL,
	PHASE_INDEX_STAGE_CLEAR,
	PHASE_INDEX_END,

	PHASE_INDEX_MAX
};


static PHASE_INDEX g_Phase;
static int g_NextSceneFlag = 0;

void Game_Initialize(void)
{
	// シードの初期化
	srand((unsigned int)time(NULL));

	g_NextSceneFlag = 0;
	g_Phase = PHASE_INDEX_FADE;

	Player_Initialize();
	Friend_Initialize();
	Enemy_Initialize();
	Boss_Initialize();
	Bullet_Initialize();
	Bomb_Initialize();
	SnowJewel_Initialize();
	Score_Initialize();
	Explosion_Initialize();
	Shop_Initialize();

	PlaySound(SOUND_LABEL_BGM001);

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		float x, y;
		x = (float)(SCREEN_WIDTH * 0.25f);
		y = (float)(SCREEN_HEIGHT * 0.5f);
		Player_Create(x, y);
	}

	for (int i = 0; i < 10; i++)
	{
		float x, y;
		x = (float)(SCREEN_WIDTH - 24);
		y = (float)(frand() * SCREEN_HEIGHT);
		Enemy_Create(x, y);
	}

	for (int i = 0; i < MAX_SNOW_JEWEL; i++)
	{
		float x, y;
		x = (float)(SNOW_JEWEL_W / 2);
		y = (float)(SCREEN_HEIGHT / 2);
		SnowJewel_Create(x, y);
	}

	for (int i = 0; i < MAX_SHOP; i++)
	{
		float x, y;
		x = SHOP_W * 2;
		y = SHOP_H / 2 + 10.0f;
		Shop_Create(x, y);
	}

	g_EnemyBirthCount = 0;
	g_BossBirthInterval = 200;
	g_BossBirthIntervalCnt = 0;
	SetScore(0);

	Fade_Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
}

void Game_Finalize(void)
{
	StopSound(SOUND_LABEL_BGM001);
}

void Game_Update(void)
{
	bool bShop = Shop_IsActivate(0);

	switch (g_Phase)
	{
	case PHASE_INDEX_FADE:
		if (!Fade_IsFade()) {
			g_Phase = PHASE_INDEX_PLAYER_NORMAL;
			// PlaySound(SOUND_LABEL_BGM000);
		}
		break;
	case PHASE_INDEX_PLAYER_NORMAL:

		if (bShop == false)
		{

		g_BossBirthCnt++;
		g_EnemyBirthCount++;
		g_BossBirthCount++;
		g_EnemyBirthNumber = randBirth();
		g_EnemyBirthNumber += 3;
		g_BossBirthNumber = BOSS_MAX - randBossBirth();

		//敵生成
		if (g_EnemyBirthCount % 150 == 0)
		{
			for (int i = 0; i < g_EnemyBirthNumber; i++)
			{
				float x, y;
				x = (float)(SCREEN_WIDTH - 24);
				y = (float)(frand() * SCREEN_HEIGHT);
				Enemy_Create(x, y);
			}

			g_EnemyBirthCount = 0;
		}
		
		//ボス生成
		if (g_BossBirthCount % (g_BossBirthInterval - g_BossBirthIntervalCnt) == 0)
		{
			for (int i = 0; i < g_BossBirthNumber; i++)
			//for (int i = 0; i < 1; i++)
			{
				float x, y;
				x = (float)(SCREEN_WIDTH - 24);
				y = (float)(frand() * SCREEN_HEIGHT);
				Boss_Create(x, y);
			}

			g_BossBirthCount = 0;
		}

		//ボス生成間隔の縮小
		if (g_BossBirthCnt >= 600)
		{
			g_BossBirthIntervalCnt += 1;
			g_BossBirthCnt = 0;
		}

		//ボス生成間隔の縮小限界
		if (g_BossBirthIntervalCnt >= 50)
		{
			g_BossBirthIntervalCnt = 50;
		}

		//ボス生成時間の最大値
		if (g_BossBirthCount >= 1500)
		{
			g_BossBirthCount = 0;
		}

		Player_Update();
		Friend_Update();
		Enemy_Update();
		Boss_Update();
		Bullet_Update();
		Bomb_Update();
		Score_Update();
		SnowJewel_Update();
		Explosion_Update();
		Shop_Update();

		//判定を取る対象の移動が終わってから当たり判定を取る

		//弾と敵の当たり判定
		Collision_Bullet_vs_Enemy();
		Collision_Bullet_vs_Boss();
		Collision_SnowJewel_vs_Enemy();
		Collision_SnowJewel_vs_Boss();
		Collision_Player_vs_Enemy();
		Collision_Player_vs_Boss();
		Collision_Friend_vs_Enemy();
		Collision_Friend_vs_Boss();
		Collision_Bomb_vs_Enemy();
		Collision_Bomb_vs_Boss();
		Collision_Player_vs_Shop();
		}

		if (bShop == true)
		{
			Shop_Update();
			Score_Update();
		}

		//デバッグ用
		/*if (Keyboard_IsTrigger(DIK_RETURN) || Player_IsEnable(0) == false || SnowJewel_IsEnable(0) == false)
		{
			g_NextSceneFlag = 1;
		}*/

		if (Player_IsEnable(0) == false || SnowJewel_IsEnable(0) == false)
		{
			g_NextSceneFlag = 1;
		}

		//ゲームの終了チェック
		if (Game_EndCheck())
		{
			Fade_Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
			g_Phase = PHASE_INDEX_STAGE_CLEAR;
		}
		break;
	case PHASE_INDEX_STAGE_CLEAR:
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_RESULT);
			g_Phase = PHASE_INDEX_END;
		}
		break;
	case PHASE_INDEX_END:
		break;
	}
}

void Game_Draw(void)
{
	bool bShop = Shop_IsActivate(0);

	if (bShop == false)
	{
		BackGround_Draw();
		Enemy_Draw();
		Bullet_Draw();
		Bomb_Draw();
		Boss_Draw();

		Player_Draw();
		Friend_Draw();

		SnowJewel_Draw();

		Explosion_Draw();
		Score_Draw();
		Shop_Draw();

	}

	if (bShop == true)
	{
		Shop_Draw();
		Score_Draw();
	}
}


bool Game_EndCheck(void)
{
	if (g_NextSceneFlag != 0)
		return true;

	return false;
}

double frand(void)
{
	return (double)rand() / RAND_MAX;
}

int randBirth(void)
{
	return rand() % 8;
}

int randBossBirth(void)
{
	return rand() % 4 + 6;
}

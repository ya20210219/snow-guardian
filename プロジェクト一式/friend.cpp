#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include <d3dx9.h>
#include "bullet.h"
#include "Friend.h"
#include "sound.h"
#include "player.h"
#include "explosion.h"
#include "shop.h"

// プレイヤー座標

static int  g_FriendAnimation;
static bool g_Friend1Move;
static bool g_Friend2Move;
static bool g_Friend3Move;
static bool g_FriendBirthStop;
static int  g_FriendBirthTime;
static int  g_FriendBulletCount[MAX_FRIEND];
static int	g_FriendSkillDrawNum;
static int  g_FriendEnablecnt;
static int  g_F_LifeSpan;

typedef struct FriendSkill
{
	float PosX;
	float PosY;
}FriendSkill;

static Friend g_Friend[MAX_FRIEND];

static FriendSkill g_FriendSkill[2];


void Friend_Initialize(void)
{
	for (int i = 0; i < MAX_FRIEND; i++)
	{
		g_Friend[i].enable = false;

	}
	g_F_LifeSpan = 600;

}

void Friend_Update(void)
{
	D3DXVECTOR2 vecSpeed1(0.0f, 0.0f);
	D3DXVECTOR2 vecSpeed2(0.0f, 0.0f);
	D3DXVECTOR2 vecSpeed3(0.0f, 0.0f);

	Player* pPlayer = GetPlayer();

	g_F_LifeSpan = 600;
	g_F_LifeSpan = g_F_LifeSpan + Shop_FriendLifespan();
	   
	//分身召喚
	if (Keyboard_IsPress(DIK_1))
	{
		Friend_Create((pPlayer + 0)->PlayerX, (pPlayer + 0)->PlayerY);
	}

	for (int i = 0; i < MAX_FRIEND; i++) {

		if (!Friend_IsEnable(i))
		{
			continue;
		}

		//----------1体目の動き---------------------------
		//下側
		if (pPlayer->PlayerY - g_Friend[0].FriendY >= 75.0f)
		{
			vecSpeed1 += D3DXVECTOR2(0.0f, 1.0f);
			g_Friend1Move = true;
		}

		//上側
		if (g_Friend[0].FriendY - pPlayer->PlayerY >= 75.0f)
		{
			vecSpeed1 += D3DXVECTOR2(0.0f, -1.0f);
			g_Friend1Move = true;
		}

		//右側
		if (pPlayer->PlayerX - g_Friend[0].FriendX >= 75.0f)
		{
			vecSpeed1 += D3DXVECTOR2(1.0f, 0.0f);
			g_Friend1Move = true;
		}

		//左側
		if (g_Friend[0].FriendX - pPlayer->PlayerX >= 75.0f)
		{
			vecSpeed1 += D3DXVECTOR2(-1.0f, 0.0f);
			g_Friend1Move = true;
		}

		//----------2体目の動き---------------------------

		//下側
		if (g_Friend[0].FriendY - g_Friend[1].FriendY >= 75.0f)
		{
			vecSpeed2 += D3DXVECTOR2(0.0f, 1.0f);
			g_Friend2Move = true;
		}

		//上側
		if (g_Friend[1].FriendY - g_Friend[0].FriendY >= 75.0f)
		{
			vecSpeed2 += D3DXVECTOR2(0.0f, -1.0f);
			g_Friend2Move = true;
		}

		//右側
		if (g_Friend[0].FriendX - g_Friend[1].FriendX >= 75.0f)
		{
			vecSpeed2 += D3DXVECTOR2(1.0f, 0.0f);
			g_Friend2Move = true;
		}

		//左側
		if (g_Friend[1].FriendX - g_Friend[0].FriendX >= 75.0f)
		{
			vecSpeed2 += D3DXVECTOR2(-1.0f, 0.0f);
			g_Friend2Move = true;
		}

		//----------3体目の動き---------------------------

		//下側
		if (g_Friend[1].FriendY - g_Friend[2].FriendY >= 75.0f)
		{
			vecSpeed3 += D3DXVECTOR2(0.0f, 1.0f);
			g_Friend3Move = true;
		}

		//上側
		if (g_Friend[2].FriendY - g_Friend[1].FriendY >= 75.0f)
		{
			vecSpeed3 += D3DXVECTOR2(0.0f, -1.0f);
			g_Friend3Move = true;
		}

		//右側
		if (g_Friend[1].FriendX - g_Friend[2].FriendX >= 75.0f)
		{
			vecSpeed3 += D3DXVECTOR2(1.0f, 0.0f);
			g_Friend3Move = true;
		}

		//左側
		if (g_Friend[2].FriendX - g_Friend[1].FriendX >= 75.0f)
		{
			vecSpeed3 += D3DXVECTOR2(-1.0f, 0.0f);
			g_Friend3Move = true;
		}

		g_FriendBulletCount[i]++;

		if (g_FriendBulletCount[i] >= 60)
		{
			g_FriendBulletCount[i] = 0;
		}

		// 弾を発射する処理
		if (Keyboard_IsPress(DIK_SPACE) && g_FriendBulletCount[i] % 10 == 0)
		{
			Bullet_Create(g_Friend[i].FriendX + 20, g_Friend[i].FriendY + 30, 2);
		}

	}
		D3DXVec2Normalize(&vecSpeed1, &vecSpeed1);	//どんな長さでも1.0fに正規化する
		D3DXVec2Normalize(&vecSpeed2, &vecSpeed2);	//どんな長さでも1.0fに正規化する
		D3DXVec2Normalize(&vecSpeed3, &vecSpeed3);	//どんな長さでも1.0fに正規化する

		if (g_Friend1Move == true)
		{
			vecSpeed1 *= 0.2f;			//速度
			g_Friend[0].FriendSpeed += vecSpeed1;			//加速していく
			g_Friend[0].FriendX += g_Friend[0].FriendSpeed.x;
			g_Friend[0].FriendY += g_Friend[0].FriendSpeed.y;
		}
		if (g_Friend2Move == true)
		{
			vecSpeed2 *= 0.2f;			//速度
			g_Friend[1].FriendSpeed += vecSpeed2;			//加速していく
			g_Friend[1].FriendX += g_Friend[1].FriendSpeed.x;
			g_Friend[1].FriendY += g_Friend[1].FriendSpeed.y;
		}
		if (g_Friend3Move == true)
		{
			vecSpeed3 *= 0.2f;			//速度
			g_Friend[2].FriendSpeed += vecSpeed3;			//加速していく
			g_Friend[2].FriendX += g_Friend[2].FriendSpeed.x;
			g_Friend[2].FriendY += g_Friend[2].FriendSpeed.y;
		}

		g_Friend[0].FriendSpeed *= 0.96f;				//減速
		g_Friend[1].FriendSpeed *= 0.96f;				//減速
		g_Friend[2].FriendSpeed *= 0.96f;				//減速

		//for文無理?


		for (int i = 0; i < MAX_FRIEND; i++) 
		{
			if (!Friend_IsEnable(i))
			{
				continue;
			}

			//ポジションの位置更新
			g_Friend[i].col_circle.pos.x = g_Friend[i].FriendX;
			g_Friend[i].col_circle.pos.y = g_Friend[i].FriendY;
			g_Friend[i].col_circle.r = 25.0f;
		}

		g_FriendEnablecnt = 0;

		for (int i = 0; i < MAX_FRIEND; i++)
		{
			if (g_Friend[i].enable == true)
			{
				g_FriendEnablecnt += 1;
			}
		}

	//クールダウン
	if (g_FriendBirthStop == true && g_FriendEnablecnt != 3)
	{
		g_FriendBirthTime++;
	}

	//MAXでなければクールダウン描写
	if (g_FriendBirthStop && g_FriendBirthTime % 4 == 0 && g_FriendEnablecnt != 3)
	{
		g_FriendSkillDrawNum += 1;
	}
	//クールダウン終了
	if (g_FriendBirthTime >= 300)
	{
		PlaySound(SOUND_LABEL_SE_SKILLRECHARGE);
 		g_FriendBirthStop = false;
		g_FriendBirthTime = 0;
		g_FriendSkillDrawNum = 0;
	}

	//寿命カウント開始
	for (int i = 0; i < MAX_FRIEND; i++)
	{
		if (g_Friend[i].enable == true)
		{
			g_Friend[i].LifeTimer += 1;
		}

		//寿命
		if (g_Friend[i].LifeTimer >= g_F_LifeSpan)	//30秒
		{
			Explosion_Create(g_Friend[i].FriendX, g_Friend[i].FriendY);
			Friend_Destroy(i);
			g_Friend[i].LifeTimer = 0;
		}


		if (g_Friend[i].LifeTimer >= (g_F_LifeSpan - 300))
		{
			g_Friend[i].LifeCntDown = true;
		}

		if (g_Friend[i].LifeCntDown == true)
		{
			g_Friend[i].CntDownBlinking += 1;
		}

		if (g_Friend[i].LifeCntDown == true && g_Friend[i].CntDownBlinking <= 10)
		{
			g_Friend[i].LifeCntDown = false;
		}
		if (g_Friend[i].CntDownBlinking >= 20)
		{
			g_Friend[i].CntDownBlinking = 0;
		}

	}

	for (int i = 0; i < 2; i++)
	{
		g_FriendSkill[i].PosX = SCREEN_WIDTH - SCREEN_WIDTH + 50;
		g_FriendSkill[i].PosY = SCREEN_HEIGHT - 50;
	}
}

void Friend_Draw(void)
{
	for (int i = 0; i < MAX_FRIEND; i++)
	{
		// もし仲間がすでに有効だったら？
		if (!g_Friend[i].enable)
		{
			continue;
		}

		int tw = Texture_GetWidth(TEXTURE_INDEX_FRIEND);
		int th = Texture_GetHeight(TEXTURE_INDEX_FRIEND);

		//仲間描画
		Sprite_Draw(TEXTURE_INDEX_FRIEND,						//テクスチャ管理番号
			g_Friend[i].FriendX,								//描画座標x
			g_Friend[i].FriendY,								//描画座標y
			0, 0,												//テクスチャ切り取り座標x,y
			40, 60,												//テクスチャ切り取り幅x,y
			tw * 0.5f,											//中心座標x
			th * 0.5f,											//中心座標y
			1.0f,												//拡大率x方向
			1.0f,												//拡大率y方向
			0.0f,												//回転角度(ラジアン)
			0);													//描画の色


		if (g_Friend[i].LifeCntDown == true)
		{
			Sprite_Draw(TEXTURE_INDEX_TIMER,						//テクスチャ管理番号
				g_Friend[i].FriendX,								//描画座標x
				g_Friend[i].FriendY - 25.0f,						//描画座標y
				0, 0,												//テクスチャ切り取り座標x,y
				20, 23,												//テクスチャ切り取り幅x,y
				tw * 0.5f,											//中心座標x
				th * 0.5f,											//中心座標y
				1.0f,												//拡大率x方向
				1.0f,												//拡大率y方向
				0.0f,												//回転角度(ラジアン)
				0);													//描画の色
		}

	}
		//仲間スキル描画
		Sprite_Draw(TEXTURE_INDEX_FRIEND_SKILL,					//テクスチャ管理番号
			g_FriendSkill[1].PosX,								//描画座標x
			g_FriendSkill[1].PosY,								//描画座標y
			0, 0,												//テクスチャ切り取り座標x,y
			40, 80,												//テクスチャ切り取り幅x,y
			40 * 0.5f,											//中心座標x
			80 * 0.5f,											//中心座標y
			1.0f,												//拡大率x方向
			1.0f,												//拡大率y方向
			0.0f,												//回転角度(ラジアン)
			4);													//描画の色			

		//仲間スキルクールダウン描画
		if (g_FriendBirthStop == true)
		{
			Sprite_Draw(TEXTURE_INDEX_FRIEND_SKILL,					//テクスチャ管理番号
				g_FriendSkill[0].PosX,								//描画座標x
				g_FriendSkill[0].PosY,								//描画座標y
				0, 0,												//テクスチャ切り取り座標x,y
				40, g_FriendSkillDrawNum,							//テクスチャ切り取り幅x,y
				40 * 0.5f,											//中心座標x
				80 * 0.5f,											//中心座標y
				1.0f,												//拡大率x方向
				1.0f,												//拡大率y方向
				0.0f,												//回転角度(ラジアン)
				0);													//描画の色
		}

		if (g_FriendBirthStop == false)
		{
			Sprite_Draw(TEXTURE_INDEX_FRIEND_SKILL,					//テクスチャ管理番号
				g_FriendSkill[0].PosX,								//描画座標x
				g_FriendSkill[0].PosY,								//描画座標y
				0, 0,												//テクスチャ切り取り座標x,y
				40, 80,												//テクスチャ切り取り幅x,y
				40 * 0.5f,											//中心座標x
				80 * 0.5f,											//中心座標y
				1.0f,												//拡大率x方向
				1.0f,												//拡大率y方向
				0.0f,												//回転角度(ラジアン)
				0);													//描画の色
		}
}


void Friend_Create(float x, float y)
{

	for (int i = 0; i < MAX_FRIEND; i++)
	{
		// もし仲間がすでに有効だったら？
		if (g_Friend[i].enable || g_FriendBirthStop == true)
		{
			continue;
		}

		// 仲間の座標に引数の値を代入する
		g_Friend[i].FriendX = x;
		g_Friend[i].FriendY = y;

		//ポジションの位置更新
		g_Friend[i].col_circle.pos.x = g_Friend[i].FriendX + 20.0f;
		g_Friend[i].col_circle.pos.y = g_Friend[i].FriendY + 30.0f;
		g_Friend[i].col_circle.r = 25.0f;

		//仲間を有効にする
		g_Friend[i].enable = true;
		g_FriendBirthStop = true;

		PlaySound(SOUND_LABEL_SE_FRIENDSKILL);

		break;
	}
}

void Friend_Destroy(int index)
{
	PlaySound(SOUND_LABEL_SE_FRIEND_GOODBYE);
	g_Friend[index].LifeTimer = 0;
	g_Friend[index].HpDrawNum = 0;
	g_Friend[index].enable = false;
}

bool  Friend_IsEnable(int index)
{
	return  g_Friend[index].enable;
}

CIRCLE* Friend_GetCircle(int index)
{
	return (&g_Friend[index].col_circle);
}

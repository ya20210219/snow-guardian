#include "main.h"
#include "texture.h"
#include "sprite.h"
#include <math.h>
#include "enemy.h"
#include "SnowJewel.h"
#include "collision.h"
#include "Score.h"


#define ENEMY_SPEED_X (-2.0f)
#define ENEMY_SPEED_Y (0.0f)
#define ENEMY_WIDTH  (48)
#define ENEMY_HEIGHT (48)

typedef struct Enemy_tag
{
	float	x, y;
	float   speed_x, speed_y;
	int		Life;
	bool	enable;

	CIRCLE	col_circle;		//ポジションを持っている
} Enemy;

static Enemy g_Enemys[ENEMY_MAX];

static float g_EnemiesPlusSpd;
static int   g_EnemiesMgr;

void Enemy_Initialize(void)
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_Enemys[i].enable = false;
	}

	g_EnemiesPlusSpd = 1;
}

void Enemy_Update(void)
{
	float kyori = 0;
	float hyouteki_x = (SNOW_JEWEL_W / 2);
	float hyouteki_y = (SCREEN_HEIGHT / 2);

	g_EnemiesMgr++;
	if (g_EnemiesMgr % 600 == 0)
	{
		g_EnemiesPlusSpd *= 1.05f;
		g_EnemiesMgr = 0;
	}

	for (int i = 0; i < ENEMY_MAX; i++) {

		if (!g_Enemys[i].enable)
		{
			continue;
		}

		for (int j = 0; j < MAX_SNOW_JEWEL; j++)
		{
			if (!SnowJewel_IsEnable(j))
				continue;

			kyori = GetFloatCircle(Enemy_GetCircle(i), SnowJewel_GetCircle(j));
		}


		g_Enemys[i].speed_x = (hyouteki_x - g_Enemys[i].x) / kyori;
		g_Enemys[i].speed_y = (hyouteki_y - g_Enemys[i].y) / kyori;
		g_Enemys[i].x += (g_Enemys[i].speed_x * g_EnemiesPlusSpd);
		g_Enemys[i].y += (g_Enemys[i].speed_y * g_EnemiesPlusSpd);

		g_Enemys[i].col_circle.pos.x = g_Enemys[i].x;
		g_Enemys[i].col_circle.pos.y = g_Enemys[i].y;
		g_Enemys[i].col_circle.r = 24.0f;
	}
}

void Enemy_Draw(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!g_Enemys[i].enable)
		{
			continue;
		}

		Sprite_Draw(TEXTURE_INDEX_FIRE_ENEMY,
			g_Enemys[i].x - ENEMY_WIDTH / 2, g_Enemys[i].y - ENEMY_HEIGHT / 2,
			0, 0,
			ENEMY_WIDTH, ENEMY_HEIGHT, 0);
	}
}

void Enemy_Create(float x, float y)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// もし敵がすでに有効だったら？
		if (g_Enemys[i].enable)
		{
			continue;
		}

		// 敵の座標に引数の値を代入する
		g_Enemys[i].x = x;
		g_Enemys[i].y = y;
		g_Enemys[i].Life = 1;

		//ポジションの位置更新
		g_Enemys[i].col_circle.pos.x = g_Enemys[i].x;
		g_Enemys[i].col_circle.pos.y = g_Enemys[i].y;
		g_Enemys[i].col_circle.r = 24.0f;					//敵の半径を送っている

		// 敵を有効にする
		g_Enemys[i].enable = true;

		break;
	}
}

void Enemy_Destroy(int index)
{
	g_Enemys[index].Life += -1;
	if (g_Enemys[index].Life <= 0)
	{
		AddScore(5);
		g_Enemys[index].enable = false;
	}
}

bool Enemy_IsEnable(int index)
{
	return g_Enemys[index].enable;
}

CIRCLE* Enemy_GetCircle(int index)
{
	return (&g_Enemys[index].col_circle);
}

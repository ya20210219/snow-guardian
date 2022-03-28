#include "main.h"
#include "texture.h"
#include "sprite.h"
#include <math.h>
#include "boss.h"
#include "SnowJewel.h"
#include "collision.h"
#include "Score.h"

#define BOSS_SPEED_X (-2.0f)
#define BOSS_SPEED_Y (0.0f)
#define BOSS_WIDTH  (120)
#define BOSS_HEIGHT (120)
#define MAX_BOSS_HP (10)

typedef struct BOSS_tag
{
	float	x, y;
	float   speed_x, speed_y;
	int     Life;
	int     HpColor;
	bool	enable;

	CIRCLE	col_circle;		//�|�W�V�����������Ă���
}BOSS;

static BOSS g_Boss[BOSS_MAX];

static float g_BossPlusSpd;
static int   g_BossMgr;

void Boss_Initialize(void)
{
	for (int i = 0; i < BOSS_MAX; i++) {
		g_Boss[i].enable = false;
	}

	g_BossPlusSpd = 1;
}

void Boss_Update(void)
{
	float kyori = 0;
	float hyouteki_x = (SNOW_JEWEL_W / 2);
	float hyouteki_y = (SCREEN_HEIGHT / 2);

	g_BossMgr++;
	if (g_BossMgr % 600 == 0)
	{
		g_BossPlusSpd *= 1.02f;
		g_BossMgr = 0;
	}

	for (int i = 0; i < BOSS_MAX; i++) {

		if (!g_Boss[i].enable)
		{
			continue;
		}

		for (int j = 0; j < MAX_SNOW_JEWEL; j++)
		{
			if (!SnowJewel_IsEnable(j))
				continue;

			kyori = GetFloatCircle(Boss_GetCircle(i), SnowJewel_GetCircle(j));
		}

		if (g_Boss[i].Life >= 8)
		{
			g_Boss[i].HpColor = 3;
		}

		if (g_Boss[i].Life <= 7)
		{
			g_Boss[i].HpColor = 2;
		}

		if (g_Boss[i].Life <= 3)
		{
			g_Boss[i].HpColor = 1;
		}

		g_Boss[i].speed_x = (hyouteki_x - g_Boss[i].x) / kyori;
		g_Boss[i].speed_y = (hyouteki_y - g_Boss[i].y) / kyori;
		g_Boss[i].x += (g_Boss[i].speed_x * g_BossPlusSpd);
		g_Boss[i].y += (g_Boss[i].speed_y * g_BossPlusSpd);

		g_Boss[i].col_circle.pos.x = g_Boss[i].x;
		g_Boss[i].col_circle.pos.y = g_Boss[i].y;
		g_Boss[i].col_circle.r = 55.0f;

	}
}

void Boss_Draw(void)
{
	for (int i = 0; i < BOSS_MAX; i++)
	{
		if (!g_Boss[i].enable)
		{
			continue;
		}

		Sprite_Draw(TEXTURE_INDEX_BOSS,
			g_Boss[i].x - BOSS_WIDTH / 2, g_Boss[i].y - BOSS_HEIGHT / 2,
			0, 0,
			BOSS_WIDTH, BOSS_HEIGHT, 0);

		//HP�o�[
		Sprite_Draw(TEXTURE_INDEX_HPBAR,									//�e�N�X�`���Ǘ��ԍ�
			g_Boss[i].x - BOSS_WIDTH / 2 + 20.0f,							//�`����Wx
			g_Boss[i].y - BOSS_HEIGHT / 2 - 20.0f,							//�`����Wy
			0, 0,															//�e�N�X�`���؂�����Wx,y
			10 * g_Boss[i].Life, 10,										//�e�N�X�`���؂��蕝x,y
			10.0f * 0.5f,													//���S���Wx
			10.0f * 0.5f,													//���S���Wy
			1.0f,															//�g�嗦x����
			1.0f,															//�g�嗦y����
			0.0f,															//��]�p�x(���W�A��)
			g_Boss[i].HpColor);												//�`�悷��F
	}
}

void Boss_Create(float x, float y)
{
	for (int i = 0; i < BOSS_MAX; i++)
	{
		// �������G�����łɗL����������H
		if (g_Boss[i].enable)
		{
			continue;
		}

		// ���G�̍��W�Ɉ����̒l��������
		g_Boss[i].x = x;
		g_Boss[i].y = y;
		g_Boss[i].Life = 10;

		//�|�W�V�����̈ʒu�X�V
		g_Boss[i].col_circle.pos.x = g_Boss[i].x;
		g_Boss[i].col_circle.pos.y = g_Boss[i].y;
		g_Boss[i].col_circle.r = 55.0f;					//���G�̔��a�𑗂��Ă���

		// ���G��L���ɂ���
		g_Boss[i].enable = true;

		break;
	}
}

void Boss_Destroy(int index)
{
	g_Boss[index].Life += -1;
	if (g_Boss[index].Life <= 0)
	{
		AddScore(20);
		g_Boss[index].enable = false;
	}
}

bool Boss_IsEnable(int index)
{
	return g_Boss[index].enable;
}

CIRCLE* Boss_GetCircle(int index)
{
	return (&g_Boss[index].col_circle);
}

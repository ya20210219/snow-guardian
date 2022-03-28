#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "player.h"


#define BULLET_WIDTH   (32)
#define BULLET_HEIGHT  (32)
#define BULLET_SPEED_X (-10.0f)
#define BULLET_SPEED_Y (-10.0f)


/*------------------------------------------------------------------------------
   �\���̐錾
------------------------------------------------------------------------------*/
typedef struct Bullet_tag
{
	float	x, y;
	float	rotation;
	int     pattern;
	bool	enable;

	CIRCLE  col_circle;
} Bullet;


/*------------------------------------------------------------------------------
   �O���[�o���ϐ��錾
------------------------------------------------------------------------------*/
static Bullet g_Bullets[BULLET_MAX];
static int    g_BulletsDirection = 0;


/*------------------------------------------------------------------------------
   �֐���`
------------------------------------------------------------------------------*/

//������
void Bullet_Initialize(void)
{
	for (int i = 0; i < BULLET_MAX; i++) {
		g_Bullets[i].enable = false;
	}
}

//�X�V����
void Bullet_Update(void)
{
	for (int i = 0; i < BULLET_MAX; i++) {

		if (g_Bullets[i].enable) {
			g_Bullets[i].rotation += 2.0f;
			if (g_Bullets[i].pattern == 0)	//S
			{
				g_Bullets[i].x += (BULLET_SPEED_X - BULLET_SPEED_X);
				g_Bullets[i].y += (-1 * BULLET_SPEED_Y);
			}
			if (g_Bullets[i].pattern == 1)	//A
			{
				g_Bullets[i].x += BULLET_SPEED_X;
				g_Bullets[i].y += (BULLET_SPEED_Y - BULLET_SPEED_Y);
			}
			if (g_Bullets[i].pattern == 2)	//D
			{
				g_Bullets[i].x += (-1 * BULLET_SPEED_X);
				g_Bullets[i].y += (BULLET_SPEED_Y - BULLET_SPEED_Y);
			}
			if (g_Bullets[i].pattern == 3)	//W
			{
				g_Bullets[i].x += (BULLET_SPEED_X - BULLET_SPEED_X);
				g_Bullets[i].y += BULLET_SPEED_Y;
			}
			if (g_Bullets[i].pattern == 4)	//WA
			{
				g_Bullets[i].x += BULLET_SPEED_X;
				g_Bullets[i].y += BULLET_SPEED_Y;
			}
			if (g_Bullets[i].pattern == 5)	//WD
			{
				g_Bullets[i].x += (-1 * BULLET_SPEED_X);
				g_Bullets[i].y += BULLET_SPEED_Y;
			}
			if (g_Bullets[i].pattern == 6)	//SD
			{
				g_Bullets[i].x += (-1 * BULLET_SPEED_X);
				g_Bullets[i].y += (-1 * BULLET_SPEED_Y);
			}
			if (g_Bullets[i].pattern == 7)	//SA
			{
				g_Bullets[i].x += BULLET_SPEED_X;
				g_Bullets[i].y += (-1 * BULLET_SPEED_Y);
			}


			//�����蔻��p��CIRCLE�����W���X�V
			g_Bullets[i].col_circle.pos.x = g_Bullets[i].x;
			g_Bullets[i].col_circle.pos.y = g_Bullets[i].y;

			// ��ʊO�ɏo����
			int tw = Texture_GetWidth(TEXTURE_INDEX_BULLET);
			int th = Texture_GetHeight(TEXTURE_INDEX_BULLET);

			if (g_Bullets[i].x - tw * 0.5f > SCREEN_WIDTH ||
				g_Bullets[i].x + tw * 0.5f < (SCREEN_WIDTH - SCREEN_WIDTH) ||
				g_Bullets[i].y + th * 0.5f > SCREEN_HEIGHT ||
				g_Bullets[i].y - th * 0.5f < (SCREEN_HEIGHT - SCREEN_HEIGHT))
			{
 				g_Bullets[i].enable = false;
			}
		}
	}
}

//�`�揈��
void Bullet_Draw(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullets[i].enable)
		{
			int tw = Texture_GetWidth(TEXTURE_INDEX_BULLET);
			int th = Texture_GetHeight(TEXTURE_INDEX_BULLET);
			Sprite_Draw(TEXTURE_INDEX_BULLET,
				g_Bullets[i].x - tw * 0.5f, g_Bullets[i].y - th * 0.5f,
				0, 0, tw, th, tw * 0.5f, th * 0.5f, 1.0f, 1.0f, g_Bullets[i].rotation, 0);
		}
	}
}

void Bullet_Create(float x, float y, int pattern)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		// �����e�����łɗL����������H
		if (g_Bullets[i].enable)
		{
			continue;
		}

		// �e�̍��W�Ɉ����̒l��������
		g_Bullets[i].x = x;
		g_Bullets[i].y = y;
		g_Bullets[i].pattern = pattern;


		g_Bullets[i].col_circle.pos.x = g_Bullets[i].x;
		g_Bullets[i].col_circle.pos.y = g_Bullets[i].y;

		g_Bullets[i].col_circle.r = 18.0f;

		// �e��L���ɂ���
		g_Bullets[i].enable = true;

		break;
	}
}

void Bullet_Destroy(int index)
{
	g_Bullets[index].enable = false;
}

bool Bullet_IsEnable(int index)
{
	return g_Bullets[index].enable;
}

CIRCLE* Bullet_GetCircle(int index)
{
	return (&g_Bullets[index].col_circle);
}



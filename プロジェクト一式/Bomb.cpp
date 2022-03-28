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
   �\���̐錾
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
   �O���[�o���ϐ��錾
------------------------------------------------------------------------------*/
static BOMB g_Bombs[BOMB_MAX];
static BombSkill g_BombSkill[2];
static int  g_BombsDirection = 0;

static bool  g_BombSkillflg;
static int  g_BombSkillDrawNum;
static int  g_BombLifeSpan;


/*------------------------------------------------------------------------------
   �֐���`
------------------------------------------------------------------------------*/

//������
void Bomb_Initialize(void)
{
	for (int i = 0; i < BOMB_MAX; i++) {
		g_Bombs[i].enable = false;
	}

	g_BombSkillflg = false;
	g_BombLifeSpan = 300;
	g_BombSkillDrawNum = 0;
}

//�X�V����
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
			
			//�����蔻��p��CIRCLE�����W���X�V
			g_Bombs[i].col_circle.pos.x = g_Bombs[i].x;
			g_Bombs[i].col_circle.pos.y = g_Bombs[i].y;

		}
	}

	for (int i = 0; i < 2; i++)
	{
		g_BombSkill[i].PosX = SCREEN_WIDTH - SCREEN_WIDTH + 150;
		g_BombSkill[i].PosY = SCREEN_HEIGHT - 50;
	}

	//�{��(�ł��X)
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

//�`�揈��
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

		//�{���X�L���`��
		Sprite_Draw(TEXTURE_INDEX_BOMB_SKILL,					//�e�N�X�`���Ǘ��ԍ�
			g_BombSkill[1].PosX,								//�`����Wx
			g_BombSkill[1].PosY,								//�`����Wy
			0, 0,												//�e�N�X�`���؂�����Wx,y
			64, 80,												//�e�N�X�`���؂��蕝x,y
			64 * 0.5f,											//���S���Wx
			80 * 0.5f,											//���S���Wy
			1.0f,												//�g�嗦x����
			1.0f,												//�g�嗦y����
			0.0f,												//��]�p�x(���W�A��)
			4);													//�`��̐F

		//�{���X�L���N�[���_�E���`��
		if (g_BombSkillflg == false)
		{
			Sprite_Draw(TEXTURE_INDEX_BOMB_SKILL,					//�e�N�X�`���Ǘ��ԍ�
				g_BombSkill[0].PosX,								//�`����Wx
				g_BombSkill[0].PosY,								//�`����Wy
				0, 0,												//�e�N�X�`���؂�����Wx,y
				64, (8 * (g_BombSkillDrawNum / 3)),					//�e�N�X�`���؂��蕝x,y
				64 * 0.5f,											//���S���Wx
				80 * 0.5f,											//���S���Wy
				1.0f,												//�g�嗦x����
				1.0f,												//�g�嗦y����
				0.0f,												//��]�p�x(���W�A��)
				0);													//�`��̐F
		}

		if (g_BombSkillflg == true)
		{
			Sprite_Draw(TEXTURE_INDEX_BOMB_SKILL,					//�e�N�X�`���Ǘ��ԍ�
				g_BombSkill[0].PosX,								//�`����Wx
				g_BombSkill[0].PosY,								//�`����Wy
				0, 0,												//�e�N�X�`���؂�����Wx,y
				64, 80,												//�e�N�X�`���؂��蕝x,y
				64 * 0.5f,											//���S���Wx
				80 * 0.5f,											//���S���Wy
				1.0f,												//�g�嗦x����
				1.0f,												//�g�嗦y����
				0.0f,												//��]�p�x(���W�A��)
				0);													//�`��̐F
		}
	}
}

void Bomb_Create(float x, float y)
{
	for (int i = 0; i < BOMB_MAX; i++)
	{
		// �����{�������łɗL����������H
		if (g_Bombs[i].enable)
		{
			continue;
		}

		// �{���̍��W�Ɉ����̒l��������
		g_Bombs[i].x = x;
		g_Bombs[i].y = y;


		g_Bombs[i].col_circle.pos.x = g_Bombs[i].x;
		g_Bombs[i].col_circle.pos.y = g_Bombs[i].y;

		g_Bombs[i].col_circle.r = 100.0f;

		// �{����L���ɂ���
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

//g_BombSkillDrawNum�̑����֐�
void AddDrawNum(int add)
{
	g_BombSkillDrawNum += add;
}


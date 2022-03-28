#include "main.h"
#include "texture.h"
#include "sprite.h"
#include <math.h>
#include "SnowJewel.h"



static SNOWJEWEL g_SnowJewel[MAX_SNOW_JEWEL];

void SnowJewel_Initialize(void)
{
	for (int i = 0; i < MAX_SNOW_JEWEL; i++) {
		g_SnowJewel[i].enable = false;
	}
}

void SnowJewel_Update(void)
{
	for (int i = 0; i < MAX_SNOW_JEWEL; i++) {

		if (!SnowJewel_IsEnable(i))
		{
			continue;
		}

		if (g_SnowJewel[i].Life >= 7)
		{
			g_SnowJewel[i].HpColor = 3;
		}

		if (g_SnowJewel[i].Life <= 6)
		{
			g_SnowJewel[i].HpColor = 2;
		}

		if (g_SnowJewel[i].Life <= 3)
		{
			g_SnowJewel[i].HpColor = 1;
		}
	}


}

void SnowJewel_Draw(void)
{
	for (int i = 0; i < MAX_SNOW_JEWEL; i++) {

		if (!SnowJewel_IsEnable(i))
		{
			continue;
		}

		int tw = Texture_GetWidth(TEXTURE_INDEX_SNOW_JEWEL);
		int th = Texture_GetHeight(TEXTURE_INDEX_SNOW_JEWEL);
		Sprite_Draw(TEXTURE_INDEX_SNOW_JEWEL,					//�e�N�X�`���Ǘ��ԍ�
			g_SnowJewel[i].posx,									//�`����Wx
			g_SnowJewel[i].posy,									//�`����Wy
			0, 0,												//�e�N�X�`���؂�����Wx,y
			tw, th,												//�e�N�X�`���؂��蕝x,y
			tw * 0.5f,											//���S���Wx
			th * 0.5f,											//���S���Wy
			1.0f,												//�g�嗦x����
			1.0f,												//�g�嗦y����
			0.0f,												//��]�p�x(���W�A��)
			0);

		//HP�o�[
		Sprite_Draw(TEXTURE_INDEX_HPBAR,									//�e�N�X�`���Ǘ��ԍ�
			g_SnowJewel[i].posx - SNOW_JEWEL_W / 2 + 20.0f,					//�`����Wx
			g_SnowJewel[i].posy - SNOW_JEWEL_H / 2 - 20.0f,					//�`����Wy
			0, 0,															//�e�N�X�`���؂�����Wx,y
			10 * g_SnowJewel[i].Life, 10,									//�e�N�X�`���؂��蕝x,y
			10.0f * 0.5f,													//���S���Wx
			10.0f * 0.5f,													//���S���Wy
			1.0f,															//�g�嗦x����
			1.0f,															//�g�嗦y����
			0.0f,															//��]�p�x(���W�A��)
			g_SnowJewel[i].HpColor);										//�`�悷��F
	}
}


void SnowJewel_Create(float x, float y)
{
	for (int i = 0; i < MAX_SNOW_JEWEL; i++)
	{
		// �������������łɗL����������H
		if (g_SnowJewel[i].enable)
		{
			continue;
		}

		// �����̍��W�Ɉ����̒l��������
		g_SnowJewel[i].posx = x;
		g_SnowJewel[i].posy = y;
		g_SnowJewel[i].Life = 9;

		//�|�W�V�����̈ʒu�X�V
		g_SnowJewel[i].col_circle.pos.x = g_SnowJewel[i].posx;
		g_SnowJewel[i].col_circle.pos.y = g_SnowJewel[i].posy;
		g_SnowJewel[i].col_circle.r = SNOW_JEWEL_W / 2;

		//������L���ɂ���
		g_SnowJewel[i].enable = true;

		break;
	}
}


void SnowJewel_Destroy(int index)
{
	g_SnowJewel[index].Life += -3;
	if (g_SnowJewel[index].Life <= 0)
	{
		g_SnowJewel[index].enable = false;
	}
}

void SnowJewel_Delete(int index)
{
	g_SnowJewel[index].Life += -99;
	if (g_SnowJewel[index].Life <= 0)
	{
		g_SnowJewel[index].enable = false;
	}
}

bool  SnowJewel_IsEnable(int index)
{
	return  g_SnowJewel[index].enable;
}

SNOWJEWEL* GetSnowJewel()
{
	return g_SnowJewel;
}

CIRCLE* SnowJewel_GetCircle(int index)
{
	return (&g_SnowJewel[index].col_circle);
}

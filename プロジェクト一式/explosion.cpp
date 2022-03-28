#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include <d3dx9.h>
#include "Friend.h"
#include "sound.h"
#include "explosion.h"

static Explosion g_Explosion[MAX_EXPLOSION];

void Explosion_Initialize(void)
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		g_Explosion[i].enable = false;
	}
}

void Explosion_Update(void)
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		if (g_Explosion[i].enable == true)
		{
			g_Explosion[i].frame += 1;
			if (g_Explosion[i].frame >= 3)
			{
				g_Explosion[i].cnt += 1;
				g_Explosion[i].frame = 0;
			}

			if (g_Explosion[i].cnt == 3 && g_Explosion[i].frame == 3)
			{
				g_Explosion[i].enable = false;
				g_Explosion[i].cnt = 0;
				g_Explosion[i].frame = 0;
			}
		}
	}

}

void Explosion_Draw(void)
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		// �������j�����łɗL����������H
		if (!g_Explosion[i].enable)
		{
			continue;
		}	

		//�����`��
		Sprite_Draw(TEXTURE_INDEX_EXPLOSION,					//�e�N�X�`���Ǘ��ԍ�
			g_Explosion[i].PosX,								//�`����Wx
			g_Explosion[i].PosY,								//�`����Wy
			60 * g_Explosion[i].frame,
			60 * g_Explosion[i].cnt,							//�e�N�X�`���؂�����Wx,y
			60, 60,												//�e�N�X�`���؂��蕝x,y
			60 * 0.5f,											//���S���Wx
			60 * 0.5f,											//���S���Wy
			1.0f,												//�g�嗦x����
			1.0f,												//�g�嗦y����
			0.0f,												//��]�p�x(���W�A��)
			0);													//�`��̐F
	}

}

void Explosion_Create(float x, float y)
{

	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		// �������������łɗL����������H
		if (g_Explosion[i].enable)
		{
			continue;
		}

		// �����̍��W�Ɉ����̒l��������
		g_Explosion[i].PosX = x;
		g_Explosion[i].PosY = y;

		//������L���ɂ���
		g_Explosion[i].enable = true;

		break;
	}
}
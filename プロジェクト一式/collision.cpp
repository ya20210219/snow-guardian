
#include "collision.h"
#include "enemy.h"
#include "bullet.h"
#include "SnowJewel.h"
#include "player.h"
#include "Friend.h"
#include "sound.h"
#include "Boss.h"
#include "bomb.h"
#include "shop.h"


bool HitCheckCircle(CIRCLE* cA, CIRCLE* cB)
{
	//�x�N�g�����v�Z����
	D3DXVECTOR2 dist;	//����

	//B����A�Ɍ������x�N�g�����v�Z����
	dist = cA->pos - cB->pos;

	//�x�N�g��dist�̑傫�����v�Z����
	float length = D3DXVec2Length(&dist);

	//cA�̔��a��cB�̔��a�𑫂����l���v�Z����
	float size = cA->r + cB->r;

	//length��size�̔�r������size�̕����傫����΃q�b�g���Ă���Ƃ�������
	if (length < size)
		return true;

	//�q�b�g���Ă��Ȃ�
	return false;
}

float GetFloatCircle(CIRCLE* cA, CIRCLE* cB)
{
	//�x�N�g�����v�Z����
	D3DXVECTOR2 dist;	//����

	//B����A�Ɍ������x�N�g�����v�Z����
	dist = cA->pos - cB->pos;

	//�x�N�g��dist�̑傫�����v�Z����
	float length = D3DXVec2Length(&dist);

	return length;
}

bool HitCheckBox(BOX* bA, BOX* bB)
{
	//A�̏㉺���E
	float bA_left;
	float bA_right;
	float bA_top;
	float bA_bottom;

	//B�̏㉺���E
	float bB_left;
	float bB_right;
	float bB_top;
	float bB_bottom;

	//A�̋�`��ݒ�
	bA_left = bA->pos.x - (bA->size.x / 2);
	bA_right = bA->pos.x + (bA->size.x / 2);
	bA_top = bA->pos.y - (bA->size.y / 2);
	bA_bottom = bA->pos.y + (bA->size.y / 2);

	//B�̋�`��ݒ�
	bB_left = bB->pos.x - (bB->size.x / 2);
	bB_right = bB->pos.x + (bB->size.x / 2);
	bB_top = bB->pos.y - (bB->size.y / 2);
	bB_bottom = bB->pos.y + (bB->size.y / 2);

	//A�̍����B�̉E���傫�����������Ă�\��������
	if (bA_left < bB_right)
	{
		//A�̉E���B�̍������������������Ă�\��������
		if (bA_right > bB_left)
		{
			//A�̏���B�̉����傫�����������Ă�\��������
			if (bA_top < bB_bottom)
			{
				//A�̉����B�̏オ���������������Ă�\��������
				if (bA_bottom > bB_top)
				{
					//�S�Ă̔����ʂ����ꍇ�����蔻��ɂȂ�
					return true;
				}

			}
		}
	}

	//�q�b�g���Ă��Ȃ�
	return false;
}

void Collision_Bullet_vs_Enemy()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		//�e�̗L���t���O�`�F�b�N(true�łȂ��ꍇ)
		if (!Bullet_IsEnable(i))
			continue;

		for (int j = 0; j < ENEMY_MAX; j++)
		{
			//�G�̗L���t���O�`�F�b�N(true�łȂ��ꍇ)
			if (!Enemy_IsEnable(j))
				continue;

			if (HitCheckCircle(Bullet_GetCircle(i), Enemy_GetCircle(j)))
			{
				//�q�b�g���Ă���
				Enemy_Destroy(j);
				Bullet_Destroy(i);
				AddDrawNum(1);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_Bullet_vs_Boss()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		//�e�̗L���t���O�`�F�b�N(true�łȂ��ꍇ)
		if (!Bullet_IsEnable(i))
			continue;

		for (int j = 0; j < BOSS_MAX; j++)
		{
			//�G�̗L���t���O�`�F�b�N(true�łȂ��ꍇ)
			if (!Boss_IsEnable(j))
				continue;

			if (HitCheckCircle(Bullet_GetCircle(i), Boss_GetCircle(j)))
			{
				//�q�b�g���Ă���
				Boss_Destroy(j);
				Bullet_Destroy(i);
				AddDrawNum(1);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_Bomb_vs_Enemy()
{
	for (int i = 0; i < BOMB_MAX; i++)
	{
		//�e�̗L���t���O�`�F�b�N(true�łȂ��ꍇ)
		if (!Bomb_IsEnable(i))
			continue;

		for (int j = 0; j < ENEMY_MAX; j++)
		{
			//�G�̗L���t���O�`�F�b�N(true�łȂ��ꍇ)
			if (!Enemy_IsEnable(j))
				continue;

			if (HitCheckCircle(Bomb_GetCircle(i), Enemy_GetCircle(j)))
			{
				//�q�b�g���Ă���
				Enemy_Destroy(j);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_Bomb_vs_Boss()
{
	for (int i = 0; i < BOMB_MAX; i++)
	{
		//�e�̗L���t���O�`�F�b�N(true�łȂ��ꍇ)
		if (!Bomb_IsEnable(i))
			continue;

		for (int j = 0; j < BOSS_MAX; j++)
		{
			//�G�̗L���t���O�`�F�b�N(true�łȂ��ꍇ)
			if (!Boss_IsEnable(j))
				continue;

			if (HitCheckCircle(Bomb_GetCircle(i), Boss_GetCircle(j)))
			{
				//�q�b�g���Ă���
				Boss_Destroy(j);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_SnowJewel_vs_Enemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//�G�̗L���t���O�`�F�b�N(true�łȂ��ꍇ)
		if (!Enemy_IsEnable(i))
			continue;

		for (int j = 0; j < MAX_SNOW_JEWEL; j++)
		{
			if (!SnowJewel_IsEnable(j))
				continue;

			if (HitCheckCircle(Enemy_GetCircle(i), SnowJewel_GetCircle(j)))
			{
				//�q�b�g���Ă���
				SnowJewel_Destroy(j);
				Enemy_Destroy(i);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_SnowJewel_vs_Boss()
{
	for (int i = 0; i < BOSS_MAX; i++)
	{
		//�G�̗L���t���O�`�F�b�N(true�łȂ��ꍇ)
		if (!Boss_IsEnable(i))
			continue;

		for (int j = 0; j < MAX_SNOW_JEWEL; j++)
		{
			if (!SnowJewel_IsEnable(j))
				continue;

			if (HitCheckCircle(Boss_GetCircle(i), SnowJewel_GetCircle(j)))
			{
				//�q�b�g���Ă���
				SnowJewel_Delete(j);
				Boss_Destroy(i);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_Player_vs_Enemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//�G�̗L���t���O�`�F�b�N(true�łȂ��ꍇ)
		if (!Enemy_IsEnable(i))
			continue;

		for (int j = 0; j < MAX_PLAYER; j++)
		{
			if (!Player_IsEnable(j))
				continue;

			if (HitCheckCircle(Enemy_GetCircle(i), Player_GetCircle(j)))
			{
				//�q�b�g���Ă���
				Player_Destroy(j);
				Enemy_Destroy(i);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_Friend_vs_Enemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//�G�̗L���t���O�`�F�b�N(true�łȂ��ꍇ)
		if (!Enemy_IsEnable(i))
			continue;

		for (int j = 0; j < MAX_FRIEND; j++)
		{
			if (!Friend_IsEnable(j))
				continue;

			if (HitCheckCircle(Enemy_GetCircle(i), Friend_GetCircle(j)))
			{
				//�q�b�g���Ă���
				Friend_Destroy(j);
				Enemy_Destroy(i);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_Player_vs_Boss()
{
	for (int i = 0; i < BOSS_MAX; i++)
	{
		//�G�̗L���t���O�`�F�b�N(true�łȂ��ꍇ)
		if (!Boss_IsEnable(i))
			continue;

		for (int j = 0; j < MAX_PLAYER; j++)
		{
			if (!Player_IsEnable(j))
				continue;

			if (HitCheckCircle(Boss_GetCircle(i), Player_GetCircle(j)))
			{
				//�q�b�g���Ă���
				Player_Destroy(j);
				Boss_Destroy(i);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_Friend_vs_Boss()
{
	for (int i = 0; i < BOSS_MAX; i++)
	{
		//�G�̗L���t���O�`�F�b�N(true�łȂ��ꍇ)
		if (!Boss_IsEnable(i))
			continue;

		for (int j = 0; j < MAX_FRIEND; j++)
		{
			if (!Friend_IsEnable(j))
				continue;

			if (HitCheckCircle(Boss_GetCircle(i), Friend_GetCircle(j)))
			{
				//�q�b�g���Ă���
				Friend_Destroy(j);
				Boss_Destroy(i);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
}

void Collision_Player_vs_Shop()
{
	for (int i = 0; i < MAX_SHOP; i++)
	{
		//�G�̗L���t���O�`�F�b�N(true�łȂ��ꍇ)
		if (!Shop_IsEnable(i))
			continue;

		for (int j = 0; j < MAX_PLAYER; j++)
		{
			if (!Player_IsEnable(j))
				continue;

			if (HitCheckCircle(Shop_GetCircle(i), Player_GetCircle(j)))
			{
				//�q�b�g���Ă���
				Shop_Activate(i);

				StopSound(SOUND_LABEL_BGM001);
				PlaySound(SOUND_LABEL_SHOP_BGM);
			}
		}
	}
}
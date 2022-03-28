#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include <d3dx9.h>
#include "bullet.h"
#include "player.h"
#include "sound.h"
#include "Friend.h"
#include "bomb.h"
#include "shop.h"

static int g_PlayerAnimation;
static int g_PlayerBulletPattern;
static int g_PlayerMoveAnimation;
static int g_AnimeFrame;
static int g_PlayerBulletCount;
static int g_BulletRate;
static bool g_isBulletDual;

static Player g_Player[MAX_PLAYER];

void Player_Initialize(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_Player[i].enable = false;
	}

	g_PlayerAnimation = 0;
	g_PlayerMoveAnimation = 0;
	g_PlayerBulletPattern = 0;
	g_AnimeFrame = 0;
	g_isBulletDual = false;
}

void Player_Update(void)
{
	D3DXVECTOR2 vecSpeed(0.0f, 0.0f);
	g_BulletRate = 10;

	g_BulletRate = 10 - Shop_BulletRate();
	g_isBulletDual = Shop_BulletDual();

	for (int i = 0; i < MAX_PLAYER; i++) {

		if (!Player_IsEnable(i))
		{
			continue;
		}

		if (Keyboard_IsPress(DIK_S)) {
			vecSpeed += D3DXVECTOR2(0.0f, 1.0f);
			g_PlayerBulletPattern = 0;
		}

		if (Keyboard_IsPress(DIK_A)) {
			vecSpeed += D3DXVECTOR2(-1.0f, 0.0f);
			g_PlayerMoveAnimation = 0;
			g_PlayerBulletPattern = 1;
		}

		if (Keyboard_IsPress(DIK_D)) {
			vecSpeed += D3DXVECTOR2(1.0f, 0.0f);
			g_PlayerMoveAnimation = 1;
			g_PlayerBulletPattern = 2;
		}

		if (Keyboard_IsPress(DIK_W)) {
			vecSpeed += D3DXVECTOR2(0.0f, -1.0f);
			g_PlayerBulletPattern = 3;
		}


		if (Keyboard_IsPress(DIK_W) && Keyboard_IsPress(DIK_A)) {
			vecSpeed += D3DXVECTOR2(-1.0f, -1.0f);
			g_PlayerMoveAnimation = 0;
			g_PlayerBulletPattern = 4;
		}

		if (Keyboard_IsPress(DIK_W) && Keyboard_IsPress(DIK_D)) {
			vecSpeed += D3DXVECTOR2(1.0f, -1.0f);
			g_PlayerMoveAnimation = 1;
			g_PlayerBulletPattern = 5;
		}

		if (Keyboard_IsPress(DIK_S) && Keyboard_IsPress(DIK_D)) {
			vecSpeed += D3DXVECTOR2(1.0f, 1.0f);
			g_PlayerBulletPattern = 6;
			g_PlayerMoveAnimation = 1;
		}

		if (Keyboard_IsPress(DIK_S) && Keyboard_IsPress(DIK_A)) {
			vecSpeed += D3DXVECTOR2(-1.0f, 1.0f);
			g_PlayerBulletPattern = 7;
			g_PlayerMoveAnimation = 0;
		}

		D3DXVec2Normalize(&vecSpeed, &vecSpeed);	//�ǂ�Ȓ����ł�1.0f�ɐ��K������

		if (Keyboard_IsPress(DIK_W)
			|| Keyboard_IsPress(DIK_A)
			|| Keyboard_IsPress(DIK_S)
			|| Keyboard_IsPress(DIK_D)) {
			vecSpeed *= 0.2f;			//���x
		}

		g_Player[0].PlayerSpeed += vecSpeed;			//�������Ă���

		g_Player[0].PlayerX += g_Player[0].PlayerSpeed.x;
		g_Player[0].PlayerY += g_Player[0].PlayerSpeed.y;

		g_Player[0].PlayerSpeed *= 0.96f;				//����

		int tw = Texture_GetWidth(TEXTURE_INDEX_PLAYER) / 2;
		int th = Texture_GetHeight(TEXTURE_INDEX_PLAYER);

		g_Player[0].PlayerX = min(g_Player[0].PlayerX, SCREEN_WIDTH - tw * 0.5f);			//min�͗����̐��l���ׂď����������̗p����
		g_Player[0].PlayerX = max(g_Player[0].PlayerX, tw * 0.5f);							//max�͗����̐��l���ׂđ傫�������̗p����
		g_Player[0].PlayerY = min(g_Player[0].PlayerY, SCREEN_HEIGHT - th * 0.5f);
		g_Player[0].PlayerY = max(g_Player[0].PlayerY, th * 0.5f);

		g_PlayerBulletCount++;

		if (g_PlayerBulletCount >= 60)
		{
			g_PlayerBulletCount = 0;
		}

		// �e�𔭎˂��鏈��
		if (Keyboard_IsPress(DIK_SPACE) && g_PlayerBulletCount % g_BulletRate == 0 && g_isBulletDual == false)
		{
			PlaySound(SOUND_LABEL_SE_SHOT);
			Bullet_Create(g_Player[0].PlayerX + 20, g_Player[0].PlayerY + 30, g_PlayerBulletPattern);
		}

		if (Keyboard_IsPress(DIK_SPACE) && g_PlayerBulletCount % g_BulletRate == 0 && g_isBulletDual == true)
		{
			if (g_PlayerBulletPattern != 0 && g_PlayerBulletPattern != 3)
			{
				PlaySound(SOUND_LABEL_SE_SHOT);
				Bullet_Create(g_Player[0].PlayerX + 20, g_Player[0].PlayerY + 50, g_PlayerBulletPattern);
				Bullet_Create(g_Player[0].PlayerX + 20, g_Player[0].PlayerY + 10, g_PlayerBulletPattern);
			}

			else if (g_PlayerBulletPattern == 0 || g_PlayerBulletPattern == 3)
			{
				PlaySound(SOUND_LABEL_SE_SHOT);
				Bullet_Create(g_Player[0].PlayerX - 10, g_Player[0].PlayerY + 30, g_PlayerBulletPattern);
				Bullet_Create(g_Player[0].PlayerX + 40, g_Player[0].PlayerY + 30, g_PlayerBulletPattern);
			}

		}

		//�|�W�V�����̈ʒu�X�V
		g_Player[i].col_circle.pos.x = g_Player[i].PlayerX;
		g_Player[i].col_circle.pos.y = g_Player[i].PlayerY;
		g_Player[i].col_circle.r = 20.0f;

	}
}

void Player_Draw(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		// �����Ⴞ��܂����łɗL����������H
		if (!g_Player[i].enable)
		{
			continue;
		}

		int tw = Texture_GetWidth(TEXTURE_INDEX_PLAYER) / 2;
		int th = Texture_GetHeight(TEXTURE_INDEX_PLAYER);

		Sprite_Draw(TEXTURE_INDEX_PLAYER,						//�e�N�X�`���Ǘ��ԍ�
			g_Player[0].PlayerX/* - 16.0f*/,					//�`����Wx
			g_Player[0].PlayerY/* - 16.0f*/,					//�`����Wy
			40 * g_PlayerMoveAnimation, 0,						//�e�N�X�`���؂�����Wx,y
			40, 60,												//�e�N�X�`���؂��蕝x,y
			tw * 0.5f,											//���S���Wx
			th * 0.5f,											//���S���Wy
			1.0f,												//�g�嗦x����
			1.0f,												//�g�嗦y����
			0.0f,												//��]�p�x(���W�A��)
			0													//�`�悷��F�̃p�^�[���ԍ�
		);
	}
}


void Player_Create(float x, float y)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		// �����Ⴞ��܂����łɗL����������H
		if (g_Player[i].enable)
		{
			continue;
		}

		// �Ⴞ��܂̍��W�Ɉ����̒l��������
		g_Player[i].PlayerX = x;
		g_Player[i].PlayerY = y;

		//�|�W�V�����̈ʒu�X�V
		g_Player[i].col_circle.pos.x = g_Player[i].PlayerX - 20.0f;
		g_Player[i].col_circle.pos.y = g_Player[i].PlayerY - 30.0f;
		g_Player[i].col_circle.r = 20.0f;

		//�Ⴞ��܂�L���ɂ���
		g_Player[i].enable = true;

		break;
	}
}

void Player_Destroy(int index)
{
	g_Player[index].enable = false;
}

bool  Player_IsEnable(int index)
{
	return  g_Player[index].enable;
}

CIRCLE* Player_GetCircle(int index)
{
	return (&g_Player[index].col_circle);
}

Player* GetPlayer()
{
	return g_Player;
}
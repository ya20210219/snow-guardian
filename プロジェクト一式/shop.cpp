#include "main.h"
#include "texture.h"
#include "sprite.h"
#include <math.h>
#include "Shop.h"
#include "input.h"
#include "player.h"
#include "Friend.h"
#include "bomb.h"
#include "Score.h"
#include "sound.h"

#define TEXT_POSX
#define TEXT_POSY

static Shop g_Shop[MAX_SHOP];
static float g_WitchPosX;
static float g_WitchPosY;
static int g_F_LifeSpanPlus;
static int g_B_LifeSpanPlus;
static int g_B_Rate;
static bool g_B_Dual;
static int g_ShopListNum;
static bool g_ShopStay;
static int g_ShopStayCnt;
static float g_ShopArrowPosX;
static float g_ShopArrowPosY;
static int g_ShopTxtNum;

static int g_ShopList1Value;
static int g_ShopList2Value;
static int g_ShopList3Value;
static int g_ShopList4Value;

static bool g_ShopList1Soldout;
static bool g_ShopList2Soldout;
static bool g_ShopList3Soldout;
static bool g_ShopList4Soldout;

static bool g_ShopNewflg;
static bool g_ShopNotEnough;

void Shop_Initialize(void)
{
	for (int i = 0; i < MAX_SHOP; i++) {
		g_Shop[i].enable = false;
		g_Shop[i].Shopflg = false;
	}

	g_WitchPosX = 300.0f;
	g_WitchPosY = SCREEN_HEIGHT / 3;

	g_F_LifeSpanPlus = 0;
	g_ShopArrowPosX = 635.0f;
	g_ShopArrowPosY = 90.0f;
	g_ShopTxtNum = 0;
	g_ShopList1Value = 200;
	g_ShopList2Value = 3600;
	g_ShopList3Value = 500;
	g_ShopList4Value = 200;
	g_ShopList1Soldout = false;
	g_ShopList2Soldout = false;
	g_ShopList3Soldout = false;
	g_ShopList4Soldout = false;
	g_ShopNotEnough = false;
	g_ShopNewflg = true;
}

void Shop_Update(void)
{
	Player* pPlayer = GetPlayer();
	int nScore = ScoreCount();

	for (int i = 0; i < MAX_SHOP; i++) {

		if (!Shop_IsActivate(i))
		{
			continue;
		}

		if (Keyboard_IsPress(DIK_BACK))
		{
			g_Shop[i].Shopflg = false;
			g_Shop[i].enable = true;
			pPlayer[i].PlayerX = SCREEN_WIDTH * 0.25f;
			pPlayer[i].PlayerY = SCREEN_HEIGHT * 0.5f;


			StopSound(SOUND_LABEL_SHOP_BGM);
			PlaySound(SOUND_LABEL_BGM001);
		}

		if (Keyboard_IsPress(DIK_1))
		{
			g_ShopListNum = 1;
			g_ShopTxtNum = 1;
			g_ShopArrowPosY = 90.0f;
		}
		if (Keyboard_IsPress(DIK_2))
		{
			g_ShopListNum = 2;
			g_ShopTxtNum = 2;
			g_ShopArrowPosY = 220.0f;
		}
		if (Keyboard_IsPress(DIK_3))
		{
			g_ShopListNum = 3;
			g_ShopTxtNum = 3;
			g_ShopArrowPosY = 350.0f;
		}
		if (Keyboard_IsPress(DIK_4))
		{
			g_ShopListNum = 4;
			g_ShopTxtNum = 4;
			g_ShopArrowPosY = 490.0f;
		}


		//�U�����xUP
		if (g_ShopListNum == 1 && nScore >= g_ShopList1Value && g_ShopStay == false && Keyboard_IsPress(DIK_RETURN))
		{
			g_B_Rate += 1;
			if (g_B_Rate >= 8)
			{
				g_B_Rate = 8;
				g_ShopList1Soldout = true;
			}
			AddScore(-g_ShopList1Value);
			g_ShopStay = true;
			PlaySound(SOUND_LABEL_SE_SHOP_BUY);
			g_ShopList1Value += (g_ShopList1Value / 2);
		}
				
		//�U��2��
		if (g_ShopListNum == 2 && nScore >= g_ShopList2Value && g_ShopStay == false && Keyboard_IsPress(DIK_RETURN))
		{
			g_B_Dual = true;
			g_ShopList2Soldout = true;
			AddScore(-g_ShopList2Value);
			PlaySound(SOUND_LABEL_SE_SHOP_BUY);
		}

		//�����{�����ʎ��ԉ���
		if (g_ShopListNum == 3 && nScore >= g_ShopList3Value && g_ShopStay == false && Keyboard_IsPress(DIK_RETURN))
		{
			g_B_LifeSpanPlus += 120;
			if (g_B_LifeSpanPlus >= 600)
			{
				g_B_LifeSpanPlus = 600;
				g_ShopList3Soldout = true;
			}
			AddScore(-g_ShopList3Value);
			g_ShopStay = true;
			PlaySound(SOUND_LABEL_SE_SHOP_BUY);
			g_ShopList3Value += (g_ShopList3Value / 2);
		}

		//���ԏ������ԉ���
		if (g_ShopListNum == 4 && nScore >= g_ShopList4Value && g_ShopStay == false && Keyboard_IsPress(DIK_RETURN))
		{
			g_F_LifeSpanPlus += 300;
			if (g_F_LifeSpanPlus >= 1800)
			{
				g_F_LifeSpanPlus = 1800;
				g_ShopList4Soldout = true;
			}
			AddScore(-g_ShopList4Value);
			g_ShopStay = true;
			PlaySound(SOUND_LABEL_SE_SHOP_BUY);
			g_ShopList4Value += (g_ShopList4Value / 2);
		}

		//�V���b�v1�̃X�R�A������ĂȂ�����
		if (g_ShopListNum == 1 && nScore < g_ShopList1Value && g_ShopStay == false && Keyboard_IsPress(DIK_RETURN))
		{
			g_ShopNotEnough = true;
		}
		//�V���b�v2�̃X�R�A������ĂȂ�����
		if (g_ShopListNum == 2 && nScore < g_ShopList2Value && g_ShopStay == false && Keyboard_IsPress(DIK_RETURN))
		{
			g_ShopNotEnough = true;
		}
		//�V���b�v3�̃X�R�A������ĂȂ�����
		if (g_ShopListNum == 3 && nScore < g_ShopList3Value && g_ShopStay == false && Keyboard_IsPress(DIK_RETURN))
		{
			g_ShopNotEnough = true;
		}
		//�V���b�v4�̃X�R�A������ĂȂ�����
		if (g_ShopListNum == 4 && nScore < g_ShopList4Value && g_ShopStay == false && Keyboard_IsPress(DIK_RETURN))
		{
			g_ShopNotEnough = true;
		}
	}

	//�܂��ǂ���`�̕`�您��јA�őj�~
	if (g_ShopStay == true)
	{
		g_ShopStayCnt++;
		if (g_ShopStayCnt >= 90)
		{
			g_ShopStay = false;
			g_ShopTxtNum = 0;
			g_ShopStayCnt = 0;
		}
	}

	//�������b�Z�[�W����
	if (g_ShopTxtNum == 5)
	{
		g_ShopStayCnt++;
		if (g_ShopStayCnt >= 120 || Keyboard_IsPress(DIK_1) || Keyboard_IsPress(DIK_2) || Keyboard_IsPress(DIK_3) || Keyboard_IsPress(DIK_4))
		{
			g_ShopTxtNum = 0;
			g_ShopNewflg = false;
			g_ShopStayCnt = 0;
		}
	}

	//�X�R�A������Ȃ�
	if (g_ShopNotEnough == true)
	{
		g_ShopStayCnt++;
		if (g_ShopStayCnt >= 60)
		{
			g_ShopNotEnough = false;
			g_ShopStayCnt = 0;
		}
	}
}

void Shop_Draw(void)
{
	for (int i = 0; i < MAX_SHOP; i++) {

		if (!Shop_IsEnable(i))
		{
			continue;
		}

		if (g_Shop[i].enable == true)
		{
			int tw = Texture_GetWidth(TEXTURE_INDEX_SHOP);
			int th = Texture_GetHeight(TEXTURE_INDEX_SHOP);

			//�X(���@�w)
			Sprite_Draw(TEXTURE_INDEX_SHOP,							//�e�N�X�`���Ǘ��ԍ�
				g_Shop[i].posx,										//�`����Wx
				g_Shop[i].posy,										//�`����Wy
				0, 0,												//�e�N�X�`���؂�����Wx,y
				tw, th,												//�e�N�X�`���؂��蕝x,y
				tw * 0.5f,											//���S���Wx
				th * 0.5f,											//���S���Wy
				1.0f,												//�g�嗦x����
				1.0f,												//�g�嗦y����
				0.0f,												//��]�p�x(���W�A��)
				0);
		}		
	}

	for (int i = 0; i < MAX_SHOP; i++)
	{
		//�X����
		if (g_Shop[i].Shopflg == true)
		{
			int tw = Texture_GetWidth(TEXTURE_INDEX_SHOP_BG);
			int th = Texture_GetHeight(TEXTURE_INDEX_SHOP_BG);

			//�X�w�i
			Sprite_Draw(TEXTURE_INDEX_SHOP_BG,							//�e�N�X�`���Ǘ��ԍ�
				SCREEN_WIDTH * 0.5f,								//�`����Wx
				SCREEN_HEIGHT * 0.5f,								//�`����Wy
				0, 0,												//�e�N�X�`���؂�����Wx,y
				tw, th,												//�e�N�X�`���؂��蕝x,y
				tw * 0.5f,											//���S���Wx
				th * 0.5f,											//���S���Wy
				1.0f,												//�g�嗦x����
				1.0f,												//�g�嗦y����
				0.0f,												//��]�p�x(���W�A��)
				0);

			//�����`��
			Sprite_Draw(TEXTURE_INDEX_WITCH,						//�e�N�X�`���Ǘ��ԍ�
				g_WitchPosX,										//�`����Wx
				g_WitchPosY,										//�`����Wy
				0, 0,												//�e�N�X�`���؂�����Wx,y
				350, 300,											//�e�N�X�`���؂��蕝x,y
				350 * 0.5f,											//���S���Wx
				300 * 0.5f,											//���S���Wy
				1.0f,												//�g�嗦x����
				1.0f,												//�g�嗦y����
				0.0f,												//��]�p�x(���W�A��)
				0);

			//�A�C�e���I����
			Sprite_Draw(TEXTURE_INDEX_SHOP_ARROW,						//�e�N�X�`���Ǘ��ԍ�
				g_ShopArrowPosX,										//�`����Wx
				g_ShopArrowPosY,										//�`����Wy
				0, 0,												//�e�N�X�`���؂�����Wx,y
				80, 80,											//�e�N�X�`���؂��蕝x,y
				80 * 0.5f,											//���S���Wx
				80 * 0.5f,											//���S���Wy
				1.0f,												//�g�嗦x����
				1.0f,												//�g�嗦y����
				0.0f,												//��]�p�x(���W�A��)
				0);

			//�������b�Z�[�W
			if (g_ShopTxtNum == 5)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_TXT_WELCOME,				//�e�N�X�`���Ǘ��ԍ�
					320,												//�`����Wx
					SCREEN_HEIGHT - 100,								//�`����Wy
					0, 0,												//�e�N�X�`���؂�����Wx,y
					625, 200,											//�e�N�X�`���؂��蕝x,y
					625 * 0.5f,											//���S���Wx
					200 * 0.5f,											//���S���Wy
					1.0f,												//�g�嗦x����
					1.0f,												//�g�嗦y����
					0.0f,												//��]�p�x(���W�A��)
					0);
			}

			//��{���b�Z�[�W
			if (g_ShopTxtNum == 0 && g_ShopStay == false)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_TXT_DEFAULT,				//�e�N�X�`���Ǘ��ԍ�
					320,												//�`����Wx
					SCREEN_HEIGHT - 100,								//�`����Wy
					0, 0,												//�e�N�X�`���؂�����Wx,y
					625, 200,											//�e�N�X�`���؂��蕝x,y
					625 * 0.5f,											//���S���Wx
					200 * 0.5f,											//���S���Wy
					1.0f,												//�g�嗦x����
					1.0f,												//�g�嗦y����
					0.0f,												//��]�p�x(���W�A��)
					0);
			}


			//�A�C�e���P�̃��b�Z�[�W
			if (g_ShopTxtNum == 1 && g_ShopStay == false)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_TXT_LIST1,				//�e�N�X�`���Ǘ��ԍ�
					320,												//�`����Wx
					SCREEN_HEIGHT - 100,								//�`����Wy
					0, 0,												//�e�N�X�`���؂�����Wx,y
					625, 200,											//�e�N�X�`���؂��蕝x,y
					625 * 0.5f,											//���S���Wx
					200 * 0.5f,											//���S���Wy
					1.0f,												//�g�嗦x����
					1.0f,												//�g�嗦y����
					0.0f,												//��]�p�x(���W�A��)
					0);
			}

			if (g_ShopTxtNum == 2 && g_ShopStay == false)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_TXT_LIST2,				//�e�N�X�`���Ǘ��ԍ�
					320,												//�`����Wx
					SCREEN_HEIGHT - 100,								//�`����Wy
					0, 0,												//�e�N�X�`���؂�����Wx,y
					625, 200,											//�e�N�X�`���؂��蕝x,y
					625 * 0.5f,											//���S���Wx
					200 * 0.5f,											//���S���Wy
					1.0f,												//�g�嗦x����
					1.0f,												//�g�嗦y����
					0.0f,												//��]�p�x(���W�A��)
					0);
			}

			if (g_ShopTxtNum == 3 && g_ShopStay == false)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_TXT_LIST3,				//�e�N�X�`���Ǘ��ԍ�
					320,												//�`����Wx
					SCREEN_HEIGHT - 100,								//�`����Wy
					0, 0,												//�e�N�X�`���؂�����Wx,y
					625, 200,											//�e�N�X�`���؂��蕝x,y
					625 * 0.5f,											//���S���Wx
					200 * 0.5f,											//���S���Wy
					1.0f,												//�g�嗦x����
					1.0f,												//�g�嗦y����
					0.0f,												//��]�p�x(���W�A��)
					0);
			}

			if (g_ShopTxtNum == 4 && g_ShopStay == false)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_TXT_LIST4,				//�e�N�X�`���Ǘ��ԍ�
					320,												//�`����Wx
					SCREEN_HEIGHT - 100,								//�`����Wy
					0, 0,												//�e�N�X�`���؂�����Wx,y
					625, 200,											//�e�N�X�`���؂��蕝x,y
					625 * 0.5f,											//���S���Wx
					200 * 0.5f,											//���S���Wy
					1.0f,												//�g�嗦x����
					1.0f,												//�g�嗦y����
					0.0f,												//��]�p�x(���W�A��)
					0);
			}

			//�A�C�e��1������؂�̏ꍇ�\��
			if (g_ShopList1Soldout == true)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_SOLDOUT,					//�e�N�X�`���Ǘ��ԍ�
					SCREEN_WIDTH - (350 / 2),							//�`����Wx
					88.0f,													//�`����Wy
					0, 0,												//�e�N�X�`���؂�����Wx,y
					350, 95,											//�e�N�X�`���؂��蕝x,y
					350 * 0.5f,											//���S���Wx
					95 * 0.5f,											//���S���Wy
					1.0f,												//�g�嗦x����
					1.0f,												//�g�嗦y����
					0.0f,												//��]�p�x(���W�A��)
					0);
			}

			if (g_ShopList2Soldout == true)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_SOLDOUT,					//�e�N�X�`���Ǘ��ԍ�
					SCREEN_WIDTH - (350 / 2),							//�`����Wx
					218.0f,												//�`����Wy
					0, 0,												//�e�N�X�`���؂�����Wx,y
					350, 95,											//�e�N�X�`���؂��蕝x,y
					350 * 0.5f,											//���S���Wx
					95 * 0.5f,											//���S���Wy
					1.0f,												//�g�嗦x����
					1.0f,												//�g�嗦y����
					0.0f,												//��]�p�x(���W�A��)
					0);
			}

			if (g_ShopList3Soldout == true)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_SOLDOUT,					//�e�N�X�`���Ǘ��ԍ�
					SCREEN_WIDTH - (350 / 2),							//�`����Wx
					348.0f,												//�`����Wy
					0, 0,												//�e�N�X�`���؂�����Wx,y
					350, 95,											//�e�N�X�`���؂��蕝x,y
					350 * 0.5f,											//���S���Wx
					95 * 0.5f,											//���S���Wy
					1.0f,												//�g�嗦x����
					1.0f,												//�g�嗦y����
					0.0f,												//��]�p�x(���W�A��)
					0);
			}

			if (g_ShopList4Soldout == true)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_SOLDOUT,					//�e�N�X�`���Ǘ��ԍ�
					SCREEN_WIDTH - (350 / 2),							//�`����Wx
					488.0f,												//�`����Wy
					0, 0,												//�e�N�X�`���؂�����Wx,y
					350, 95,											//�e�N�X�`���؂��蕝x,y
					350 * 0.5f,											//���S���Wx
					95 * 0.5f,											//���S���Wy
					1.0f,												//�g�嗦x����
					1.0f,												//�g�嗦y����
					0.0f,												//��]�p�x(���W�A��)
					0);
			}

			//�X�R�A�s�����b�Z�[�W
			if (g_ShopNotEnough == true)
			{
				Sprite_Draw(TEXTURE_INDEX_SHOP_NOT_ENOUGH,				//�e�N�X�`���Ǘ��ԍ�
					320,												//�`����Wx
					SCREEN_HEIGHT - 100,								//�`����Wy
					0, 0,												//�e�N�X�`���؂�����Wx,y
					625, 200,											//�e�N�X�`���؂��蕝x,y
					625 * 0.5f,											//���S���Wx
					200 * 0.5f,											//���S���Wy
					1.0f,												//�g�嗦x����
					1.0f,												//�g�嗦y����
					0.0f,												//��]�p�x(���W�A��)
					0);
			}
		}
	}

	//�܂��ǂ���`�̕`��
	if (g_ShopStay == true && g_Shop[0].Shopflg == true)
	{
		Sprite_Draw(TEXTURE_INDEX_SHOP_TXT_THX,					//�e�N�X�`���Ǘ��ԍ�
			320,												//�`����Wx
			SCREEN_HEIGHT - 100,								//�`����Wy
			0, 0,												//�e�N�X�`���؂�����Wx,y
			625, 200,											//�e�N�X�`���؂��蕝x,y
			625 * 0.5f,											//���S���Wx
			200 * 0.5f,											//���S���Wy
			1.0f,												//�g�嗦x����
			1.0f,												//�g�嗦y����
			0.0f,												//��]�p�x(���W�A��)
			0);
	}
}


void Shop_Create(float x, float y)
{
	for (int i = 0; i < MAX_SHOP; i++)
	{
		// �����X�����łɗL����������H
		if (g_Shop[i].enable)
		{
			continue;
		}

		// �X�̍��W�Ɉ����̒l��������
		g_Shop[i].posx = x;
		g_Shop[i].posy = y;

		//�|�W�V�����̈ʒu�X�V
		g_Shop[i].col_circle.pos.x = g_Shop[i].posx;
		g_Shop[i].col_circle.pos.y = g_Shop[i].posy;
		g_Shop[i].col_circle.r = SHOP_W / 2;

		//�X��L���ɂ���
		g_Shop[i].enable = true;

		break;
	}
}

void Shop_Activate(int index)
{
	g_Shop[index].enable = false;
	g_Shop[index].Shopflg = true;
	if (g_ShopNewflg == true)
	{
		g_ShopTxtNum = 5;
	}

	if (g_ShopNewflg == false)
	{
		g_ShopTxtNum = 0;
	}

}

bool  Shop_IsEnable(int index)
{
	return  g_Shop[index].enable;
}

bool  Shop_IsActivate(int index)
{
	return  g_Shop[index].Shopflg;
}

CIRCLE* Shop_GetCircle(int index)
{
	return (&g_Shop[index].col_circle);
}

int Shop_FriendLifespan()
{
	return g_F_LifeSpanPlus;
}

int Shop_BombLifespan()
{
	return g_B_LifeSpanPlus;
}

int Shop_BulletRate()
{
	return g_B_Rate;
}

bool Shop_BulletDual()
{
	return g_B_Dual;
}

int Shop_List1Value()
{
	return g_ShopList1Value;
}

int Shop_List2Value()
{
	return g_ShopList2Value;
}

int Shop_List3Value()
{
	return g_ShopList3Value;
}

int Shop_List4Value()
{
	return g_ShopList4Value;
}

bool Shop_List1SoldOut()
{
	return g_ShopList1Soldout;
}

bool Shop_List2SoldOut()
{
	return g_ShopList2Soldout;
}

bool Shop_List3SoldOut()
{
	return g_ShopList3Soldout;
}

bool Shop_List4SoldOut()
{
	return g_ShopList4Soldout;
}

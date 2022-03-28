//-------------------------------------------------//
//[score.cpp]�X�R�A
//                      author:��   date:2020/06/09
//-------------------------------------------------//

#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "windows.h"
#include "Score.h"
#include "player.h"
#include "SnowJewel.h"
#include "shop.h"
#include <d3dx9.h>


//�}�N��-------------------------------------------------//



//�O���[�o���ϐ�-------------------------------------------------//

static int g_Score;
static bool g_ShopCheck;

static Score g_ScorePos[MAX_SCORE];
static Value g_ValuePos[4][MAX_SCORE];



//������-------------------------------------------------//
void Score_Initialize()
{
	g_Score = 0;

	for (int i = 0; i < MAX_SCORE; i++)
	{
		g_ScorePos[i].ScorePosX = SCORE_POS_X; 
		g_ScorePos[i].ScorePosY = SCORE_POS_Y;
		g_ScorePos[i].DrawScoreNumX = 0;
		g_ScorePos[i].DrawScoreNumY= 0;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < MAX_SCORE; j++)
		{
			g_ValuePos[i][j].ValuePosX = SCORE_POS_X;
			if (i == 0)
			{
				g_ValuePos[i][j].ValuePosY = 155.0f;
			}
			if (i == 1)
			{
				g_ValuePos[i][j].ValuePosY = 280.0f;
			}
			if (i == 2)
			{
				g_ValuePos[i][j].ValuePosY = 420.0f;
			}
			if (i == 3)
			{
				g_ValuePos[i][j].ValuePosY = 555.0f;
			}

			g_ValuePos[i][j].DrawValueNumX = 0;
			g_ValuePos[i][j].DrawValueNumY = 0;
		}
	}
}

//�X�V-------------------------------------------------//
void Score_Update()
{
	Player* pPlayer = GetPlayer();
	SNOWJEWEL* pSnowJewel = GetSnowJewel();

	//�Q�[���I�[�o�[�ɂȂ�����A���U���g���̃|�W�V�����ֈړ�������
	if (pPlayer->enable == false ||  pSnowJewel->enable == false)
	{
		for (int i = 0; i < MAX_SCORE; i++)
		{
			g_ScorePos[i].ScorePosX = SCORE_POS_X - ((SCREEN_WIDTH / 4) + (NUM_SIZE_X / 2));
			g_ScorePos[i].ScorePosY = SCORE_POS_Y + (SCREEN_HEIGHT / 3);
			g_ScorePos[i].DrawScoreNumX = 0;
			g_ScorePos[i].DrawScoreNumY = 0;	
		}
	}
}

//�`��-------------------------------------------------//
void Score_Draw()
{
	//�v�Z�p�ϐ��ɃX�R�A������
	int score = g_Score;  //�v�Z�p�ϐ�

	for (int i = 0; i < MAX_SCORE; i++)
	{
		int num = 0;				    //���������l�����
		g_ScorePos[i].DrawScoreNumY = 0;

		num = score % 10;				//�X�R�A��1�̈ʂ𔲂��o��
		score /= 10;					//�X�R�A��1�̈ʂ��炵�Ă���

		if (num >= 5)
		{
			g_ScorePos[i].DrawScoreNumY = 1;
			num -= 5;
		}

		g_ScorePos[i].DrawScoreNumX = num;

		int tw = Texture_GetWidth(TEXTURE_INDEX_NUMBER) / 5;
		int th = Texture_GetHeight(TEXTURE_INDEX_NUMBER) / 2;

		Sprite_Draw(TEXTURE_INDEX_NUMBER,						//�e�N�X�`���Ǘ��ԍ�
			g_ScorePos[i].ScorePosX - (NUM_SIZE_X * i),			//�`����Wx
			g_ScorePos[i].ScorePosY,							//�`����Wy
			g_ScorePos[i].DrawScoreNumX * NUM_SIZE_X,			//�e�N�X�`���؂�����Wx
			(int)(NUM_SIZE_Y * g_ScorePos[i].DrawScoreNumY),	//�e�N�X�`���؂�����Wy
			(int)(NUM_SIZE_X), (int)(NUM_SIZE_Y),			//�e�N�X�`���؂��蕝x,y
			tw * 0.5f,											//���S���Wx
			th * 0.5f,											//���S���Wy
			1.0f,												//�g�嗦x����
			1.0f,												//�g�嗦y����
			0.0f,												//��]�p�x(���W�A��)
			0);
	}

	g_ShopCheck = Shop_IsActivate(0);
	if (g_ShopCheck == true)
	{
		//�l�i�\���p
		for (int i = 0; i < 4; i++)
		{
			int value;
			bool SoldOut;

			//�v�Z�p�ϐ��ɃX�R�A������
			if(i == 0)
			{
				value = Shop_List1Value();  //�v�Z�p�ϐ�
				SoldOut = Shop_List1SoldOut();
			}
			if(i == 1)
			{
				value = Shop_List2Value();  //�v�Z�p�ϐ�
				SoldOut = Shop_List2SoldOut();
			}
			if(i == 2)
			{
				value = Shop_List3Value();  //�v�Z�p�ϐ�
				SoldOut = Shop_List3SoldOut();
			}
			if(i == 3)
			{
				value = Shop_List4Value();  //�v�Z�p�ϐ�
				SoldOut = Shop_List4SoldOut();
			}


			for (int j = 0; j < MAX_SCORE; j++)
			{
				int Vnum = 0;				    //���������l�����
				g_ValuePos[i][j].DrawValueNumY = 0;

				Vnum = value % 10;				//�X�R�A��1�̈ʂ𔲂��o��
				value /= 10;					//�X�R�A��1�̈ʂ��炵�Ă���

				if (Vnum >= 5)
				{
					g_ValuePos[i][j].DrawValueNumY = 1;
					Vnum -= 5;
				}

				g_ValuePos[i][j].DrawValueNumX = Vnum;

				int tw = Texture_GetWidth(TEXTURE_INDEX_NUMBER) / 5;
				int th = Texture_GetHeight(TEXTURE_INDEX_NUMBER) / 2;

				if (SoldOut == false)
				{
					Sprite_Draw(TEXTURE_INDEX_NUMBER,							//�e�N�X�`���Ǘ��ԍ�
						g_ValuePos[i][j].ValuePosX - ((VALUE_SIZE_X / 2) * j),	//�`����Wx
						g_ValuePos[i][j].ValuePosY,								//�`����Wy
						g_ValuePos[i][j].DrawValueNumX * VALUE_SIZE_X,			//�e�N�X�`���؂�����Wx
						VALUE_SIZE_Y * g_ValuePos[i][j].DrawValueNumY,			//�e�N�X�`���؂�����Wy
						(int)VALUE_SIZE_X, (int)VALUE_SIZE_Y,					//�e�N�X�`���؂��蕝x,y
						tw * 0.5f,												//���S���Wx
						th * 0.5f,												//���S���Wy
						0.5f,													//�g�嗦x����
						0.5f,													//�g�嗦y����
						0.0f,													//��]�p�x(���W�A��)
						0);
				}
			}
		}
	}
			  
	//�����������
	if (g_Score > 99999)
	{
		g_Score = 99999;
	}
}

//�X�R�A�̑����֐�
void AddScore(int add)
{
	g_Score += add;
}

//�X�R�A�̐ݒ�֐�
void SetScore(int set)
{
	g_Score += set;
}

int ScoreCount()
{
	return g_Score;
}

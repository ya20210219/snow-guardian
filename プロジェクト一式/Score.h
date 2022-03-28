#pragma once
//-------------------------------------------------//
//[score.h]�X�R�A
//                      author:��   date:2020/06/09
//-------------------------------------------------//

#include <d3dx9.h>

#define MAX_SCORE (5)
#define NUM_SIZE_X (256 / 5)
#define NUM_SIZE_Y (50.0f)
#define VALUE_SIZE_X (256 / 5)
#define VALUE_SIZE_Y (50.0f)
#define SCORE_POS_X (SCREEN_WIDTH - (NUM_SIZE_X / 2 * MAX_SCORE))        //�X�R�A��\������ꏊ��x
#define SCORE_POS_Y ((SCREEN_HEIGHT - SCREEN_HEIGHT) + (NUM_SIZE_Y / 2))  //�X�R�A��\������ꏊ��y

typedef struct Score
{
	float ScorePosX;
	float ScorePosY;
	int   DrawScoreNumX;
	int   DrawScoreNumY;
}Score;

typedef struct Value
{
	float ValuePosX;
	float ValuePosY;
	int   DrawValueNumX;
	int   DrawValueNumY;
}Value;

//�v���g�^�C�v�錾
void Score_Initialize();
void Score_Update();
void Score_Draw();
void SetScore(int num);
void AddScore(int add);
void SetScore(int set);
void SetScorePos(D3DXVECTOR2 pos);
int ScoreCount();

//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#pragma once

#include <windows.h>
#include "xaudio2.h"						// �T�E���h�����ŕK�v

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000,				// BGM0
	SOUND_LABEL_BGM001,				// BGM1
	SOUND_LABEL_SHOP_BGM,			//�V���b�v����BGM

	SOUND_LABEL_SE_SHOT,			// �e���ˉ�
	SOUND_LABEL_SE_EXPLOSION,		// ������
	SOUND_LABEL_SE_MAGICSKILL,		// �{���X�L��������
	SOUND_LABEL_SE_FRIENDSKILL,		// ���ԏ�����
	SOUND_LABEL_SE_SKILLRECHARGE,	// ���ԏ�����
	SOUND_LABEL_SE_SHOP_BUY,		// �A�C�e���w����
	SOUND_LABEL_SE_FRIEND_GOODBYE,	// ���Ԏ��Ԑ؂�

	SOUND_LABEL_MAX,

} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);


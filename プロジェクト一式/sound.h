//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#pragma once

#include <windows.h>
#include "xaudio2.h"						// サウンド処理で必要

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000,				// BGM0
	SOUND_LABEL_BGM001,				// BGM1
	SOUND_LABEL_SHOP_BGM,			//ショップ中のBGM

	SOUND_LABEL_SE_SHOT,			// 弾発射音
	SOUND_LABEL_SE_EXPLOSION,		// 爆発音
	SOUND_LABEL_SE_MAGICSKILL,		// ボムスキル発動音
	SOUND_LABEL_SE_FRIENDSKILL,		// 仲間召喚音
	SOUND_LABEL_SE_SKILLRECHARGE,	// 仲間召喚音
	SOUND_LABEL_SE_SHOP_BUY,		// アイテム購入音
	SOUND_LABEL_SE_FRIEND_GOODBYE,	// 仲間時間切れ

	SOUND_LABEL_MAX,

} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);


//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_START = 0,		// start
	SOUND_LABEL_BGM_GAME,			// game
	SOUND_LABEL_BGM_RESULT,			// result
	SOUND_LABEL_SE_TITLE_BUTTON,	// タイトルボタン音
	SOUND_LABEL_SE_JUMP,			// ジャンプ音
	SOUND_LABEL_SE_COIN,			// コイン音
	SOUND_LABEL_SE_KEY,				// 鍵音
	SOUND_LABEL_SE_DOOR,			// ドア音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif

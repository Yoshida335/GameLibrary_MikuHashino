//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_START = 0,		// start
	SOUND_LABEL_BGM_GAME,			// game
	SOUND_LABEL_BGM_RESULT,			// result
	SOUND_LABEL_SE_TITLE_BUTTON,	// �^�C�g���{�^����
	SOUND_LABEL_SE_JUMP,			// �W�����v��
	SOUND_LABEL_SE_COIN,			// �R�C����
	SOUND_LABEL_SE_KEY,				// ����
	SOUND_LABEL_SE_DOOR,			// �h�A��
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif

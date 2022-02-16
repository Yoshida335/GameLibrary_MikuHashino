#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

typedef enum
{
	SignType_01 = 0,	//*
	SignType_02,		//=
	SignType_03,		//+
	SignType_04,		//-
	SignType_05,		//%
	SignType_06,		//.
	SignType_MAX
}SignType;

//プロトタイプ宣言
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetResult(int nScore, D3DXVECTOR3 pos, D3DXVECTOR3 size);
void SetSign(D3DXVECTOR3 pos, D3DXVECTOR3 size, SignType type);
int GetResultScore(void);

#endif

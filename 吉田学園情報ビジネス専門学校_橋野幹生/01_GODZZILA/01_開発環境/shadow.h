//----------------------------------------
//　影
//----------------------------------------
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//マクロ定義
#define MAX_SHADOW		(256)	//影の最大数

//影の構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float size_X;
	float size_Z;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Shadow;

//プロトタイプ宣言
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float size_x, float size_z);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);

#endif

//----------------------------------------
//　ライン
//----------------------------------------
#ifndef _LINE_H_
#define _LINE_H_

#include "main.h"

//マクロ定義
#define MAX_LINE		(256)		//ラインの最大数

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	D3DXVECTOR3 start;
	D3DXVECTOR3 finish;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Line;

//プロトタイプ宣言
void InitLine(void);
void UninitLine(void);
void UpdateLine(void);
void DrawLine(void);
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 finish, D3DXCOLOR col);

#endif

//----------------------------------------
//　壁
//----------------------------------------
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//マクロ定義
#define MAX_WALL	(256)		//壁の最大数
#define WALL_X		(300.0f)	// x方向への値	横幅
#define WALL_Y		(140.0f)		// y方向への値	高さ
#define WALL_Z		(0.0f)		// z方向への値	縦幅

typedef enum
{
	TYPE_WARKING = 0,
	TYPE_BILL,
	MAX_TYPE
}WALLTYPE;

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 size;
	D3DXCOLOR col;
	D3DXMATRIX mtxWorld;
	bool bUse;
	WALLTYPE type;
}Wall;

//プロトタイプ宣言
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 size, WALLTYPE type);
Wall * GetWall(void);

#endif


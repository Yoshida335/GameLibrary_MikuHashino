#ifndef _LADDER_H_
#define _LADDER_H_

#include "main.h"

//マクロ定義
#define MAX_LADDER			(128)			//最大梯子数
#define LADDER_WIDTH		(40.0f)			//梯子の幅
#define LADDER_HEIGHT		(40.0f)			//梯子の高さ

//種類
typedef enum
{
	LADDER_TYPE_0 = 0,		//共通
	LADDER_TYPE_1,			//上
	LADDER_TYPE_MAX
}LADDERTYPE;

//状態
typedef enum
{
	LADDER_STATE_OUT = 0,
	LADDER_STATE_IN,
	LADDER_STATE_ON,
	LADDER_STATE_MAX
}LADDERSTATE;

//梯子の構造体
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	float fWidth;			//幅
	float fHeight;			//高さ
	bool bUse;				//使用しているかどうか
	LADDERSTATE state;		//状態
	LADDERTYPE type;
}LADDER;

//プロトタイプ宣言
void InitLadder(void);
void UninitLadder(void);
void UpdateLadder(void);
void DrawLadder(void);
void SetLadder(D3DXVECTOR3 pos, float fWidth, float fHeight, LADDERTYPE type);
bool CollisionLadder(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight);
LADDER * GetLadder(void);

#endif


#ifndef _LADDER_H_
#define _LADDER_H_

#include "main.h"

//マクロ定義
#define MAX_LADDER			(256)			//最大梯子数
#define LADDER_WIDTH		(40.0f)			//梯子の幅
#define LADDER_HEIGHT		(40.0f)			//梯子の高さ

//種類
typedef enum
{
	LADDER_TYPE_0 = 0,		//通常
	LADDER_TYPE_1,			//上方向のみ移動
	LADDER_TYPE_MAX
}LADDERTYPE;

//梯子の構造体
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	float fWidth;			//幅
	float fHeight;			//高さ
	bool bUse;				//使用しているかどうか
	LADDERTYPE type;		//種類
}LADDER;

//プロトタイプ宣言
void InitLadder(void);		//梯子の初期化処理
void UninitLadder(void);	//梯子の終了処理
void UpdateLadder(void);	//梯子の更新処理
void DrawLadder(void);		//梯子の描画処理
void SetLadder(D3DXVECTOR3 pos, float fWidth, float fHeight, LADDERTYPE type);	//梯子の設定
bool CollisionLadder(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight);	//梯子の当たり判定
LADDER * GetLadder(void);	//梯子の情報

#endif


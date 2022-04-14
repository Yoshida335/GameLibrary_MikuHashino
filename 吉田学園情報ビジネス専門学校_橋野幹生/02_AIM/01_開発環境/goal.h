//----------------------------------------
//	ゴールのヘッダー
//　Author：橋野幹生
//----------------------------------------
#ifndef _GOAL_H_
#define _GOAL_H_

#include "main.h"

//マクロ定義
#define MAX_GOAL			(128)		//最大ゴール数
#define GOAL_WIDTH			(60.0f)		//ゴールの幅
#define GOAL_HEIGHT			(80.0f)		//ゴールの高さ

//ゴールの状態
typedef enum
{
	GOAL_STATE_CLAUSE = 0,	//閉まっている状態
	GOAL_STATE_OPEN,		//開いている状態
	GOAL_STATE_MAX
}GoalState;

//ブロックの構造体
typedef struct
{
	D3DXVECTOR3 pos;	//現在の位置
	float fWidth;		//幅
	float fHeight;		//高さ
	GoalState state;	//状態
	bool bUse;			//使用しているかどうか
}Goal;

//プロトタイプ宣言
void InitGoal(void);	//ゴールの初期化処理
void UninitGoal(void);	//ゴールの終了処理
void UpdateGoal(void);	//ゴールの更新処理
void DrawGoal(void);	//ゴールの描画処理
void SetGoal(D3DXVECTOR3 pos);	//ゴールの設定
void CollisionGoal(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, float fWidth, float fHeight, bool PlayerItem);	//ゴールの当たり判定

#endif
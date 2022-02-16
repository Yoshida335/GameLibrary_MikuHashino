#ifndef _GOAL_H_
#define _GOAL_H_

#include "main.h"

//マクロ定義
#define MAX_GOAL			(128)			//最大アイテム数
#define GOAL_WIDTH			(60.0f)		//アイテムの幅
#define GOAL_HEIGHT			(80.0f)		//アイテムの高さ

//アイテムの種類
typedef enum
{
	GOAL_STATE_CLAUSE = 0,
	GOAL_STATE_OPEN,
	GOAL_STATE_MAX
}GoalState;

//ブロックの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	float fWidth;			//幅
	float fHeight;			//高さ
	GoalState state;		//状態
	bool bUse;				//使用しているかどうか
}Goal;

//プロトタイプ宣言
void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
void SetGoal(D3DXVECTOR3 pos);
void CollisionGoal(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, float fWidth, float fHeight, bool PlayerItem);

#endif

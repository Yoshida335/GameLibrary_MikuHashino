#ifndef _STAGE_H_
#define _STAGE_H_

#include "main.h"

//ステージの状態
typedef enum
{
	STAGESTATE_NOMAL = 0,		//通常状態
	STAGESTATE_DAMAGE,			//ダメージ状態
	STAGESTATE_MAX
}STAGESTATE;

//ステージ構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	STAGESTATE state;		//状態
	int nCounterState;		//状態カウンター
	int nLife;				//体力
	bool bUse;				//使用しているかどうか
}Stage;

//プロトタイプ宣言
void InitStage(void);
void UninitStage(void);
void UpdateStage(void);
void DrawStage(void);
void HitStage(int nDamage);
Stage * GetStage(void);

#endif

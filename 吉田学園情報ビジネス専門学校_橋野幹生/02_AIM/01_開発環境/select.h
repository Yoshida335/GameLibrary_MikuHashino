//----------------------------------------
//	選択画面のヘッダー
//	Author：橋野幹生
//----------------------------------------
#ifndef _SELECT_H_
#define _SELECT_H_

#include "main.h"

//選択ステージの種類
typedef enum
{
	STAGE_No_0 = 0,	//ステージ1
	STAGE_No_1,		//ステージ2
	STAGE_No_2,		//ステージ3
	STAGE_No_MAX
}STAGE_No;


//マクロ定義
#define MAX_SELECT			(2)			//最大選択数
#define SELECT_WIDTH		(400.0f)	//セレクトの幅
#define SELECT_HEIGHT		(100.0f)	//セレクトの高さ	

//選択している状態
typedef enum
{
	SELECT_OFF = 0,	//選択していない
	SELECT_ON,		//選択されている
	SELECT_MAX
}SelectState;

//ステージ選択の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	SelectState state;	//状態
}SELECT;

//プロトタイプ宣言
void InitSelect(void);		//選択画面の初期化処理
void UninitSelect(void);	//選択画面の終了処理
void UpdateSelect(void);	//選択画面の更新処理
void DrawSelect(void);		//選択画面の描画処理
STAGE_No * GetSelect(void);	//選択ステージの情報

#endif


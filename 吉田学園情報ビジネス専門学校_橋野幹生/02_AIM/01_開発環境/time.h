//----------------------------------------
//	タイマーのヘッダー
//	Author：橋野幹生
//----------------------------------------
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"

//マクロ定義
#define TIME_WIDTH				(20.0f)		//タイマーの幅
#define TIME_HEIGHT				(25.0f)		//タイマーの高さ
#define STARTTIME_WIDTH			(200.0f)	//スタートの幅
#define STARTTIME_HEIGHT		(250.0f)	//スタートの高さ

//フェードの状態
typedef enum
{
	TIME_ON = 0,	//タイマー起動中
	TIME_OFF,		//タイマー起動外
	TIME_START,		//タイマー起動開始
	TIME_MAX
}TIME;

typedef struct
{
	TIME state;
}TIMESTATE;

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	bool bUse;			//使っているかどうか
	int time;			//タイム
}START;

//プロトタイプ宣言
void InitTime(void);	//タイマーの初期化処理
void UninitTime(void);	//タイマーの終了処理
void UpdateTime(void);	//タイマーの更新処理
void DrawTime(void);	//タイマーの描画処理
void SetTime(int nTime);		//タイマーの設定
TIMESTATE * GetStartTime(void);	//タイマーの状態情報
int * GetTime(void);	//時間の情報
void ClearTime(void);	//クリアしたときのタイマーの処理

#endif


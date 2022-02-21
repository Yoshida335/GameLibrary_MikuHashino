#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"

//マクロ定義
#define TIME_WIDTH				(20.0f)			//タイマーの幅
#define TIME_HEIGHT				(25.0f)			//タイマーの高さ
#define STARTTIME_WIDTH			(200.0f)		//スタートの幅
#define STARTTIME_HEIGHT		(250.0f)		//スタートの高さ

//フェードの状態
typedef enum
{
	TIME_ON = 0,			//タイマー起動中
	TIME_OFF,				//タイマー起動外
	TIME_START,				//タイマー起動開始
	TIME_MAX
}TIME;

typedef struct
{
	TIME state;
}STARTTIME;

typedef struct
{
	D3DXVECTOR3 pos;
	bool bUse;
	int time;
}START;

//プロトタイプ宣言
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
void SetTime(int nTime);
STARTTIME * GetStartTime(void);
int * GetTime(void);
void ClearTime(void);

#endif


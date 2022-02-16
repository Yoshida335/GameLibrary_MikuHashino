#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"

//フェードの状態
typedef enum
{
	TIME_ON = 0,			//タイム中
	TIME_OFF,				//タイム終了
	TIME_MAX
}TIME;

//プロトタイプ宣言
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
int * GetTime(void);
void AddTime(int nTime);

#endif


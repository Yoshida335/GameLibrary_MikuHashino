#ifndef _SELECT_H_
#define _SELECT_H_

#include "main.h"

//ブロックの種類
typedef enum
{
	STAGE_No_0 = 0,
	STAGE_No_1,
	STAGE_No_2,
	STAGE_No_MAX
}STAGE_No;


//マクロ定義
#define MAX_SELECT			(2)				//最大選択数
#define SELECT_WIDTH		(400.0f)		//セレクトの幅
#define SELECT_HEIGHT		(100.0f)		//セレクトの高さ	

typedef enum
{
	SELECT_OFF = 0,
	SELECT_ON,
	SELECT_MAX
}SelectState;

typedef struct
{
	D3DXVECTOR3 pos;
	SelectState state;
}SELECT;

//プロトタイプ宣言
void InitSelect(void);
void UninitSelect(void);
void UpdateSelect(void);
void DrawSelect(void);
STAGE_No * GetSelect(void);

#endif


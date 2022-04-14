#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "main.h"

//マクロ定義
#define MAX_BUTTON			(128)		//最大ボタン数
#define BUTTON_WIDTH		(40.0f)		//ボタンの幅
#define BUTTON_HEIGHT		(30.0f)		//ボタンの高さ	
#define BUTTON_LIFE			(1)			//ボタンの寿命

//状態
typedef enum
{
	BUTTON_STATE_OFF = 0,
	BUTTON_STATE_ON,
	BUTTON_STATE_MAX
}BUTTONSTATE;

//種類
typedef enum
{
	BUTTON_TYPE_0 = 0,
	BUTTON_TYPE_MAX
}BUTTONTYPE;

//構造体
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	float fWidth;			//幅
	float fHeight;			//高さ
	bool bUse;				//使用しているかどうか
	BUTTONSTATE state;		//状態
	int nLife;				//寿命
}BUTTON;

//プロトタイプ宣言
void InitButton(void);
void UninitButton(void);
void UpdateButton(void);
void DrawButton(void);
void SetButton(D3DXVECTOR3 pos, float fWidth, float fHeight, int life);
bool CollisionButton(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight);

#endif

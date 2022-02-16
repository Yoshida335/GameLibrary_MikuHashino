//----------------------------------------
//　背景
//----------------------------------------
#ifndef _BG_H_
#define _BG_H_

#include "main.h"

//マクロ定義
#define MAX_BG	(3)	//背景の最大テクスチャ数

typedef enum
{
	BG_TITLE = 0,
	BG_RESULT,
	BG_SCORE
}BG_TYPE;

//プロトタイプ宣言
void InitBg(void);			//背景の初期化処理
void UninitBg(void);		//背景の終了処理
void UpdateBg(void);		//背景の更新処理
void DrawBg(void);			//背景の描画処理
void SetBg(BG_TYPE type);	//背景の設定

#endif

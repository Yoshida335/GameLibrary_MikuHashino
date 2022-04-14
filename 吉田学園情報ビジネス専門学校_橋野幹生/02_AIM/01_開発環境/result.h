//----------------------------------------
//	リザルト画面のヘッダー
//	Author：橋野幹生
//----------------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

//リザルトの種類
enum Result_Type
{
	RESULT_TYPE_OVER = 0,	//ゲームオーバー
	RESULT_TYPE_CLEAR,		//ゲームクリア
	RESULT_TYPE_MAX
};

//プロトタイプ宣言
void InitResult(Result_Type nResult);	//リザルト画面の初期化処理
void UninitResult(void);	//リザルト画面の終了処理
void UpdateResult(void);	//リザルト画面の更新処理
void DrawResult(void);		//リザルト画面の描画処理

#endif
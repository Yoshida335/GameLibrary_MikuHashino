//----------------------------------------
//	ゲーム画面のヘッダー
//　Author：橋野幹生
//----------------------------------------
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "time.h"

//プロトタイプ宣言
void InitGame(void);	//ゲーム画面の初期化処理
void UninitGame(void);	//ゲーム画面の終了処理
void UpdateGame(void);	//ゲーム画面の更新処理
void DrawGame(void);	//ゲーム画面の描画処理

#endif

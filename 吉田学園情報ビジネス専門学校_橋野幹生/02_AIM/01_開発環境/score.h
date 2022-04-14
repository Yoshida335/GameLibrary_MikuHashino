//----------------------------------------
//	スコアのヘッダー
//	Author：橋野幹生
//----------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

//プロトタイプ宣言
void InitScore(void);		//スコアの初期化処理
void UninitScore(void);		//スコアの終了処理
void UpdateScore(void);		//スコアの更新処理
void DrawScore(void);		//スコアの描画処理
void SetScore(int nScore);	//スコアの設定
void AddScore(int nValue);	//スコアの加算処理

#endif
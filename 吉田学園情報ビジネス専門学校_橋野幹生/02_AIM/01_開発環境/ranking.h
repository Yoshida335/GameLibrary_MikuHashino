//----------------------------------------
//	ランキングのヘッダー
//	Author：橋野幹生
//----------------------------------------
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//マクロ定義
#define MAX_RANK		(5)	//ランキング数

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nScore;			//スコア
}RankScore;

//プロトタイプ宣言
void InitRanking(void);		//ランキングの初期化処理
void UninitRanking(void);	//ランキングの終了処理
void UpdateRanking(void);	//ランキングの更新処理
void DrawRanking(void);		//ランキングの描画処理
void ResetRanking(void);	//ランキングのリセット処理
void SetRanking(void);		//ランキングの設定
void SaveRanking(void);		//ランキングの保存処理

#endif

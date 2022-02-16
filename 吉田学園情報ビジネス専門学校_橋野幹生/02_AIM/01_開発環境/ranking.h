#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//マクロ定義
#define MAX_RANK			(5)	//ランキング数

typedef struct
{
	D3DXVECTOR3 pos;
	int nScore;
}RankScore;

//プロトタイプ宣言
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(void);
void SetRanking(void);

#endif

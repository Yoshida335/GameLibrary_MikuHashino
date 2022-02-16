#ifndef _RESULTSCORE_H_
#define _RESULTSCORE_H_

#include "main.h"

#define MAX_RESULTSCORE	(16)

//プロトタイプ宣言
void InitResultScore(void);
void UninitResultScore(void);
void UpdateResultScore(void);
void DrawResultScore(void);
void SetResultScore(int nResultScore, D3DXVECTOR3 pos, D3DXVECTOR3 size);

#endif
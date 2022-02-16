#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

#define MAX_SCORE	(16)

//プロトタイプ宣言
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore, D3DXVECTOR3 pos, D3DXVECTOR3 size);

#endif

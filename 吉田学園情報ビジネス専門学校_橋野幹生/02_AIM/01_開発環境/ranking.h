#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//�}�N����`
#define MAX_RANK			(5)	//�����L���O��

typedef struct
{
	D3DXVECTOR3 pos;
	int nScore;
}RankScore;

//�v���g�^�C�v�錾
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(void);
void SetRanking(void);

#endif

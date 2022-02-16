#ifndef _LADDER_H_
#define _LADDER_H_

#include "main.h"

//�}�N����`
#define MAX_LADDER			(128)			//�ő��q��
#define LADDER_WIDTH		(40.0f)			//��q�̕�
#define LADDER_HEIGHT		(40.0f)			//��q�̍���

//���
typedef enum
{
	LADDER_TYPE_0 = 0,		//����
	LADDER_TYPE_1,			//��
	LADDER_TYPE_MAX
}LADDERTYPE;

//���
typedef enum
{
	LADDER_STATE_OUT = 0,
	LADDER_STATE_IN,
	LADDER_STATE_ON,
	LADDER_STATE_MAX
}LADDERSTATE;

//��q�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	float fWidth;			//��
	float fHeight;			//����
	bool bUse;				//�g�p���Ă��邩�ǂ���
	LADDERSTATE state;		//���
	LADDERTYPE type;
}LADDER;

//�v���g�^�C�v�錾
void InitLadder(void);
void UninitLadder(void);
void UpdateLadder(void);
void DrawLadder(void);
void SetLadder(D3DXVECTOR3 pos, float fWidth, float fHeight, LADDERTYPE type);
bool CollisionLadder(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight);
LADDER * GetLadder(void);

#endif


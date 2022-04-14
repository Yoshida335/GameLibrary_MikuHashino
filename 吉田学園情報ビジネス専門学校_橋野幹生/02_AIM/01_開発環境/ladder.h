#ifndef _LADDER_H_
#define _LADDER_H_

#include "main.h"

//�}�N����`
#define MAX_LADDER			(256)			//�ő��q��
#define LADDER_WIDTH		(40.0f)			//��q�̕�
#define LADDER_HEIGHT		(40.0f)			//��q�̍���

//���
typedef enum
{
	LADDER_TYPE_0 = 0,		//�ʏ�
	LADDER_TYPE_1,			//������݈̂ړ�
	LADDER_TYPE_MAX
}LADDERTYPE;

//��q�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	float fWidth;			//��
	float fHeight;			//����
	bool bUse;				//�g�p���Ă��邩�ǂ���
	LADDERTYPE type;		//���
}LADDER;

//�v���g�^�C�v�錾
void InitLadder(void);		//��q�̏���������
void UninitLadder(void);	//��q�̏I������
void UpdateLadder(void);	//��q�̍X�V����
void DrawLadder(void);		//��q�̕`�揈��
void SetLadder(D3DXVECTOR3 pos, float fWidth, float fHeight, LADDERTYPE type);	//��q�̐ݒ�
bool CollisionLadder(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight);	//��q�̓����蔻��
LADDER * GetLadder(void);	//��q�̏��

#endif


#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//�}�N����`
#define MAX_BLOCK			(128)		//�ő�u���b�N��
#define BLOCK_WIDTH			(40.0f)		//�u���b�N�̕�
#define BLOCK_HEIGHT		(40.0f)		//�u���b�N�̍���
#define BLOCK_MOVE			(0.2f)		//�u���b�N�̓����X�s�[�h	
#define BLOCK_MOVE_LIFE		(200)		//�����u���b�N�̎���
#define BLOCK_ITEM_LIFE		(1)			//�����u���b�N�̎���

//�u���b�N�̎��
typedef enum
{
	BLOCKTYPE_NOMAL = 0,
	BLOCKTYPE_UP,
	BLOCKTYPE_ITEM,
	BLOCKTYPE_ACT,
	BLOCKTYPE_MAX
}BLOCKTYPE;

//�u���b�N�̏��
typedef enum
{
	BLOCKSTATE_NOMAL = 0,
	BLOCKSTATE_UP,
	BLOCKSTATE_MOVE,
	BLOCKSTATE_ITEM,
	BLOCKSTATE_ACT,
	BLOCKSTATE_RL,
	BLOCKSTATE_MAX
}BLOCKSTATE;

//�u���b�N�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 rot;		//�p�x
	D3DXVECTOR3 move;		//�ړ���
	float fWidth;			//��
	float fHeight;			//����
	bool bUse;				//�g�p���Ă��邩�ǂ���
	BLOCKTYPE type;			//�u���b�N�̎��
	float rot2;				//�V���Ȋp�x
	float flength;			//�΂ߒ���
	BLOCKSTATE state;		//���
	int nLife;
}BLOCK;

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, BLOCKTYPE type,BLOCKSTATE state, float fWidth, float fHeight, int life);
bool CollisionBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight, BLOCK ** pblock);
void CollisionBlock2(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight, BLOCKSTATE state);
bool ActBlock(D3DXVECTOR3 * pos, float fWidth, float fHeight);
BLOCK * GetBlock(void);

#endif

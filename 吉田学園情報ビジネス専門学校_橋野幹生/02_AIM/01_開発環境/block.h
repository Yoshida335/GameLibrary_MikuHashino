//----------------------------------------
//�@�u���b�N�̃w�b�_�[
//�@Author�F���슲��
//----------------------------------------
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//�}�N����`
#define MAX_BLOCK			(256)		//�ő�u���b�N��
#define BLOCK_WIDTH			(40.0f)		//�u���b�N�̕�
#define BLOCK_HEIGHT		(40.0f)		//�u���b�N�̍���
#define BLOCK_MOVE			(0.2f)		//�u���b�N�̓����X�s�[�h	
#define BLOCK_MOVE_LIFE		(200)		//�����u���b�N�̎���
#define BLOCK_ITEM_LIFE		(1)			//�����u���b�N�̎���

//�u���b�N�̎��
typedef enum
{
	BLOCKTYPE_NOMAL = 0,	//�ʏ�u���b�N
	BLOCKTYPE_UP,			//������ɓ����u���b�N
	BLOCKTYPE_ITEM,			//�A�C�e���u���b�N
	BLOCKTYPE_MAX
}BLOCKTYPE;

//�u���b�N�̏��
typedef enum
{
	BLOCKSTATE_NOMAL = 0,	//�ʏ���
	BLOCKSTATE_UP,			//������Ɉړ�
	BLOCKSTATE_MOVE,		//�����Ă�����
	BLOCKSTATE_ITEM,		//�A�C�e�����
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
}BLOCK;

//�v���g�^�C�v�錾
void InitBlock(void);		//�u���b�N�̏���������
void UninitBlock(void);		//�u���b�N�̏I������
void UpdateBlock(void);		//�u���b�N�̍X�V����
void DrawBlock(void);		//�u���b�N�̕`�揈��
void SetBlock(D3DXVECTOR3 pos, BLOCKTYPE type,BLOCKSTATE state, float fWidth, float fHeight);	//�u���b�N�̐ݒ�
bool CollisionBlock_P(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight);	//�v���C���[�̓����蔻��	// , BLOCK ** pblock
void CollisionBlock_B(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, float fWidth, float fHeight);			//�u���b�N�Ƃ̓����蔻��
BLOCK * GetBlock(void);		//�u���b�N�̏��

#endif

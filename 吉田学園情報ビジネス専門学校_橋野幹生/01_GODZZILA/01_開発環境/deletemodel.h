//----------------------------------------
//�@���f��(�j���)
//�@Author�F���슲��
//----------------------------------------
#ifndef _DELETEMODEL_H_
#define _DELETEMODEL_H_

#include "main.h"

//�}�N����`
#define MAX_DELETEMODEL			(126)	//���f��(�j���)�̍ő吔

//���f��(�j���)�̎��
typedef enum
{
	TYPE_DELETEBILL_01 = 0,
	TYPE_DELETEBILL_02,
	TYPE_DLETEMAX
}DELETEMODELTYPE;

//���f��(�j���)�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXCOLOR col;			//�F
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	bool bUse;				//�g���Ă��邩�ǂ���
	DELETEMODELTYPE type;	//���
}DeleteModel;

//�v���g�^�C�v�錾
void InitDeleteModel(void);		//���f��(�j���)�̏�����
void UninitDeleteModel(void);	//���f��(�j���)�̏I��
void UpdateDeleteModel(void);	//���f��(�j���)�̍X�V
void DrawDeleteModel(void);		//���f��(�j���)�̕`��
void SetDeleteModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//���f��(�j���)�̐ݒ�

#endif


//----------------------------------------
//�@���f��
//----------------------------------------
#ifndef _DELETEMODEL_H_
#define _DELETEMODEL_H_

#include "main.h"

//�}�N����`
#define MAX_DELETEMODEL			(126)	//���f���̍ő吔

//���f���̎��
typedef enum
{
	TYPE_DELETEBILL_01 = 0,
	TYPE_DELETEBILL_02,
	TYPE_DLETEMAX
}DELETEMODELTYPE;

//���f���̍\����
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
void InitDeleteModel(void);		//���f���̏�����
void UninitDeleteModel(void);		//���f���̏I��
void UpdateDeleteModel(void);		//���f���̍X�V
void DrawDeleteModel(void);		//���f���̕`��
void SetDeleteModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//���f���̐ݒ�

#endif


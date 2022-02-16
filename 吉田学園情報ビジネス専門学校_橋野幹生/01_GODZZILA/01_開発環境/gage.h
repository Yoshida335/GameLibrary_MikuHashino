//----------------------------------------
//�@
//----------------------------------------
#ifndef _GAGE_H_
#define _GAGE_H_

#include "main.h"

//�}�N����`
#define MAX_GAGE	(256)	//�r���{�[�h�̍ő吔

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
	D3DXCOLOR col;				//�J���[
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	bool bUse;					//�g�p���Ă��邩�ǂ���
	int nLife;					//����
	int nMaxLife;				//�ő����
}Gage;

//�v���g�^�C�v�錾
void InitGage(void);				//�r���{�[�h�̏���������
void UninitGage(void);				//�r���{�[�h�̏I������
void UpdateGage(void);				//�r���{�[�h�̍X�V����
void DrawGage(void);				//�r���{�[�h�̕`�揈��
void SetGage(D3DXVECTOR3 pos, int nLife);	//�r���{�[�h�̐ݒ�
void HitGage(int nCntGage, int nDamage);

#endif



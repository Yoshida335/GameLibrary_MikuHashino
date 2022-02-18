//----------------------------------------
//�@���C��
//�@Author�F���슲��
//----------------------------------------
#ifndef _LINE_H_
#define _LINE_H_

#include "main.h"

//�}�N����`
#define MAX_LINE		(256)		//���C���̍ő吔

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//�p�x
	D3DXCOLOR col;			//�J���[
	D3DXVECTOR3 start;		//���C���̎n�܂�̈ʒu
	D3DXVECTOR3 finish;		//���C���̏I���̈ʒu
	D3DXMATRIX mtxWorld;	//���[���h�}�g���N�X
	bool bUse;
}Line;

//�v���g�^�C�v�錾
void InitLine(void);	//���C���̏�����
void UninitLine(void);	//���C���̏I��
void UpdateLine(void);	//���C���̍X�V
void DrawLine(void);	//���C���̕`��
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 finish, D3DXCOLOR col);	//���C���̐ݒ�

#endif

//----------------------------------------
//�@���b�V���@(�~��)
//----------------------------------------
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

#include "main.h"

//�}�N����`
#define MAX_CYLINDER	(256)	//�~���̍ő吔

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;			//���݂̈ʒu
	D3DXVECTOR3 posOld;			//�O��̈ʒu
	D3DXVECTOR3 rot;			//����
	D3DXCOLOR col;				//�J���[
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	bool bUse;					//�g�p���Ă��邩�ǂ���
}Cylinder;

//�v���g�^�C�v�錾
void InitMeshCylinder(void);		//�~���̏���������
void UninitMeshCylinder(void);		//�~���̏I������
void UpdateMeshCylinder(void);		//�~���̍X�V����
void DrawMeshCylinder(void);		//�~���̕`�揈��
void SetMeshCylinder(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//�~���̕`�揈��

#endif
//----------------------------------------
//�@����
//----------------------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//�}�N����`
#define MAX_EXPLOSION	(256)	//�r���{�[�h�̍ő吔

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
	D3DXCOLOR col;				//�J���[
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	bool bUse;					//�g�p���Ă��邩�ǂ���
	int nCntAnim;				//�A�j���[�V�����J�E���^�[
	int nPatternAnim;			//�A�j���[�V�����p�^�[��No.
}Explosion;

//�v���g�^�C�v�錾
void InitExplosion(void);				//�r���{�[�h�̏���������
void UninitExplosion(void);				//�r���{�[�h�̏I������
void UpdateExplosion(void);				//�r���{�[�h�̍X�V����
void DrawExplosion(void);				//�r���{�[�h�̕`�揈��
void SetExplosion(D3DXVECTOR3 pos);		//�r���{�[�h�̐ݒ�

#endif

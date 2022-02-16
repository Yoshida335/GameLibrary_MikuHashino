//----------------------------------------
//�@
//----------------------------------------
#ifndef _SCOREGAGE_H_
#define _SCOREGAGE_H_

#include "main.h"

//�}�N����`
#define MAX_SCOREGAGE	(256)	//�r���{�[�h�̍ő吔

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
	D3DXCOLOR col;				//�J���[
	bool bUse;					//�g�p���Ă��邩�ǂ���
	int nLife;					//����
	int nMaxLife;				//�ő����
}ScoreGage;

//�v���g�^�C�v�錾
void InitScoreGage(void);				//�r���{�[�h�̏���������
void UninitScoreGage(void);				//�r���{�[�h�̏I������
void UpdateScoreGage(void);				//�r���{�[�h�̍X�V����
void DrawScoreGage(void);				//�r���{�[�h�̕`�揈��
void SetScoreGage(D3DXVECTOR3 pos, int nLife);	//�r���{�[�h�̐ݒ�
void HitScoreGage(int nCntScoreGage, int nDamage);

#endif


//----------------------------------------
//�@�w�i
//----------------------------------------
#ifndef _BG_H_
#define _BG_H_

#include "main.h"

//�}�N����`
#define MAX_BG	(3)	//�w�i�̍ő�e�N�X�`����

typedef enum
{
	BG_TITLE = 0,
	BG_RESULT,
	BG_SCORE
}BG_TYPE;

//�v���g�^�C�v�錾
void InitBg(void);			//�w�i�̏���������
void UninitBg(void);		//�w�i�̏I������
void UpdateBg(void);		//�w�i�̍X�V����
void DrawBg(void);			//�w�i�̕`�揈��
void SetBg(BG_TYPE type);	//�w�i�̐ݒ�

#endif

//----------------------------------------
//	�I����ʂ̃w�b�_�[
//	Author�F���슲��
//----------------------------------------
#ifndef _SELECT_H_
#define _SELECT_H_

#include "main.h"

//�I���X�e�[�W�̎��
typedef enum
{
	STAGE_No_0 = 0,	//�X�e�[�W1
	STAGE_No_1,		//�X�e�[�W2
	STAGE_No_2,		//�X�e�[�W3
	STAGE_No_MAX
}STAGE_No;


//�}�N����`
#define MAX_SELECT			(2)			//�ő�I��
#define SELECT_WIDTH		(400.0f)	//�Z���N�g�̕�
#define SELECT_HEIGHT		(100.0f)	//�Z���N�g�̍���	

//�I�����Ă�����
typedef enum
{
	SELECT_OFF = 0,	//�I�����Ă��Ȃ�
	SELECT_ON,		//�I������Ă���
	SELECT_MAX
}SelectState;

//�X�e�[�W�I���̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	SelectState state;	//���
}SELECT;

//�v���g�^�C�v�錾
void InitSelect(void);		//�I����ʂ̏���������
void UninitSelect(void);	//�I����ʂ̏I������
void UpdateSelect(void);	//�I����ʂ̍X�V����
void DrawSelect(void);		//�I����ʂ̕`�揈��
STAGE_No * GetSelect(void);	//�I���X�e�[�W�̏��

#endif


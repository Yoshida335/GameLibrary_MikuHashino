//----------------------------------------
//�@�|�[�Y���j���[�̃w�b�_�[
//�@Author�F���슲��
//----------------------------------------
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//���j���[�̏��
typedef enum
{
	PAUSE_OFF = 0,	//�I������Ă�����
	PAUSE_ON,		//�I������Ă��Ȃ����
	PAUSE_MAX
}PauseState;

//�|�[�Y���j���[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	PauseState state;		//���
}PAUSE;

//�v���g�^�C�v�錾
void InitPause(void);		//�|�[�Y�̏���������
void UninitPause(void);		//�|�[�Y�̏I������
void UpdatePause(void);		//�|�[�Y�̍X�V����
void DrawPause(void);		//�|�[�Y�̕`�揈��

#endif



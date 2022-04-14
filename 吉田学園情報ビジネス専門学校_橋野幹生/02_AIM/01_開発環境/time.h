//----------------------------------------
//	�^�C�}�[�̃w�b�_�[
//	Author�F���슲��
//----------------------------------------
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"

//�}�N����`
#define TIME_WIDTH				(20.0f)		//�^�C�}�[�̕�
#define TIME_HEIGHT				(25.0f)		//�^�C�}�[�̍���
#define STARTTIME_WIDTH			(200.0f)	//�X�^�[�g�̕�
#define STARTTIME_HEIGHT		(250.0f)	//�X�^�[�g�̍���

//�t�F�[�h�̏��
typedef enum
{
	TIME_ON = 0,	//�^�C�}�[�N����
	TIME_OFF,		//�^�C�}�[�N���O
	TIME_START,		//�^�C�}�[�N���J�n
	TIME_MAX
}TIME;

typedef struct
{
	TIME state;
}TIMESTATE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	bool bUse;			//�g���Ă��邩�ǂ���
	int time;			//�^�C��
}START;

//�v���g�^�C�v�錾
void InitTime(void);	//�^�C�}�[�̏���������
void UninitTime(void);	//�^�C�}�[�̏I������
void UpdateTime(void);	//�^�C�}�[�̍X�V����
void DrawTime(void);	//�^�C�}�[�̕`�揈��
void SetTime(int nTime);		//�^�C�}�[�̐ݒ�
TIMESTATE * GetStartTime(void);	//�^�C�}�[�̏�ԏ��
int * GetTime(void);	//���Ԃ̏��
void ClearTime(void);	//�N���A�����Ƃ��̃^�C�}�[�̏���

#endif


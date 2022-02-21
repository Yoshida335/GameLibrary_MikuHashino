#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"

//�}�N����`
#define TIME_WIDTH				(20.0f)			//�^�C�}�[�̕�
#define TIME_HEIGHT				(25.0f)			//�^�C�}�[�̍���
#define STARTTIME_WIDTH			(200.0f)		//�X�^�[�g�̕�
#define STARTTIME_HEIGHT		(250.0f)		//�X�^�[�g�̍���

//�t�F�[�h�̏��
typedef enum
{
	TIME_ON = 0,			//�^�C�}�[�N����
	TIME_OFF,				//�^�C�}�[�N���O
	TIME_START,				//�^�C�}�[�N���J�n
	TIME_MAX
}TIME;

typedef struct
{
	TIME state;
}STARTTIME;

typedef struct
{
	D3DXVECTOR3 pos;
	bool bUse;
	int time;
}START;

//�v���g�^�C�v�錾
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
void SetTime(int nTime);
STARTTIME * GetStartTime(void);
int * GetTime(void);
void ClearTime(void);

#endif


#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"

//�t�F�[�h�̏��
typedef enum
{
	TIME_ON = 0,			//�^�C����
	TIME_OFF,				//�^�C���I��
	TIME_MAX
}TIME;

//�v���g�^�C�v�錾
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
int * GetTime(void);
void AddTime(int nTime);

#endif


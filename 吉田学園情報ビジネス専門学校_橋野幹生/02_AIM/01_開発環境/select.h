#ifndef _SELECT_H_
#define _SELECT_H_

#include "main.h"

//�u���b�N�̎��
typedef enum
{
	STAGE_No_0 = 0,
	STAGE_No_1,
	STAGE_No_2,
	STAGE_No_MAX
}STAGE_No;


//�}�N����`
#define MAX_SELECT			(2)				//�ő�I��
#define SELECT_WIDTH		(400.0f)		//�Z���N�g�̕�
#define SELECT_HEIGHT		(100.0f)		//�Z���N�g�̍���	

typedef enum
{
	SELECT_OFF = 0,
	SELECT_ON,
	SELECT_MAX
}SelectState;

typedef struct
{
	D3DXVECTOR3 pos;
	SelectState state;
}SELECT;

//�v���g�^�C�v�錾
void InitSelect(void);
void UninitSelect(void);
void UpdateSelect(void);
void DrawSelect(void);
STAGE_No * GetSelect(void);

#endif


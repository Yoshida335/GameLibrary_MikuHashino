#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "main.h"

//�}�N����`
#define MAX_BUTTON			(128)		//�ő�{�^����
#define BUTTON_WIDTH		(40.0f)		//�{�^���̕�
#define BUTTON_HEIGHT		(30.0f)		//�{�^���̍���	
#define BUTTON_LIFE			(1)			//�{�^���̎���

//���
typedef enum
{
	BUTTON_STATE_OFF = 0,
	BUTTON_STATE_ON,
	BUTTON_STATE_MAX
}BUTTONSTATE;

//���
typedef enum
{
	BUTTON_TYPE_0 = 0,
	BUTTON_TYPE_MAX
}BUTTONTYPE;

//�\����
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	float fWidth;			//��
	float fHeight;			//����
	bool bUse;				//�g�p���Ă��邩�ǂ���
	BUTTONSTATE state;		//���
	int nLife;				//����
}BUTTON;

//�v���g�^�C�v�錾
void InitButton(void);
void UninitButton(void);
void UpdateButton(void);
void DrawButton(void);
void SetButton(D3DXVECTOR3 pos, float fWidth, float fHeight, int life);
bool CollisionButton(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight);

#endif

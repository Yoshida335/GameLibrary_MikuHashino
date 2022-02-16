//----------------------------------------
//�@���C��
//----------------------------------------
#ifndef _LINE_H_
#define _LINE_H_

#include "main.h"

//�}�N����`
#define MAX_LINE		(256)		//���C���̍ő吔

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	D3DXVECTOR3 start;
	D3DXVECTOR3 finish;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Line;

//�v���g�^�C�v�錾
void InitLine(void);
void UninitLine(void);
void UpdateLine(void);
void DrawLine(void);
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 finish, D3DXCOLOR col);

#endif

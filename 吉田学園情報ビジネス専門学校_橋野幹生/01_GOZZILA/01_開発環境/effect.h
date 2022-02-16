//----------------------------------------
//�@�G�t�F�N�g
//----------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//�}�N����`
#define MAX_EFFECT	(1000)	//�r���{�[�h�̍ő吔

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 size;
	bool bUse;
	int nLife;
}Effect;

//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nLife, D3DXVECTOR3 size);

#endif

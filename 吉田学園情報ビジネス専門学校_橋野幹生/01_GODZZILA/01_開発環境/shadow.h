//----------------------------------------
//�@�e
//----------------------------------------
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//�}�N����`
#define MAX_SHADOW		(256)	//�e�̍ő吔

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float size_X;
	float size_Z;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Shadow;

//�v���g�^�C�v�錾
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float size_x, float size_z);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);

#endif

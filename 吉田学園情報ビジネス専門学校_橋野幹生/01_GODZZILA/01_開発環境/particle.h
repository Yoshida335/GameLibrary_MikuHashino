//----------------------------------------
//�@�p�[�e�B�N��
//----------------------------------------
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//�}�N����`
#define MAX_PARTICLE	(256)	//�r���{�[�h�̍ő吔

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 size;
	bool bUse;
	int nLife;
}Particle;

//�v���g�^�C�v�錾
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nLife, D3DXVECTOR3 size);

#endif



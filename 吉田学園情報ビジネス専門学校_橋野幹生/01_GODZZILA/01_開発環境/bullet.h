//----------------------------------------
//�@�e
//�@Author�F���슲��
//----------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//�}�N����`
#define MAX_BULLET	(128)	//�e�̍ő吔

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXCOLOR col;			//�J���[
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nIdxShadow;			//�e�p
	bool bUse;				//�g�p���Ă��邩�ǂ���
	int nLife;				//����
	D3DXVECTOR3 posdis;
}Bullet;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void CollisionBullet(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size, D3DXVECTOR3 *move);

#endif


//----------------------------------------
//�@�G
//----------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//�}�N����`
#define MAX_ENEMY			(126)	//���f���̍ő吔
#define ENEMY_SPEED			(1.0f)	//���f���̈ړ����x

//���f���̎��
typedef enum
{
	TYPE_ENEMY_01 = 0,
	TYPE_ENEMY_MAX
}ENEMYTYPE;

//���f���̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 diff;		//�����p
	D3DXVECTOR3 rotDest;	//�ړI�̊p�x
	int IdxShadow;			//�e�p
	bool bUse;				//�g���Ă��邩�ǂ���
	D3DXVECTOR3 vtxMin;		//���_�̍ŏ��l���擾�p
	D3DXVECTOR3 vtxMax;		//���_�̍ő�l���擾�p
	ENEMYTYPE nType;		//���f���̎��
	int nLife;				//�̗�
	D3DXVECTOR3 posdis;		//�v���C���[�Ƃ̍������߂�
	D3DXVECTOR3 size;		//�T�C�Y�ۑ�
	bool bAttack;
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);		//���f���̏�����
void UninitEnemy(void);		//���f���̏I��
void UpdateEnemy(void);		//���f���̍X�V
void DrawEnemy(void);		//���f���̕`��
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ENEMYTYPE type, int life);	//���f���̐ݒ�
void CollisionEnemy(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size);
void HitEnemyl(int nCntModel, int nDamage);
void CollisionENEMY(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size, D3DXVECTOR3 *move);

#endif


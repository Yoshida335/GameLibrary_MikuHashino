#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include <stdlib.h>
#include <time.h>

//�}�N����`
#define MAX_ENEMY				(128)	//�G�̍ő吔

//�G�̎��
typedef enum
{
	ENEMY_TYPE_000 = 0,			//�ʏ�
	ENEMY_TYPE_001,				//���
	ENEMY_TYPE_002,				//�A�C�e��
	ENEMY_TYPE_MAX
}ENEMYTYPE;

//�G�̏��
typedef enum
{
	ENEMYSTATE_NOMAL = 0,		//�ʏ���
	ENEMYSTATE_DAMAGE,			//�_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//�G�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	ENEMYTYPE nType;		//���
	ENEMYSTATE state;		//���
	int nCounterState;		//��ԃJ�E���^�[
	int nLife;				//�̗�
	bool bUse;				//�g�p���Ă��邩�ǂ���
	D3DXVECTOR3 move;		//�ړ���
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE nType);
Enemy * GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);
void CollisionEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pCol, D3DXVECTOR3 * pMove, float fWidth, float fHeight);

#endif
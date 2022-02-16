//----------------------------------------
//�@���f��
//----------------------------------------
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//�}�N����`
#define MAX_MODEL			(126)	//���f���̍ő吔
#define MODEL_SPEED			(1.0f)	//���f���̈ړ����x

//���f���̎��
typedef enum
{
	TYPE_BILL_01 = 0,
	TYPE_BILL_02,
	TYPE_MAX
}MODELTYPE;

//���f���̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXCOLOR col;			//�F
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	float diff;				//�����p
	float rotDestModel;		//�ړI�̊p�x
	int IdxShadow;			//�e�p
	bool bUse;				//�g���Ă��邩�ǂ���
	D3DXVECTOR3 vtxMin;		//���_�̍ŏ��l���擾�p
	D3DXVECTOR3 vtxMax;		//���_�̍ő�l���擾�p
	MODELTYPE nType;		//���f���̎��
	int nLife;				//�̗�
	bool bHit;				//�U�����������Ă��邩�ǂ���
	int nCntTime;
}Model;

typedef struct
{
	float nModelP;
	float nMaxLife;
	float nMax;
}Parcent;

//�v���g�^�C�v�錾
void InitModel(void);		//���f���̏�����
void UninitModel(void);		//���f���̏I��
void UpdateModel(void);		//���f���̍X�V
void DrawModel(void);		//���f���̕`��
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE type, int life);	//���f���̐ݒ�
bool CollisionModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size, D3DXVECTOR3 *move);	//���f���̓����蔻��
void CollisionAttack(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size);	//���f���̓����蔻��
void HitModel(int nCntModel, int nDamage);
Parcent * GetModeParcent(void);
void SaveParcent(void);
void LoadP(void);

#endif

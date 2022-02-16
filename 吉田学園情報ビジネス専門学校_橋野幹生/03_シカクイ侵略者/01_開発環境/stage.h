#ifndef _STAGE_H_
#define _STAGE_H_

#include "main.h"

//�X�e�[�W�̏��
typedef enum
{
	STAGESTATE_NOMAL = 0,		//�ʏ���
	STAGESTATE_DAMAGE,			//�_���[�W���
	STAGESTATE_MAX
}STAGESTATE;

//�X�e�[�W�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	STAGESTATE state;		//���
	int nCounterState;		//��ԃJ�E���^�[
	int nLife;				//�̗�
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Stage;

//�v���g�^�C�v�錾
void InitStage(void);
void UninitStage(void);
void UpdateStage(void);
void DrawStage(void);
void HitStage(int nDamage);
Stage * GetStage(void);

#endif

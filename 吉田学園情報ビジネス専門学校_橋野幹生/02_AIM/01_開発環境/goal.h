//----------------------------------------
//	�S�[���̃w�b�_�[
//�@Author�F���슲��
//----------------------------------------
#ifndef _GOAL_H_
#define _GOAL_H_

#include "main.h"

//�}�N����`
#define MAX_GOAL			(128)		//�ő�S�[����
#define GOAL_WIDTH			(60.0f)		//�S�[���̕�
#define GOAL_HEIGHT			(80.0f)		//�S�[���̍���

//�S�[���̏��
typedef enum
{
	GOAL_STATE_CLAUSE = 0,	//�܂��Ă�����
	GOAL_STATE_OPEN,		//�J���Ă�����
	GOAL_STATE_MAX
}GoalState;

//�u���b�N�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//���݂̈ʒu
	float fWidth;		//��
	float fHeight;		//����
	GoalState state;	//���
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Goal;

//�v���g�^�C�v�錾
void InitGoal(void);	//�S�[���̏���������
void UninitGoal(void);	//�S�[���̏I������
void UpdateGoal(void);	//�S�[���̍X�V����
void DrawGoal(void);	//�S�[���̕`�揈��
void SetGoal(D3DXVECTOR3 pos);	//�S�[���̐ݒ�
void CollisionGoal(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, float fWidth, float fHeight, bool PlayerItem);	//�S�[���̓����蔻��

#endif
#ifndef _GOAL_H_
#define _GOAL_H_

#include "main.h"

//�}�N����`
#define MAX_GOAL			(128)			//�ő�A�C�e����
#define GOAL_WIDTH			(60.0f)		//�A�C�e���̕�
#define GOAL_HEIGHT			(80.0f)		//�A�C�e���̍���

//�A�C�e���̎��
typedef enum
{
	GOAL_STATE_CLAUSE = 0,
	GOAL_STATE_OPEN,
	GOAL_STATE_MAX
}GoalState;

//�u���b�N�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	float fWidth;			//��
	float fHeight;			//����
	GoalState state;		//���
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Goal;

//�v���g�^�C�v�錾
void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
void SetGoal(D3DXVECTOR3 pos);
void CollisionGoal(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, float fWidth, float fHeight, bool PlayerItem);

#endif

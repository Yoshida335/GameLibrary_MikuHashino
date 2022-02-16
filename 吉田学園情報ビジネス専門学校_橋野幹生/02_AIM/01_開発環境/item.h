#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//�}�N����`
#define MAX_ITEM			(128)		//�ő�A�C�e����
#define ITEM_WIDTH			(30.0f)		//�A�C�e���̕�
#define ITEM_HEIGHT			(30.0f)		//�A�C�e���̍���

//�A�C�e���̎��
typedef enum
{
	ITEM_TYPE_0 = 0,		//�R�C��
	ITEM_TYPE_1,			//�C(�W�����v�̓A�b�v)
	ITEM_TYPE_3,			//��
	ITEM_TYPE_4,			//�C(�X�s�[�h�A�b�v)
	ITEM_TYPE_MAX
}ITEM_TYPE;

//�u���b�N�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	float fWidth;			//��
	float fHeight;			//����
	int nCounterAnim;		//�J�E���^�[
	int nPatternAnim;		//�p�^�[���ԍ�
	ITEM_TYPE type;			//���
	bool bUse;				//�g�p���Ă��邩�ǂ���
}ITEM;

//�v���g�^�C�v�錾
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, ITEM_TYPE type);
ITEM * GetItem(void);
bool CollisionItem(D3DXVECTOR3 * pos, float fWidth, float fHeight, ITEM ** item);
void DeleteItem(int nCntItem);
int Coin(void);

#endif

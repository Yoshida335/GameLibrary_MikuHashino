//----------------------------------------
//	�A�C�e���̃w�b�_�[
//�@Author�F���슲��
//----------------------------------------
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//�}�N����`
#define MAX_ITEM		(128)	//�ő�A�C�e����
#define ITEM_WIDTH		(30.0f)	//�A�C�e���̕�
#define ITEM_HEIGHT		(30.0f)	//�A�C�e���̍���

//�A�C�e���̎��
typedef enum
{
	ITEM_COIN = 0,	//�R�C��
	ITEM_KEY,		//��
	ITEM_TYPE_MAX
}ITEM_TYPE;

//�u���b�N�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//���݂̈ʒu
	float fWidth;		//��
	float fHeight;		//����
	int nCounterAnim;	//�J�E���^�[
	int nPatternAnim;	//�p�^�[���ԍ�
	ITEM_TYPE type;		//���
	bool bUse;			//�g�p���Ă��邩�ǂ���
}ITEM;

//�v���g�^�C�v�錾
void InitItem(void);	//�A�C�e���̏���������
void UninitItem(void);	//�A�C�e���̏I������
void UpdateItem(void);	//�A�C�e���̍X�V����
void DrawItem(void);	//�A�C�e���̕`�揈��
void SetItem(D3DXVECTOR3 pos, ITEM_TYPE type);	//�A�C�e���̐ݒ�
ITEM * GetItem(void);	//�A�C�e���̏��
void CollisionItem(D3DXVECTOR3 * pos, float fWidth, float fHeight, ITEM ** item);	//�A�C�e���̓����蔻��
void DeleteItem(int nCntItem);	//�A�C�e���̏���
int GetNumCoin(void);	//�R�C���̖������

#endif

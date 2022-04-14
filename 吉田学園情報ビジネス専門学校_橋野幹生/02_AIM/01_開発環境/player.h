//----------------------------------------
//	�v���C���[�̃w�b�_�[
//	Author�F���슲��
//----------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "item.h"

//�v���C���[�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nCounterAnim;		//�J�E���^�[
	int nPatternAnim;		//�p�^�[���ԍ�
	int nDirectionMove;		//�����@0�F�E�����@1�F������
	bool bIsJumping;		//�W�����v��
	ITEM * pItem;			//�A�C�e���̏��
}Player;

//�v���C���[�A�C�e���̒�`
typedef enum
{
	PLAYER_ITEM_COIN = 0,	//�R�C��
	PLAYER_ITEM_KEY,		//��
	PLAYER_ITEM_MAX
}PLAYRE_ITEM;

//�v���g�^�C�v�錾
void InitPlayer(void);		//�v���C���[�̏���������
void UninitPlayer(void);	//�v���C���[�̏I������
void UpdatePlayer(void);	//�v���C���[�̍X�V����
void DrawPlayer(void);		//�v���C���[�̕`�揈��
void PlayerMove(void);		//�v���C���[�̈ړ�����
void PlayerItem(void);		//�v���C���[�̃A�C�e����������

#endif

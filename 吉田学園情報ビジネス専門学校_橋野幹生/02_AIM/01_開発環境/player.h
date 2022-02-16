//----------------------------------------
//�v���C���[
//----------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "item.h"
#include "block.h"

//�}�N����`
#define PLAYER_WIDTH		(30.0f)			//�v���C���[�̕�
#define PLAYER_HEIGHT		(30.0f)			//�v���C���[�̍���
#define PLAYER_SPEED		(0.8f)			//�v���C���[�̈ړ��̑���
#define PLAYER_JUMP			(20.0f)			//�v���C���[�̃W�����v��

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
	bool bIsCatching;
	ITEM * pItem;
	BLOCK * pBlock;
}Player;

//�v���C���[�A�C�e���̒�`
typedef enum
{
	PLAYER_ITEM_COIN = 0,
	PLAYER_ITEM_JUMPSHOSE,
	PLAYER_ITEM_KEY,
	PLAYER_ITEM_SPEEDSHOSE,
	PLAYER_ITEM_MAX
}PLAYRE_ITEM;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void PlayerMove(void);
void PlayerItem(void);

#endif

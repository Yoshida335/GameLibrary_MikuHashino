//----------------------------------------
//	�v���C���[�̏���
//�@Author�F���슲��
//----------------------------------------
#include "player.h"
#include "input.h"
#include "block.h"
#include "fade.h"
#include "ladder.h"
#include "goal.h"
#include "sound.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Player g_Player;
bool g_PlayerItem[PLAYER_ITEM_MAX];

//----------------------------------------------
//	�v���C���[�̏���������
//----------------------------------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Player.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f);		//���݂̈ʒu�̏����ݒ�
	g_Player.posOld = g_Player.pos;									//�O��̈ʒu�̏����ݒ�
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ړ��ʂ̏����ݒ�
	g_Player.nCounterAnim = 0;			//�J�E���^�[������
	g_Player.nPatternAnim = 0;			//�p�^�[���ԍ�������
	g_Player.nDirectionMove = 0;		//����
	g_Player.bIsJumping = false;		//�W�����v��������
	g_Player.pItem = NULL;		//�A�C�e��

	//�A�C�e���������Ă��邩�ǂ���
	g_PlayerItem[PLAYER_ITEM_COIN] = false;
	g_PlayerItem[PLAYER_ITEM_KEY] = false;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\���т܂�2.png",
		&g_pTexturePlayer);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_WIDTH / 2, g_Player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_WIDTH / 2, g_Player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_WIDTH / 2, g_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_WIDTH / 2, g_Player.pos.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhm = 1.0f;
	pVtx[1].rhm = 1.0f;
	pVtx[2].rhm = 1.0f;
	pVtx[3].rhm = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((1.0f / 4) * g_Player.nPatternAnim,		(1.0f / 1) * g_Player.nDirectionMove);
	pVtx[1].tex = D3DXVECTOR2((1.0f / 4) * (g_Player.nPatternAnim + 1), (1.0f / 1) * g_Player.nDirectionMove);
	pVtx[2].tex = D3DXVECTOR2((1.0f / 4) * g_Player.nPatternAnim,		(1.0f / 1) * g_Player.nDirectionMove + (1.0f / 2));
	pVtx[3].tex = D3DXVECTOR2((1.0f / 4) * (g_Player.nPatternAnim + 1), (1.0f / 1) * g_Player.nDirectionMove + (1.0f / 2));

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//----------------------------------------------
//	�v���C���[�̏I������
//----------------------------------------------
void UninitPlayer(void)
{
	if (g_pVtxBuffPlayer != NULL)
	{//���_�o�b�t�@�̔j��
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}

	if (g_pTexturePlayer != NULL)
	{//�e�N�X�`���̔j��
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}

//----------------------------------------------
//	�v���C���[�̍X�V����
//----------------------------------------------
void UpdatePlayer(void)
{
	VERTEX_2D * pVtx;	//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//�d��
	g_Player.move.y += 0.8f;

	//�O��̈ʒu��ۑ�
	g_Player.posOld = g_Player.pos;

	//�A�C�e�������Ă邩
	PlayerItem();

	//�v���C���[�̈ړ�����
	PlayerMove();

	//�u���b�N�Ƃ̓����蔻��
	CollisionBlock_P(&g_Player.pos, &g_Player.posOld, &g_Player.move, PLAYER_WIDTH, PLAYER_HEIGHT);

	//�A�C�e���Ƃ̓����蔻��
	CollisionItem(&g_Player.pos, PLAYER_WIDTH, PLAYER_HEIGHT, &g_Player.pItem);

	//��q
	CollisionLadder(&g_Player.pos, &g_Player.posOld, &g_Player.move, PLAYER_WIDTH, PLAYER_HEIGHT);

	//�S�[��
	CollisionGoal(&g_Player.pos, &g_Player.posOld, PLAYER_WIDTH, PLAYER_HEIGHT, g_PlayerItem[PLAYER_ITEM_KEY]);

	//�W�����v�̉�
	g_Player.bIsJumping = !CollisionBlock_P(&g_Player.pos, &g_Player.posOld, &g_Player.move, PLAYER_WIDTH, PLAYER_HEIGHT);

	if (g_Player.pos.x - PLAYER_WIDTH / 2 >= SCREEN_WIDTH)
	{//��ʊO(�E��)�ɏo����
		g_Player.pos = D3DXVECTOR3(0.0f - PLAYER_WIDTH / 2 + 0.01f, g_Player.pos.y, 0.0f);			//�΂߂��蔲���h�~�̂��� +0.01f ���Ă�
	}
	else if (g_Player.pos.x + PLAYER_WIDTH / 2 <= 0.0f)
	{//��ʊO(����)�ɏo����
		g_Player.pos = D3DXVECTOR3(SCREEN_WIDTH + PLAYER_WIDTH / 2 - 0.01f, g_Player.pos.y, 0.0f);	//�΂߂��蔲���h�~�̂��� +0.01f ���Ă�
	}
	if (g_Player.pos.y >= SCREEN_HEIGHT)
	{//��ʊO(����)�ɏo���� 
		g_Player.pos.y = SCREEN_HEIGHT;
		g_Player.move.y = 0.0f;
		g_Player.bIsJumping = false;
	}

	//���_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_WIDTH / 2, g_Player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_WIDTH / 2, g_Player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_WIDTH / 2, g_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_WIDTH / 2, g_Player.pos.y, 0.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((1.0f / 4) * g_Player.nPatternAnim, (1.0f / 2) * g_Player.nDirectionMove);
	pVtx[1].tex = D3DXVECTOR2((1.0f / 4) * (g_Player.nPatternAnim + 1), (1.0f / 2) * g_Player.nDirectionMove);
	pVtx[2].tex = D3DXVECTOR2((1.0f / 4) * g_Player.nPatternAnim, (1.0f / 2) * g_Player.nDirectionMove + (1.0f / 2));
	pVtx[3].tex = D3DXVECTOR2((1.0f / 4) * (g_Player.nPatternAnim + 1), (1.0f / 2) * g_Player.nDirectionMove + (1.0f / 2));

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//----------------------------------------------
//	�v���C���[�̕`�揈��
//----------------------------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	//�|���S���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//----------------------------------------------
//	�v���C���[�̈ړ�����
//----------------------------------------------
void PlayerMove(void)
{
	g_Player.nCounterAnim += 1;

	//g_Player.bIsJumping = false;

	//���E�ړ�
	if (GetKeyboardPress(DIK_A) == true)
	{//A�L�[�������ꂽ
	 //�������Ɉړ�
		g_Player.move.x -= PLAYER_SPEED;

		g_Player.nDirectionMove = 1;	//������
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//D�L�[�������ꂽ
	 //�E�����Ɉړ�
		g_Player.move.x += PLAYER_SPEED;

		g_Player.nDirectionMove = 0;	//�E����
	}

	//��q�ł̏㉺�ړ�
	if (GetKeyboardPress(DIK_W) == true)
	{//W�L�[�������ꂽ
		if (CollisionLadder(&g_Player.pos, &g_Player.posOld, &g_Player.move, PLAYER_WIDTH, PLAYER_HEIGHT) == true)
		{
			g_Player.move.y = -2.0f;
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//S�L�[�������ꂽ
		if (CollisionLadder(&g_Player.pos, &g_Player.posOld, &g_Player.move, PLAYER_WIDTH, PLAYER_HEIGHT) == true)
		{
			g_Player.move.y = 2.0f;
		}
	}

	//�W�����v
	if (GetKeyboardTrigger(DIK_SPACE) == true && g_Player.bIsJumping == false)
	{//�X�y�[�X�L�[�������ꂽ
		g_Player.move.y -= PLAYER_JUMP;

		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_JUMP);

		g_Player.bIsJumping = true;

		if (g_Player.nPatternAnim == 0)
		{//�v���C���[���~�܂��Ă���p�^�[���ԍ��̎�
			g_Player.nPatternAnim += 1;
		}
	}

	if (g_Player.bIsJumping != true && GetKeyboardPress(DIK_F) != true)
	{//�W�����v������Ȃ���
		if (g_Player.move.x >= 1.0f || g_Player.move.x <= -1.0f)
		{//�v���C���[�������Ă��鎞
			if ((g_Player.nCounterAnim % 8) == 0)
			{//��莞�Ԍo��
			 //�p�^�[��No.���X�V����
				g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % 4;
			}
		}
		else
		{//�v���C���[���~�܂�����
			if (g_Player.nPatternAnim == 1)
			{//�v���C���[���i��ł�p�^�[���ԍ��̎�
				g_Player.nPatternAnim += 1;
			}
			if (g_Player.nPatternAnim == 2)
			{//�v���C���[���i��ł�p�^�[���ԍ��̎�
				g_Player.nPatternAnim += 2;
			}
			if (g_Player.nPatternAnim == 3)
			{//�v���C���[���i��ł�p�^�[���ԍ��̎�
				g_Player.nPatternAnim += 3;
			}
		}
	}

	if (g_Player.nPatternAnim >= 4)
	{
		g_Player.nPatternAnim = 0;		//�p�^�[���ԍ����O�ɖ߂�
	}

	//�ʒu���X�V
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;

	//�ړ��ʂ��X�V(����������)
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.2f;
}

//----------------------------------------------
//	�v���C���[�̃A�C�e������
//----------------------------------------------
void PlayerItem(void)
{
	if (g_Player.pItem != NULL)
	{
		switch (g_Player.pItem->type)
		{
		case ITEM_COIN:
			g_PlayerItem[PLAYER_ITEM_COIN] = true;
			break;

		case ITEM_KEY:
			g_PlayerItem[PLAYER_ITEM_KEY] = true;
			break;
		}
	}
}

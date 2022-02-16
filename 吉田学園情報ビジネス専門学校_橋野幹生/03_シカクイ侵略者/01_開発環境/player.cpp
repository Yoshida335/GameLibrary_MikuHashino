#include "main.h"
#include "enemy.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
#include "time.h"

//�}�N����`
#define PLAYER_SIZE			(80.0f)	//�v���C���[�̃T�C�Y
#define PLAYER_WIDTH		(80.0f)	//�v���C���[�̕�
#define PLAYER_HEIGHT		(80.0f)	//�v���C���[�̍���
#define PLAYER_MOVE			(7.0f)	//�v���C���[�̈ړ�����
#define ATTACK_TIME			(10)	//�e�̍U���Ԋu�̎���
#define BULLET_MOVE			(8.0f)

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturePLAYER = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPLAYER = NULL;
LPDIRECT3DTEXTURE9 g_pTextureBR = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBR = NULL;
int g_nCounterAnimPlayer;						//�A�j���[�V�����J�E���^�[
int g_nPatternAnimPlayer;						//�A�j���[�V�����p�^�[��No.
Player g_Player;
D3DXVECTOR3 g_posBR;
float g_fLengthPlayer;							//�Ίp���̒���
float g_fAnglePlayer;							//�Ίp���̊p�x
int g_nCountAttack = 0;							//�U���Ԋu�̃J�E���^�[
int g_BulletRot;								//�e�̔��ˌ���

//----------------------------------------
//  �v���C���[�̏������ݒ菈��
//----------------------------------------
void InitPLAYER(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\���т܂�2.png",
		&g_pTexturePLAYER);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\yazirusi.png",
		&g_pTextureBR);

	g_nCounterAnimPlayer = 0;		//�J�E���^�[��������
	g_nPatternAnimPlayer = 0;		//�p�^�[��No.��������
	g_Player.pos = D3DXVECTOR3(500.0f, 600.0f, 0.0f);		//���݂̈ʒu������
	g_Player.posOld = D3DXVECTOR3(500.0f, 600.0f, 0.0f);	//�O��̈ʒu������
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ��ʏ�����
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����������
	g_Player.bUse = false;
	g_BulletRot = 2;
	g_posBR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�Ίp���̒����Z�o
	g_fLengthPlayer = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_HEIGHT * PLAYER_HEIGHT) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	g_fAnglePlayer = atan2f(PLAYER_WIDTH, PLAYER_HEIGHT);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPLAYER,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBR,
		NULL);

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPLAYER->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhm = 1.0f;
	pVtx[1].rhm = 1.0f;
	pVtx[2].rhm = 1.0f;
	pVtx[3].rhm = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPLAYER->Unlock();

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBR->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posBR.x - 100.0f, g_posBR.y - 25.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posBR.x + 100.0f, g_posBR.y - 25.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posBR.x - 100.0f, g_posBR.y + 25.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posBR.x + 100.0f, g_posBR.y + 25.0f, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBR->Unlock();
}

//----------------------------------------
//  �v���C���[�̏I������
//----------------------------------------
void UninitPLAYER(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePLAYER != NULL)
	{
		g_pTexturePLAYER->Release();
		g_pTexturePLAYER = NULL;
	}

	if (g_pTextureBR != NULL)
	{
		g_pTextureBR->Release();
		g_pTextureBR = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPLAYER != NULL)
	{
		g_pVtxBuffPLAYER->Release();
		g_pVtxBuffPLAYER = NULL;
	}

	if (g_pVtxBuffBR != NULL)
	{
		g_pVtxBuffBR->Release();
		g_pVtxBuffBR = NULL;
	}
}

//----------------------------------------
//  �v���C���[�̍X�V����
//----------------------------------------
void UpdatePLAYER(void)
{
	//�ʒu�ۑ�
	g_Player.posOld = g_Player.pos;

	//�G�l�~�[�Ƃ̓����蔻��
	CollisionBlock(&g_Player.pos, &g_Player.posOld, &g_Player.move, PLAYER_WIDTH, PLAYER_HEIGHT);

	//�v���C���[�̐���
	PlayerControl();
}

//----------------------------------------
//  �v���C���[�̕`�揈��
//----------------------------------------
void DrawPLAYER(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPLAYER, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePLAYER);

	//�|���S���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	/*//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBR, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBR);

	//�|���S���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);*/
}

//----------------------------------------
//  �v���C���[�̐��䏈��
//----------------------------------------
void PlayerControl(void)
{
	//�v���C���[�̓��쏈��
	PlayerMove();

	//�v���C���[�̍U��(�e����)����
	PlayerAttack();
}

//----------------------------------------
//  �v���C���[�̓��쏈��
//----------------------------------------
void PlayerMove(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPLAYER->Lock(0, 0, (void**)&pVtx, 0);

	g_nCounterAnimPlayer++;			//�J�E���^�[�����Z

	if (GetKeyboardPress(DIK_A) == true)
	{//A�L�[�������ꂽ
		if (g_Player.pos.x >= PLAYER_SIZE)
		{
			//g_posPlayer.x += sinf(-D3DX_PI / 2.0f) * PLAYER_MOVE;
			//g_posPlayer.y += cosf(-D3DX_PI / 2.0f) * PLAYER_MOVE;

			g_Player.move.x += sinf(-D3DX_PI / 2.0f) * 0.8f;
			g_Player.move.y += cosf(-D3DX_PI / 2.0f) * 0.8f;
		}

		if ((g_nCounterAnimPlayer % 6) == 0)
		{//��莞�Ԍo��
		 //�p�^�[��No.���X�V����
			g_nPatternAnimPlayer = (g_nPatternAnimPlayer + 1) % 4;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.25f * g_nPatternAnimPlayer + 0.25f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(0.25f * g_nPatternAnimPlayer, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.25f * g_nPatternAnimPlayer + 0.25f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.25f * g_nPatternAnimPlayer, 1.0f);
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//D�L�[�������ꂽ
		if (g_Player.pos.x <= SCREEN_WIDTH - 340.0f - PLAYER_SIZE)
		{
				//g_posPlayer.x += sinf(D3DX_PI / 2.0f) * PLAYER_MOVE;
				//g_posPlayer.y += cosf(D3DX_PI / 2.0f) * PLAYER_MOVE;

				g_Player.move.x += sinf(D3DX_PI / 2.0f) * 0.8f;
				g_Player.move.y += cosf(D3DX_PI / 2.0f) * 0.8f;
		}

		if ((g_nCounterAnimPlayer % 12) == 0)
		{//��莞�Ԍo��
		 //�p�^�[��No.���X�V����
			g_nPatternAnimPlayer = (g_nPatternAnimPlayer + 1) % 4;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.25f * g_nPatternAnimPlayer, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(0.25f * g_nPatternAnimPlayer + 0.25f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.25f * g_nPatternAnimPlayer, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.25f * g_nPatternAnimPlayer + 0.25f, 1.0f);
		}
	}
	else
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);
	}

		//�ʒu���X�V
		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;

		//�ړ��ʂ��X�V(����������)
		g_Player.move.x += (0.0f - g_Player.move.x) * 0.15f;
		g_Player.move.y += (0.0f - g_Player.move.y) * 0.15f;

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[3].pos.z = 0.0f;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPLAYER->Unlock();
}

//----------------------------------------
//  �v���C���[�̍U������(�e����)����
//----------------------------------------
void PlayerAttack(void)
{
	g_nCountAttack++;		//�U���Ԋu�̃J�E���^�[

	//�ǂ̊p�x��������₷������
	if (GetKeyboardTrigger(DIK_RIGHT) == true)
	{//���L�[������
		if (g_BulletRot == 0)
		{
			g_BulletRot = 5;
		}
		else
		{
			g_BulletRot -= 1;
		}
	}
	else if (GetKeyboardTrigger(DIK_LEFT) == true)
	{//���L�[������
		if (g_BulletRot == 4)
		{
			g_BulletRot = 0;
		}
		else
		{
			g_BulletRot += 1;
		}
	}

	//if (g_nCountAttack > ATTACK_TIME)
	//{
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{//�X�y�[�X�L�[������
	 //�e�̐ݒ�
		switch (g_BulletRot)
		{
		case 0:
			SetBullet(g_Player.pos, D3DXVECTOR3(BULLET_MOVE, 0.0f, 0.0f));
			break;

		case 1:
			SetBullet(g_Player.pos, D3DXVECTOR3(BULLET_MOVE, -BULLET_MOVE, 0.0f));
			break;

		case 2:
			SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -BULLET_MOVE, 0.0f));
			break;

		case 3:
			SetBullet(g_Player.pos, -D3DXVECTOR3(BULLET_MOVE, BULLET_MOVE, 0.0f));
			break;

		case 4:
			SetBullet(g_Player.pos, -D3DXVECTOR3(BULLET_MOVE, 0.0f, 0.0f));
			break;
		}
		g_nCountAttack = 0;

		//�T�E���h�̍Đ�
		//PlaySound(SOUND_LABEL_SE_SHOT);
	}
	//}
}

//----------------------------------------
//  �v���C���[�̃q�b�g����
//----------------------------------------
void HitPlayer(int nDamage)
{
	g_Player.nLife -= nDamage;

	if (g_Player.nLife == 0)
	{
		SetExplosion(g_Player.pos, 255);

		g_Player.bDisp = false;
		g_Player.state = PLAYERSTATE_DEATH;
		g_Player.nCounterState = 60;
	}
	else
	{
		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.nCounterState = 5;

		VERTEX_2D * pVtx;

		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPLAYER->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPLAYER->Unlock();
	}
}

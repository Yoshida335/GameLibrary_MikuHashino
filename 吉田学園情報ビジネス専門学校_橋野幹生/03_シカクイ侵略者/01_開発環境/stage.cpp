#include "stage.h"
#include "enemy.h"
#include "fade.h"
#include "explosion.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureStage = {};				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStage = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Stage g_Stage;

//----------------------------------------
//  �X�e�[�W�̏������ݒ菈��
//----------------------------------------
void InitStage(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\STAGE.png",
		&g_pTextureStage);

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStage,
		NULL);

	//������
	g_Stage.pos = D3DXVECTOR3(480.0f, SCREEN_HEIGHT - 40.0f, 0.0f);
	g_Stage.nLife = 10;
	g_Stage.state = STAGESTATE_NOMAL;
	g_Stage.bUse = false;
	g_Stage.nCounterState = 0;

	VERTEX_2D * pVtx;	//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Stage.pos.x - 480.0f, g_Stage.pos.y - 40.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Stage.pos.x + 480.0f, g_Stage.pos.y - 40.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Stage.pos.x - 480.0f, g_Stage.pos.y + 40.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Stage.pos.x + 480.0f, g_Stage.pos.y + 40.0f, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffStage->Unlock();
}

//----------------------------------------
//�@�X�e�[�W�̏I������
//----------------------------------------
void UninitStage(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureStage != NULL)
	{
		g_pTextureStage->Release();
		g_pTextureStage = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffStage != NULL)
	{
		g_pVtxBuffStage->Release();
		g_pVtxBuffStage = NULL;
	}
}

//----------------------------------------
//  �X�e�[�W�̍X�V����
//----------------------------------------
void UpdateStage(void)
{
	//VERTEX_2D * pVtx;

	////���_�������b�N���A���_���ւ̃|�C���^���擾
	//g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

	//	if (g_Stage.bUse == true)
	//	{//�X�e�[�W���g�p����Ă���
	//		switch (g_Stage.state)
	//		{
	//		case STAGESTATE_NOMAL:
	//			//���_���W�̐ݒ�
	//			pVtx[0].pos = D3DXVECTOR3(g_Stage.pos.x - 480.0f, g_Stage.pos.y - 40.0f, 0.0f);
	//			pVtx[1].pos = D3DXVECTOR3(g_Stage.pos.x + 480.0f, g_Stage.pos.y - 40.0f, 0.0f);
	//			pVtx[2].pos = D3DXVECTOR3(g_Stage.pos.x - 480.0f, g_Stage.pos.y + 40.0f, 0.0f);
	//			pVtx[3].pos = D3DXVECTOR3(g_Stage.pos.x + 480.0f, g_Stage.pos.y + 40.0f, 0.0f);

	//			break;

	//		case STAGESTATE_DAMAGE:
	//			g_Stage.nCounterState--;

	//			if (g_Stage.nCounterState <= 0)
	//			{
	//				g_Stage.state = STAGESTATE_NOMAL;

	//				//���_�J���[�̐ݒ�
	//				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//			}

	//			break;
	//		}
	//	}

	////���_�o�b�t�@���A�����b�N����
	//g_pVtxBuffStage->Unlock();
}

//----------------------------------------
//  �X�e�[�W�̕`�揈��
//----------------------------------------
void DrawStage(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStage, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureStage);

	//�|���S���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//----------------------------------------
//  �X�e�[�W�̃q�b�g����
//----------------------------------------
void HitStage(int nDamage)
{
	g_Stage.nLife -= nDamage;

	if (g_Stage.nLife <= 0)
	{
		//���[�h�ݒ�(�Q�[����ʂɈڍs)
		//SetFade(MODE_RESULT);
	}
	else
	{
		g_Stage.state = STAGESTATE_DAMAGE;
		g_Stage.nCounterState = 5;

		VERTEX_2D * pVtx;

		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffStage->Unlock();
	}
}

//----------------------------------------
//  �X�e�[�W�̐ݒ�
//----------------------------------------
Stage * GetStage(void)
{
	return &g_Stage;
}


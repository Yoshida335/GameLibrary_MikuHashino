#include "bg.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBG[2] = {};			//�e�N�X�`��(2����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG[2] = {};		//���_�o�b�t�@�ւ̃|�C���^
float g_aPosTexV;									//�e�N�X�`�����W�̊J�n�ʒu(V�l)

//----------------------------------------
//  �w�i�̏������ݒ菈��
//----------------------------------------
void InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_aPosTexV = 0.0f;

	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(
	//	pDevice,
	//	"data\\TEXTURE\\sky000.jpg",
	//	&g_pTextureBG[0]);
	//
	//D3DXCreateTextureFromFile(
	//	pDevice,
	//	"data\\TEXTURE\\mountain000.png",
	//	&g_pTextureBG[1]);

	//���_�o�b�t�@�̐���
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffBG[nCnt],
			NULL);
	}

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG[0]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(g_aPosTexV, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_aPosTexV + 0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aPosTexV, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aPosTexV + 0.25f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG[0]->Unlock();

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG[1]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT - 200.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG[1]->Unlock();
}

//----------------------------------------
//  �w�i�̏I������
//----------------------------------------
void UninitBG(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBG[nCnt] != NULL)
		{
			g_pTextureBG[nCnt]->Release();
			g_pTextureBG[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_pVtxBuffBG[nCnt] != NULL)
		{
			g_pVtxBuffBG[nCnt]->Release();
			g_pVtxBuffBG[nCnt] = NULL;
		}
	}
}

//----------------------------------------
//�@�w�i�̍X�V����
//----------------------------------------
void UpdateBG(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG[0]->Lock(0, 0, (void**)&pVtx, 0);

	g_aPosTexV += 0.0001f;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_aPosTexV, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_aPosTexV + 0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aPosTexV, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aPosTexV + 0.25f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG[0]->Unlock();
}

//----------------------------------------
//  �w�i�̕`�揈��
//----------------------------------------
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffBG[nCnt], 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBG[nCnt]);

		//�|���S���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//----------------------------------------
//	�Z���N�g�̏���
//�@Author�F���슲��
//----------------------------------------
#include "select.h"
#include "input.h"
#include "sound.h"
#include "fade.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureSelect[MAX_SELECT] = {};	//�e�N�X�`��(2����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelect = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBGG = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBGG = {};		//���_�o�b�t�@�ւ̃|�C���^
SELECT g_Select[MAX_SELECT];
STAGE_No g_nSelect;
bool g_bSelect = false;

//----------------------------------------
//  �Z���N�g�̏������ݒ菈��
//----------------------------------------
void InitSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	g_bSelect = false;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\stage_1.png",
		&g_pTextureSelect[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\stage_2.png",
		&g_pTextureSelect[1]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\BGG.png",
		&g_pTextureBGG);

	//������
	for (int nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
	{
		g_Select[nCntSelect].pos = D3DXVECTOR3((SCREEN_WIDTH / 2), 280.0f + (200.0f * nCntSelect), 0.0f);
		g_Select[nCntSelect].state = SELECT_OFF;
	}
	g_nSelect = STAGE_No_0;
	g_Select[0].state = SELECT_ON;

	//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SELECT,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffSelect,
			NULL);

		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SELECT,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffBGG,
			NULL);

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
	{
		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Select[nCntSelect].pos.x - (SELECT_WIDTH / 2), g_Select[nCntSelect].pos.y - (SELECT_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Select[nCntSelect].pos.x + (SELECT_WIDTH / 2), g_Select[nCntSelect].pos.y - (SELECT_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Select[nCntSelect].pos.x - (SELECT_WIDTH / 2), g_Select[nCntSelect].pos.y + (SELECT_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Select[nCntSelect].pos.x + (SELECT_WIDTH / 2), g_Select[nCntSelect].pos.y + (SELECT_HEIGHT / 2), 0.0f);

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

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect->Unlock();

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBGG->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBGG->Unlock();
}

//----------------------------------------
//  �Z���N�g�̏I������
//----------------------------------------
void UninitSelect(void)
{
	//�T�E���h�̒�~
	StopSound();

	for (int nCnt = 0; nCnt < MAX_SELECT; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureSelect[nCnt] != NULL)
		{
			g_pTextureSelect[nCnt]->Release();
			g_pTextureSelect[nCnt] = NULL;
		}
	}

	//�e�N�X�`���̔j��
	if (g_pTextureBGG != NULL)
	{
		g_pTextureBGG->Release();
		g_pTextureBGG = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSelect != NULL)
	{
		g_pVtxBuffSelect->Release();
		g_pVtxBuffSelect = NULL;
	}
}

//----------------------------------------
//�@�Z���N�g�̍X�V����
//----------------------------------------
void UpdateSelect(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//RETURN�L�[�������ꂽ
		if (!g_bSelect)
		{
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_TITLE_BUTTON);

			//���[�h�ݒ�(�Q�[����ʂɈڍs)
			SetFade(MODE_RULE);

			g_bSelect = true;
		}
	}

	if (GetKeyboardTrigger(DIK_W) == true)
	{//W�L�[�������ꂽ
		switch (g_nSelect)
		{
		case 0:
			g_nSelect = STAGE_No_1;
			g_Select[0].state = SELECT_OFF;
			g_Select[STAGE_No_0].state = SELECT_ON;
			break;

		case 1:
			g_nSelect = STAGE_No_0;
			g_Select[1].state = SELECT_OFF;
			g_Select[STAGE_No_0].state = SELECT_ON;
			break;
		}
	}
	if (GetKeyboardTrigger(DIK_S) == true)
	{//S�L�[�������ꂽ
		switch (g_nSelect)
		{
		case 0:
			g_nSelect = STAGE_No_1;

			g_Select[0].state = SELECT_OFF;
			g_Select[STAGE_No_1].state = SELECT_ON;
			break;

		case 1:
			g_nSelect = STAGE_No_0;

			g_Select[1].state = SELECT_OFF;
			g_Select[STAGE_No_0].state = SELECT_ON;
			break;
		}
	}
	
	for (int nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
	{
		switch (g_Select[nCntSelect].state)
		{
		case SELECT_OFF:
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			break;

		case SELECT_ON:
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}

		pVtx += 4;
	}

	if (GetKeyboardTrigger(DIK_F1) == true)
	{//S�L�[�������ꂽ
		g_nSelect = STAGE_No_0;
		SetFade(MODE_GAME);
	}
	if (GetKeyboardTrigger(DIK_F2) == true)
	{//S�L�[�������ꂽ
		g_nSelect = STAGE_No_1;
		SetFade(MODE_GAME);
	}
	if (GetKeyboardTrigger(DIK_F3) == true)
	{//S�L�[�������ꂽ
		g_nSelect = STAGE_No_2;
		SetFade(MODE_GAME);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect->Unlock();

}

//----------------------------------------
//  �Z���N�g�̕`�揈��
//----------------------------------------
void DrawSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBGG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBGG);

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSelect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_SELECT; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureSelect[nCnt]);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt * 4,
			2);
	}


}

//----------------------------------------
//  �X�e�[�W�ԍ��̏��
//----------------------------------------
STAGE_No * GetSelect(void)
{
	return &g_nSelect;
}
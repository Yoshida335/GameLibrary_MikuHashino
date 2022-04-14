//----------------------------------------
//	�^�C�g����ʂ̏���
//	Author�F���슲��
//----------------------------------------
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

LPDIRECT3DTEXTURE9 g_pTextureTitle[2] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle[2] = {};	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posText;
bool bTitle;	//��񂾂��N���p

//----------------------------------------
//  �^�C�g���̏������ݒ菈��
//----------------------------------------
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\title.png",
		&g_pTextureTitle[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\PRESSENTER.png",
		&g_pTextureTitle[1]);

	//�ʒu������(PRESS ENTER)
	g_posText = D3DXVECTOR3((SCREEN_WIDTH / 2), 500.0f, 0.0f);
	bTitle = false;

	//���_�o�b�t�@�̐���
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffTitle[nCnt],
			NULL);
	}

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//�w�i�̒��_�o�b�t�@
	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle[0]->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTitle[0]->Unlock();

	//�e�L�X�g�̒��_�o�b�t�@
	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle[1]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posText.x - 150.0f, g_posText.y - 60.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posText.x + 150.0f, g_posText.y - 60.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posText.x - 150.0f, g_posText.y + 60.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posText.x + 150.0f, g_posText.y + 60.0f, 0.0f);

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
	g_pVtxBuffTitle[1]->Unlock();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM_START);
}

//----------------------------------------
//  �^�C�g���̏I������
//----------------------------------------
void UninitTitle(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_pTextureTitle[nCnt] != NULL)
		{//�e�N�X�`���̔j��
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_pVtxBuffTitle[nCnt] != NULL)
		{//���_�o�b�t�@�̔j��
			g_pVtxBuffTitle[nCnt]->Release();
			g_pVtxBuffTitle[nCnt] = NULL;
		}
	}
}

//----------------------------------------
//  �^�C�g���̍X�V�ݒ菈��
//----------------------------------------
void UpdateTitle(void)
{
	//�e�L�X�g�̒��_
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle[1]->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		if (!bTitle)
		{//��񂾂��N��
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_TITLE_BUTTON);

			//���[�h�ݒ�(�Z���N�g��ʂɈڍs)
			SetFade(MODE_SELECT);

			bTitle = true;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle[1]->Unlock();
}

//----------------------------------------
//  �^�C�g���̕`�揈��
//----------------------------------------
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffTitle[nCnt], 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCnt]);

		//�|���S���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

#include "rule.h"
#include "input.h"
#include "fade.h"
#include "select.h"

LPDIRECT3DTEXTURE9 g_pTextureRule[3] = {};				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRule = NULL;			//���_�o�b�t�@�ւ̃|�C���^

//----------------------------------------
//  �^�C�g���̏������ݒ菈��
//----------------------------------------
void InitRule(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\Rule_0.png",
		&g_pTextureRule[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\Rule_1.png",
		&g_pTextureRule[1]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\ball.png",
		&g_pTextureRule[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRule,
		NULL);

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffRule->Lock(0, 0, (void**)&pVtx, 0);

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

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRule->Unlock();
}

//----------------------------------------
//  �^�C�g���̏I������
//----------------------------------------
void UninitRule(void)
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureRule[nCnt] != NULL)
		{
			g_pTextureRule[nCnt]->Release();
			g_pTextureRule[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRule != NULL)
	{
		g_pVtxBuffRule->Release();
		g_pVtxBuffRule = NULL;
	}
}

//----------------------------------------
//  �^�C�g���̍X�V�ݒ菈��
//----------------------------------------
void UpdateRule(void)
{
	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		//���[�h�ݒ�(�Z���N�g��ʂɈڍs)
		SetFade(MODE_GAME);
	}

}

//----------------------------------------
//  �^�C�g���̕`�揈��
//----------------------------------------
void DrawRule(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	STAGE_No * pSelect;
	pSelect = GetSelect();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRule, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRule[*pSelect]);

	//�|���S���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
}

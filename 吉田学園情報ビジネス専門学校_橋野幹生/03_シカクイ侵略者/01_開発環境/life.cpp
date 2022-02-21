#include "life.h"
#include "main.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;
LPDIRECT3DTEXTURE9 g_pTextureLifeT = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLifeT = NULL;
D3DXVECTOR3 g_posLife[3];	//�^�C���̐�
D3DXVECTOR3 g_posLifeT;
int nLifeHP;

//----------------------------------------
//  �^�C���̏������ݒ菈��
//----------------------------------------
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number.png",
		&g_pTextureLife);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\Life.png",
		&g_pTextureLifeT);

	for (int nCnLifeT = 0; nCnLifeT < 3; nCnLifeT++)
	{
		g_posLife[nCnLifeT] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏���
	}
	g_posLifeT = D3DXVECTOR3(1050.0f, 530.0f, 0.0f);
	nLifeHP = 10;

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLifeT,
		NULL);

	VERTEX_2D * pVtx;	//���_���ւ̃|�C���^

						//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnLifeT = 0; nCnLifeT < 3; nCnLifeT++)
	{
		g_posLife[nCnLifeT] = D3DXVECTOR3(35.0f * nCnLifeT + 990.0f, 600.0f, 0.0f);
	}

	for (int nCnLifeT = 0; nCnLifeT < 3; nCnLifeT++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posLife[nCnLifeT].x - 20.0f, g_posLife[nCnLifeT].y - 25.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posLife[nCnLifeT].x + 20.0f, g_posLife[nCnLifeT].y - 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posLife[nCnLifeT].x - 20.0f, g_posLife[nCnLifeT].y + 25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posLife[nCnLifeT].x + 20.0f, g_posLife[nCnLifeT].y + 25.0f, 0.0f);

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

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLifeT->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posLifeT.x - 80.0f, g_posLifeT.y - 25.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posLifeT.x + 80.0f, g_posLifeT.y - 25.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posLifeT.x - 80.0f, g_posLifeT.y + 25.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posLifeT.x + 80.0f, g_posLifeT.y + 25.0f, 0.0f);

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
	g_pVtxBuffLifeT->Unlock();
}

//----------------------------------------
//�@�^�C���̏I������
//----------------------------------------
void UninitLife(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	if (g_pTextureLifeT != NULL)
	{
		g_pTextureLifeT->Release();
		g_pTextureLifeT = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}

	if (g_pVtxBuffLifeT != NULL)
	{
		g_pVtxBuffLifeT->Release();
		g_pVtxBuffLifeT = NULL;
	}
}

//----------------------------------------
//  �^�C���̍X�V����
//----------------------------------------
void UpdateLife(void)
{
	int aPosTexU[3];					//�e���̐������i�[

	aPosTexU[0] = nLifeHP % 1000 / 100;
	aPosTexU[1] = nLifeHP % 100 / 10;
	aPosTexU[2] = nLifeHP % 10;

	VERTEX_2D * pVtx;	//���_���ւ̃|�C���^

						//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLife = 0; nCntLife < 3; nCntLife++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntLife], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntLife] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntLife], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntLife] + 0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();
}

//----------------------------------------
//  �^�C���̕`�揈��
//----------------------------------------
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnLifeT = 0; nCnLifeT < 3; nCnLifeT++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureLife);

		//�|���S���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnLifeT * 4, 2);
	}

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLifeT, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureLifeT);

	//�|���S���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//----------------------------------------
//  �X�R�A�̐ݒ菈��
//----------------------------------------
void SetLife(int nLife)
{
	nLifeHP -= nLife;
}

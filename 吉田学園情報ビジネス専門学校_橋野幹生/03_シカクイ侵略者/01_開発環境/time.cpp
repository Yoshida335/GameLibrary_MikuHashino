#include "time.h"
#include "fade.h"
#include "enemy.h"
#include "input.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;
LPDIRECT3DTEXTURE9 g_pTextureTT = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTT = NULL;
D3DXVECTOR3 g_posTime[3];	//�^�C���̐�
D3DXVECTOR3 g_posTT;
int g_nTime;				//���݂̃^�C��
int g_nCntTime;				//�J�E���g�^�C��
TIME g_TimeState;
int g_nCnt;					//��񂾂��N������p

//----------------------------------------
//  �^�C���̏������ݒ菈��
//----------------------------------------
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number.png",
		&g_pTextureTime);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\TIME.png",
		&g_pTextureTT);

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		g_posTime[nCntT] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏���
	}
	g_posTT = D3DXVECTOR3(1050.0f, 100.0f, 0.0f);
	g_nTime = 60;					//�^�C���̏�����
	g_nCntTime = 60;
	g_TimeState = TIME_ON;
	g_nCnt = 0;

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTT,
		NULL);

	VERTEX_2D * pVtx;	//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		g_posTime[nCntT] = D3DXVECTOR3(35.0f * nCntT + 990.0f, 170.0f, 0.0f);
	}

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posTime[nCntT].x - 20.0f, g_posTime[nCntT].y - 25.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime[nCntT].x + 20.0f, g_posTime[nCntT].y - 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime[nCntT].x - 20.0f, g_posTime[nCntT].y + 25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime[nCntT].x + 20.0f, g_posTime[nCntT].y + 25.0f, 0.0f);

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
	g_pVtxBuffTime->Unlock();

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTT->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posTT.x - 80.0f, g_posTT.y - 25.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posTT.x + 80.0f, g_posTT.y - 25.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posTT.x - 80.0f, g_posTT.y + 25.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posTT.x + 80.0f, g_posTT.y + 25.0f, 0.0f);

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
	g_pVtxBuffTT->Unlock();
}

//----------------------------------------
//�@�^�C���̏I������
//----------------------------------------
void UninitTime(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	if (g_pTextureTT != NULL)
	{
		g_pTextureTT->Release();
		g_pTextureTT = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}

	if (g_pVtxBuffTT != NULL)
	{
		g_pVtxBuffTT->Release();
		g_pVtxBuffTT = NULL;
	}
}

//----------------------------------------
//  �^�C���̍X�V����
//----------------------------------------
void UpdateTime(void)
{
	int nTimePos[3];

	switch (g_TimeState)
	{
	case TIME_ON:
		if (g_nTime != 0)
		{//���݂̎��Ԃ��O����Ȃ�������
			g_nCntTime--;
		}

		if (g_nCntTime <= 0)
		{//�J�E���g�����O��������
			g_nTime--;

			g_nCntTime = 60;

			if (g_nTime == 55)
			{
				//�G�̐ݒ�
				SetEnemy(D3DXVECTOR3(100.0f, 130.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(300.0f,  50.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(500.0f, 130.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(700.0f,  50.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(900.0f, 130.0f, 0.0f), ENEMY_TYPE_000);
			}

			if (g_nTime == 45)
			{
				//�G�̐ݒ�
				SetEnemy(D3DXVECTOR3( 80.0f, 100.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(280.0f, 180.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(500.0f, 250.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(680.0f, 180.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(880.0f, 100.0f, 0.0f), ENEMY_TYPE_000);
			}

			if (g_nTime == 35)
			{
				//�G�̐ݒ�
				SetEnemy(D3DXVECTOR3( 60.0f, 80.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(300.0f, 180.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(400.0f, 180.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(500.0f, 180.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(600.0f, 180.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(700.0f, 180.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(900.0f, 80.0f, 0.0f), ENEMY_TYPE_000);
			}

			if (g_nTime == 25)
			{
				//�G�̐ݒ�
				SetEnemy(D3DXVECTOR3(100.0f, 130.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(300.0f, 50.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(500.0f, 130.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(700.0f, 50.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(900.0f, 130.0f, 0.0f), ENEMY_TYPE_000);
			}

			if (g_nTime == 15)
			{
				//�G�̐ݒ�
				SetEnemy(D3DXVECTOR3( 80.0f, 150.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(280.0f, 80.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(500.0f, 80.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(680.0f, 80.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(880.0f, 150.0f, 0.0f), ENEMY_TYPE_000);
			}
		}

		nTimePos[0] = g_nTime % 1000 / 100;
		nTimePos[1] = g_nTime % 100 / 10;
		nTimePos[2] = g_nTime % 10;


		VERTEX_2D * pVtx;	//���_���ւ̃|�C���^

		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntT = 0; nCntT < 3; nCntT++)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.1f * nTimePos[nCntT], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f * nTimePos[nCntT] + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * nTimePos[nCntT], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f * nTimePos[nCntT] + 0.1f, 1.0f);

			pVtx += 4;
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTime->Unlock();

		if (g_nTime <= 0)
		{
			g_TimeState = TIME_OFF;
		}

#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//���[�h�ݒ�(�Q�[����ʂɈڍs)
			SetFade(MODE_RESULT);
		}
#endif

		break;

	case TIME_OFF:
		if(g_nCnt == 0)
		{
			//���[�h�ݒ�(�Q�[����ʂɈڍs)
			SetFade(MODE_RESULT);

			g_nCnt = 1;
		}

		break;
	}

}//----------------------------------------
//  �^�C���̕`�揈��
//----------------------------------------
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTime);

		//�|���S���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntT * 4, 2);
	}

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTT, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTT);

	//�|���S���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

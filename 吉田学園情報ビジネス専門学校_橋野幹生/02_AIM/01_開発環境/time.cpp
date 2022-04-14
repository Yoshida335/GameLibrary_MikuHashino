//----------------------------------------
//	�^�C���̏���
//�@Author�F���슲��
//----------------------------------------
#include "time.h"
#include "fade.h"
#include "input.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;		//�^�C�}�[�̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureStartTime = NULL;	//�^�C�}�[�̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureStart = NULL;		//�X�^�[�g�̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStartTime = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStart = NULL;
D3DXVECTOR3 g_posTime[3];	//�^�C���̐�
START g_StartTime;			//�X�^�[�g�̃^�C��
START g_StartText;			//�X�^�[�g
int g_nTime;				//���݂̃^�C��
int g_nCntTime;				//�J�E���g�^�C��
TIMESTATE g_TimeState;
bool g_bTimer = 0;
int g_clearTime;
int g_nMaxTime;

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

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number_123.png",
		&g_pTextureStartTime);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\start.png",
		&g_pTextureStart);

	//�^�C�}�[�̏�����
	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		g_posTime[nCntT] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏���
	}
	g_nTime = 0;					//�^�C���̏�����
	g_nCntTime = 60;				//�t���[����
	g_TimeState.state = TIME_OFF;	//�^�C�}�[�̏��
	g_bTimer = false;	//��񂾂��N��
	g_clearTime = 0;	//�N���A�^�C���ۑ��p
	g_nMaxTime = 0;		//�^�C�}�[�̍ő�^�C�����ۑ��p

	//�X�^�[�g�J�E���g�_�E��
	g_StartTime.pos = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f);		//�ʒu�̏���
	g_StartTime.bUse = false;	//�g���Ă��邩�ǂ���
	g_StartTime.time = 2;		//�g�p����

	//�X�^�[�g����
	g_StartText.pos = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f);		//�ʒu�̏���
	g_StartText.bUse = false;	//�g���Ă��邩�ǂ���
	g_StartText.time = 1;		//�g�p����

	//���_�o�b�t�@�̐ݒ�
	//�^�C�}�[
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);
	//�X�^�[�g�J�E���g�_�E��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStartTime,
		NULL);
	//�X�^�[�g����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStart,
		NULL);

	VERTEX_2D * pVtx;	//���_���ւ̃|�C���^

	{//�^�C�}�[
		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntT = 0; nCntT < 3; nCntT++)
		{
			g_posTime[nCntT] = D3DXVECTOR3(35.0f * nCntT + (SCREEN_WIDTH / 2) - 35.0f, TIME_HEIGHT, 0.0f);
		}

		for (int nCntT = 0; nCntT < 3; nCntT++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posTime[nCntT].x - TIME_WIDTH, g_posTime[nCntT].y - TIME_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posTime[nCntT].x + TIME_WIDTH, g_posTime[nCntT].y - TIME_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posTime[nCntT].x - TIME_WIDTH, g_posTime[nCntT].y + TIME_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posTime[nCntT].x + TIME_WIDTH, g_posTime[nCntT].y + TIME_HEIGHT, 0.0f);

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
	}

	{//�X�^�[�g�J�E���g�_�E��
		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffStartTime->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_StartTime.pos.x - STARTTIME_WIDTH, g_StartTime.pos.y - STARTTIME_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_StartTime.pos.x + STARTTIME_WIDTH, g_StartTime.pos.y - STARTTIME_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_StartTime.pos.x - STARTTIME_WIDTH, g_StartTime.pos.y + STARTTIME_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_StartTime.pos.x + STARTTIME_WIDTH, g_StartTime.pos.y + STARTTIME_HEIGHT, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2((1.0f / 3.0f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((1.0f / 3.0f), 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffStartTime->Unlock();
	}

	{//�X�^�[�g����
		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffStart->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_StartText.pos.x - 300.0f, g_StartText.pos.y - STARTTIME_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_StartText.pos.x + 300.0f, g_StartText.pos.y - STARTTIME_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_StartText.pos.x - 300.0f, g_StartText.pos.y + STARTTIME_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_StartText.pos.x + 300.0f, g_StartText.pos.y + STARTTIME_HEIGHT, 0.0f);

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
		g_pVtxBuffStart->Unlock();
	}
}

//----------------------------------------
//�@�^�C���̏I������
//----------------------------------------
void UninitTime(void)
{
	if (g_pTextureTime != NULL)
	{//�e�N�X�`���̔j��
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	if (g_pTextureStartTime != NULL)
	{//�e�N�X�`���̔j��
		g_pTextureStartTime->Release();
		g_pTextureStartTime = NULL;
	}

	if (g_pTextureStart != NULL)
	{//�e�N�X�`���̔j��
		g_pTextureStart->Release();
		g_pTextureStart = NULL;
	}

	if (g_pVtxBuffTime != NULL)
	{//���_�o�b�t�@�̔j��
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}

	if (g_pVtxBuffStartTime != NULL)
	{//���_�o�b�t�@�̔j��
		g_pVtxBuffStartTime->Release();
		g_pVtxBuffStartTime = NULL;
	}
}

//----------------------------------------
//  �^�C���̍X�V����
//----------------------------------------
void UpdateTime(void)
{
	int nTimePos[3];
	int nStartTimePos;

	VERTEX_2D * pVtx;	//���_���ւ̃|�C���^

	switch (g_TimeState.state)
	{
	case TIME_ON:
		if (g_nTime != 0)
		{//���݂̎��Ԃ��O����Ȃ�������
			g_nCntTime--;
		}
		else if (g_nTime <= 0)
		{
			if (!g_bTimer)
			{
				ClearTime();

				//���[�h�ݒ�(�Q�[����ʂɈڍs)
				SetFade(MODE_RESULT_OVER);

				g_bTimer = true;
			}
		}
		if (g_nCntTime <= 0)
		{//�J�E���g�����O��������
			g_nTime--;
			g_nCntTime = 60;
			g_clearTime++;
		}

		nTimePos[0] = g_nTime % 1000 / 100;
		nTimePos[1] = g_nTime % 100 / 10;
		nTimePos[2] = g_nTime % 10;

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

#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//���[�h�ݒ�(�Q�[����ʂɈڍs)
			SetFade(MODE_RESULT_OVER);
		}
#endif
		break;

	case TIME_OFF:
		g_StartTime.bUse = true;

		if (g_StartTime.time >= 0)
		{//���݂̎��Ԃ��O����Ȃ�������
			g_nCntTime--;

			nStartTimePos = g_StartTime.time % 10;

			//���_�������b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffStartTime->Lock(0, 0, (void**)&pVtx, 0);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2((1.0f / 3.0f) * nStartTimePos, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((1.0f / 3.0f) * nStartTimePos + (1.0f / 3.0f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2((1.0f / 3.0f) * nStartTimePos, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((1.0f / 3.0f) * nStartTimePos + (1.0f / 3.0f), 1.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffStartTime->Unlock();
		}
		else
		{
			g_StartTime.bUse = false;
			g_TimeState.state = TIME_START;
		}
		if (g_nCntTime <= 0)
		{//�J�E���g�����O��������

			g_StartTime.time--;
			g_nCntTime = 60;
		}

		break;

	case TIME_START:
		g_StartText.bUse = true;

		if (g_StartText.time != 0)
		{//���݂̎��Ԃ��O����Ȃ�������
			g_nCntTime--;
		}
		else if (g_StartText.time <= 0)
		{
			g_StartText.bUse = false;
			g_TimeState.state = TIME_ON;
		}

		if (g_nCntTime <= 0)
		{//�J�E���g�����O��������
			g_StartText.time--;
			g_nCntTime = 60;
		}
		break;
	}
}

//----------------------------------------
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

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	//�|���S���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTime);

		//�|���S���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntT * 4, 2);
	}


	if (g_StartTime.bUse == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffStartTime, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureStartTime);

		//�|���S���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	if (g_StartText.bUse == true)
	{//�g�p����Ă�����
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffStart, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureStart);

		//�|���S���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//----------------------------------------
//	�^�C�}�[�̐ݒ�
//----------------------------------------
void SetTime(int nTime)
{
	g_nTime = nTime;
	g_nMaxTime = nTime;
}

//----------------------------------------
//	�^�C�}�[�̏�ԏ��
//----------------------------------------
TIMESTATE * GetStartTime(void)
{
	return &g_TimeState;
}

//----------------------------------------
//	�^�C�}�[�̎��Ԃ̏��
//----------------------------------------
int * GetTime(void)
{
	return &g_clearTime;
}

//----------------------------------------
//	�N���A�����Ƃ��̃^�C�}�[�̏���
//----------------------------------------
void ClearTime(void)
{
	g_clearTime = (g_nMaxTime - g_clearTime);
}
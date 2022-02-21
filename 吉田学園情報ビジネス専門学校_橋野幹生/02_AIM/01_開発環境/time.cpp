#include "time.h"
#include "fade.h"
#include "input.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;			//�^�C�}�[�̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureStartTime = NULL;			//�^�C�}�[�̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureStart = NULL;		//�X�^�[�g�̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStartTime = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStart = NULL;
D3DXVECTOR3 g_posTime[3];	//�^�C���̐�
START g_StartTime;		//�X�^�[�g�̃^�C��
START g_StartText;			//�X�^�[�g
int g_nTime;				//���݂̃^�C��
int g_nCntTime;				//�J�E���g�^�C��
STARTTIME g_TimeState;
int g_nCnt = 0;
int clearTime;
int g_nSetTime;

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

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		g_posTime[nCntT] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏���
	}
	g_nTime = 0;					//�^�C���̏�����
	g_nCntTime = 60;
	g_TimeState.state = TIME_OFF;
	g_nCnt = 0;
	clearTime = 0;
	g_nSetTime = 0;

	g_StartTime.pos = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f);		//�ʒu�̏���
	g_StartTime.bUse = false;
	g_StartTime.time = 2;

	g_StartText.pos = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f);		//�ʒu�̏���
	g_StartText.bUse = false;
	g_StartText.time = 1;

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStartTime,
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStart,
		NULL);

	VERTEX_2D * pVtx;	//���_���ւ̃|�C���^

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

	if (g_pTextureStartTime != NULL)
	{
		g_pTextureStartTime->Release();
		g_pTextureStartTime = NULL;
	}

	if (g_pTextureStart != NULL)
	{
		g_pTextureStart->Release();
		g_pTextureStart = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}

	if (g_pVtxBuffStartTime != NULL)
	{
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
			if (g_nCnt == 0)
			{
				ClearTime();

				//���[�h�ݒ�(�Q�[����ʂɈڍs)
				SetFade(MODE_RESULT);

				g_nCnt = 1;
			}
		}
		if (g_nCntTime <= 0)
		{//�J�E���g�����O��������
			g_nTime--;
			g_nCntTime = 60;
			clearTime++;
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
			SetFade(MODE_RESULT);
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
	{
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

void SetTime(int nTime)
{
	g_nTime = nTime;
	g_nSetTime = nTime;
}

STARTTIME * GetStartTime(void)
{
	return &g_TimeState;
}

int * GetTime(void)
{
	return &clearTime;
}

void ClearTime(void)
{
	clearTime = (g_nSetTime - clearTime);
}
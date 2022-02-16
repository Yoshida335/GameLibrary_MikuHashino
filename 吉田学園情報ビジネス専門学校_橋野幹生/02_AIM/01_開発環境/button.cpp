#include "button.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureButton = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffButton = NULL;
BUTTON g_Button[MAX_BUTTON];
int g_nCntLife;

//----------------------------------------
//�@�{�^���̏���������
//----------------------------------------
void InitButton(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntButton;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block000.jpg",
		&g_pTextureButton);

	//�e�̏�����
	for (nCntButton = 0; nCntButton < MAX_BUTTON; nCntButton++)
	{
		g_Button[nCntButton].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���݂̈ʒu
		g_Button[nCntButton].fWidth = BUTTON_WIDTH;						//��
		g_Button[nCntButton].fHeight = BUTTON_HEIGHT;					//����
		g_Button[nCntButton].bUse = false;								//�g���Ă��邩�ǂ���
		g_Button[nCntButton].state = BUTTON_STATE_OFF;					//���
		g_Button[nCntButton].nLife = 10;								//����
	}

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BUTTON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffButton,
		NULL);

	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffButton->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntButton = 0; nCntButton < MAX_BUTTON; nCntButton++)
	{
		//���_���W�X�V
		pVtx[0].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x - (BUTTON_WIDTH / 2), g_Button[nCntButton].pos.y - BUTTON_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x + (BUTTON_WIDTH / 2), g_Button[nCntButton].pos.y - BUTTON_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x - (BUTTON_WIDTH / 2), g_Button[nCntButton].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x + (BUTTON_WIDTH / 2), g_Button[nCntButton].pos.y, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhm = 1.0f;
		pVtx[1].rhm = 1.0f;
		pVtx[2].rhm = 1.0f;
		pVtx[3].rhm = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffButton->Unlock();
}

//----------------------------------------
//�@�{�^���̏I������
//----------------------------------------
void UninitButton(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureButton != NULL)
	{
		g_pTextureButton->Release();
		g_pTextureButton = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffButton != NULL)
	{
		g_pVtxBuffButton->Release();
		g_pVtxBuffButton = NULL;
	}
}

//----------------------------------------
//�@�{�^���̍X�V����
//----------------------------------------
void UpdateButton(void)
{
	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffButton->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntButton = 0; nCntButton < MAX_BUTTON; nCntButton++)
	{
		if (g_Button[nCntButton].bUse == true)
		{//�g�p����Ă���ꍇ
			switch (g_Button[nCntButton].state)
			{
			case BUTTON_STATE_OFF:
				g_Button[nCntButton].fHeight = BUTTON_HEIGHT;
				g_Button[nCntButton].nLife = BUTTON_LIFE;
				break;

			case BUTTON_STATE_ON:
				if (g_Button[nCntButton].nLife != 0)
				{//���݂̎��Ԃ��O����Ȃ�������
					g_nCntLife--;
				}
				else if(g_Button[nCntButton].nLife <= 0)
				{
					g_Button[nCntButton].state = BUTTON_STATE_OFF;
				}
				if (g_nCntLife <= 0)
				{//�J�E���g�����O��������
					g_Button[nCntButton].nLife--;

					g_nCntLife = 60;
				}

				g_Button[nCntButton].fHeight = BUTTON_HEIGHT - 20.0f;
				break;
			}

			pVtx[0].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x - (g_Button[nCntButton].fWidth / 2), g_Button[nCntButton].pos.y - g_Button[nCntButton].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x + (g_Button[nCntButton].fWidth / 2), g_Button[nCntButton].pos.y - g_Button[nCntButton].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x - (g_Button[nCntButton].fWidth / 2), g_Button[nCntButton].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x + (g_Button[nCntButton].fWidth / 2), g_Button[nCntButton].pos.y, 0.0f);

		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffButton->Unlock();
}

//----------------------------------------
//�@�{�^���̕`�揈��
//----------------------------------------
void DrawButton(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntButton;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffButton, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	for (nCntButton = 0; nCntButton < MAX_BUTTON; nCntButton++)
	{
		if (g_Button[nCntButton].bUse == true)
		{//�u���b�N���g�p����Ă���
		 //�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntButton * 4,
				2);
		}
	}
}

//----------------------------------------
//�@�{�^���̐ݒ�
//----------------------------------------
void SetButton(D3DXVECTOR3 pos, float fWidth, float fHeight, int life)
{
	int nCntButton;

	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffButton->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntButton = 0; nCntButton < MAX_BUTTON; nCntButton++)
	{
		if (g_Button[nCntButton].bUse == false)
		{//�g�p����Ă��Ȃ��ꍇ
			g_Button[nCntButton].pos = pos;
			g_Button[nCntButton].fWidth = fWidth;
			g_Button[nCntButton].fHeight = fHeight;
			g_Button[nCntButton].state = BUTTON_STATE_OFF;
			g_Button[nCntButton].bUse = true;
			g_Button[nCntButton].nLife = life;

			pVtx[0].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x - (g_Button[nCntButton].fWidth / 2), g_Button[nCntButton].pos.y - g_Button[nCntButton].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x + (g_Button[nCntButton].fWidth / 2), g_Button[nCntButton].pos.y - g_Button[nCntButton].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x - (g_Button[nCntButton].fWidth / 2), g_Button[nCntButton].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x + (g_Button[nCntButton].fWidth / 2), g_Button[nCntButton].pos.y, 0.0f);
			break;
		}

		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffButton->Unlock();
}

//----------------------------------------
//�@�{�^���̓����蔻��
//----------------------------------------
bool CollisionButton(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight)
{
	int nCntButton;
	bool bIsLanding = false;		//���n���Ă��邩�ǂ���

	for (nCntButton = 0; nCntButton < MAX_BUTTON; nCntButton++)
	{
		if (g_Button[nCntButton].bUse == true)
		{//�g�p����Ă��鎞
			if (pPosOld->x - (fWidth / 2) < g_Button[nCntButton].pos.x + (g_Button[nCntButton].fWidth / 2)
				&& pPosOld->x + (fWidth / 2) > g_Button[nCntButton].pos.x - (g_Button[nCntButton].fWidth / 2))
			{//�v���C���[��x���W���u���b�N�ɏd�Ȃ��Ă��鎞
				if (pPosOld->y <= g_Button[nCntButton].pos.y - g_Button[nCntButton].fHeight
					&& pPos->y >= g_Button[nCntButton].pos.y - g_Button[nCntButton].fHeight)
				{//�u���b�N�ɂ߂荞�񂾎�(�㑤����)
					bIsLanding = true;
					pPos->y = g_Button[nCntButton].pos.y - g_Button[nCntButton].fHeight;
					pMove->y = 0.0f;

					if (g_Button[nCntButton].state == BUTTON_STATE_OFF)
					{//OFF��Ԃ̎�
						g_Button[nCntButton].state = BUTTON_STATE_ON;
					}
				}
				else if (pPosOld->y - fHeight >= g_Button[nCntButton].pos.y
					&& pPos->y - fHeight <= g_Button[nCntButton].pos.y)
				{//�u���b�N�ɂ߂荞�񂾎�(��������)
					pPos->y = g_Button[nCntButton].pos.y + fHeight;
					pMove->y = 0.0f;
				}
			}
			if (pPos->y - fHeight <= g_Button[nCntButton].pos.y
				&& pPosOld->y > g_Button[nCntButton].pos.y - g_Button[nCntButton].fHeight)
			{//�v���C���[��y���W���u���b�N�ɏd�Ȃ��Ă��鎞
				if (pPosOld->x + (fWidth / 2) <= g_Button[nCntButton].pos.x - (g_Button[nCntButton].fWidth / 2)
					&& pPos->x + (fWidth / 2) >= g_Button[nCntButton].pos.x - (g_Button[nCntButton].fWidth / 2))
				{//�u���b�N�ɂ߂荞�񂾎�(��������)
					pPos->x = g_Button[nCntButton].pos.x - (g_Button[nCntButton].fWidth / 2) - (fWidth / 2);
					pMove->x = 0.0f;
				}
				else if (pPosOld->x - (fWidth / 2) >= g_Button[nCntButton].pos.x + (g_Button[nCntButton].fWidth / 2)
					&& pPos->x - (fWidth / 2) <= g_Button[nCntButton].pos.x + (g_Button[nCntButton].fWidth / 2))
				{//�u���b�N�ɂ߂荞�񂾎�(�E������)
					pPos->x = g_Button[nCntButton].pos.x + (g_Button[nCntButton].fWidth / 2) + (fWidth / 2);
					pMove->x = 0.0f;
				}
			}
		}
	}

	return bIsLanding;
}
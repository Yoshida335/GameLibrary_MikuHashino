//----------------------------------------
//�@�S�[���̏���
//�@Author�F���슲��
//----------------------------------------
#include "goal.h"
#include "fade.h"
#include "block.h"
#include "sound.h"
#include "time.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureGoal = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Goal g_Goal[MAX_GOAL];
bool g_bGoal = false;

//----------------------------------------
//�@�S�[���̏���������
//----------------------------------------
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	g_bGoal = false;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\door.png",
		&g_pTextureGoal);

	//�A�C�e���̏�����
	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		g_Goal[nCntGoal].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
		g_Goal[nCntGoal].fWidth = GOAL_WIDTH;			//��
		g_Goal[nCntGoal].fHeight = GOAL_HEIGHT;			//����
		g_Goal[nCntGoal].state = GOAL_STATE_CLAUSE;		//���
		g_Goal[nCntGoal].bUse = false;		//�g���Ă��邩�ǂ���
	}

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_GOAL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGoal,
		NULL);

	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		//���_���W�X�V
		pVtx[0].pos = D3DXVECTOR3(g_Goal[nCntGoal].pos.x - (GOAL_WIDTH / 2), g_Goal[nCntGoal].pos.y - GOAL_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Goal[nCntGoal].pos.x + (GOAL_WIDTH / 2), g_Goal[nCntGoal].pos.y - GOAL_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Goal[nCntGoal].pos.x - (GOAL_WIDTH / 2), g_Goal[nCntGoal].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Goal[nCntGoal].pos.x + (GOAL_WIDTH / 2), g_Goal[nCntGoal].pos.y, 0.0f);

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

		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGoal->Unlock();
}

//----------------------------------------
//�@�S�[���̏I������
//----------------------------------------
void UninitGoal(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}
}

//----------------------------------------
//�@�S�[���̍X�V����
//----------------------------------------
void UpdateGoal(void)
{
	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		if (g_Goal[nCntGoal].bUse == true)
		{
			switch (g_Goal[nCntGoal].state)
			{
			case GOAL_STATE_CLAUSE:

				break;

			case GOAL_STATE_OPEN:
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

				break;
			}
		}

		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGoal->Unlock();
}

//----------------------------------------
//�@�S�[���̕`�揈��
//----------------------------------------
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntGoal;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		if (g_Goal[nCntGoal].bUse == true)
		{//�u���b�N���g�p����Ă���
		 //�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureGoal);

			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntGoal * 4,
				2);
		}
	}
}

//----------------------------------------
//�@�S�[���̐ݒ�
//----------------------------------------
void SetGoal(D3DXVECTOR3 pos)
{
	int nCntGoal;

	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		if (g_Goal[nCntGoal].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ��ꍇ
			g_Goal[nCntGoal].pos = pos;
			g_Goal[nCntGoal].bUse = true;

			//���_���W�X�V
			pVtx[0].pos = D3DXVECTOR3(g_Goal[nCntGoal].pos.x - (GOAL_WIDTH / 2), g_Goal[nCntGoal].pos.y - GOAL_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Goal[nCntGoal].pos.x + (GOAL_WIDTH / 2), g_Goal[nCntGoal].pos.y - GOAL_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Goal[nCntGoal].pos.x - (GOAL_WIDTH / 2), g_Goal[nCntGoal].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Goal[nCntGoal].pos.x + (GOAL_WIDTH / 2), g_Goal[nCntGoal].pos.y, 0.0f);

			break;
		}

		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGoal->Unlock();
}

//----------------------------------------
//�@�S�[���̓����蔻��
//----------------------------------------
void CollisionGoal(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, float fWidth, float fHeight, bool PlayerItem)
{
	int nCntGoal;

	for (nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		if (g_Goal[nCntGoal].bUse == true)
		{
			if (pos->y - fHeight <= g_Goal[nCntGoal].pos.y + (g_Goal[nCntGoal].fHeight / 2) &&
				pos->y >= g_Goal[nCntGoal].pos.y - (g_Goal[nCntGoal].fHeight / 2) &&
				posOld->y <= g_Goal[nCntGoal].pos.y + (g_Goal[nCntGoal].fHeight / 2))
			{
				if (pos->x + (fWidth / 2) >= g_Goal[nCntGoal].pos.x - (g_Goal[nCntGoal].fWidth / 2) &&
					pos->x - (fWidth / 2) <= g_Goal[nCntGoal].pos.x + (g_Goal[nCntGoal].fWidth / 2))
				{
					if (g_Goal[nCntGoal].state == GOAL_STATE_CLAUSE)
					{
						if (PlayerItem == true)
						{
							g_Goal[nCntGoal].state = GOAL_STATE_OPEN;
							 
							if (!g_bGoal)
							{
								//���[�h�ݒ�(�Q�[����ʂɈڍs)
								SetFade(MODE_RESULT_CLEAR);

								ClearTime();

								//�T�E���h�̍Đ�
								PlaySound(SOUND_LABEL_SE_DOOR);

								g_bGoal = true;
							}
						}
					}
				}
			}
		}
	}
}

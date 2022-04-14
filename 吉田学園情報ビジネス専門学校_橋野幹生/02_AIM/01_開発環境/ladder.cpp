//----------------------------------------
//�@��q�̏���
//�@Author�F���슲��
//----------------------------------------
#include "ladder.h"
#include "input.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureLadder = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLadder = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LADDER g_Ladder[MAX_LADDER];

//----------------------------------------------
//	��q�̏���������
//----------------------------------------------
void InitLadder(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntLadder;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\ladder.png",
		&g_pTextureLadder);

	//�A�C�e���̏�����
	for (nCntLadder = 0; nCntLadder < MAX_LADDER; nCntLadder++)
	{
		g_Ladder[nCntLadder].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
		g_Ladder[nCntLadder].fWidth = LADDER_WIDTH;		//��
		g_Ladder[nCntLadder].fHeight = LADDER_HEIGHT;	//����
		g_Ladder[nCntLadder].bUse = false;				//�g���Ă��邩�ǂ���
		g_Ladder[nCntLadder].type = LADDER_TYPE_0;		//���
	}

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LADDER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLadder,
		NULL);

	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLadder->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLadder = 0; nCntLadder < MAX_LADDER; nCntLadder++)
	{//�ő吔����
		//���_���W�X�V
		pVtx[0].pos = D3DXVECTOR3(g_Ladder[nCntLadder].pos.x - (LADDER_WIDTH / 2), g_Ladder[nCntLadder].pos.y - (LADDER_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Ladder[nCntLadder].pos.x + (LADDER_WIDTH / 2), g_Ladder[nCntLadder].pos.y - (LADDER_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Ladder[nCntLadder].pos.x - (LADDER_WIDTH / 2), g_Ladder[nCntLadder].pos.y + (LADDER_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Ladder[nCntLadder].pos.x + (LADDER_WIDTH / 2), g_Ladder[nCntLadder].pos.y + (LADDER_HEIGHT / 2), 0.0f);

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
	g_pVtxBuffLadder->Unlock();
}

//----------------------------------------
//�@��q�̏I������
//----------------------------------------
void UninitLadder(void)
{
	if (g_pTextureLadder != NULL)
	{//�e�N�X�`���̔j��
		g_pTextureLadder->Release();
		g_pTextureLadder = NULL;
	}

	if (g_pVtxBuffLadder != NULL)
	{//���_�o�b�t�@�̔j��
		g_pVtxBuffLadder->Release();
		g_pVtxBuffLadder = NULL;
	}
}

//----------------------------------------
//�@��q�̍X�V����
//----------------------------------------
void UpdateLadder(void)
{
	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLadder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLadder = 0; nCntLadder < MAX_LADDER; nCntLadder++)
	{//�ő吔����
		if (g_Ladder[nCntLadder].bUse == true)
		{//��q���g�p����Ă��鎞
			switch (g_Ladder[nCntLadder].type)
			{
			case LADDER_TYPE_0:
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);	//�F
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				break;

			case LADDER_TYPE_1:
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	//�ԐF
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				break;
			}
		}

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLadder->Unlock();
}

//----------------------------------------
//�@��q�̕`�揈��
//----------------------------------------
void DrawLadder(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLadder, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureLadder);

	for (int nCntLadder = 0; nCntLadder < MAX_LADDER; nCntLadder++)
	{//�ő吔����
		if (g_Ladder[nCntLadder].bUse == true)
		{//�u���b�N���g�p����Ă���
		 //�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntLadder * 4,
				2);
		}
	}
}

//----------------------------------------
//�@��q�̐ݒ�
//----------------------------------------
void SetLadder(D3DXVECTOR3 pos, float fWidth, float fHeight, LADDERTYPE type)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLadder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLadder = 0; nCntLadder < MAX_LADDER; nCntLadder++)
	{
		if (g_Ladder[nCntLadder].bUse == false)
		{
			g_Ladder[nCntLadder].pos = pos;			//�ʒu
			g_Ladder[nCntLadder].fWidth = fWidth;	//��
			g_Ladder[nCntLadder].fHeight = fHeight;	//����
			g_Ladder[nCntLadder].bUse = true;		//�g���Ă����Ԃɂ���
			g_Ladder[nCntLadder].type = type;		//���

			//���_���W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_Ladder[nCntLadder].pos.x - (g_Ladder[nCntLadder].fWidth / 2), g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Ladder[nCntLadder].pos.x + (g_Ladder[nCntLadder].fWidth / 2), g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Ladder[nCntLadder].pos.x - (g_Ladder[nCntLadder].fWidth / 2), g_Ladder[nCntLadder].pos.y + (g_Ladder[nCntLadder].fHeight / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Ladder[nCntLadder].pos.x + (g_Ladder[nCntLadder].fWidth / 2), g_Ladder[nCntLadder].pos.y + (g_Ladder[nCntLadder].fHeight / 2), 0.0f);

			break;
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLadder->Unlock();
}

//----------------------------------------
//�@��q�̓����蔻��
//----------------------------------------
bool CollisionLadder(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight)
{
	bool bIsCatching = false;

	for (int nCntLadder = 0; nCntLadder < MAX_LADDER; nCntLadder++)
	{
		if (g_Ladder[nCntLadder].bUse == true)
		{//��q���g�p����Ă��鎞
			if (g_Ladder[nCntLadder].pos.x - (g_Ladder[nCntLadder].fWidth / 2) <= pos->x &&
				g_Ladder[nCntLadder].pos.x + (g_Ladder[nCntLadder].fWidth / 2) >= pos->x)
			{
				switch (g_Ladder[nCntLadder].type)
				{
				case LADDER_TYPE_0:
					if (g_Ladder[nCntLadder].pos.y + (g_Ladder[nCntLadder].fHeight / 2) > pos->y - fHeight &&
						g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2) < pos->y)
					{//�o���͈�(���͈̔͂ɂ���Ƃ���q����邱�Ƃ��\)
						bIsCatching = true;
						pMove->y = 0.0f;

						if (posOld->y <= g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2)
							&& pos->y >= g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2))
						{//��q�ɂ߂荞�񂾎�(�㑤����)
							bIsCatching = true;

							if (!GetKeyboardPress(DIK_S))
							{
								pos->y = g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2);
								pMove->y = 0.0f;
							}
						}
					}
					break;

				case LADDER_TYPE_1:
					if (g_Ladder[nCntLadder].pos.y + (g_Ladder[nCntLadder].fHeight / 2) > pos->y - fHeight &&
						g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2) < pos->y)
					{//�o���͈�(���͈̔͂ɂ���Ƃ���q����邱�Ƃ��\)
						bIsCatching = true;
						pMove->y = 0.0f;

						if (posOld->y <= g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2)
							&& pos->y >= g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2))
						{//��q�ɂ߂荞�񂾎�(�㑤����)
							pos->y = g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2);
							pMove->y = 0.0f;
						}
					}
					break;

				default:
					break;
				}
			}
		}
	}

	return bIsCatching;
}

//----------------------------------------
//�@��q�̏��
//----------------------------------------
LADDER * GetLadder(void)
{
	return g_Ladder;
}
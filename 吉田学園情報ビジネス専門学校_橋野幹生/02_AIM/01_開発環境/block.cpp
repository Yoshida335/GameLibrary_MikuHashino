//----------------------------------------
//�@�u���b�N�̏���
//�@Author�F���슲��
//----------------------------------------
#include "block.h"
#include "player.h"
#include "input.h"
#include "item.h"
#include "stage.h"
#include "sound.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBlock[BLOCKTYPE_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;			//���_�o�b�t�@�ւ̃|�C���^
BLOCK g_Block[MAX_BLOCK];
float g_fLengthBlock;		//�Ίp���̒���
float g_fAngleBlock;		//�Ίp���̊p�x

//----------------------------------------
//�@�u���b�N�̏���������
//----------------------------------------
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block000.png",
		&g_pTextureBlock[BLOCKTYPE_NOMAL]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block001.png",
		&g_pTextureBlock[BLOCKTYPE_UP]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block_002.png",
		&g_pTextureBlock[BLOCKTYPE_ITEM]);

	//�u���b�N�̏�����
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_Block[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���݂̈ʒu
		g_Block[nCntBlock].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
		g_Block[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�p�x
		g_Block[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
		g_Block[nCntBlock].fWidth = 0.0f;							//��
		g_Block[nCntBlock].fHeight = 0.0f;							//����
		g_Block[nCntBlock].bUse = false;							//�g���Ă��邩
		g_Block[nCntBlock].type = BLOCKTYPE_NOMAL;					//���
		g_Block[nCntBlock].rot2 = 0.0f;								//�p�x
		g_Block[nCntBlock].flength = 0.0f;							//�΂ߒ���
		g_Block[nCntBlock].state = BLOCKSTATE_NOMAL;				//���
	}

	//�Ίp���̒����Z�o
	g_fLengthBlock = sqrtf(BLOCK_WIDTH * BLOCK_WIDTH + BLOCK_HEIGHT * BLOCK_HEIGHT) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	g_fAngleBlock = atan2f(BLOCK_WIDTH, BLOCK_HEIGHT);

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�X�V
		pVtx[0].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (-D3DX_PI + g_fAngleBlock)) * g_fLengthBlock;
		pVtx[0].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (-D3DX_PI + g_fAngleBlock)) * g_fLengthBlock;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (D3DX_PI - g_fAngleBlock)) * g_fLengthBlock;
		pVtx[1].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (D3DX_PI - g_fAngleBlock)) * g_fLengthBlock;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (0.0f - g_fAngleBlock)) * g_fLengthBlock;
		pVtx[2].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (0.0f - g_fAngleBlock)) * g_fLengthBlock;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (0.0f + g_fAngleBlock)) * g_fLengthBlock;
		pVtx[3].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (0.0f + g_fAngleBlock)) * g_fLengthBlock;
		pVtx[3].pos.z = 0.0f;

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
	g_pVtxBuffBlock->Unlock();
}

//----------------------------------------
//�@�u���b�N�̏I������
//----------------------------------------
void UninitBlock(void)
{
	for (int nCntTex = 0; nCntTex < BLOCKTYPE_MAX; nCntTex++)
	{
		if (g_pTextureBlock[nCntTex] != NULL)
		{//�e�N�X�`���̔j��
			g_pTextureBlock[nCntTex]->Release();
			g_pTextureBlock[nCntTex] = NULL;
		}
	}

	if (g_pVtxBuffBlock != NULL)
	{//���_�o�b�t�@�̔j��
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//----------------------------------------
//�@�u���b�N�̍X�V����
//----------------------------------------
void UpdateBlock(void)
{
	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�ő�u���b�N����
		if (g_Block[nCntBlock].bUse)
		{//�g�p����Ă�����
			g_Block[nCntBlock].posOld = g_Block[nCntBlock].pos;	//���݂̈ʒu��ۑ�

			switch (g_Block[nCntBlock].state)
			{
			case BLOCKSTATE_NOMAL:	//�m�[�}�����
				g_Block[nCntBlock].move.y = 0.0f;
				break;

			case BLOCKSTATE_UP:		//��������
				g_Block[nCntBlock].pos.y -= (BLOCK_WIDTH / 2);
				g_Block[nCntBlock].state = BLOCKSTATE_NOMAL;

				//�u���b�N���m�̓����蔻��
				CollisionBlock_B(&g_Block[nCntBlock].pos, &g_Block[nCntBlock].posOld, g_Block[nCntBlock].fWidth, g_Block[nCntBlock].fHeight);
				break;

			case BLOCKSTATE_ITEM:	//�A�C�e�����
				g_Block[nCntBlock].move.y = -1.0f;
				SetItem(D3DXVECTOR3(g_Block[nCntBlock].pos.x, g_Block[nCntBlock].pos.y - BLOCK_HEIGHT, g_Block[nCntBlock].pos.z), ITEM_COIN);

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

				g_Block[nCntBlock].state = BLOCKSTATE_NOMAL;
				break;
			}

			g_Block[nCntBlock].pos += g_Block[nCntBlock].move;

			//���_���W�X�V
			pVtx[0].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (-D3DX_PI + g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength;
			pVtx[0].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (-D3DX_PI + g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (D3DX_PI - g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength;
			pVtx[1].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (D3DX_PI - g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (0.0f - g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength;
			pVtx[2].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (0.0f - g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (0.0f + g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength;
			pVtx[3].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (0.0f + g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength;
			pVtx[3].pos.z = 0.0f;
		}

		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//----------------------------------------
//�@�u���b�N�̕`�揈��
//----------------------------------------
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�ő�u���b�N������
		if (g_Block[nCntBlock].bUse == true)
		{//�u���b�N���g�p����Ă���
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock[g_Block[nCntBlock].type]);

			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBlock * 4,
				2);
		}
	}
}

//----------------------------------------
//�@�u���b�N�̐ݒ�
//----------------------------------------
void SetBlock(D3DXVECTOR3 pos, BLOCKTYPE type, BLOCKSTATE state, float fWidth, float fHeight)
{
	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�ő�u���b�N������
		if (g_Block[nCntBlock].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ��ꍇ
			g_Block[nCntBlock].pos = pos;			//�ʒu
			g_Block[nCntBlock].type = type;			//���
			g_Block[nCntBlock].state = state;		//���
			g_Block[nCntBlock].bUse = true;			//�g�p���Ă����Ԃɂ���
			g_Block[nCntBlock].fWidth = fWidth;		//��
			g_Block[nCntBlock].fHeight = fHeight;	//����

			//�Ίp���̒����Z�o
			g_Block[nCntBlock].flength = sqrtf(fWidth * fWidth + fHeight * fHeight) / 2.0f;

			//�Ίp���̊p�x���Z�o����
			g_Block[nCntBlock].rot2 = atan2f(fWidth, fHeight);

			//���_���W�X�V
			pVtx[0].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (-D3DX_PI + g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength + g_Block[nCntBlock].move.x;
			pVtx[0].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (-D3DX_PI + g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength + g_Block[nCntBlock].move.y;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (D3DX_PI - g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength + g_Block[nCntBlock].move.x;
			pVtx[1].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (D3DX_PI - g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength + g_Block[nCntBlock].move.y;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (0.0f - g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength + g_Block[nCntBlock].move.x;
			pVtx[2].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (0.0f - g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength + g_Block[nCntBlock].move.y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (0.0f + g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength + g_Block[nCntBlock].move.x;
			pVtx[3].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (0.0f + g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength + g_Block[nCntBlock].move.y;
			pVtx[3].pos.z = 0.0f;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f * (g_Block[nCntBlock].fWidth / BLOCK_WIDTH), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f * (g_Block[nCntBlock].fHeight / BLOCK_HEIGHT));
			pVtx[3].tex = D3DXVECTOR2(1.0f * (g_Block[nCntBlock].fWidth / BLOCK_WIDTH), 1.0f * (g_Block[nCntBlock].fHeight / BLOCK_HEIGHT));

			break;
		}

		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//----------------------------------------
//�@�u���b�N�̓����蔻��(�v���C���[)
//----------------------------------------
bool CollisionBlock_P(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight)	// , BLOCK ** pblock
{
	int nCntBlock;
	bool bIsLanding = false;		//���n���Ă��邩�ǂ���

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{//�u���b�N���g�p����Ă��鎞
			if (pPosOld->x - (fWidth / 2) < g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2)
				&& pPosOld->x + (fWidth / 2) > g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2))
			{//�v���C���[��x���W���u���b�N�ɏd�Ȃ��Ă��鎞
				if (pPosOld->y <= g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2 + g_Block[nCntBlock].move.y)
					&& pPos->y >= g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2))
				{//�u���b�N�ɂ߂荞�񂾎�(�㑤����)
					bIsLanding = true;
					pPos->y = g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2);
					pMove->y = 0.0f;

					/*if (pblock != NULL)
					{
						*pblock = &g_Block[nCntBlock];
					}*/
				}
				else if (pPosOld->y - fHeight >= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2 - g_Block[nCntBlock].move.y)
					&& pPos->y - fHeight <= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2))
				{//�u���b�N�ɂ߂荞�񂾎�(��������)
					pPos->y = g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2) + fHeight;
					pMove->y = 0.0f;

					if (g_Block[nCntBlock].type == BLOCKTYPE_UP)
					{
						g_Block[nCntBlock].state = BLOCKSTATE_UP;
					}
					else if (g_Block[nCntBlock].type == BLOCKTYPE_ITEM)
					{
						g_Block[nCntBlock].state = BLOCKSTATE_ITEM;
					}
				}
			}
			if (pPos->y - fHeight <= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2)
					   && pPosOld->y > g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2))
			{//�v���C���[��y���W���u���b�N�ɏd�Ȃ��Ă��鎞
				if (pPosOld->x + (fWidth / 2) <= g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2 + g_Block[nCntBlock].move.x)
					&& pPos->x + (fWidth / 2) >= g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2))
				{//�u���b�N�ɂ߂荞�񂾎�(��������)
					pPos->x = g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2) - (fWidth / 2);
					pMove->x = 0.0f;

					/*if (pblock != NULL)
					{
						*pblock = &g_Block[nCntBlock];
					}*/
				}
				else if (pPosOld->x - (fWidth / 2) >= g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2 - g_Block[nCntBlock].move.x)
					&& pPos->x - (fWidth / 2) <= g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2))
				{//�u���b�N�ɂ߂荞�񂾎�(�E������)
					pPos->x = g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2) + (fWidth / 2);
					pMove->x = 0.0f;

					/*if (pblock != NULL)
					{
						*pblock = &g_Block[nCntBlock];
					}*/
				}
			}
		}
	}

	return bIsLanding;
}

//----------------------------------------
//�@�u���b�N�̓����蔻��
//----------------------------------------
void CollisionBlock_B(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, float fWidth, float fHeight)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{//�u���b�N���g�p����Ă��鎞
			{
				if (pPosOld->x - (fWidth / 2) < g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2)
					&& pPosOld->x + (fWidth / 2) > g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2))
				{
					if (pPosOld->y - (fHeight / 2.0f) >= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2)
						&& pPos->y - (fHeight / 2.0f) <= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2))
					{//�u���b�N�ɓ���������A�߂�
						pPos->y = g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2) + (fHeight / 2);
					}
				}
			}
		}
	}
}

//----------------------------------------
//�@�u���b�N�̏��
//----------------------------------------
BLOCK * GetBlock(void)
{
	return g_Block;
}

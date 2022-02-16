#include "block.h"
#include "player.h"
#include "input.h"
#include "item.h"
#include "stage.h"
#include "sound.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBlock[BLOCKTYPE_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;
BLOCK g_Block[MAX_BLOCK];
float g_fLengthBlock;				//�Ίp���̒���
float g_fAngleBlock;				//�Ίp���̊p�x

//----------------------------------------
//�@�u���b�N�̏���������
//----------------------------------------
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block000.jpg",
		&g_pTextureBlock[BLOCKTYPE_NOMAL]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block001.png",
		&g_pTextureBlock[BLOCKTYPE_UP]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block_002.png",
		&g_pTextureBlock[BLOCKTYPE_ITEM]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block000.jpg",
		&g_pTextureBlock[BLOCKTYPE_ACT]);

	//�u���b�N�̏�����
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_Block[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���݂̈ʒu
		g_Block[nCntBlock].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�O��̈ʒu
		g_Block[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�p�x
		g_Block[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
		g_Block[nCntBlock].fWidth = 0.0f;								//��
		g_Block[nCntBlock].fHeight = 0.0f;								//����
		g_Block[nCntBlock].bUse = false;								//�g���Ă��邩
		g_Block[nCntBlock].type = BLOCKTYPE_NOMAL;						//���
		g_Block[nCntBlock].rot2 = 0.0f;									//�p�x
		g_Block[nCntBlock].flength = 0.0f;								//�΂ߒ���
		g_Block[nCntBlock].state = BLOCKSTATE_NOMAL;					//���
		g_Block[nCntBlock].nLife = 0;									//����
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

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
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
	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < BLOCKTYPE_MAX; nCntTex++)
	{
		if (g_pTextureBlock[nCntTex] != NULL)
		{
			g_pTextureBlock[nCntTex]->Release();
			g_pTextureBlock[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBlock != NULL)
	{
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
	{
		if (g_Block[nCntBlock].bUse == true)
		{
			g_Block[nCntBlock].posOld = g_Block[nCntBlock].pos;

			ActBlock(&g_Block[nCntBlock].pos, g_Block[nCntBlock].fWidth, g_Block[nCntBlock].fHeight);

			if (ActBlock(&g_Block[nCntBlock].pos, g_Block[nCntBlock].fWidth, g_Block[nCntBlock].fHeight) != true
				&& BLOCKTYPE_ACT == g_Block[nCntBlock].type)
			{
				g_Block[nCntBlock].state = BLOCKSTATE_ACT;
			}

			switch (g_Block[nCntBlock].state)
			{
			case BLOCKSTATE_NOMAL:
				g_Block[nCntBlock].move.y = 0.0f;
				break;

			case BLOCKSTATE_UP:
				g_Block[nCntBlock].pos.y -= (BLOCK_WIDTH / 2);

				g_Block[nCntBlock].state = BLOCKSTATE_NOMAL;
				break;

			case BLOCKSTATE_MOVE:
				g_Block[nCntBlock].nLife -= 1;

				if (g_Block[nCntBlock].nLife >= 0)
				{
					g_Block[nCntBlock].move.y = BLOCK_MOVE;
				}
				else if (g_Block[nCntBlock].nLife >= -BLOCK_MOVE_LIFE)
				{
					g_Block[nCntBlock].move.y = -BLOCK_MOVE;
				}
				else if (g_Block[nCntBlock].nLife <= -BLOCK_MOVE_LIFE)
				{
					g_Block[nCntBlock].nLife = BLOCK_MOVE_LIFE;
				}

				break;

			case BLOCKSTATE_ITEM:
				g_Block[nCntBlock].move.y = -1.0f;

				SetItem(D3DXVECTOR3(g_Block[nCntBlock].pos.x, g_Block[nCntBlock].pos.y - BLOCK_HEIGHT, g_Block[nCntBlock].pos.z), ITEM_TYPE_0);

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

				g_Block[nCntBlock].state = BLOCKSTATE_NOMAL;
				break;

			case BLOCKSTATE_ACT:
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				break;

			case BLOCKSTATE_RL:
				//�d��
				g_Block[nCntBlock].move.y += 0.1f;

				CollisionBlock2(&g_Block[nCntBlock].pos, &g_Block[nCntBlock].posOld, &g_Block[nCntBlock].move, BLOCK_WIDTH, BLOCK_HEIGHT, g_Block[nCntBlock].state);

				if (g_Block[nCntBlock].pos.x - (BLOCK_WIDTH / 2) >= SCREEN_WIDTH)
				{//��ʊO(�E��)�ɏo����
					g_Block[nCntBlock].pos = D3DXVECTOR3(0.0f - PLAYER_WIDTH / 2, g_Block[nCntBlock].pos.y, 0.0f);
				}
				else if (g_Block[nCntBlock].pos.x + (BLOCK_WIDTH / 2) <= 0.0f)
				{//��ʊO(����)�ɏo����
					g_Block[nCntBlock].pos = D3DXVECTOR3(SCREEN_WIDTH + PLAYER_WIDTH / 2, g_Block[nCntBlock].pos.y, 0.0f);
				}

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

				break;
			}

			g_Block[nCntBlock].pos += g_Block[nCntBlock].move;

			//�u���b�N���m�̓����蔻��
			CollisionBlock2(&g_Block[nCntBlock].pos, &g_Block[nCntBlock].posOld, &g_Block[nCntBlock].move, g_Block[nCntBlock].fWidth, g_Block[nCntBlock].fHeight, g_Block[nCntBlock].state);
		}

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

		//��ʊO����
		if (g_Block[nCntBlock].pos.x + (BLOCK_WIDTH / 2) <= 0.0f ||
			g_Block[nCntBlock].pos.x - (BLOCK_WIDTH / 2) >= SCREEN_WIDTH ||
			g_Block[nCntBlock].pos.y + (BLOCK_HEIGHT / 2) <= 0.0f ||
			g_Block[nCntBlock].pos.y - (BLOCK_HEIGHT / 2) >= SCREEN_HEIGHT)
		{//��ʊO�ɏo����
			g_Block[nCntBlock].bUse = false;
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
	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
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
void SetBlock(D3DXVECTOR3 pos, BLOCKTYPE type, BLOCKSTATE state, float fWidth, float fHeight, int life)
{
	int nCntBlock;

	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ��ꍇ
			g_Block[nCntBlock].pos = pos;
			g_Block[nCntBlock].type = type;
			g_Block[nCntBlock].state = state;
			g_Block[nCntBlock].bUse = true;
			g_Block[nCntBlock].fWidth = fWidth;
			g_Block[nCntBlock].fHeight = fHeight;
			g_Block[nCntBlock].nLife = life;

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
bool CollisionBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight, BLOCK ** pblock)
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
					pPos->y = g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2);// -g_Block[nCntBlock].move.y;
					pMove->y = 0.0f;

					if (pblock != NULL)
					{
						*pblock = &g_Block[nCntBlock];
					}
				}
				else if (pPosOld->y - fHeight >= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2 - g_Block[nCntBlock].move.y)
					&& pPos->y - fHeight <= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2))
				{//�u���b�N�ɂ߂荞�񂾎�(��������)
					pPos->y = g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2) + fHeight;
					pMove->y = 0.0f;

					if (g_Block[nCntBlock].type == BLOCKTYPE_UP && g_Block[nCntBlock].nLife >= 0)
					{
						g_Block[nCntBlock].state = BLOCKSTATE_UP;
						g_Block[nCntBlock].nLife -= 1;
					}
					else if (g_Block[nCntBlock].type == BLOCKTYPE_ITEM && g_Block[nCntBlock].nLife != 0)
					{
						g_Block[nCntBlock].state = BLOCKSTATE_ITEM;
						g_Block[nCntBlock].nLife = 0;
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

					if (pblock != NULL)
					{
						*pblock = &g_Block[nCntBlock];
					}
				}
				else if (pPosOld->x - (fWidth / 2) >= g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2 - g_Block[nCntBlock].move.x)
					&& pPos->x - (fWidth / 2) <= g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2))
				{//�u���b�N�ɂ߂荞�񂾎�(�E������)
					pPos->x = g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2) + (fWidth / 2);
					pMove->x = 0.0f;

					if (pblock != NULL)
					{
						*pblock = &g_Block[nCntBlock];
					}
				}
			}
		}
	}

	return bIsLanding;
}

//----------------------------------------
//�@�u���b�N�̓����蔻��
//----------------------------------------
void CollisionBlock2(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight, BLOCKSTATE state)
{
	int nCntBlock;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{//�u���b�N���g�p����Ă��鎞
			if (BLOCKSTATE_UP == state)		//��BLOCKSTATE_ACT
			{
				if (pPosOld->y - (fHeight / 2) >= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2)
					&& pPos->y - (fHeight / 2) <= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2))
				{
					if (pPosOld->x - (fWidth / 2) < g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2)
						&& pPosOld->x + (fWidth / 2) > g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2))
					{//�u���b�N�ɂ߂荞�񂾎�(��������)
						pPos->y = g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2) + (fWidth / 2);
						pMove->y = 0.0f;
					}
				}
			}
			else if (BLOCKSTATE_RL == state)
			{
				if (pPosOld->x - (fWidth / 2) < g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2)
					&& pPosOld->x + (fWidth / 2) > g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2))
				{//�v���C���[��x���W���u���b�N�ɏd�Ȃ��Ă��鎞
					if (pPosOld->y + (fHeight / 2 - g_Block[nCntBlock].move.y) <= g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2 + g_Block[nCntBlock].move.y)
						&& pPos->y + (fHeight / 2) >= g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2))
					{//�u���b�N�ɂ߂荞�񂾎�(�㑤����)
						pPos->y = g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2) - (fHeight / 2);
						pMove->y = 0.0f;
					}
					else if (pPosOld->y - (fHeight / 2 + g_Block[nCntBlock].move.y) >= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2 - g_Block[nCntBlock].move.y)
						&& pPos->y - (fHeight / 2) <= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2))
					{//�u���b�N�ɂ߂荞�񂾎�(��������)
						pPos->y = g_Block[nCntBlock].pos.y + g_Block[nCntBlock].fHeight + (fHeight / 2);
						pMove->y = 0.0f;
					}
				}
				if (pPos->y - (fHeight / 2) <= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2)
					&& pPosOld->y + (fHeight / 2) >= g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2))
				{//�v���C���[��y���W���u���b�N�ɏd�Ȃ��Ă��鎞
					if (pPosOld->x + (fWidth / 2 - g_Block[nCntBlock].move.x) <= g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2 + g_Block[nCntBlock].move.x)
						&& pPos->x + (fWidth / 2) >= g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2))
					{//�u���b�N�ɂ߂荞�񂾎�(��������)
						pPos->x = g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2) - (fWidth / 2);
						pMove->x = 0.0f;
					}
					else if (pPosOld->x - (fWidth / 2 + g_Block[nCntBlock].move.x) >= g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2 - g_Block[nCntBlock].move.x)
						&& pPos->x - (fWidth / 2) <= g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2))
					{//�u���b�N�ɂ߂荞�񂾎�(�E������)
						pPos->x = g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2) + (fWidth / 2);
						pMove->x = 0.0f;
					}
				}
			}
		}
	}
}

//----------------------------------------
//�@�u���b�N�̏�m�F
//----------------------------------------
bool ActBlock(D3DXVECTOR3 * pos, float fWidth, float fHeight)
{
	bool bIsAct = false;
	int nCntBlock;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{
			if (pos->x - (fWidth / 2) < g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2)
				&& pos->x + (fWidth / 2) > g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2))
			{
				if (pos->y - (g_Block[nCntBlock].fHeight / 2) >= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2))
				{
					bIsAct = true;
				}
			}
		}
	}

	return bIsAct;
}

//----------------------------------------
//�@�u���b�N�̏��
//----------------------------------------
BLOCK * GetBlock(void)
{
	return g_Block;
}

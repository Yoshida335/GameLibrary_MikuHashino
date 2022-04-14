//----------------------------------------
//	�A�C�e���̏���
//�@Author�F���슲��
//----------------------------------------
#include "item.h"
#include "score.h"
#include "sound.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureItem[ITEM_TYPE_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;			//���_�o�b�t�@�ւ̃|�C���^
ITEM g_Item[MAX_ITEM];
int g_nCntCoin;		//�������R�C���̖���

//----------------------------------------
//�@�A�C�e���̏���������
//----------------------------------------
void InitItem(void)
{
	g_nCntCoin = 0;		// �l��������Ԃɂ���

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\coin000.png",
		&g_pTextureItem[ITEM_COIN]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\key001.png",
		&g_pTextureItem[ITEM_KEY]);

	//�A�C�e���̏�����
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_Item[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
		g_Item[nCntItem].fWidth = ITEM_WIDTH;	//��
		g_Item[nCntItem].fHeight = ITEM_HEIGHT;	//����
		g_Item[nCntItem].nCounterAnim = 0;		//�A�j���[�V�����J�E���^
		g_Item[nCntItem].nPatternAnim = 0;		//�A�j���[�V�����p�^�[��
		g_Item[nCntItem].type = ITEM_COIN;	//���
		g_Item[nCntItem].bUse = false;			//�g���Ă��邩�ǂ���
	}

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//���_���W�X�V
		pVtx[0].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y + (ITEM_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y + (ITEM_HEIGHT / 2), 0.0f);

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
	g_pVtxBuffItem->Unlock();
}

//----------------------------------------
//�@�A�C�e���̏I������
//----------------------------------------
void UninitItem(void)
{
	//�e�N�X�`���̔j��
	for (int i = 0; i < ITEM_TYPE_MAX; i++)
	{
		if (g_pTextureItem[i] != NULL)
		{
			g_pTextureItem[i]->Release();
			g_pTextureItem[i] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//----------------------------------------
//�@�A�C�e���̍X�V����
//----------------------------------------
void UpdateItem(void)
{
	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{
			switch (g_Item[nCntItem].type)
			{
			case ITEM_COIN:
				g_Item[nCntItem].nCounterAnim += 1;

				if ((g_Item[nCntItem].nCounterAnim % 15) == 0)
				{//��莞�Ԍo��
				 //�p�^�[��No.���X�V����
					g_Item[nCntItem].nPatternAnim = (g_Item[nCntItem].nPatternAnim + 1) % 4;
				}

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.25f * g_Item[nCntItem].nPatternAnim, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.25f * g_Item[nCntItem].nPatternAnim + 0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.25f * g_Item[nCntItem].nPatternAnim, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.25f * g_Item[nCntItem].nPatternAnim + 0.25f, 1.0f);
				break;

			case ITEM_KEY:
				break;

			default:
				break;
			}
		}
		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//----------------------------------------
//�@�A�C�e���̕`�揈��
//----------------------------------------
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntItem;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{//�u���b�N���g�p����Ă���
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItem[g_Item[nCntItem].type]);

			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntItem * 4,
				2);
		}
	}
}

//----------------------------------------
//�@�A�C�e���̐ݒ�
//----------------------------------------
void SetItem(D3DXVECTOR3 pos, ITEM_TYPE type)
{
	int nCntItem;

	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == false)
		{
			g_Item[nCntItem].pos = pos;
			g_Item[nCntItem].type = type;
			g_Item[nCntItem].bUse = true;

			//���_���W�X�V
			pVtx[0].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y + (ITEM_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y + (ITEM_HEIGHT / 2), 0.0f);

			switch (g_Item[nCntItem].type)
			{
			case ITEM_COIN:
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);
				break;

			case ITEM_KEY:
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
				break;
			}
			break;
		}

		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//----------------------------------------
//�@�A�C�e���̏��
//----------------------------------------
ITEM * GetItem(void)
{
	return g_Item;
}

//----------------------------------------
//�@�A�C�e���̓����蔻��
//----------------------------------------
void CollisionItem(D3DXVECTOR3 * pos, float fWidth, float fHeight, ITEM ** item)
{
	ITEM * pItem;
	pItem = GetItem();
	*item = NULL;

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (pItem->bUse == true)
		{
			if (pos->x + (fWidth / 2) >= pItem->pos.x - (pItem->fWidth / 2) &&
				pos->x - (fWidth / 2) <= pItem->pos.x + (pItem->fWidth / 2) &&
				pos->y - fHeight <= pItem->pos.y + (pItem->fHeight / 2) &&
				pos->y >= pItem->pos.y - (pItem->fHeight / 2))
			{//�A�C�e���ɓ���������
				DeleteItem(nCntItem);

				if (item != NULL)
				{
					*item = pItem;
				}
			}
		}
		pItem++;
	}
}

//----------------------------------------
//�@�A�C�e���̏���
//----------------------------------------
void DeleteItem(int nCntItem)
{
	//�A�C�e���̔�\��
	g_Item[nCntItem].bUse = false;

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_SE_COIN);

	if (g_Item[nCntItem].type ==ITEM_COIN)
	{
		g_nCntCoin++;
	}
}

//----------------------------------------
//�@�R�C���̖���
//----------------------------------------
int GetNumCoin(void)
{
	return g_nCntCoin;
}
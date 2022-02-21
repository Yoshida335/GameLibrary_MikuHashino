#include "enemy.h"
#include "explosion.h"
#include "score.h"
#include "player.h"
#include "stage.h"
#include "bullet.h"

//�}�N����`
#define NUM_ENEMY			(3)			//�G�̎��
#define ENEMY_SIZE			(40.0f)		//�G�̃T�C�Y
#define ENEMY_MOVE			(0.5f)		//�G�̑��x

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureEnemy[ENEMY_TYPE_MAX] = {};	//�e�N�X�`��(4����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;				//���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];									//�G�̏��
int g_BulletCnt, g_BulletCnt2;

//----------------------------------------
//�@�G�̏���������
//----------------------------------------
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block_000.png",
		&g_pTextureEnemy[ENEMY_TYPE_000]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block_001.png",
		&g_pTextureEnemy[ENEMY_TYPE_001]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block_002.png",
		&g_pTextureEnemy[ENEMY_TYPE_002]);

	//�G�̏�����
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = ENEMY_TYPE_000;
		g_aEnemy[nCntEnemy].nLife = 2;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	g_BulletCnt = 0;
	g_BulletCnt2 = 0;

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);

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
	g_pVtxBuffEnemy->Unlock();

}

//----------------------------------------
//�@�G�̏I������
//----------------------------------------
void UninitEnemy(void)
{
	int nCnt;

	for (nCnt = 0; nCnt < ENEMY_TYPE_MAX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureEnemy[nCnt] != NULL)
		{
			g_pTextureEnemy[nCnt]->Release();
			g_pTextureEnemy[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//----------------------------------------
//�@�G�̍X�V����
//----------------------------------------
void UpdateEnemy(void)
{
	int nCntEnemy;

	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G���g�p����Ă���
			g_aEnemy[nCntEnemy].move.y += ENEMY_MOVE;
			g_BulletCnt += 1;

			//if (g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].move.y >= SCREEN_HEIGHT - 80.0f - ENEMY_SIZE)
			//{
			//	SetExplosion(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].move.y, 0.0f), 255);
			//	g_aEnemy[nCntEnemy].bUse = false;
			//	g_aEnemy[nCntEnemy].move.y = 0.0f;
			//}

			//�G���e�o�����̎��s����̌���
			//if (g_BulletCnt >= 240)
			//{
			//	for (int nCnt = 0; nCnt < 3; nCnt++)
			//	{
			//		if (g_BulletCnt >= 100)
			//		{
			//			SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].move, 0.0f), D3DXVECTOR3(0.0f, 4.0f, 0.0f));
			//		}
			//		g_BulletCnt2 = 0;
			//	}
			//	g_BulletCnt = 0;
			//}

			//�X�e�[�W�̓����蔻��
			CollisionStage(g_aEnemy[nCntEnemy].pos, ENEMY_SIZE, g_aEnemy[nCntEnemy].move, &g_aEnemy[nCntEnemy].nLife);

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NOMAL:
				//���_���W�X�V
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE + g_aEnemy[nCntEnemy].move.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE + g_aEnemy[nCntEnemy].move.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE + g_aEnemy[nCntEnemy].move.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE + g_aEnemy[nCntEnemy].move.y, 0.0f);

				break;

			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;

					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}

				break;
			}
		}

		if (g_aEnemy[nCntEnemy].nLife <= 0)
		{
			g_aEnemy[nCntEnemy].move.y = 0.0f;

			g_aEnemy[nCntEnemy].bUse = false;
		}

		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//----------------------------------------
//�@�G�̕`�揈��
//----------------------------------------
void DrawEnemy(void)
{
	// �f�o�C�X�֌W
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();			//�f�o�C�X�̎擾

	int nCntEnemy;

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G���g�p����Ă���
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureEnemy[g_aEnemy[nCntEnemy].nType]);

		 //�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEnemy * 4,
				2);
		}
	}
}

//----------------------------------------
//�@�G�̐ݒ�
// ����
// [pos] �G�̈ʒu
// [nType] �G�̎��
//----------------------------------------
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE nType)
{
	int nCntEnemy;

	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//�G���g�p����Ă��Ȃ��ꍇ
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].nLife = 5;
			g_aEnemy[nCntEnemy].bUse = true;

			//���_���W�X�V
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE + g_aEnemy[nCntEnemy].move.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE + g_aEnemy[nCntEnemy].move.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE + g_aEnemy[nCntEnemy].move.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE + g_aEnemy[nCntEnemy].move.y, 0.0f);

			break;
		}

		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//----------------------------------------
//�@�G�̏��
//----------------------------------------
Enemy * GetEnemy(void)
{
	return g_aEnemy;
}

//----------------------------------------
//�@�G�̃q�b�g����
//----------------------------------------
void HitEnemy(int nCntEnemy, int nDamage)
{
  	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		SetExplosion(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].move.y, 0.0f), 255);

		AddScore(500);

		g_aEnemy[nCntEnemy].move.y = 0.0f;

		g_aEnemy[nCntEnemy].bUse = false;
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;

		VERTEX_2D * pVtx;

		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nCntEnemy * 4;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEnemy->Unlock();
	}
}

//----------------------------------------
//�@�u���b�N�̓����蔻��
//----------------------------------------
void CollisionBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pCol, D3DXVECTOR3 * pMove, float fWidth, float fHeight)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�u���b�N���g�p����Ă��鎞
				if (pCol->x - (fWidth / 2) < g_aEnemy[nCntEnemy].pos.x + (ENEMY_SIZE / 2)
					&& pCol->x + (fWidth / 2) > g_aEnemy[nCntEnemy].pos.x - (ENEMY_SIZE / 2))
				{//�v���C���[��x���W���u���b�N�ɏd�Ȃ��Ă��鎞
					if (pCol->y + (fHeight / 2 - g_aEnemy[nCntEnemy].move.y) <= g_aEnemy[nCntEnemy].pos.y - (ENEMY_SIZE / 2 + g_aEnemy[nCntEnemy].move.y)
						&& pPos->y + (fHeight / 2) >= g_aEnemy[nCntEnemy].pos.y - (ENEMY_SIZE / 2))
					{//�u���b�N�ɂ߂荞�񂾎�(�㑤����)
						pPos->y = g_aEnemy[nCntEnemy].pos.y - (ENEMY_SIZE / 2) - (fHeight / 2);
						pMove->y = 0.0f;
					}
					else if (pCol->y - (fHeight / 2 + g_aEnemy[nCntEnemy].move.y) >= g_aEnemy[nCntEnemy].pos.y + (ENEMY_SIZE / 2 - g_aEnemy[nCntEnemy].move.y)
						&& pPos->y - (fHeight / 2) <= g_aEnemy[nCntEnemy].pos.y + (ENEMY_SIZE / 2))
					{//�u���b�N�ɂ߂荞�񂾎�(��������)
						pPos->y = g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE + (fHeight / 2);
						pMove->y = 0.0f;
					}
				}
				if (pPos->y - (fHeight / 2) <= g_aEnemy[nCntEnemy].pos.y + (ENEMY_SIZE / 2)
					&& pCol->y + (fHeight / 2) >= g_aEnemy[nCntEnemy].pos.y - (ENEMY_SIZE / 2))
				{//�v���C���[��y���W���u���b�N�ɏd�Ȃ��Ă��鎞
					if (pCol->x + (fWidth / 2 - g_aEnemy[nCntEnemy].move.x) <= g_aEnemy[nCntEnemy].pos.x - (ENEMY_SIZE / 2 + g_aEnemy[nCntEnemy].move.x)
						&& pPos->x + (fWidth / 2) >= g_aEnemy[nCntEnemy].pos.x - (ENEMY_SIZE / 2))
					{//�u���b�N�ɂ߂荞�񂾎�(��������)
						pPos->x = g_aEnemy[nCntEnemy].pos.x - (ENEMY_SIZE / 2) - (fWidth / 2);
						pMove->x = 0.0f;
					}
					else if (pCol->x - (fWidth / 2 + g_aEnemy[nCntEnemy].move.x) >= g_aEnemy[nCntEnemy].pos.x + (ENEMY_SIZE / 2 - g_aEnemy[nCntEnemy].move.x)
						&& pPos->x - (fWidth / 2) <= g_aEnemy[nCntEnemy].pos.x + (ENEMY_SIZE / 2))
					{//�u���b�N�ɂ߂荞�񂾎�(�E������)
						pPos->x = g_aEnemy[nCntEnemy].pos.x + (ENEMY_SIZE / 2) + (fWidth / 2);
						pMove->x = 0.0f;
					
				}
			}
		}
	}
}

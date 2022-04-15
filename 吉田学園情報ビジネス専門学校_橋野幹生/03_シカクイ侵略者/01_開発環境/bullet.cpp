//----------------------------------------
//�@�e����
//�@Author�F���슲��
//----------------------------------------
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"

//�}�N����`
#define MAX_BULLET			(128)		//�e�̍ő吔
#define BULLET_SIZE			(20.0f)		//�e�̃T�C�Y
#define BULLET_WIDTH		(30.0f)		//�e�̕�
#define BULLET_HEIGHT		(30.0f)		//�e�̍���
#define BULLET_LIEF			(80)		//�e�̃��C�t
#define ENEMY_MOVE2			(0.5f)		//�G�̑��x

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//����
	int nLife;				//����
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Bullet;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;
Bullet g_aBullet[MAX_BULLET];		//�e�̏��
float g_fLengthBullet;				//�Ίp���̒���
float g_fAngleBullet;				//�Ίp���̊p�x
float g_MoveCnt;

//----------------------------------------
//�@�e�̏���������
//----------------------------------------
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\BULLET.png",
		&g_pTextureBullet);

	//�e�̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = BULLET_LIEF;
		g_aBullet[nCntBullet].bUse = false;
	}
	g_MoveCnt = 0;

	//�Ίp���̒����Z�o
	g_fLengthBullet = sqrtf(BULLET_WIDTH * BULLET_WIDTH + BULLET_HEIGHT * BULLET_HEIGHT) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	g_fAngleBullet = atan2f(BULLET_WIDTH, BULLET_HEIGHT);

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

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
	g_pVtxBuffBullet->Unlock();
}

//----------------------------------------
//�@�e�̏I������
//----------------------------------------
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//----------------------------------------
//�@�e�̍X�V����
//----------------------------------------
void UpdateBullet(void)
{
	int nCntBullet;

	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���
			Enemy * pEnemy;
			int nCntEnemy;

			//�G�̏��̎擾
			pEnemy = GetEnemy();

			for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				
				if (pEnemy->bUse == true)
				{//�G���g�p����Ă���
					if (g_MoveCnt != 0)
					{
						pEnemy->move.y += ENEMY_MOVE2;

						g_MoveCnt = 1;
					}
					g_MoveCnt = 0;

					if (g_aBullet[nCntBullet].pos.x - 10.0f >= pEnemy->pos.x - 50.0f &&
						g_aBullet[nCntBullet].pos.x + 10.0f <= pEnemy->pos.x + 50.0f &&
						g_aBullet[nCntBullet].pos.y - 10.0f >= pEnemy->pos.y - 50.0f + pEnemy->move.y &&
						g_aBullet[nCntBullet].pos.y + 10.0f <= pEnemy->pos.y + 50.0f + pEnemy->move.y)
					{//�G�ƒe����������
 						HitEnemy(nCntEnemy, 1);

						g_aBullet[nCntBullet].bUse = false;
					}
				}
			}

			//�ʒu���X�V
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;

			//���_���W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

			if (g_aBullet[nCntBullet].pos.y < 0)
			{//��ʂ̊O�ɏo����
				g_aBullet[nCntBullet].bUse = false;
			}

			g_aBullet[nCntBullet].nLife -= 1;			//�����̃J�E���g�_�E��

			if (g_aBullet[nCntBullet].nLife == 0)
			{//�������s����
				//�����̐ݒ�
				SetExplosion(g_aBullet[nCntBullet].pos, 255);

				g_aBullet[nCntBullet].bUse = false;
			}
		}

		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//----------------------------------------
//�@�e�̕`�揈��
//----------------------------------------
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBullet * 4,
				2);
		}
	}
}

//----------------------------------------
//�@�e�̐ݒ菈��
//----------------------------------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	int nCntBullet;

	VERTEX_2D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//�e���g�p����Ă��Ȃ��ꍇ
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = BULLET_LIEF;
			g_aBullet[nCntBullet].bUse = true;

			break;
		}

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}
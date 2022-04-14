//----------------------------------------
//	�����L���O�̏���
//�@Author�F���슲��
//----------------------------------------
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include <stdio.h>
#include <string.h>
#include "time.h"
#include "sound.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL;		//�����̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;	//�����̒��_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRank_Bg = NULL;		//�w�i�̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank_Bg = NULL;	//�w�i�̒��_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;			//���ʂ̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;		//���ʂ̒��_�o�b�t�@�ւ̃|�C���^
int g_aRankScore[MAX_RANK + 1];				//�����L���O�X�R�A���[�ő僉���L���O�� + �l������SCORE����镪]
D3DXVECTOR3 g_aRankpos[MAX_RANK][3];		//�����L���O�ʒu���
int g_nCntY;								//�ő僉���L���O�����񂷗p
D3DXVECTOR3 rankpos[MAX_RANK];
bool bRanking = false;

//----------------------------------------
//  �����L���O�̏������ݒ菈��
//----------------------------------------
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	bRanking = false;	// false�ɂ���

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number_white.png",	//����
		&g_pTextureRankScore);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\ranking.png",	//�w�i
		&g_pTextureRank_Bg);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\rank_number.png",	//����
		&g_pTextureRank);

	for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
	{
		for (int nCntRank = 0; nCntRank < 3; nCntRank++)
		{
			g_aRankpos[g_nCntY][nCntRank] = D3DXVECTOR3(580.0f + (70.0f * nCntRank), 180.0f + (120.0f * g_nCntY), 0.0f);		//�ʒu�̏���
		}
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3 * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank_Bg,
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
	{
		for (int nCntRank = 0; nCntRank < 3; nCntRank++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aRankpos[g_nCntY][nCntRank].x - 40.0f, g_aRankpos[g_nCntY][nCntRank].y - 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRankpos[g_nCntY][nCntRank].x + 40.0f, g_aRankpos[g_nCntY][nCntRank].y - 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRankpos[g_nCntY][nCntRank].x - 40.0f, g_aRankpos[g_nCntY][nCntRank].y + 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRankpos[g_nCntY][nCntRank].x + 40.0f, g_aRankpos[g_nCntY][nCntRank].y + 50.0f, 0.0f);

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
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankScore->Unlock();

	{
	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRank_Bg->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	g_pVtxBuffRank_Bg->Unlock();
	}

	for (int i = 0; i < MAX_RANK; i++)
	{
		rankpos[i] = D3DXVECTOR3(400.0f, 180.0f + (120.0f * i), 0.0f);
	}

	{
		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < MAX_RANK; i++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(rankpos[i].x - 70.0f, rankpos[i].y - 40.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(rankpos[i].x + 70.0f, rankpos[i].y - 40.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(rankpos[i].x - 70.0f, rankpos[i].y + 40.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(rankpos[i].x + 70.0f, rankpos[i].y + 40.0f, 0.0f);

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
			pVtx[0].tex = D3DXVECTOR2(0.0f, (1.0f / 5) * i);
			pVtx[1].tex = D3DXVECTOR2(1.0f, (1.0f / 5) * i);
			pVtx[2].tex = D3DXVECTOR2(0.0f, (1.0f / 5) * i + (1.0f / 5));
			pVtx[3].tex = D3DXVECTOR2(1.0f, (1.0f / 5) * i + (1.0f / 5));

			pVtx += 4;
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffRank->Unlock();
	}

	SetRanking();
}

//----------------------------------------
//  �����L���O�̏I������
//----------------------------------------
void UninitRanking(void)
{
	//�T�E���h�̒�~
	StopSound();

	if (g_pTextureRankScore != NULL)
	{//�e�N�X�`���̔j��
		g_pTextureRankScore->Release();
		g_pTextureRankScore = NULL;
	}

	if (g_pVtxBuffRankScore != NULL)
	{//���_�o�b�t�@�̔j��
		g_pVtxBuffRankScore->Release();
		g_pVtxBuffRankScore = NULL;
	}

	if (g_pTextureRank_Bg != NULL)
	{//�e�N�X�`���̔j��
		g_pTextureRank_Bg->Release();
		g_pTextureRank_Bg = NULL;
	}

	if (g_pVtxBuffRank_Bg != NULL)
	{//���_�o�b�t�@�̔j��
		g_pVtxBuffRank_Bg->Release();
		g_pVtxBuffRank_Bg = NULL;
	}

	if (g_pTextureRank != NULL)
	{//�e�N�X�`���̔j��
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	if (g_pVtxBuffRank != NULL)
	{//���_�o�b�t�@�̔j��
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}
}

//----------------------------------------
//�@�����L���O�̍X�V����
//----------------------------------------
void UpdateRanking(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (!bRanking)
		{
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_TITLE_BUTTON);

			//���[�h�ݒ�(�Q�[����ʂɈڍs)
			SetFade(MODE_TITLE);

			bRanking = true;
		}
	}
}

//----------------------------------------
//  �����L���O�̕`�揈��
//----------------------------------------
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank_Bg, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRank_Bg);

	//�|���S���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	int nCnt = 0;

	for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
	{
		for (int nCntRank = 0; nCntRank < 3; nCntRank++, nCnt++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRankScore);

			//�|���S���̐ݒ�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MAX_RANK; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRank);

		//�|���S���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}
}

//----------------------------------------
//  �����L���O�X�R�A���̏����ݒ�(�O������ǂݍ���)
//----------------------------------------
void ResetRanking(void)
{
	FILE *pFile;

	//�t�@�C�����J��
	pFile = fopen("data\\ranking.txt", "r");		//(�e�L�X�g�����w��, ���[�h���w��)

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
	 //�t�@�C������l��ǂݍ���
		for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
		{//�����L���O������
			fscanf(pFile, "%d\n", &g_aRankScore[g_nCntY]);
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("\n***�@�t�@�C�����J���܂���ł����@***\n");
	}
}

//----------------------------------------
//  �����L���O�̐ݒ�
//----------------------------------------
void SetRanking(void)
{
	int aPosTexU[MAX_RANK][3];		//�e���̐������i�[

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	int * nMyTime = GetTime();

	//�G�̏��̎擾
	g_aRankScore[5] = *nMyTime;

	int nData;
	int nCount[2];

	for (nCount[1] = 0; nCount[1] < 5; nCount[1]++)
	{
		for (nCount[0] = nCount[1] + 1; nCount[0] < 6; nCount[0]++)
		{
			if (g_aRankScore[nCount[0]] < g_aRankScore[nCount[1]])
			{
				nData = g_aRankScore[nCount[0]];
				g_aRankScore[nCount[0]] = g_aRankScore[nCount[1]];
				g_aRankScore[nCount[1]] = nData;
			}
		}
	}

	for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
	{
		for (int nCntRank = 0; nCntRank < 3; nCntRank++)
		{
			aPosTexU[g_nCntY][0] = g_aRankScore[g_nCntY] % 1000 / 100;
			aPosTexU[g_nCntY][1] = g_aRankScore[g_nCntY] % 100 / 10;
			aPosTexU[g_nCntY][2] = g_aRankScore[g_nCntY] % 10;
		}
	}

	for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
	{
		for (int nCntScore = 0; nCntScore < 3; nCntScore++)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[g_nCntY][nCntScore], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexU[g_nCntY][nCntScore] + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[g_nCntY][nCntScore], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexU[g_nCntY][nCntScore] + 0.1f, 1.0f);

			pVtx += 4;
		}
	}

	//�����L���O��Score��ۑ�
	SaveRanking();

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankScore->Unlock();
}

//----------------------------------------
//  �����L���O�̃X�R�A���O���ɕۑ�
//----------------------------------------
void SaveRanking(void)
{
	FILE *pFile;

	//�t�@�C�����J��
	pFile = fopen("data\\ranking.txt", "w");		//(�e�L�X�g�����w��, ���[�h���w��)

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
	 //�t�@�C���ɒl�������o��
		for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
		{
			fprintf(pFile, "%d\n", g_aRankScore[g_nCntY]);
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("\n***�@�t�@�C�����J���܂���ł����@***\n");
	}
}

//----------------------------------------
//�@���C���̏���
//�@Author�F���슲��
//----------------------------------------
#include "Line.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLine = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Line g_aLine[MAX_LINE];

//---------------------------------------------------
//	���C���̏�����
//---------------------------------------------------
void InitLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�擾

	//���C���̊e�l������
	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		g_aLine[nCntLine].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine[nCntLine].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine[nCntLine].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aLine[nCntLine].start =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine[nCntLine].finish = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine[nCntLine].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * MAX_LINE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLine,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 2;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffLine->Unlock();
}

//---------------------------------------------------
//	���C���̏I������
//---------------------------------------------------
void UninitLine(void)
{
	if (g_pVtxBuffLine != NULL)
	{
		g_pVtxBuffLine->Release();
		g_pVtxBuffLine = NULL;
	}
}

//---------------------------------------------------
//	���C���̍X�V����
//---------------------------------------------------
void UpdateLine(void)
{

}

//---------------------------------------------------
//	���C���̕`�揈��
//---------------------------------------------------
void DrawLine(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		if (g_aLine[nCntLine].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aLine[nCntLine].mtxWorld);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aLine[nCntLine].pos.x, g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z);
			D3DXMatrixMultiply(&g_aLine[nCntLine].mtxWorld, &g_aLine[nCntLine].mtxWorld, &mtxTrans);

			//���C�g�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aLine[nCntLine].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffLine, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_LINELIST,
				nCntLine * 2,
				1);

			//���C�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}
}

//---------------------------------------------------
//	���C���̐ݒ�
//---------------------------------------------------
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 finish, D3DXCOLOR col)
{
	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		if (g_aLine[nCntLine].bUse == false)
		{
			g_aLine[nCntLine].pos = pos;
			g_aLine[nCntLine].rot = rot;
			g_aLine[nCntLine].col = col;
			g_aLine[nCntLine].start = start;
			g_aLine[nCntLine].finish = finish;
			g_aLine[nCntLine].bUse = true;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(start.x, start.y, start.z);
			pVtx[1].pos = D3DXVECTOR3(finish.x, finish.y, finish.z);

			//���_�J���[
			pVtx[0].col = g_aLine[nCntLine].col;
			pVtx[1].col = g_aLine[nCntLine].col;

			break;
		}

		pVtx += 2;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffLine->Unlock();
}

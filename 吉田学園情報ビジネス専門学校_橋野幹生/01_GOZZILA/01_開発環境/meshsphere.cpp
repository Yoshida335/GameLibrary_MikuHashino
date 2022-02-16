//----------------------------------------
//�@���b�V��(���~)�̏���
//�@Author�F���슲��
//----------------------------------------
#include "meshsphere.h"

#define MESHSPHERE_X_BLOCK		(16)	// X���̃u���b�N��
#define MESHSPHERE_Z_BLOCK		(4)		// Z���̃u���b�N��

#define MESHSPHERE_VERTEX		((MESHSPHERE_X_BLOCK + 1) * (MESHSPHERE_Z_BLOCK + 1))									//���b�V���̒��_
#define MESHSPHERE_INDEX		((MESHSPHERE_X_BLOCK  + 1) * 2 * MESHSPHERE_Z_BLOCK + (MESHSPHERE_Z_BLOCK - 1) * 2)		//�C���f�b�N�X��
#define MESHSPHERE_PRIMITIVE	((MESHSPHERE_X_BLOCK * MESHSPHERE_Z_BLOCK * 2) + (MESHSPHERE_Z_BLOCK - 1) * 4)			//�|���S����

#define MESHSPHERE_SIZE			(1000.0f)

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshSphere = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshSphere = NULL;			//���b�V���t�B�[���h�̃e�N�X�`��
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshSphere = NULL;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMeshSphere;		//�ʒu
D3DXVECTOR3 g_rotMeshSphere;		//����
D3DXVECTOR3 g_Rot;					//����
D3DXMATRIX g_mtxWorldMeshSphere;	//���[���h�}�g���b�N�X

//---------------------------------------------------
//	�|���S���̏�����
//---------------------------------------------------
void InitMeshSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;			//�f�o�C�X�擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\sky000.jpg",
		&g_pTextureMeshSphere);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHSPHERE_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshSphere,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHSPHERE_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshSphere,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshSphere->Lock(0, 0, (void**)&pVtx, 0);

	int nCnt = 0;

	g_posMeshSphere = D3DXVECTOR3(0.0f, 20000.0f, 0.0f);
	g_rotMeshSphere = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_����ݒ�(���~)
	for (int nCnt_V = 0; nCnt_V < MESHSPHERE_Z_BLOCK + 1; nCnt_V++)
	{
		for (int nCnt_H = 0; nCnt_H < MESHSPHERE_X_BLOCK + 1; nCnt_H++, nCnt++)
		{
			//�p�x�v�Z
			g_Rot.y = ((D3DX_PI * 2) / MESHSPHERE_X_BLOCK) * nCnt_H;
			g_Rot.z = ((-D3DX_PI) / MESHSPHERE_Z_BLOCK) * nCnt_V;

			//�p�x�̐��K��
			if (g_Rot.y > D3DX_PI)
			{
				g_Rot.y -= D3DX_PI * 2;
			}
			else if (g_Rot.y < -D3DX_PI)
			{
				g_Rot.y += D3DX_PI * 2;
			}
			//�p�x�̐��K��
			if (g_Rot.z > D3DX_PI)
			{
				g_Rot.z -= D3DX_PI * 2;
			}
			else if (g_Rot.z < -D3DX_PI)
			{
				g_Rot.z += D3DX_PI * 2;
			}

			//���_���W�̐ݒ�
			pVtx[nCnt].pos.x = sinf(g_Rot.y) *  cosf(g_Rot.z) * MESHSPHERE_SIZE;			//(;��;)< �����99gg99gg >(;o;)< ����gg99gg99
			pVtx[nCnt].pos.y = sinf(g_Rot.z) * MESHSPHERE_SIZE;
			pVtx[nCnt].pos.z = cosf(g_Rot.y) * cosf(g_Rot.z) * MESHSPHERE_SIZE;

			//�e���_�̖@���̐ݒ�
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			//���K������(�傫��1�̃x�N�g���ɂ���)
			D3DXVec3Normalize(&pVtx[nCnt].nor, &pVtx[nCnt].nor);

			//���_�J���[
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[nCnt].tex = D3DXVECTOR2(1.0f - (1.0f / MESHSPHERE_X_BLOCK) * nCnt_H, 1.0f - (1.0f / MESHSPHERE_Z_BLOCK) * nCnt_V);
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshSphere->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD * pIdx;
	g_pIdxBuffMeshSphere->Lock(0, 0, (void**)&pIdx, 0);

	nCnt = 0;
	int nCntPlas = 0;

	//�C���f�b�N�X�̐ݒ�
	for (int nCnt_Z = 0; nCnt_Z < MESHSPHERE_Z_BLOCK; nCnt_Z++)
	{
		for (int nCnt_X = 0; nCnt_X < MESHSPHERE_X_BLOCK + 1; nCnt_X++, nCnt++)
		{
			pIdx[nCnt] = (MESHSPHERE_X_BLOCK + 1) + nCntPlas;
			pIdx[nCnt + 1] = nCntPlas;

			nCnt++;
			nCntPlas++;
		}

		if (nCnt_Z != (MESHSPHERE_Z_BLOCK - 1))
		{
			pIdx[nCnt] = nCntPlas - 1;
			pIdx[nCnt + 1] = nCntPlas + (MESHSPHERE_X_BLOCK + 1);

			nCnt += 2;
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshSphere->Unlock();

	g_rotMeshSphere = D3DXVECTOR3(D3DX_PI, 0.0f, 0.0f);
}

//---------------------------------------------------
//	�|���S���̏I������
//---------------------------------------------------
void UninitMeshSphere(void)
{
	//���_�o�b�t�@�j��
	if (g_pVtxBuffMeshSphere != NULL)
	{
		g_pVtxBuffMeshSphere->Release();
		g_pVtxBuffMeshSphere = NULL;
	}

	//�e�N�X�`���j��
	if (g_pTextureMeshSphere != NULL)
	{
		g_pTextureMeshSphere->Release();
		g_pTextureMeshSphere = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshSphere != NULL)
	{
		g_pIdxBuffMeshSphere->Release();
		g_pIdxBuffMeshSphere = NULL;
	}
}

//---------------------------------------------------
//	�|���S���̍X�V����
//---------------------------------------------------
void UpdateMeshSphere(void)
{

}

//---------------------------------------------------
//	�|���S���̕`�揈��
//---------------------------------------------------
void DrawMeshSphere(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshSphere);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotMeshSphere.y, g_rotMeshSphere.x, g_rotMeshSphere.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshSphere,
		&g_mtxWorldMeshSphere, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshSphere.x, g_posMeshSphere.y, g_posMeshSphere.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshSphere, &g_mtxWorldMeshSphere, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshSphere);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshSphere, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshSphere);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshSphere);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHSPHERE_VERTEX, 0, MESHSPHERE_PRIMITIVE);

	pDevice->SetTexture(0, NULL);
}


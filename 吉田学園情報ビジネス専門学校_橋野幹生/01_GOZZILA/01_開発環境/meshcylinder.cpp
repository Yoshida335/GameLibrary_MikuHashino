//----------------------------------------
//�@���b�V��(�~��)�̏���
//�@Author�F���슲��
//----------------------------------------
#include "meshcylinder.h"
#include "model.h"

#define MESHCYLINDER_X_BLOCK		(8)		// X���̃u���b�N��
#define MESHCYLINDER_Z_BLOCK		(4)		// Z���̃u���b�N��

#define MESHCYLINDER_WIDHT			(10.0f)		//��
#define MESHCYLINDER_HEIGHT			(20.0f)		//����

#define MESHCYLINDER_VERTEX			((MESHCYLINDER_X_BLOCK + 1) * (MESHCYLINDER_Z_BLOCK + 1))									//���b�V���̒��_
#define MESHCYLINDER_INDEX			((MESHCYLINDER_X_BLOCK  + 1) * 2 * MESHCYLINDER_Z_BLOCK + (MESHCYLINDER_Z_BLOCK - 1) * 2)	//�C���f�b�N�X��
#define MESHCYLINDER_PRIMITIVE		((MESHCYLINDER_X_BLOCK * MESHCYLINDER_Z_BLOCK * 2) + (MESHCYLINDER_Z_BLOCK - 1) * 4)		//�|���S����

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;			//���b�V���t�B�[���h�̃e�N�X�`��
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Cylinder g_Cylinder[MAX_CYLINDER];

//---------------------------------------------------
//	���b�V��(�~��)�̏�����
//---------------------------------------------------
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;			//�f�o�C�X�擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\Shock_wave_ring001.png",
		&g_pTextureMeshCylinder);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHCYLINDER_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHCYLINDER_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCylinder = 0; nCntCylinder < MAX_CYLINDER; nCntCylinder++)
	{
		//�ʒu�ݒ�
		g_Cylinder[nCntCylinder].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Cylinder[nCntCylinder].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Cylinder[nCntCylinder].bUse = false;
	}
	int nCnt = 0;

		//���_����ݒ�(�~��)
		for (int nCnt_V = 0; nCnt_V < MESHCYLINDER_Z_BLOCK + 1; nCnt_V++)
		{
			for (int nCnt_H = 0; nCnt_H < MESHCYLINDER_X_BLOCK + 1; nCnt_H++, nCnt++)
			{

				for (int nCntCylinder = 0; nCntCylinder < MAX_CYLINDER; nCntCylinder++)
				{
				//�p�x�v�Z
				g_Cylinder[nCntCylinder].rot.y = ((D3DX_PI * 2) / MESHCYLINDER_X_BLOCK) * (float)nCnt_H;

				//�p�x�̐��K��
				if (g_Cylinder[nCntCylinder].rot.y > D3DX_PI)
				{
					g_Cylinder[nCntCylinder].rot.y -= D3DX_PI * 2;
				}
				else if (g_Cylinder[nCntCylinder].rot.y < -D3DX_PI)
				{
					g_Cylinder[nCntCylinder].rot.y += D3DX_PI * 2;
				}

				//�������ς���Ă����̂�������������
				//float nDara1 = MESHCYLINDER_WIDHT * cosf(g_Cylinder[nCntCylinder].rot.y);
				//float nDara2 = MESHCYLINDER_WIDHT * sinf(g_Cylinder[nCntCylinder].rot.y);


				//���_���W�̐ݒ�
				pVtx[nCnt].pos.x = sinf(g_Cylinder[nCntCylinder].rot.y) * MESHCYLINDER_WIDHT;
				pVtx[nCnt].pos.y = (MESHCYLINDER_HEIGHT / MESHCYLINDER_Z_BLOCK) * nCnt_V;
				pVtx[nCnt].pos.z = cosf(g_Cylinder[nCntCylinder].rot.y) * MESHCYLINDER_WIDHT;

				//�e���_�̖@���̐ݒ�
				pVtx[nCnt].nor = D3DXVECTOR3(0.0f, g_Cylinder[nCntCylinder].rot.y, 0.0f);

				//���K������(�傫��1�̃x�N�g���ɂ���)
				D3DXVec3Normalize(&pVtx[nCnt].nor, &pVtx[nCnt].nor);

				//���_�J���[
				pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`�����W�̐ݒ�
				pVtx[nCnt].tex = D3DXVECTOR2(1.0f - (1.0f / MESHCYLINDER_X_BLOCK) * nCnt_H, 1.0f - (1.0f / MESHCYLINDER_Z_BLOCK) * nCnt_V);
			}
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshCylinder->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD * pIdx;
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	nCnt = 0;
	int nCntPlas = 0;

	//�C���f�b�N�X�̐ݒ�
	for (int nCnt_Z = 0; nCnt_Z < MESHCYLINDER_Z_BLOCK; nCnt_Z++)
	{
		for (int nCnt_X = 0; nCnt_X < MESHCYLINDER_X_BLOCK + 1; nCnt_X++, nCnt++)
		{
			pIdx[nCnt] = (MESHCYLINDER_X_BLOCK + 1) + nCntPlas;
			pIdx[nCnt + 1] = nCntPlas;

			nCnt++;
			nCntPlas++;
		}

		if (nCnt_Z != (MESHCYLINDER_Z_BLOCK - 1))
		{
			pIdx[nCnt] = nCntPlas - 1;
			pIdx[nCnt + 1] = nCntPlas + (MESHCYLINDER_X_BLOCK + 1);

			nCnt += 2;
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshCylinder->Unlock();
}

//---------------------------------------------------
//	���b�V��(�~��)�̏I������
//---------------------------------------------------
void UninitMeshCylinder(void)
{
	//���_�o�b�t�@�j��
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	//�e�N�X�`���j��
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}
//---------------------------------------------------
//	���b�V��(�~��)�̍X�V����
//---------------------------------------------------
void UpdateMeshCylinder(void)
{
	for (int nCntCylinder = 0; nCntCylinder < MAX_CYLINDER; nCntCylinder++)
	{
		if (g_Cylinder[nCntCylinder].bUse == true)
		{
			//g_aBullet[nCntBullet].pos.x -= sinf(g_aBullet[nCntBullet].rot.y) * 1.0f;
			//g_aBullet[nCntBullet].pos.z -= cosf(g_aBullet[nCntBullet].rot.y) * 1.0f;

			//g_Cylinder[nCntCylinder].pos.x = sinf(g_Cylinder[nCntCylinder].rot.y) * -10.0f;
			//g_Cylinder[nCntCylinder].pos.z = cosf(g_Cylinder[nCntCylinder].rot.y) * -10.0f;

			//CollisionAttack(&g_Cylinder[nCntCylinder].pos, &g_Cylinder[nCntCylinder].posOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f));

			//��]������
			//g_Cylinder[nCntCylinder].rot.y += 0.05f;

			//�p�x�̐��K��
			if (g_Cylinder[nCntCylinder].rot.y > D3DX_PI)
			{
				g_Cylinder[nCntCylinder].rot.y -= D3DX_PI * 2;
			}
			else if (g_Cylinder[nCntCylinder].rot.y < -D3DX_PI)
			{
				g_Cylinder[nCntCylinder].rot.y += D3DX_PI * 2;
			}
		}
	}
}

//---------------------------------------------------
//	���b�V��(�~��)�̕`�揈��
//---------------------------------------------------
void DrawMeshCylinder(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X

	// Z�o�b�t�@�Ɋւ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	
	for (int nCntCylinder = 0; nCntCylinder < MAX_CYLINDER; nCntCylinder++)
	{
		if (g_Cylinder[nCntCylinder].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Cylinder[nCntCylinder].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Cylinder[nCntCylinder].rot.y, g_Cylinder[nCntCylinder].rot.x, g_Cylinder[nCntCylinder].rot.z);
			D3DXMatrixMultiply(&g_Cylinder[nCntCylinder].mtxWorld,
				&g_Cylinder[nCntCylinder].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Cylinder[nCntCylinder].pos.x, g_Cylinder[nCntCylinder].pos.y, g_Cylinder[nCntCylinder].pos.z);
			D3DXMatrixMultiply(&g_Cylinder[nCntCylinder].mtxWorld, &g_Cylinder[nCntCylinder].mtxWorld, &mtxTrans);

			//���C�g�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Cylinder[nCntCylinder].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshCylinder);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//���u�����f�B���O�����Z�����ɐݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshCylinder);

			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHCYLINDER_VERTEX, 0, MESHCYLINDER_PRIMITIVE);

			//���u�����f�B���O�����ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			//���C�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			//�e�N�X�`������NULL�ɂ���
			pDevice->SetTexture(0, NULL);
		}
	}

	// Z�o�b�t�@�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			//�K��l�F�l�����݂̃s�N�Z���̒l�ȉ��̏ꍇ�́A�V�����s�N�Z�����󂯓����B
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

void SetMeshCylinder(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntCylinder = 0; nCntCylinder < MAX_CYLINDER; nCntCylinder++)
	{
		if (g_Cylinder[nCntCylinder].bUse == false)
		{
			g_Cylinder[nCntCylinder].pos = pos;
			g_Cylinder[nCntCylinder].rot = rot;
			g_Cylinder[nCntCylinder].bUse = true;

			break;
		}
	}
}
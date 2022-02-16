//----------------------------------------
//�@�V��̏���
//�@Author�F���슲��
//----------------------------------------
#include "meshtop.h"
#include "meshsphere.h"

#define MESHTOP_X_BLOCK		(16)		// X���̃u���b�N��
#define MESHTOP_Z_BLOCK		(1)			// Z���̃u���b�N��

#define MESHTOP_VERTEX		((MESHTOP_X_BLOCK + 1) * (MESHTOP_Z_BLOCK + 1))								//���b�V���̒��_
#define MESHTOP_INDEX		((MESHTOP_X_BLOCK  + 1) * 2 * MESHTOP_Z_BLOCK + (MESHTOP_Z_BLOCK - 1) * 2)	//�C���f�b�N�X��
#define MESHTOP_PRIMITIVE	((MESHTOP_X_BLOCK * MESHTOP_Z_BLOCK * 2) + (MESHTOP_Z_BLOCK - 1) * 4)		//�|���S����

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshTop = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMeshTop;		//�ʒu
D3DXVECTOR3 g_rotMeshTop;		//����
D3DXMATRIX g_mtxWorldMeshTop;	//���[���h�}�g���b�N�X

//---------------------------------------------------
//	�V��̏�����
//---------------------------------------------------
void InitMeshTop(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;			//�f�o�C�X�擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHTOP_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshTop,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshTop->Lock(0, 0, (void**)&pVtx, 0);

	int nCnt = 0;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f,  50.0f);
	pVtx[1].pos = D3DXVECTOR3(	0.0f, 0.0f,  50.0f);
	pVtx[2].pos = D3DXVECTOR3( 50.0f, 0.0f,  50.0f);
	pVtx[3].pos = D3DXVECTOR3(-50.0f, 0.0f,   0.0f);
	pVtx[4].pos = D3DXVECTOR3(	0.0f, 0.0f,   0.0f);
	pVtx[5].pos = D3DXVECTOR3( 50.0f, 0.0f,   0.0f);
	pVtx[6].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[7].pos = D3DXVECTOR3(	0.0f, 0.0f, -50.0f);
	pVtx[8].pos = D3DXVECTOR3( 50.0f, 0.0f, -50.0f);

	//�e���_�̖@���̐ݒ�(�x�N�g���̑傫���͂P�ɂ���)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshTop->Unlock();
}

//---------------------------------------------------
//	�V��̏I������
//---------------------------------------------------
void UninitMeshTop(void)
{
	//���_�o�b�t�@�j��
	if (g_pVtxBuffMeshTop != NULL)
	{
		g_pVtxBuffMeshTop->Release();
		g_pVtxBuffMeshTop = NULL;
	}
}

//---------------------------------------------------
//	�V��̍X�V����
//---------------------------------------------------
void UpdateMeshTop(void)
{

}

//---------------------------------------------------
//	�V��̕`�揈��
//---------------------------------------------------
void DrawMeshTop(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshTop);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotMeshTop.y, g_rotMeshTop.x, g_rotMeshTop.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshTop,
		&g_mtxWorldMeshTop, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshTop.x, g_posMeshTop.y, g_posMeshTop.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshTop, &g_mtxWorldMeshTop, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshTop);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshTop, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, MESHTOP_VERTEX, 0, MESHTOP_PRIMITIVE);

	pDevice->SetTexture(0, NULL);
}


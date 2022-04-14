//----------------------------------------
//	���U���g��ʂ̏���
//�@Author�F���슲��
//----------------------------------------
#include "result.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureResult[RESULT_TYPE_MAX] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Result_Type g_ResultType = RESULT_TYPE_OVER;		//���U���g�̎��
bool g_bResult = false;		//��񂾂��N���p

//----------------------------------------
//  ���U���g�̏���������
//----------------------------------------
void InitResult(Result_Type nResult)
{
	g_ResultType = nResult;	//��ނ�ݒ�
	g_bResult = false;		//false�ɂ���

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\result_over.png",
		&g_pTextureResult[RESULT_TYPE_OVER]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\result_clear.png",
		&g_pTextureResult[RESULT_TYPE_CLEAR]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM_RESULT);
}

//----------------------------------------
//  ���U���g�̏I������
//----------------------------------------
void UninitResult(void)
{
	//�e�N�X�`���̔j��
	for (int i = 0; i < RESULT_TYPE_MAX; i++)
	{
		if (g_pTextureResult[i] != NULL)
		{
			g_pTextureResult[i]->Release();
			g_pTextureResult[i] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//----------------------------------------
//  ���U���g�̍X�V����
//----------------------------------------
void UpdateResult(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (!g_bResult)
		{
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_TITLE_BUTTON);

			//���[�h�ݒ�(�Q�[����ʂɈڍs)
			SetFade(MODE_RANKING);

			g_bResult = true;
		}
	}
}

//----------------------------------------
//  ���U���g�̕`�揈��
//----------------------------------------
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult[g_ResultType]);

	//�|���S���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
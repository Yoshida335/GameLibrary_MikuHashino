//----------------------------------------
//	�X�e�[�W�̏���
//�@Author�F���슲��
//----------------------------------------
#include "item.h"
#include "block.h"
#include "stage.h"
#include "goal.h"
#include "ladder.h"
#include "time.h"
#include "button.h"
#include "sound.h"
#include "map.h"

//�O���[�o���ϐ��錾
int g_numCoin = 0;
int g_nStage = 0;
bool g_bStage = false;

//----------------------------------------------
//	�X�e�[�W�̑I������
//----------------------------------------------
void SelectStage(STAGE_No nSelect)
{
	g_numCoin = 0;
	g_nStage = nSelect;
	g_bStage = false;

	switch (nSelect)
	{
	case STAGE_No_0:
		//���Ԑݒ�
		SetMap(MAP_01);
		break;

	case STAGE_No_1:
		//���Ԑݒ�
		SetMap(MAP_02);
		break;
	}

	//�^�C�}�[�ݒ�
	SetTime(90);

	//�S�[���ݒ�
	SetGoal(D3DXVECTOR3((SCREEN_WIDTH / 2), SCREEN_HEIGHT - (BLOCK_HEIGHT / 2), 0.0f));
}

//----------------------------------------------
//	�X�e�[�W�̍X�V
//----------------------------------------------
void UpdateStage(void)
{
	g_numCoin = GetNumCoin();

	if (!g_bStage)
	{
		if (g_numCoin >= 5)
		{
			switch (g_nStage)
			{
			case STAGE_No_0:
				//�A�C�e�� -----------------------------------
				SetItem(D3DXVECTOR3(350.0f, 80.0f, 0.0f), ITEM_KEY);
				break;

			case STAGE_No_1:
				SetItem(D3DXVECTOR3((SCREEN_WIDTH / 2) - 60.0f, 260.0f, 0.0f), ITEM_KEY);
				break;
			}
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_KEY);

			g_bStage = true;
		}
	}
}
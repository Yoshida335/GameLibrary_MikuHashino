#include "game.h"
#include "input.h"
#include "bg.h"
#include "player.h"
#include "block.h"
#include "fade.h"
#include "item.h"
#include "time.h"
#include "score.h"
#include "ladder.h"
#include "button.h"
#include "goal.h"
#include "sound.h"
#include "stage.h"
#include "select.h"

//�O���[�o���ϐ��錾
bool g_bPause = false;		//�|�[�Y�����ǂ���

void InitGame(void)
{
	//�w�i�̏������ݒ�
	InitBG();

	//�^�C���̏������ݒ�
	InitTime();

	//�X�R�A�̏������ݒ�
	InitScore();

	//�v���C���[�̏���������
	InitPlayer();

	//�A�C�e���̏���������
	InitItem();

	//�S�[���̏���������
	InitGoal();

	//��q�̏���������
	InitLadder();

	//�u���b�N�̏���������
	InitBlock();

	//�{�^���̏���������
	InitButton();

	STAGE_No * pSelect;
	pSelect = GetSelect();

	Stage(*pSelect);

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM_GAME);

	g_bPause = false;		//�|�[�Y����
}

void UninitGame(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�w�i�̏I������
	UninitBG();

	//�^�C���̏I������
	UninitTime();

	//�X�R�A�̏I���ݒ�
	UninitScore();

	//�v���C���[�̏I������
	UninitPlayer();

	//�A�C�e���̏I������
	UninitItem();

	//�S�[���̏I������
	UninitGoal();

	//��q�̏I������
	UninitLadder();

	//�u���b�N�̏I������
	UninitBlock();

	//�{�^���̏I������
	UninitButton();
}

void UpdateGame(void)
{
	STARTTIME * pST;
	pST = GetStartTime();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		//���[�h�ݒ�(�Q�[����ʂɈڍs)
		//SetFade(MODE_RESULT);
	}
	else
	{
		if (GetKeyboardTrigger(DIK_P) == true)
		{//�|�[�X�L�[(P�L�[)�������ꂽ
			g_bPause = g_bPause ? false : true;
		}

		if (g_bPause == false)
		{//�|�[�Y���łȂ����
			//�^�C���̍X�V����
			UpdateTime();

			if (pST->state == TIME_ON)
			{
				//�w�i�̍X�V����
				UpdateBG();

				//�X�R�A�̍X�V�ݒ�
				UpdateScore();

				//�v���C���[�̍X�V����
				UpdatePlayer();

				//�A�C�e���̍X�V����
				UpdateItem();

				//�S�[���̍X�V����
				UpdateGoal();

				//��q�̍X�V����
				UpdateLadder();

				//�u���b�N�̍X�V����
				UpdateBlock();

				//�{�^���̍X�V����
				UpdateButton();

				UpdateStage();
			}
		}
	}
}

void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBG();

	//�S�[���̕`�揈��
	DrawGoal();

	//�u���b�N�̕`�揈��
	DrawBlock();

	//��q�̕`�揈��
	DrawLadder();

	//�A�C�e���̕`�揈��
	DrawItem();

	//�{�^���̕`�揈��
	DrawButton();

	//�^�C���̕`�揈��
	DrawTime();

	//�X�R�A�̕`��ݒ�
	//DrawScore();

	//�v���C���[�̕`�揈��
	DrawPlayer();
}


//----------------------------------------
//�@�Q�[����ʂ̏���
//�@Author�F���슲��
//----------------------------------------
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
#include "goal.h"
#include "sound.h"
#include "stage.h"
#include "select.h"
#include "map.h"
#include "pause.h"

//�O���[�o���ϐ��錾
bool g_bPause = false;		//�|�[�Y�����ǂ���

//----------------------------------------
//�@�Q�[����ʂ̏���������
//----------------------------------------
void InitGame(void)
{
	//�|�[�Y��ʂ̏���������
	InitPause();

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

	STAGE_No * pSelect;
	pSelect = GetSelect();

	SelectStage(*pSelect);

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM_GAME);

	g_bPause = false;		//�|�[�Y����
}

//----------------------------------------
//�@�Q�[����ʂ̏I������
//----------------------------------------
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

	//�|�[�Y��ʂ̏I������
	UninitPause();
}

//----------------------------------------
//�@�Q�[����ʂ̍X�V����
//----------------------------------------
void UpdateGame(void)
{
	TIMESTATE * pST;
	pST = GetStartTime();

	if (GetKeyboardTrigger(DIK_P) == true)
	{//�|�[�X�L�[(P�L�[)�������ꂽ
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == true)
	{
		//�|�[�Y��ʂ̍X�V����
		UpdatePause();
	}

	if (g_bPause == false)
	{//�|�[�Y���łȂ����
		//�^�C���̍X�V����
		UpdateTime();

		//�w�i�̍X�V����
		UpdateBG();

		//�X�R�A�̍X�V�ݒ�
		UpdateScore();

		if (pST->state == TIME_ON)
		{
			//�v���C���[�̍X�V����
			UpdatePlayer();
		}

		//�A�C�e���̍X�V����
		UpdateItem();

		//�S�[���̍X�V����
		UpdateGoal();

		//�u���b�N�̍X�V����
		UpdateBlock();

		//��q�̍X�V����
		UpdateLadder();

		//�X�e�[�W�̍X�V����
		UpdateStage();
	}
}

//----------------------------------------
//�@�Q�[����ʂ̕`�揈��
//----------------------------------------
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBG();

	//�S�[���̕`�揈��
	DrawGoal();

	//�u���b�N�̕`�揈��
	DrawBlock();

	//�A�C�e���̕`�揈��
	DrawItem();

	//��q�̕`�揈��
	DrawLadder();

	//�^�C���̕`�揈��
	DrawTime();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	if (g_bPause)
	{
		//�|�[�Y��ʂ̕`�揈��
		DrawPause();
	}
}

//---------------------------------------------------
//	�|�[�Y�̏��
//---------------------------------------------------
bool * GetPause(void)
{
	return &g_bPause;
}
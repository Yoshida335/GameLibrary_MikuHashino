//----------------------------------------
//�@�Q�[����ʂ̏���
//�@Author�F���슲��
//----------------------------------------
#include "game.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "score.h"
#include "player.h"
#include "fade.h"
#include "time.h"
#include "stage.h"
#include "sound.h"
#include "life.h"

//----------------------------------------
//�@�Q�[����ʂ̏���������
//----------------------------------------
void InitGame(void)
{
	//�w�i�̏������ݒ�
	InitBG();

	//�|���S���̏������ݒ�
	InitPLAYER();

	//�G�̏������ݒ�
	InitEnemy();

	//�X�e�[�W�̏������ݒ�
	InitStage();

	//�e�̏������ݒ�
	InitBullet();

	//�e�̏������ݒ�
	InitExplosion();

	//�X�R�A�̏������ݒ�
	InitScore();

	//�^�C���̏������ݒ�
	InitTime();

	//���C�t�̏������ݒ�
	InitLife();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM001);
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

	//�|���S���̏I������
	UninitPLAYER();

	//�G�̏I������
	UninitEnemy();

	//�X�e�[�W�̏I���ݒ�
	UninitStage();

	//�e�̏I������
	UninitBullet();

	//�e�̏I������
	UninitExplosion();

	//�X�R�A�̏I������
	UninitScore();

	//���C�t�̏I������
	UninitLife();

	//�^�C���̏I������
	UninitTime();
}

//----------------------------------------
//�@�Q�[����ʂ̍X�V����
//----------------------------------------
void UpdateGame(void)
{
	//�w�i�̍X�V����
	UpdateBG();

	//�|���S���̍X�V����
	UpdatePLAYER();

	//�G�̍X�V����
	UpdateEnemy();

	//�X�e�[�W�̍X�V�ݒ�
	UpdateStage();

	//�e�̍X�V����
	UpdateBullet();

	//�e�̍X�V����
	UpdateExplosion();

	//�X�R�A�̍X�V����
	UpdateScore();

	//�^�C���̍X�V����
	UpdateTime();

	//���C�t�̍X�V����
	UpdateLife();
}

//----------------------------------------
//�@�Q�[����ʂ̕`�揈��
//----------------------------------------
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBG();

	//�e�̕`�揈��
	DrawBullet();

	//�X�e�[�W�̕`��ݒ�
	DrawStage();

	//�����̕`�揈��
	DrawExplosion();

	//�G�̕`�揈��
	DrawEnemy();

	//�|���S���̕`�揈��
	DrawPLAYER();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�^�C���̕`�揈��
	DrawTime();

	//���C�t�̕`�揈��
	DrawLife();
}
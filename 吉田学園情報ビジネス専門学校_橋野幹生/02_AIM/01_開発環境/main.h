//----------------------------------------
//�@���C��
//----------------------------------------
#ifndef _MAIN_H_				//���̃}�N������`����ĂȂ�������
#define _MAIN_H_				//�Q�d�C���N���[�h�h�~�̃}�N����`	

#include <windows.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	//�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"						//���͏����ɕK�v
#include "xinput.h"						//�W���C�p�b�h�����ɕK�v
#include "xaudio2.h"					//�T�E���h�����ɕK�v
#include "dinput.h"
#include "xaudio2.h"

//���C�u�����̃����N
#pragma comment(lib, "d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib, "d3dx9.lib")		//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib, "dxguid.lib")		//DirectX�R���|�[�g(���i)�ɕK�v
#pragma comment(lib, "winmm.lib")		//�V�X�e�������擾�ɕK�v
#pragma comment(lib, "dinput8.lib")		//���͏����ɕK�v
#pragma comment(lib, "xinput.lib")		//�W���C�p�b�h�����ɕK�v

//�}�N����`
#define SCREEN_WIDTH		(1280)		//�E�B���h�E�̕�
#define SCREEN_HEIGHT		(720)		//�E�B���h�E�̍���
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;			//���_���W
	float rhm;					//���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;				//���_�J���[
	D3DXVECTOR2 tex;			//�e�N�X�`�����W
}VERTEX_2D;

//���_���[2D]�̍\���̂��`
typedef enum
{
	//���
	MODE_TITLE = 0,			//�^�C�g�����
	MODE_SELECT,			//�Z���N�g���
	MODE_RULE,				//���[�����
	MODE_GAME,				//�Q�[�����
	MODE_RESULT,			//���U���g���
	MODE_RESULT_CLEAR,		//���U���g�N���A���
	MODE_RANKING,			//�����L���O���
	//�X�e�[�W
	MODE_STAGE_01,
	MODE_STAGE_02,
	MODE_STAGE_03,
	MODE_MAX
}MODE;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif

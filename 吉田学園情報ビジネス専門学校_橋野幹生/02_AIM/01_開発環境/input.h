//----------------------------------------
//�@�L�[�{�[�h�̓��͏����̃w�b�_�[
//----------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//�L�[�{�[�h�̏���������
void UninitKeyboard(void);			//�L�[�{�[�h�̏I������
void UpdateKeyboard(void);			//�L�[�{�[�h�̍X�V����
bool GetKeyboardPress(int nKey);	//�L�[�{�[�h�̃v���X����
bool GetKeyboardTrigger(int nKey);	//�L�[�{�[�h�̃g���K�[����

#endif
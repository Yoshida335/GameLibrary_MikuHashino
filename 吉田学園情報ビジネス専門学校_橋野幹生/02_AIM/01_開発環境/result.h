//----------------------------------------
//	���U���g��ʂ̃w�b�_�[
//	Author�F���슲��
//----------------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

//���U���g�̎��
enum Result_Type
{
	RESULT_TYPE_OVER = 0,	//�Q�[���I�[�o�[
	RESULT_TYPE_CLEAR,		//�Q�[���N���A
	RESULT_TYPE_MAX
};

//�v���g�^�C�v�錾
void InitResult(Result_Type nResult);	//���U���g��ʂ̏���������
void UninitResult(void);	//���U���g��ʂ̏I������
void UpdateResult(void);	//���U���g��ʂ̍X�V����
void DrawResult(void);		//���U���g��ʂ̕`�揈��

#endif
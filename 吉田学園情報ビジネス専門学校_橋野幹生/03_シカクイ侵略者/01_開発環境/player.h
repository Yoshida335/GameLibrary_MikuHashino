#ifndef _PLAYER_H_				//���̃}�N������`����ĂȂ�������
#define _PLAYER_H_				//�Q�d�C���N���[�h�h�~�̃}�N����`

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_APPEAR = 0,		//�o�����(�_��)
	PLAYERSTATE_NOMAL,			//�ʏ���
	PLAYERSTATE_DAMAGE,			//�_���[�W���
	PLAYERSTATE_DEATH,			//���S���
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�G�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//����
	bool bUse;				//�g�p���Ă��邩�ǂ���
	PLAYERSTATE state;		//�v���C���[�̏��
	int direction;			//�e�̌���
	int nCounterState;		//��ԊǗ��J�E���^�[
	int nLife;				//�̗�
	bool bDisp;				//�\�����邩���Ȃ���
}Player;

//�v���g�^�C�v�錾
void InitPLAYER(void);
void UninitPLAYER(void);
void UpdatePLAYER(void);
void DrawPLAYER(void);
void PlayerControl(void);
void PlayerMove(void);
void PlayerAttack(void);
void HitPlayer(int nDamage);

#endif

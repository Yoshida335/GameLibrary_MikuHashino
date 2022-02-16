//----------------------------------------
//�@��
//----------------------------------------
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//�}�N����`
#define MAX_WALL	(256)		//�ǂ̍ő吔
#define WALL_X		(300.0f)	// x�����ւ̒l	����
#define WALL_Y		(140.0f)		// y�����ւ̒l	����
#define WALL_Z		(0.0f)		// z�����ւ̒l	�c��

typedef enum
{
	TYPE_WARKING = 0,
	TYPE_BILL,
	MAX_TYPE
}WALLTYPE;

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 size;
	D3DXCOLOR col;
	D3DXMATRIX mtxWorld;
	bool bUse;
	WALLTYPE type;
}Wall;

//�v���g�^�C�v�錾
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 size, WALLTYPE type);
Wall * GetWall(void);

#endif


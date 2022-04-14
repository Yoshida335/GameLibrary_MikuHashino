//----------------------------------------
//�@�}�b�v�̏���
//�@Author�F���슲��
//----------------------------------------
#include "map.h"
#include "block.h"
#include "item.h"
#include <stdio.h>
#include <string.h>
#include "ladder.h"

//�}�N����`
#define MAX_X		(32)	// x���ɒu����u���b�N�̍ő吔
#define MAX_Y		(18)	// y���ɒu����u���b�N�̍ő吔
#define FILE_PAS_01	("data\\map001.txt")	//�X�e�[�W1�̃}�b�v�̏�񂪓����Ă���f�[�^
#define FILE_PAS_02	("data\\map002.txt")	//�X�e�[�W2�̃}�b�v�̏�񂪓����Ă���f�[�^

//�O���[�o���ϐ��錾
int nData[MAX_Y][MAX_X] = {};

//----------------------------------------
//�@�}�b�v�̐ݒ�
//----------------------------------------
void SetMap(int nSelect)
{
	FILE * pFile = NULL;

	switch (nSelect)
	{
	case MAP_01:
		pFile = fopen(FILE_PAS_01, "r");
		break;

	case MAP_02:
		pFile = fopen(FILE_PAS_02, "r");
		break;

	default:
		break;
	}

	if (pFile != NULL)
	{
		for (int nCntY = 0; nCntY < MAX_Y; nCntY++)
		{
			for (int nCntX = 0; nCntX < MAX_X; nCntX++)
			{
				fscanf(pFile, "%d", &nData[nCntY][nCntX]);
			}
		}
	}
	else
	{
		return;
	}

	for (int nCntY = 0; nCntY < MAX_Y; nCntY++)
	{
		for (int nCntX = 0; nCntX < MAX_X; nCntX++)
		{
			switch (nData[nCntY][nCntX])
			{
			case 0:	//�G�A
				break;

			case 1:	//�m�[�}���u���b�N
				SetBlock(D3DXVECTOR3((40.0f * nCntX + (40.0f / 2)), (40.0f * nCntY + (40.0f / 2)), 0.0f), BLOCKTYPE_NOMAL, BLOCKSTATE_NOMAL, BLOCK_WIDTH * 1, BLOCK_HEIGHT * 1);
				break;

			case 2:	//�A�b�v�u���b�N
				SetBlock(D3DXVECTOR3((40.0f * nCntX + (40.0f / 2)), (40.0f * nCntY + (40.0f / 2)), 0.0f),
					BLOCKTYPE_UP,
					BLOCKSTATE_NOMAL,
					BLOCK_WIDTH,
					BLOCK_HEIGHT * 1);
				break;

			case 3:	//�R�C��
				SetItem(D3DXVECTOR3((40.0f * nCntX + (40.0f / 2)), (40.0f * nCntY + (40.0f / 2)), 0.0f), ITEM_COIN);
				break;

			case 4:	//�ʏ��q
				SetLadder(D3DXVECTOR3((40.0f * nCntX + (40.0f / 2)), (40.0f * nCntY + (40.0f / 2)), 0.0f), LADDER_WIDTH, LADDER_HEIGHT, LADDER_TYPE_0);
				break;

			case 5:	//������̂ݒ�q
				SetLadder(D3DXVECTOR3((40.0f * nCntX + (40.0f / 2)), (40.0f * nCntY + (40.0f / 2)), 0.0f), LADDER_WIDTH, LADDER_HEIGHT, LADDER_TYPE_1);
				break;

			default:
				break;
			}
		}
	}
}
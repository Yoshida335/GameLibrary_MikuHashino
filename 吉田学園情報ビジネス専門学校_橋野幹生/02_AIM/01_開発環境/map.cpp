//----------------------------------------
//�@�}�b�v�̏���
//�@Author�F���슲��
//----------------------------------------
#include "map.h"
#include "block.h"
#include "item.h"
#include <stdio.h>
#include <string.h>

//�}�N����`
#define MAX_X		(32)	// x���ɒu����u���b�N�̍ő吔
#define MAX_Y		(18)	// y���ɒu����u���b�N�̍ő吔
#define FILE_PAS	("data\\map2.txt")	//�}�b�v�̏�񂪓����Ă���f�[�^

FILE * pFile;
int nData[MAX_Y][MAX_X];

//----------------------------------------
//�@�}�b�v�̐ݒ�
//----------------------------------------
void SetMap(void)
{
	float BlockX = SCREEN_WIDTH / MAX_X;
	float BlockY = SCREEN_HEIGHT / MAX_Y;

	pFile = fopen(FILE_PAS, "r");

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
				SetBlock(D3DXVECTOR3((40.0f * nCntX + (40.0f / 2)), (40.0f * nCntY + (40.0f / 2)), 0.0f), BLOCKTYPE_NOMAL, BLOCKSTATE_NOMAL, BLOCK_WIDTH * 1, BLOCK_HEIGHT * 1, 2);
				break;

			case 2:	//�A�b�v�u���b�N
				SetBlock(D3DXVECTOR3((40.0f * nCntX + (40.0f / 2)), (40.0f * nCntY + (40.0f / 2)), 0.0f),
					BLOCKTYPE_UP,
					BLOCKSTATE_NOMAL,
					BLOCK_WIDTH,
					BLOCK_HEIGHT * 1,
					7);
				break;

			case 3:	//�A�b�v�u���b�N
				SetItem(D3DXVECTOR3((40.0f * nCntX + (40.0f / 2)), (40.0f * nCntY + (40.0f / 2)), 0.0f), ITEM_TYPE_0);
				break;

			default:
				break;
			}
		}
	}


}
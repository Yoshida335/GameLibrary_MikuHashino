//----------------------------------------
//　マップの処理
//　Author：橋野幹生
//----------------------------------------
#include "map.h"
#include "block.h"
#include "item.h"
#include <stdio.h>
#include <string.h>

//マクロ定義
#define MAX_X		(32)	// x軸に置けるブロックの最大数
#define MAX_Y		(18)	// y軸に置けるブロックの最大数
#define FILE_PAS	("data\\map2.txt")	//マップの情報が入っているデータ

FILE * pFile;
int nData[MAX_Y][MAX_X];

//----------------------------------------
//　マップの設定
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
			case 0:	//エア
				break;

			case 1:	//ノーマルブロック
				SetBlock(D3DXVECTOR3((40.0f * nCntX + (40.0f / 2)), (40.0f * nCntY + (40.0f / 2)), 0.0f), BLOCKTYPE_NOMAL, BLOCKSTATE_NOMAL, BLOCK_WIDTH * 1, BLOCK_HEIGHT * 1, 2);
				break;

			case 2:	//アップブロック
				SetBlock(D3DXVECTOR3((40.0f * nCntX + (40.0f / 2)), (40.0f * nCntY + (40.0f / 2)), 0.0f),
					BLOCKTYPE_UP,
					BLOCKSTATE_NOMAL,
					BLOCK_WIDTH,
					BLOCK_HEIGHT * 1,
					7);
				break;

			case 3:	//アップブロック
				SetItem(D3DXVECTOR3((40.0f * nCntX + (40.0f / 2)), (40.0f * nCntY + (40.0f / 2)), 0.0f), ITEM_TYPE_0);
				break;

			default:
				break;
			}
		}
	}


}
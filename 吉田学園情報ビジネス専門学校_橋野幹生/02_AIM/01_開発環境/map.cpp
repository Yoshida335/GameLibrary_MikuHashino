//----------------------------------------
//　マップの処理
//　Author：橋野幹生
//----------------------------------------
#include "map.h"
#include "block.h"
#include "item.h"
#include <stdio.h>
#include <string.h>
#include "ladder.h"

//マクロ定義
#define MAX_X		(32)	// x軸に置けるブロックの最大数
#define MAX_Y		(18)	// y軸に置けるブロックの最大数
#define FILE_PAS_01	("data\\map001.txt")	//ステージ1のマップの情報が入っているデータ
#define FILE_PAS_02	("data\\map002.txt")	//ステージ2のマップの情報が入っているデータ

//グローバル変数宣言
int nData[MAX_Y][MAX_X] = {};

//----------------------------------------
//　マップの設定
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
			case 0:	//エア
				break;

			case 1:	//ノーマルブロック
				SetBlock(D3DXVECTOR3((40.0f * nCntX + (40.0f / 2)), (40.0f * nCntY + (40.0f / 2)), 0.0f), BLOCKTYPE_NOMAL, BLOCKSTATE_NOMAL, BLOCK_WIDTH * 1, BLOCK_HEIGHT * 1);
				break;

			case 2:	//アップブロック
				SetBlock(D3DXVECTOR3((40.0f * nCntX + (40.0f / 2)), (40.0f * nCntY + (40.0f / 2)), 0.0f),
					BLOCKTYPE_UP,
					BLOCKSTATE_NOMAL,
					BLOCK_WIDTH,
					BLOCK_HEIGHT * 1);
				break;

			case 3:	//コイン
				SetItem(D3DXVECTOR3((40.0f * nCntX + (40.0f / 2)), (40.0f * nCntY + (40.0f / 2)), 0.0f), ITEM_COIN);
				break;

			case 4:	//通常梯子
				SetLadder(D3DXVECTOR3((40.0f * nCntX + (40.0f / 2)), (40.0f * nCntY + (40.0f / 2)), 0.0f), LADDER_WIDTH, LADDER_HEIGHT, LADDER_TYPE_0);
				break;

			case 5:	//上方向のみ梯子
				SetLadder(D3DXVECTOR3((40.0f * nCntX + (40.0f / 2)), (40.0f * nCntY + (40.0f / 2)), 0.0f), LADDER_WIDTH, LADDER_HEIGHT, LADDER_TYPE_1);
				break;

			default:
				break;
			}
		}
	}
}
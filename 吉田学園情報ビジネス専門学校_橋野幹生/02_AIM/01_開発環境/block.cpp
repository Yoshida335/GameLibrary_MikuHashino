#include "block.h"
#include "player.h"
#include "input.h"
#include "item.h"
#include "stage.h"
#include "sound.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBlock[BLOCKTYPE_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;
BLOCK g_Block[MAX_BLOCK];
float g_fLengthBlock;				//対角線の長さ
float g_fAngleBlock;				//対角線の角度

//----------------------------------------
//　ブロックの初期化処理
//----------------------------------------
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block000.jpg",
		&g_pTextureBlock[BLOCKTYPE_NOMAL]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block001.png",
		&g_pTextureBlock[BLOCKTYPE_UP]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block_002.png",
		&g_pTextureBlock[BLOCKTYPE_ITEM]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block000.jpg",
		&g_pTextureBlock[BLOCKTYPE_ACT]);

	//ブロックの初期化
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_Block[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//現在の位置
		g_Block[nCntBlock].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//前回の位置
		g_Block[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//角度
		g_Block[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
		g_Block[nCntBlock].fWidth = 0.0f;								//幅
		g_Block[nCntBlock].fHeight = 0.0f;								//高さ
		g_Block[nCntBlock].bUse = false;								//使っているか
		g_Block[nCntBlock].type = BLOCKTYPE_NOMAL;						//種類
		g_Block[nCntBlock].rot2 = 0.0f;									//角度
		g_Block[nCntBlock].flength = 0.0f;								//斜め長さ
		g_Block[nCntBlock].state = BLOCKSTATE_NOMAL;					//状態
		g_Block[nCntBlock].nLife = 0;									//寿命
	}

	//対角線の長さ算出
	g_fLengthBlock = sqrtf(BLOCK_WIDTH * BLOCK_WIDTH + BLOCK_HEIGHT * BLOCK_HEIGHT) / 2.0f;

	//対角線の角度を算出する
	g_fAngleBlock = atan2f(BLOCK_WIDTH, BLOCK_HEIGHT);

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//頂点座標更新
		pVtx[0].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (-D3DX_PI + g_fAngleBlock)) * g_fLengthBlock;
		pVtx[0].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (-D3DX_PI + g_fAngleBlock)) * g_fLengthBlock;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (D3DX_PI - g_fAngleBlock)) * g_fLengthBlock;
		pVtx[1].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (D3DX_PI - g_fAngleBlock)) * g_fLengthBlock;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (0.0f - g_fAngleBlock)) * g_fLengthBlock;
		pVtx[2].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (0.0f - g_fAngleBlock)) * g_fLengthBlock;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (0.0f + g_fAngleBlock)) * g_fLengthBlock;
		pVtx[3].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (0.0f + g_fAngleBlock)) * g_fLengthBlock;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhm = 1.0f;
		pVtx[1].rhm = 1.0f;
		pVtx[2].rhm = 1.0f;
		pVtx[3].rhm = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();

}

//----------------------------------------
//　ブロックの終了処理
//----------------------------------------
void UninitBlock(void)
{
	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < BLOCKTYPE_MAX; nCntTex++)
	{
		if (g_pTextureBlock[nCntTex] != NULL)
		{
			g_pTextureBlock[nCntTex]->Release();
			g_pTextureBlock[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//----------------------------------------
//　ブロックの更新処理
//----------------------------------------
void UpdateBlock(void)
{
	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{
			g_Block[nCntBlock].posOld = g_Block[nCntBlock].pos;

			ActBlock(&g_Block[nCntBlock].pos, g_Block[nCntBlock].fWidth, g_Block[nCntBlock].fHeight);

			if (ActBlock(&g_Block[nCntBlock].pos, g_Block[nCntBlock].fWidth, g_Block[nCntBlock].fHeight) != true
				&& BLOCKTYPE_ACT == g_Block[nCntBlock].type)
			{
				g_Block[nCntBlock].state = BLOCKSTATE_ACT;
			}

			switch (g_Block[nCntBlock].state)
			{
			case BLOCKSTATE_NOMAL:
				g_Block[nCntBlock].move.y = 0.0f;
				break;

			case BLOCKSTATE_UP:
				g_Block[nCntBlock].pos.y -= (BLOCK_WIDTH / 2);

				g_Block[nCntBlock].state = BLOCKSTATE_NOMAL;
				break;

			case BLOCKSTATE_MOVE:
				g_Block[nCntBlock].nLife -= 1;

				if (g_Block[nCntBlock].nLife >= 0)
				{
					g_Block[nCntBlock].move.y = BLOCK_MOVE;
				}
				else if (g_Block[nCntBlock].nLife >= -BLOCK_MOVE_LIFE)
				{
					g_Block[nCntBlock].move.y = -BLOCK_MOVE;
				}
				else if (g_Block[nCntBlock].nLife <= -BLOCK_MOVE_LIFE)
				{
					g_Block[nCntBlock].nLife = BLOCK_MOVE_LIFE;
				}

				break;

			case BLOCKSTATE_ITEM:
				g_Block[nCntBlock].move.y = -1.0f;

				SetItem(D3DXVECTOR3(g_Block[nCntBlock].pos.x, g_Block[nCntBlock].pos.y - BLOCK_HEIGHT, g_Block[nCntBlock].pos.z), ITEM_TYPE_0);

				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

				g_Block[nCntBlock].state = BLOCKSTATE_NOMAL;
				break;

			case BLOCKSTATE_ACT:
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				break;

			case BLOCKSTATE_RL:
				//重力
				g_Block[nCntBlock].move.y += 0.1f;

				CollisionBlock2(&g_Block[nCntBlock].pos, &g_Block[nCntBlock].posOld, &g_Block[nCntBlock].move, BLOCK_WIDTH, BLOCK_HEIGHT, g_Block[nCntBlock].state);

				if (g_Block[nCntBlock].pos.x - (BLOCK_WIDTH / 2) >= SCREEN_WIDTH)
				{//画面外(右側)に出たら
					g_Block[nCntBlock].pos = D3DXVECTOR3(0.0f - PLAYER_WIDTH / 2, g_Block[nCntBlock].pos.y, 0.0f);
				}
				else if (g_Block[nCntBlock].pos.x + (BLOCK_WIDTH / 2) <= 0.0f)
				{//画面外(左側)に出たら
					g_Block[nCntBlock].pos = D3DXVECTOR3(SCREEN_WIDTH + PLAYER_WIDTH / 2, g_Block[nCntBlock].pos.y, 0.0f);
				}

				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

				break;
			}

			g_Block[nCntBlock].pos += g_Block[nCntBlock].move;

			//ブロック同士の当たり判定
			CollisionBlock2(&g_Block[nCntBlock].pos, &g_Block[nCntBlock].posOld, &g_Block[nCntBlock].move, g_Block[nCntBlock].fWidth, g_Block[nCntBlock].fHeight, g_Block[nCntBlock].state);
		}

		//頂点座標更新
		pVtx[0].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (-D3DX_PI + g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength;
		pVtx[0].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (-D3DX_PI + g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (D3DX_PI - g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength;
		pVtx[1].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (D3DX_PI - g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (0.0f - g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength;
		pVtx[2].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (0.0f - g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (0.0f + g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength;
		pVtx[3].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (0.0f + g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength;
		pVtx[3].pos.z = 0.0f;

		//画面外処理
		if (g_Block[nCntBlock].pos.x + (BLOCK_WIDTH / 2) <= 0.0f ||
			g_Block[nCntBlock].pos.x - (BLOCK_WIDTH / 2) >= SCREEN_WIDTH ||
			g_Block[nCntBlock].pos.y + (BLOCK_HEIGHT / 2) <= 0.0f ||
			g_Block[nCntBlock].pos.y - (BLOCK_HEIGHT / 2) >= SCREEN_HEIGHT)
		{//画面外に出たら
			g_Block[nCntBlock].bUse = false;
		}

		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//----------------------------------------
//　ブロックの描画処理
//----------------------------------------
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntBlock;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{//ブロックが使用されている
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBlock[g_Block[nCntBlock].type]);

			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBlock * 4,
				2);
		}
	}
}

//----------------------------------------
//　ブロックの設定
//----------------------------------------
void SetBlock(D3DXVECTOR3 pos, BLOCKTYPE type, BLOCKSTATE state, float fWidth, float fHeight, int life)
{
	int nCntBlock;

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == false)
		{//ブロックが使用されていない場合
			g_Block[nCntBlock].pos = pos;
			g_Block[nCntBlock].type = type;
			g_Block[nCntBlock].state = state;
			g_Block[nCntBlock].bUse = true;
			g_Block[nCntBlock].fWidth = fWidth;
			g_Block[nCntBlock].fHeight = fHeight;
			g_Block[nCntBlock].nLife = life;

			//対角線の長さ算出
			g_Block[nCntBlock].flength = sqrtf(fWidth * fWidth + fHeight * fHeight) / 2.0f;

			//対角線の角度を算出する
			g_Block[nCntBlock].rot2 = atan2f(fWidth, fHeight);

			//頂点座標更新
			pVtx[0].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (-D3DX_PI + g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength + g_Block[nCntBlock].move.x;
			pVtx[0].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (-D3DX_PI + g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength + g_Block[nCntBlock].move.y;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (D3DX_PI - g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength + g_Block[nCntBlock].move.x;
			pVtx[1].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (D3DX_PI - g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength + g_Block[nCntBlock].move.y;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (0.0f - g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength + g_Block[nCntBlock].move.x;
			pVtx[2].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (0.0f - g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength + g_Block[nCntBlock].move.y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_Block[nCntBlock].pos.x + sinf(g_Block[nCntBlock].rot.z + (0.0f + g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength + g_Block[nCntBlock].move.x;
			pVtx[3].pos.y = g_Block[nCntBlock].pos.y + cosf(g_Block[nCntBlock].rot.z + (0.0f + g_Block[nCntBlock].rot2)) * g_Block[nCntBlock].flength + g_Block[nCntBlock].move.y;
			pVtx[3].pos.z = 0.0f;

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f * (g_Block[nCntBlock].fWidth / BLOCK_WIDTH), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f * (g_Block[nCntBlock].fHeight / BLOCK_HEIGHT));
			pVtx[3].tex = D3DXVECTOR2(1.0f * (g_Block[nCntBlock].fWidth / BLOCK_WIDTH), 1.0f * (g_Block[nCntBlock].fHeight / BLOCK_HEIGHT));

			break;
		}

		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//----------------------------------------
//　ブロックの当たり判定(プレイヤー)
//----------------------------------------
bool CollisionBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight, BLOCK ** pblock)
{
	int nCntBlock;
	bool bIsLanding = false;		//着地しているかどうか

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{//ブロックが使用されている時
			if (pPosOld->x - (fWidth / 2) < g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2)
				&& pPosOld->x + (fWidth / 2) > g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2))
			{//プレイヤーのx座標がブロックに重なっている時
				if (pPosOld->y <= g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2 + g_Block[nCntBlock].move.y)
					&& pPos->y >= g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2))
				{//ブロックにめり込んだ時(上側から)
					bIsLanding = true;
					pPos->y = g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2);// -g_Block[nCntBlock].move.y;
					pMove->y = 0.0f;

					if (pblock != NULL)
					{
						*pblock = &g_Block[nCntBlock];
					}
				}
				else if (pPosOld->y - fHeight >= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2 - g_Block[nCntBlock].move.y)
					&& pPos->y - fHeight <= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2))
				{//ブロックにめり込んだ時(下側から)
					pPos->y = g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2) + fHeight;
					pMove->y = 0.0f;

					if (g_Block[nCntBlock].type == BLOCKTYPE_UP && g_Block[nCntBlock].nLife >= 0)
					{
						g_Block[nCntBlock].state = BLOCKSTATE_UP;
						g_Block[nCntBlock].nLife -= 1;
					}
					else if (g_Block[nCntBlock].type == BLOCKTYPE_ITEM && g_Block[nCntBlock].nLife != 0)
					{
						g_Block[nCntBlock].state = BLOCKSTATE_ITEM;
						g_Block[nCntBlock].nLife = 0;
					}
				}
			}
			if (pPos->y - fHeight <= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2)
					   && pPosOld->y > g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2))
			{//プレイヤーのy座標がブロックに重なっている時
				if (pPosOld->x + (fWidth / 2) <= g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2 + g_Block[nCntBlock].move.x)
					&& pPos->x + (fWidth / 2) >= g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2))
				{//ブロックにめり込んだ時(左側から)
					pPos->x = g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2) - (fWidth / 2);
					pMove->x = 0.0f;

					if (pblock != NULL)
					{
						*pblock = &g_Block[nCntBlock];
					}
				}
				else if (pPosOld->x - (fWidth / 2) >= g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2 - g_Block[nCntBlock].move.x)
					&& pPos->x - (fWidth / 2) <= g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2))
				{//ブロックにめり込んだ時(右側から)
					pPos->x = g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2) + (fWidth / 2);
					pMove->x = 0.0f;

					if (pblock != NULL)
					{
						*pblock = &g_Block[nCntBlock];
					}
				}
			}
		}
	}

	return bIsLanding;
}

//----------------------------------------
//　ブロックの当たり判定
//----------------------------------------
void CollisionBlock2(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight, BLOCKSTATE state)
{
	int nCntBlock;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{//ブロックが使用されている時
			if (BLOCKSTATE_UP == state)		//元BLOCKSTATE_ACT
			{
				if (pPosOld->y - (fHeight / 2) >= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2)
					&& pPos->y - (fHeight / 2) <= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2))
				{
					if (pPosOld->x - (fWidth / 2) < g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2)
						&& pPosOld->x + (fWidth / 2) > g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2))
					{//ブロックにめり込んだ時(下側から)
						pPos->y = g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2) + (fWidth / 2);
						pMove->y = 0.0f;
					}
				}
			}
			else if (BLOCKSTATE_RL == state)
			{
				if (pPosOld->x - (fWidth / 2) < g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2)
					&& pPosOld->x + (fWidth / 2) > g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2))
				{//プレイヤーのx座標がブロックに重なっている時
					if (pPosOld->y + (fHeight / 2 - g_Block[nCntBlock].move.y) <= g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2 + g_Block[nCntBlock].move.y)
						&& pPos->y + (fHeight / 2) >= g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2))
					{//ブロックにめり込んだ時(上側から)
						pPos->y = g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2) - (fHeight / 2);
						pMove->y = 0.0f;
					}
					else if (pPosOld->y - (fHeight / 2 + g_Block[nCntBlock].move.y) >= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2 - g_Block[nCntBlock].move.y)
						&& pPos->y - (fHeight / 2) <= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2))
					{//ブロックにめり込んだ時(下側から)
						pPos->y = g_Block[nCntBlock].pos.y + g_Block[nCntBlock].fHeight + (fHeight / 2);
						pMove->y = 0.0f;
					}
				}
				if (pPos->y - (fHeight / 2) <= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2)
					&& pPosOld->y + (fHeight / 2) >= g_Block[nCntBlock].pos.y - (g_Block[nCntBlock].fHeight / 2))
				{//プレイヤーのy座標がブロックに重なっている時
					if (pPosOld->x + (fWidth / 2 - g_Block[nCntBlock].move.x) <= g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2 + g_Block[nCntBlock].move.x)
						&& pPos->x + (fWidth / 2) >= g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2))
					{//ブロックにめり込んだ時(左側から)
						pPos->x = g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2) - (fWidth / 2);
						pMove->x = 0.0f;
					}
					else if (pPosOld->x - (fWidth / 2 + g_Block[nCntBlock].move.x) >= g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2 - g_Block[nCntBlock].move.x)
						&& pPos->x - (fWidth / 2) <= g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2))
					{//ブロックにめり込んだ時(右側から)
						pPos->x = g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2) + (fWidth / 2);
						pMove->x = 0.0f;
					}
				}
			}
		}
	}
}

//----------------------------------------
//　ブロックの上確認
//----------------------------------------
bool ActBlock(D3DXVECTOR3 * pos, float fWidth, float fHeight)
{
	bool bIsAct = false;
	int nCntBlock;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{
			if (pos->x - (fWidth / 2) < g_Block[nCntBlock].pos.x + (g_Block[nCntBlock].fWidth / 2)
				&& pos->x + (fWidth / 2) > g_Block[nCntBlock].pos.x - (g_Block[nCntBlock].fWidth / 2))
			{
				if (pos->y - (g_Block[nCntBlock].fHeight / 2) >= g_Block[nCntBlock].pos.y + (g_Block[nCntBlock].fHeight / 2))
				{
					bIsAct = true;
				}
			}
		}
	}

	return bIsAct;
}

//----------------------------------------
//　ブロックの情報
//----------------------------------------
BLOCK * GetBlock(void)
{
	return g_Block;
}

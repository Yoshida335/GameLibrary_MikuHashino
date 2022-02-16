#include "ladder.h"
#include "input.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureLadder = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLadder = NULL;
LADDER g_Ladder[MAX_LADDER];

//----------------------------------------------
//	梯子の初期化処理
//----------------------------------------------
void InitLadder(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntLadder;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\ladder.png",
		&g_pTextureLadder);

	//アイテムの初期化
	for (nCntLadder = 0; nCntLadder < MAX_LADDER; nCntLadder++)
	{
		g_Ladder[nCntLadder].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ladder[nCntLadder].fWidth = LADDER_WIDTH;
		g_Ladder[nCntLadder].fHeight = LADDER_HEIGHT;
		g_Ladder[nCntLadder].bUse = false;
		g_Ladder[nCntLadder].state = LADDER_STATE_OUT;
		g_Ladder[nCntLadder].type = LADDER_TYPE_0;
	}

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LADDER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLadder,
		NULL);

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffLadder->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLadder = 0; nCntLadder < MAX_LADDER; nCntLadder++)
	{
		//頂点座標更新
		pVtx[0].pos = D3DXVECTOR3(g_Ladder[nCntLadder].pos.x - (LADDER_WIDTH / 2), g_Ladder[nCntLadder].pos.y - (LADDER_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Ladder[nCntLadder].pos.x + (LADDER_WIDTH / 2), g_Ladder[nCntLadder].pos.y - (LADDER_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Ladder[nCntLadder].pos.x - (LADDER_WIDTH / 2), g_Ladder[nCntLadder].pos.y + (LADDER_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Ladder[nCntLadder].pos.x + (LADDER_WIDTH / 2), g_Ladder[nCntLadder].pos.y + (LADDER_HEIGHT / 2), 0.0f);

		//rhwの設定
		pVtx[0].rhm = 1.0f;
		pVtx[1].rhm = 1.0f;
		pVtx[2].rhm = 1.0f;
		pVtx[3].rhm = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);		//橙色
		pVtx[1].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLadder->Unlock();
}

//----------------------------------------
//　梯子の終了処理
//----------------------------------------
void UninitLadder(void)
{
	//テクスチャの破棄
	if (g_pTextureLadder != NULL)
	{
		g_pTextureLadder->Release();
		g_pTextureLadder = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffLadder != NULL)
	{
		g_pVtxBuffLadder->Release();
		g_pVtxBuffLadder = NULL;
	}
}

//----------------------------------------
//　梯子の更新処理
//----------------------------------------
void UpdateLadder(void)
{
	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffLadder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLadder = 0; nCntLadder < MAX_LADDER; nCntLadder++)
	{
		if (g_Ladder[nCntLadder].bUse == true)
		{//梯子が使用されている時
			switch (g_Ladder[nCntLadder].type)
			{
			case LADDER_TYPE_0:
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);		//橙色
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				break;

			case LADDER_TYPE_1:
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//赤色
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				break;
			}
		}

		pVtx += 4;
	}


	//頂点バッファをアンロックする
	g_pVtxBuffLadder->Unlock();

}

//----------------------------------------
//　梯子の描画処理
//----------------------------------------
void DrawLadder(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntLadder;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLadder, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLadder);

	for (nCntLadder = 0; nCntLadder < MAX_LADDER; nCntLadder++)
	{
		if (g_Ladder[nCntLadder].bUse == true)
		{//ブロックが使用されている
		 //ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntLadder * 4,
				2);
		}
	}
}

//----------------------------------------
//　梯子の設定
//----------------------------------------
void SetLadder(D3DXVECTOR3 pos, float fWidth, float fHeight, LADDERTYPE type)
{
	int nCntLadder;

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffLadder->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLadder = 0; nCntLadder < MAX_LADDER; nCntLadder++)
	{
		if (g_Ladder[nCntLadder].bUse == false)
		{
			g_Ladder[nCntLadder].pos = pos;
			g_Ladder[nCntLadder].fWidth = fWidth;
			g_Ladder[nCntLadder].fHeight = fHeight;
			g_Ladder[nCntLadder].bUse = true;
			g_Ladder[nCntLadder].type = type;

			//頂点座標設定
			pVtx[0].pos = D3DXVECTOR3(g_Ladder[nCntLadder].pos.x - (g_Ladder[nCntLadder].fWidth / 2), g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Ladder[nCntLadder].pos.x + (g_Ladder[nCntLadder].fWidth / 2), g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Ladder[nCntLadder].pos.x - (g_Ladder[nCntLadder].fWidth / 2), g_Ladder[nCntLadder].pos.y + (g_Ladder[nCntLadder].fHeight / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Ladder[nCntLadder].pos.x + (g_Ladder[nCntLadder].fWidth / 2), g_Ladder[nCntLadder].pos.y + (g_Ladder[nCntLadder].fHeight / 2), 0.0f);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f * (g_Ladder[nCntLadder].fWidth / LADDER_WIDTH), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f * (g_Ladder[nCntLadder].fHeight / LADDER_HEIGHT));
			pVtx[3].tex = D3DXVECTOR2(1.0f * (g_Ladder[nCntLadder].fWidth / LADDER_WIDTH), 1.0f * (g_Ladder[nCntLadder].fHeight / LADDER_HEIGHT));
			
			break;
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLadder->Unlock();
}

//----------------------------------------
//　梯子の当たり判定
//----------------------------------------
bool CollisionLadder(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight)
{
	int nCntLadder;
	bool bIsCatching = false;

	//　Wキーを押されている間にしか反応していないので、bIsLanding　みたいな着地しているとかの情報が足りない

	for (nCntLadder = 0; nCntLadder < MAX_LADDER; nCntLadder++)
	{
		if (g_Ladder[nCntLadder].bUse == true)
		{//梯子が使用されている時

			if (g_Ladder[nCntLadder].pos.x - (g_Ladder[nCntLadder].fWidth / 2) <= pos->x &&
				g_Ladder[nCntLadder].pos.x + (g_Ladder[nCntLadder].fWidth / 2) >= pos->x)
			{

				switch (g_Ladder[nCntLadder].type)
				{
				case LADDER_TYPE_0:
					if (g_Ladder[nCntLadder].pos.y + (g_Ladder[nCntLadder].fHeight / 2) > pos->y - fHeight &&
						g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2) < pos->y)
					{//登れる範囲(この範囲にいるとき梯子を上ることが可能)
						bIsCatching = true;
						pMove->y = 0.0f;

						if (posOld->y <= g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2)
							&& pos->y >= g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2))
						{//梯子にめり込んだ時(上側から)
							if (GetKeyboardPress(DIK_S) != true)
							{
								pos->y = g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2);// -g_Ladder[nCntLadder].move.y;
								pMove->y = 0.0f;
							}
						}
					}

					break;

				case LADDER_TYPE_1:
					if (g_Ladder[nCntLadder].pos.y + (g_Ladder[nCntLadder].fHeight / 2) > pos->y - fHeight &&
						g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2) < pos->y)
					{//登れる範囲(この範囲にいるとき梯子を上ることが可能)
						bIsCatching = true;
						pMove->y = 0.0f;

						if (posOld->y <= g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2)
							&& pos->y >= g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2))
						{//梯子にめり込んだ時(上側から)
							pos->y = g_Ladder[nCntLadder].pos.y - (g_Ladder[nCntLadder].fHeight / 2);// -g_Ladder[nCntLadder].move.y;
							pMove->y = 0.0f;
						}
					}
					break;
				}
			}

		}
	}

	return bIsCatching;
}

LADDER * GetLadder(void)
{
	return g_Ladder;
}

// 18 * 32
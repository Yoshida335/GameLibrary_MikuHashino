//----------------------------------------
//	アイテムの処理
//　Author：橋野幹生
//----------------------------------------
#include "item.h"
#include "score.h"
#include "sound.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureItem[ITEM_TYPE_MAX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;			//頂点バッファへのポインタ
ITEM g_Item[MAX_ITEM];
int g_nCntCoin;		//消えたコインの枚数

//----------------------------------------
//　アイテムの初期化処理
//----------------------------------------
void InitItem(void)
{
	g_nCntCoin = 0;		// 値を初期状態にする

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\coin000.png",
		&g_pTextureItem[ITEM_COIN]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\key001.png",
		&g_pTextureItem[ITEM_KEY]);

	//アイテムの初期化
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_Item[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
		g_Item[nCntItem].fWidth = ITEM_WIDTH;	//幅
		g_Item[nCntItem].fHeight = ITEM_HEIGHT;	//高さ
		g_Item[nCntItem].nCounterAnim = 0;		//アニメーションカウンタ
		g_Item[nCntItem].nPatternAnim = 0;		//アニメーションパターン
		g_Item[nCntItem].type = ITEM_COIN;	//種類
		g_Item[nCntItem].bUse = false;			//使っているかどうか
	}

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//頂点座標更新
		pVtx[0].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y + (ITEM_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y + (ITEM_HEIGHT / 2), 0.0f);

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
	g_pVtxBuffItem->Unlock();
}

//----------------------------------------
//　アイテムの終了処理
//----------------------------------------
void UninitItem(void)
{
	//テクスチャの破棄
	for (int i = 0; i < ITEM_TYPE_MAX; i++)
	{
		if (g_pTextureItem[i] != NULL)
		{
			g_pTextureItem[i]->Release();
			g_pTextureItem[i] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//----------------------------------------
//　アイテムの更新処理
//----------------------------------------
void UpdateItem(void)
{
	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{
			switch (g_Item[nCntItem].type)
			{
			case ITEM_COIN:
				g_Item[nCntItem].nCounterAnim += 1;

				if ((g_Item[nCntItem].nCounterAnim % 15) == 0)
				{//一定時間経過
				 //パターンNo.を更新する
					g_Item[nCntItem].nPatternAnim = (g_Item[nCntItem].nPatternAnim + 1) % 4;
				}

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.25f * g_Item[nCntItem].nPatternAnim, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.25f * g_Item[nCntItem].nPatternAnim + 0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.25f * g_Item[nCntItem].nPatternAnim, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.25f * g_Item[nCntItem].nPatternAnim + 0.25f, 1.0f);
				break;

			case ITEM_KEY:
				break;

			default:
				break;
			}
		}
		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//----------------------------------------
//　アイテムの描画処理
//----------------------------------------
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntItem;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{//ブロックが使用されている
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItem[g_Item[nCntItem].type]);

			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntItem * 4,
				2);
		}
	}
}

//----------------------------------------
//　アイテムの設定
//----------------------------------------
void SetItem(D3DXVECTOR3 pos, ITEM_TYPE type)
{
	int nCntItem;

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == false)
		{
			g_Item[nCntItem].pos = pos;
			g_Item[nCntItem].type = type;
			g_Item[nCntItem].bUse = true;

			//頂点座標更新
			pVtx[0].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y + (ITEM_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y + (ITEM_HEIGHT / 2), 0.0f);

			switch (g_Item[nCntItem].type)
			{
			case ITEM_COIN:
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);
				break;

			case ITEM_KEY:
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
				break;
			}
			break;
		}

		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//----------------------------------------
//　アイテムの情報
//----------------------------------------
ITEM * GetItem(void)
{
	return g_Item;
}

//----------------------------------------
//　アイテムの当たり判定
//----------------------------------------
void CollisionItem(D3DXVECTOR3 * pos, float fWidth, float fHeight, ITEM ** item)
{
	ITEM * pItem;
	pItem = GetItem();
	*item = NULL;

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (pItem->bUse == true)
		{
			if (pos->x + (fWidth / 2) >= pItem->pos.x - (pItem->fWidth / 2) &&
				pos->x - (fWidth / 2) <= pItem->pos.x + (pItem->fWidth / 2) &&
				pos->y - fHeight <= pItem->pos.y + (pItem->fHeight / 2) &&
				pos->y >= pItem->pos.y - (pItem->fHeight / 2))
			{//アイテムに当たったら
				DeleteItem(nCntItem);

				if (item != NULL)
				{
					*item = pItem;
				}
			}
		}
		pItem++;
	}
}

//----------------------------------------
//　アイテムの消去
//----------------------------------------
void DeleteItem(int nCntItem)
{
	//アイテムの非表示
	g_Item[nCntItem].bUse = false;

	//サウンドの再生
	PlaySound(SOUND_LABEL_SE_COIN);

	if (g_Item[nCntItem].type ==ITEM_COIN)
	{
		g_nCntCoin++;
	}
}

//----------------------------------------
//　コインの枚数
//----------------------------------------
int GetNumCoin(void)
{
	return g_nCntCoin;
}
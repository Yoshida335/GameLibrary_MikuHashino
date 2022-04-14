//----------------------------------------
//　ゴールの処理
//　Author：橋野幹生
//----------------------------------------
#include "goal.h"
#include "fade.h"
#include "block.h"
#include "sound.h"
#include "time.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureGoal = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;	//頂点バッファへのポインタ
Goal g_Goal[MAX_GOAL];
bool g_bGoal = false;

//----------------------------------------
//　ゴールの初期化処理
//----------------------------------------
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	g_bGoal = false;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\door.png",
		&g_pTextureGoal);

	//アイテムの初期化
	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		g_Goal[nCntGoal].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
		g_Goal[nCntGoal].fWidth = GOAL_WIDTH;			//幅
		g_Goal[nCntGoal].fHeight = GOAL_HEIGHT;			//高さ
		g_Goal[nCntGoal].state = GOAL_STATE_CLAUSE;		//状態
		g_Goal[nCntGoal].bUse = false;		//使っているかどうか
	}

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_GOAL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGoal,
		NULL);

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		//頂点座標更新
		pVtx[0].pos = D3DXVECTOR3(g_Goal[nCntGoal].pos.x - (GOAL_WIDTH / 2), g_Goal[nCntGoal].pos.y - GOAL_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Goal[nCntGoal].pos.x + (GOAL_WIDTH / 2), g_Goal[nCntGoal].pos.y - GOAL_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Goal[nCntGoal].pos.x - (GOAL_WIDTH / 2), g_Goal[nCntGoal].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Goal[nCntGoal].pos.x + (GOAL_WIDTH / 2), g_Goal[nCntGoal].pos.y, 0.0f);

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
	g_pVtxBuffGoal->Unlock();
}

//----------------------------------------
//　ゴールの終了処理
//----------------------------------------
void UninitGoal(void)
{
	//テクスチャの破棄
	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}
}

//----------------------------------------
//　ゴールの更新処理
//----------------------------------------
void UpdateGoal(void)
{
	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		if (g_Goal[nCntGoal].bUse == true)
		{
			switch (g_Goal[nCntGoal].state)
			{
			case GOAL_STATE_CLAUSE:

				break;

			case GOAL_STATE_OPEN:
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

				break;
			}
		}

		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffGoal->Unlock();
}

//----------------------------------------
//　ゴールの描画処理
//----------------------------------------
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntGoal;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		if (g_Goal[nCntGoal].bUse == true)
		{//ブロックが使用されている
		 //テクスチャの設定
			pDevice->SetTexture(0, g_pTextureGoal);

			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntGoal * 4,
				2);
		}
	}
}

//----------------------------------------
//　ゴールの設定
//----------------------------------------
void SetGoal(D3DXVECTOR3 pos)
{
	int nCntGoal;

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		if (g_Goal[nCntGoal].bUse == false)
		{//ブロックが使用されていない場合
			g_Goal[nCntGoal].pos = pos;
			g_Goal[nCntGoal].bUse = true;

			//頂点座標更新
			pVtx[0].pos = D3DXVECTOR3(g_Goal[nCntGoal].pos.x - (GOAL_WIDTH / 2), g_Goal[nCntGoal].pos.y - GOAL_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Goal[nCntGoal].pos.x + (GOAL_WIDTH / 2), g_Goal[nCntGoal].pos.y - GOAL_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Goal[nCntGoal].pos.x - (GOAL_WIDTH / 2), g_Goal[nCntGoal].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Goal[nCntGoal].pos.x + (GOAL_WIDTH / 2), g_Goal[nCntGoal].pos.y, 0.0f);

			break;
		}

		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffGoal->Unlock();
}

//----------------------------------------
//　ゴールの当たり判定
//----------------------------------------
void CollisionGoal(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, float fWidth, float fHeight, bool PlayerItem)
{
	int nCntGoal;

	for (nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
	{
		if (g_Goal[nCntGoal].bUse == true)
		{
			if (pos->y - fHeight <= g_Goal[nCntGoal].pos.y + (g_Goal[nCntGoal].fHeight / 2) &&
				pos->y >= g_Goal[nCntGoal].pos.y - (g_Goal[nCntGoal].fHeight / 2) &&
				posOld->y <= g_Goal[nCntGoal].pos.y + (g_Goal[nCntGoal].fHeight / 2))
			{
				if (pos->x + (fWidth / 2) >= g_Goal[nCntGoal].pos.x - (g_Goal[nCntGoal].fWidth / 2) &&
					pos->x - (fWidth / 2) <= g_Goal[nCntGoal].pos.x + (g_Goal[nCntGoal].fWidth / 2))
				{
					if (g_Goal[nCntGoal].state == GOAL_STATE_CLAUSE)
					{
						if (PlayerItem == true)
						{
							g_Goal[nCntGoal].state = GOAL_STATE_OPEN;
							 
							if (!g_bGoal)
							{
								//モード設定(ゲーム画面に移行)
								SetFade(MODE_RESULT_CLEAR);

								ClearTime();

								//サウンドの再生
								PlaySound(SOUND_LABEL_SE_DOOR);

								g_bGoal = true;
							}
						}
					}
				}
			}
		}
	}
}

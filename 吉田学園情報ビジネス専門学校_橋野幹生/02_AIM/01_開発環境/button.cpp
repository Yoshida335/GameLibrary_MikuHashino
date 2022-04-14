#include "button.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureButton = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffButton = NULL;
BUTTON g_Button[MAX_BUTTON];
int g_nCntLife;

//----------------------------------------
//　ボタンの初期化処理
//----------------------------------------
void InitButton(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntButton;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block000.jpg",
		&g_pTextureButton);

	//弾の初期化
	for (nCntButton = 0; nCntButton < MAX_BUTTON; nCntButton++)
	{
		g_Button[nCntButton].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//現在の位置
		g_Button[nCntButton].fWidth = BUTTON_WIDTH;						//幅
		g_Button[nCntButton].fHeight = BUTTON_HEIGHT;					//高さ
		g_Button[nCntButton].bUse = false;								//使っているかどうか
		g_Button[nCntButton].state = BUTTON_STATE_OFF;					//状態
		g_Button[nCntButton].nLife = 10;								//寿命
	}

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BUTTON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffButton,
		NULL);

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffButton->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntButton = 0; nCntButton < MAX_BUTTON; nCntButton++)
	{
		//頂点座標更新
		pVtx[0].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x - (BUTTON_WIDTH / 2), g_Button[nCntButton].pos.y - BUTTON_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x + (BUTTON_WIDTH / 2), g_Button[nCntButton].pos.y - BUTTON_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x - (BUTTON_WIDTH / 2), g_Button[nCntButton].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x + (BUTTON_WIDTH / 2), g_Button[nCntButton].pos.y, 0.0f);

		//rhwの設定
		pVtx[0].rhm = 1.0f;
		pVtx[1].rhm = 1.0f;
		pVtx[2].rhm = 1.0f;
		pVtx[3].rhm = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffButton->Unlock();
}

//----------------------------------------
//　ボタンの終了処理
//----------------------------------------
void UninitButton(void)
{
	//テクスチャの破棄
	if (g_pTextureButton != NULL)
	{
		g_pTextureButton->Release();
		g_pTextureButton = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffButton != NULL)
	{
		g_pVtxBuffButton->Release();
		g_pVtxBuffButton = NULL;
	}
}

//----------------------------------------
//　ボタンの更新処理
//----------------------------------------
void UpdateButton(void)
{
	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffButton->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntButton = 0; nCntButton < MAX_BUTTON; nCntButton++)
	{
		if (g_Button[nCntButton].bUse == true)
		{//使用されている場合
			switch (g_Button[nCntButton].state)
			{
			case BUTTON_STATE_OFF:
				g_Button[nCntButton].fHeight = BUTTON_HEIGHT;
				g_Button[nCntButton].nLife = BUTTON_LIFE;
				break;

			case BUTTON_STATE_ON:
				if (g_Button[nCntButton].nLife != 0)
				{//現在の時間が０じゃなかったら
					g_nCntLife--;
				}
				else if(g_Button[nCntButton].nLife <= 0)
				{
					g_Button[nCntButton].state = BUTTON_STATE_OFF;
				}
				if (g_nCntLife <= 0)
				{//カウント数が０だったら
					g_Button[nCntButton].nLife--;

					g_nCntLife = 60;
				}

				g_Button[nCntButton].fHeight = BUTTON_HEIGHT - 20.0f;
				break;
			}

			pVtx[0].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x - (g_Button[nCntButton].fWidth / 2), g_Button[nCntButton].pos.y - g_Button[nCntButton].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x + (g_Button[nCntButton].fWidth / 2), g_Button[nCntButton].pos.y - g_Button[nCntButton].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x - (g_Button[nCntButton].fWidth / 2), g_Button[nCntButton].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x + (g_Button[nCntButton].fWidth / 2), g_Button[nCntButton].pos.y, 0.0f);

		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffButton->Unlock();
}

//----------------------------------------
//　ボタンの描画処理
//----------------------------------------
void DrawButton(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntButton;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffButton, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	for (nCntButton = 0; nCntButton < MAX_BUTTON; nCntButton++)
	{
		if (g_Button[nCntButton].bUse == true)
		{//ブロックが使用されている
		 //ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntButton * 4,
				2);
		}
	}
}

//----------------------------------------
//　ボタンの設定
//----------------------------------------
void SetButton(D3DXVECTOR3 pos, float fWidth, float fHeight, int life)
{
	int nCntButton;

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffButton->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntButton = 0; nCntButton < MAX_BUTTON; nCntButton++)
	{
		if (g_Button[nCntButton].bUse == false)
		{//使用されていない場合
			g_Button[nCntButton].pos = pos;
			g_Button[nCntButton].fWidth = fWidth;
			g_Button[nCntButton].fHeight = fHeight;
			g_Button[nCntButton].state = BUTTON_STATE_OFF;
			g_Button[nCntButton].bUse = true;
			g_Button[nCntButton].nLife = life;

			pVtx[0].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x - (g_Button[nCntButton].fWidth / 2), g_Button[nCntButton].pos.y - g_Button[nCntButton].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x + (g_Button[nCntButton].fWidth / 2), g_Button[nCntButton].pos.y - g_Button[nCntButton].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x - (g_Button[nCntButton].fWidth / 2), g_Button[nCntButton].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Button[nCntButton].pos.x + (g_Button[nCntButton].fWidth / 2), g_Button[nCntButton].pos.y, 0.0f);
			break;
		}

		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffButton->Unlock();
}

//----------------------------------------
//　ボタンの当たり判定
//----------------------------------------
bool CollisionButton(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight)
{
	int nCntButton;
	bool bIsLanding = false;		//着地しているかどうか

	for (nCntButton = 0; nCntButton < MAX_BUTTON; nCntButton++)
	{
		if (g_Button[nCntButton].bUse == true)
		{//使用されている時
			if (pPosOld->x - (fWidth / 2) < g_Button[nCntButton].pos.x + (g_Button[nCntButton].fWidth / 2)
				&& pPosOld->x + (fWidth / 2) > g_Button[nCntButton].pos.x - (g_Button[nCntButton].fWidth / 2))
			{//プレイヤーのx座標がブロックに重なっている時
				if (pPosOld->y <= g_Button[nCntButton].pos.y - g_Button[nCntButton].fHeight
					&& pPos->y >= g_Button[nCntButton].pos.y - g_Button[nCntButton].fHeight)
				{//ブロックにめり込んだ時(上側から)
					bIsLanding = true;
					pPos->y = g_Button[nCntButton].pos.y - g_Button[nCntButton].fHeight;
					pMove->y = 0.0f;

					if (g_Button[nCntButton].state == BUTTON_STATE_OFF)
					{//OFF状態の時
						g_Button[nCntButton].state = BUTTON_STATE_ON;
					}
				}
				else if (pPosOld->y - fHeight >= g_Button[nCntButton].pos.y
					&& pPos->y - fHeight <= g_Button[nCntButton].pos.y)
				{//ブロックにめり込んだ時(下側から)
					pPos->y = g_Button[nCntButton].pos.y + fHeight;
					pMove->y = 0.0f;
				}
			}
			if (pPos->y - fHeight <= g_Button[nCntButton].pos.y
				&& pPosOld->y > g_Button[nCntButton].pos.y - g_Button[nCntButton].fHeight)
			{//プレイヤーのy座標がブロックに重なっている時
				if (pPosOld->x + (fWidth / 2) <= g_Button[nCntButton].pos.x - (g_Button[nCntButton].fWidth / 2)
					&& pPos->x + (fWidth / 2) >= g_Button[nCntButton].pos.x - (g_Button[nCntButton].fWidth / 2))
				{//ブロックにめり込んだ時(左側から)
					pPos->x = g_Button[nCntButton].pos.x - (g_Button[nCntButton].fWidth / 2) - (fWidth / 2);
					pMove->x = 0.0f;
				}
				else if (pPosOld->x - (fWidth / 2) >= g_Button[nCntButton].pos.x + (g_Button[nCntButton].fWidth / 2)
					&& pPos->x - (fWidth / 2) <= g_Button[nCntButton].pos.x + (g_Button[nCntButton].fWidth / 2))
				{//ブロックにめり込んだ時(右側から)
					pPos->x = g_Button[nCntButton].pos.x + (g_Button[nCntButton].fWidth / 2) + (fWidth / 2);
					pMove->x = 0.0f;
				}
			}
		}
	}

	return bIsLanding;
}
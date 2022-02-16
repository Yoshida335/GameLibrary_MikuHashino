#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "score.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;		//頂点バッファへのポインタ
int g_aRankScore[MAX_RANK + 1];			//ランキングスコア情報
D3DXVECTOR3 g_aRankpos[MAX_RANK][8];			//ランキング位置情報
int g_nCntY;

//----------------------------------------
//  ランキングの初期化設定処理
//----------------------------------------
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntRank;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number000.png",
		&g_pTextureRankScore);

	for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
	{
		for (nCntRank = 0; nCntRank < 8; nCntRank++)
		{
			g_aRankpos[g_nCntY][nCntRank] = D3DXVECTOR3(400.0f + (35.0f * nCntRank), 200.0f + (100.0f * g_nCntY), 0.0f);		//位置の初期
		}
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8 * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
	{
		for (nCntRank = 0; nCntRank < 8; nCntRank++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aRankpos[g_nCntY][nCntRank].x - 20.0f, g_aRankpos[g_nCntY][nCntRank].y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRankpos[g_nCntY][nCntRank].x + 20.0f, g_aRankpos[g_nCntY][nCntRank].y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRankpos[g_nCntY][nCntRank].x - 20.0f, g_aRankpos[g_nCntY][nCntRank].y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRankpos[g_nCntY][nCntRank].x + 20.0f, g_aRankpos[g_nCntY][nCntRank].y + 25.0f, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRankScore->Unlock();

	SetRanking();
}

//----------------------------------------
//  ランキングの終了処理
//----------------------------------------
void UninitRanking(void)
{
	if (g_pTextureRankScore != NULL)
	{
		g_pTextureRankScore->Release();
		g_pTextureRankScore = NULL;
	}

	if (g_pVtxBuffRankScore != NULL)
	{
		g_pVtxBuffRankScore->Release();
		g_pVtxBuffRankScore = NULL;
	}
}

//----------------------------------------
//　ランキングの更新処理
//----------------------------------------
void UpdateRanking(void)
{
	//if (GetKeyboardTrigger(DIK_RETURN) == true)
	//{//Enterキーが押された
	//	SetFade(MODE_TITLE);
	//}
}

//----------------------------------------
//  ランキングの描画処理
//----------------------------------------
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	int nCnt = 0;

	for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
	{
		for (int nCntRank = 0; nCntRank < 8; nCntRank++, nCnt++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureRankScore);

			//ポリゴンの設定
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}

//----------------------------------------
//  ランキングスコア情報の初期設定
//----------------------------------------
void ResetRanking(void)
{
	g_aRankScore[0] = 10000;
	g_aRankScore[1] = 8000;
	g_aRankScore[2] = 6000;
	g_aRankScore[3] = 4000;
	g_aRankScore[4] = 2000;
	g_aRankScore[5] = 0;
}

//----------------------------------------
//  ランキングの設定
//----------------------------------------
void SetRanking(void)
{
	int aPosTexU[MAX_RANK][8];		//各桁の数字を格納

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	//敵の情報の取得
	g_aRankScore[5] = GetScore();

	int aData[5];
	int nData;
	int nCount[2];

	for (nCount[1] = 0; nCount[1] < 5; nCount[1]++)
	{
		for (nCount[0] = nCount[1] + 1; nCount[0] < 6; nCount[0]++)
		{
			if (g_aRankScore[nCount[0]] > g_aRankScore[nCount[1]])
			{
				nData = g_aRankScore[nCount[0]];
				g_aRankScore[nCount[0]] = g_aRankScore[nCount[1]];
				g_aRankScore[nCount[1]] = nData;
			}
		}
	}

	for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
	{
		for (int nCntRank = 0; nCntRank < 8; nCntRank++)
		{
			aPosTexU[g_nCntY][0] = g_aRankScore[g_nCntY] % 100000000 / 10000000;
			aPosTexU[g_nCntY][1] = g_aRankScore[g_nCntY] % 10000000 / 1000000;
			aPosTexU[g_nCntY][2] = g_aRankScore[g_nCntY] % 1000000 / 100000;
			aPosTexU[g_nCntY][3] = g_aRankScore[g_nCntY] % 100000 / 10000;
			aPosTexU[g_nCntY][4] = g_aRankScore[g_nCntY] % 10000 / 1000;
			aPosTexU[g_nCntY][5] = g_aRankScore[g_nCntY] % 1000 / 100;
			aPosTexU[g_nCntY][6] = g_aRankScore[g_nCntY] % 100 / 10;
			aPosTexU[g_nCntY][7] = g_aRankScore[g_nCntY] % 10;
		}
	}

	for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
	{
		for (int nCntScore = 0; nCntScore < 8; nCntScore++)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[g_nCntY][nCntScore], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexU[g_nCntY][nCntScore] + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[g_nCntY][nCntScore], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexU[g_nCntY][nCntScore] + 0.1f, 1.0f);

			pVtx += 4;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRankScore->Unlock();
}


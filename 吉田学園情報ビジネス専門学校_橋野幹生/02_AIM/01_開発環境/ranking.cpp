//----------------------------------------
//	ランキングの処理
//　Author：橋野幹生
//----------------------------------------
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include <stdio.h>
#include <string.h>
#include "time.h"
#include "sound.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL;		//数字のテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;	//数字の頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRank_Bg = NULL;		//背景のテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank_Bg = NULL;	//背景の頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;			//順位のテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;		//順位の頂点バッファへのポインタ
int g_aRankScore[MAX_RANK + 1];				//ランキングスコア情報[最大ランキング数 + 獲得したSCORE入れる分]
D3DXVECTOR3 g_aRankpos[MAX_RANK][3];		//ランキング位置情報
int g_nCntY;								//最大ランキング数分回す用
D3DXVECTOR3 rankpos[MAX_RANK];
bool bRanking = false;

//----------------------------------------
//  ランキングの初期化設定処理
//----------------------------------------
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	bRanking = false;	// falseにする

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number_white.png",	//数字
		&g_pTextureRankScore);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\ranking.png",	//背景
		&g_pTextureRank_Bg);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\rank_number.png",	//順位
		&g_pTextureRank);

	for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
	{
		for (int nCntRank = 0; nCntRank < 3; nCntRank++)
		{
			g_aRankpos[g_nCntY][nCntRank] = D3DXVECTOR3(580.0f + (70.0f * nCntRank), 180.0f + (120.0f * g_nCntY), 0.0f);		//位置の初期
		}
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3 * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank_Bg,
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
	{
		for (int nCntRank = 0; nCntRank < 3; nCntRank++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aRankpos[g_nCntY][nCntRank].x - 40.0f, g_aRankpos[g_nCntY][nCntRank].y - 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRankpos[g_nCntY][nCntRank].x + 40.0f, g_aRankpos[g_nCntY][nCntRank].y - 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRankpos[g_nCntY][nCntRank].x - 40.0f, g_aRankpos[g_nCntY][nCntRank].y + 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRankpos[g_nCntY][nCntRank].x + 40.0f, g_aRankpos[g_nCntY][nCntRank].y + 50.0f, 0.0f);

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

	{
	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffRank_Bg->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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

	//頂点バッファをアンロックする
	g_pVtxBuffRank_Bg->Unlock();
	}

	for (int i = 0; i < MAX_RANK; i++)
	{
		rankpos[i] = D3DXVECTOR3(400.0f, 180.0f + (120.0f * i), 0.0f);
	}

	{
		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < MAX_RANK; i++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(rankpos[i].x - 70.0f, rankpos[i].y - 40.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(rankpos[i].x + 70.0f, rankpos[i].y - 40.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(rankpos[i].x - 70.0f, rankpos[i].y + 40.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(rankpos[i].x + 70.0f, rankpos[i].y + 40.0f, 0.0f);

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
			pVtx[0].tex = D3DXVECTOR2(0.0f, (1.0f / 5) * i);
			pVtx[1].tex = D3DXVECTOR2(1.0f, (1.0f / 5) * i);
			pVtx[2].tex = D3DXVECTOR2(0.0f, (1.0f / 5) * i + (1.0f / 5));
			pVtx[3].tex = D3DXVECTOR2(1.0f, (1.0f / 5) * i + (1.0f / 5));

			pVtx += 4;
		}

		//頂点バッファをアンロックする
		g_pVtxBuffRank->Unlock();
	}

	SetRanking();
}

//----------------------------------------
//  ランキングの終了処理
//----------------------------------------
void UninitRanking(void)
{
	//サウンドの停止
	StopSound();

	if (g_pTextureRankScore != NULL)
	{//テクスチャの破棄
		g_pTextureRankScore->Release();
		g_pTextureRankScore = NULL;
	}

	if (g_pVtxBuffRankScore != NULL)
	{//頂点バッファの破棄
		g_pVtxBuffRankScore->Release();
		g_pVtxBuffRankScore = NULL;
	}

	if (g_pTextureRank_Bg != NULL)
	{//テクスチャの破棄
		g_pTextureRank_Bg->Release();
		g_pTextureRank_Bg = NULL;
	}

	if (g_pVtxBuffRank_Bg != NULL)
	{//頂点バッファの破棄
		g_pVtxBuffRank_Bg->Release();
		g_pVtxBuffRank_Bg = NULL;
	}

	if (g_pTextureRank != NULL)
	{//テクスチャの破棄
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	if (g_pVtxBuffRank != NULL)
	{//頂点バッファの破棄
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}
}

//----------------------------------------
//　ランキングの更新処理
//----------------------------------------
void UpdateRanking(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (!bRanking)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_TITLE_BUTTON);

			//モード設定(ゲーム画面に移行)
			SetFade(MODE_TITLE);

			bRanking = true;
		}
	}
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
	pDevice->SetStreamSource(0, g_pVtxBuffRank_Bg, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRank_Bg);

	//ポリゴンの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	int nCnt = 0;

	for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
	{
		for (int nCntRank = 0; nCntRank < 3; nCntRank++, nCnt++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureRankScore);

			//ポリゴンの設定
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MAX_RANK; i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRank);

		//ポリゴンの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}
}

//----------------------------------------
//  ランキングスコア情報の初期設定(外部から読み込み)
//----------------------------------------
void ResetRanking(void)
{
	FILE *pFile;

	//ファイルを開く
	pFile = fopen("data\\ranking.txt", "r");		//(テキスト名を指定, モードを指定)

	if (pFile != NULL)
	{//ファイルが開けた場合
	 //ファイルから値を読み込む
		for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
		{//ランキング数分回す
			fscanf(pFile, "%d\n", &g_aRankScore[g_nCntY]);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("\n***　ファイルが開けませんでした　***\n");
	}
}

//----------------------------------------
//  ランキングの設定
//----------------------------------------
void SetRanking(void)
{
	int aPosTexU[MAX_RANK][3];		//各桁の数字を格納

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	int * nMyTime = GetTime();

	//敵の情報の取得
	g_aRankScore[5] = *nMyTime;

	int nData;
	int nCount[2];

	for (nCount[1] = 0; nCount[1] < 5; nCount[1]++)
	{
		for (nCount[0] = nCount[1] + 1; nCount[0] < 6; nCount[0]++)
		{
			if (g_aRankScore[nCount[0]] < g_aRankScore[nCount[1]])
			{
				nData = g_aRankScore[nCount[0]];
				g_aRankScore[nCount[0]] = g_aRankScore[nCount[1]];
				g_aRankScore[nCount[1]] = nData;
			}
		}
	}

	for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
	{
		for (int nCntRank = 0; nCntRank < 3; nCntRank++)
		{
			aPosTexU[g_nCntY][0] = g_aRankScore[g_nCntY] % 1000 / 100;
			aPosTexU[g_nCntY][1] = g_aRankScore[g_nCntY] % 100 / 10;
			aPosTexU[g_nCntY][2] = g_aRankScore[g_nCntY] % 10;
		}
	}

	for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
	{
		for (int nCntScore = 0; nCntScore < 3; nCntScore++)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[g_nCntY][nCntScore], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexU[g_nCntY][nCntScore] + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[g_nCntY][nCntScore], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexU[g_nCntY][nCntScore] + 0.1f, 1.0f);

			pVtx += 4;
		}
	}

	//ランキングのScoreを保存
	SaveRanking();

	//頂点バッファをアンロックする
	g_pVtxBuffRankScore->Unlock();
}

//----------------------------------------
//  ランキングのスコアを外部に保存
//----------------------------------------
void SaveRanking(void)
{
	FILE *pFile;

	//ファイルを開く
	pFile = fopen("data\\ranking.txt", "w");		//(テキスト名を指定, モードを指定)

	if (pFile != NULL)
	{//ファイルが開けた場合
	 //ファイルに値を書き出す
		for (g_nCntY = 0; g_nCntY < MAX_RANK; g_nCntY++)
		{
			fprintf(pFile, "%d\n", g_aRankScore[g_nCntY]);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("\n***　ファイルが開けませんでした　***\n");
	}
}

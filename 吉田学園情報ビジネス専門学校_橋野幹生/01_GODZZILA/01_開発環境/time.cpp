//----------------------------------------
//　タイムの処理
//　Author：橋野幹生
//----------------------------------------
#include "time.h"
#include "fade.h"
#include "input.h"
#include "map.h"
#include "enemy.h"
#include <time.h>

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;
D3DXVECTOR3 g_posTime[3];	//タイムの数
D3DXVECTOR3 g_posTT;
int g_nTime;				//現在のタイム
int g_nCntTime;				//カウントタイム
TIME g_TimeState;
int g_nOneTimer;			//一回だけ起動する用

//----------------------------------------
//  タイムの初期化設定処理
//----------------------------------------
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number.png",
		&g_pTextureTime);

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		g_posTime[nCntT] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期
	}
	g_posTT = D3DXVECTOR3(1050.0f, 100.0f, 0.0f);
	g_nTime = 31;					//タイムの初期化
	g_nCntTime = 60;
	g_TimeState = TIME_ON;
	g_nOneTimer = 0;

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	VERTEX_2D * pVtx;	//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		g_posTime[nCntT] = D3DXVECTOR3(35.0f * nCntT + (SCREEN_WIDTH / 2) - 35.0f, 40.0f, 0.0f);
	}

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posTime[nCntT].x - 20.0f, g_posTime[nCntT].y - 25.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime[nCntT].x + 20.0f, g_posTime[nCntT].y - 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime[nCntT].x - 20.0f, g_posTime[nCntT].y + 25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime[nCntT].x + 20.0f, g_posTime[nCntT].y + 25.0f, 0.0f);

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

	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();
}

//----------------------------------------
//　タイムの終了処理
//----------------------------------------
void UninitTime(void)
{
	//テクスチャの破棄
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//----------------------------------------
//  タイムの更新処理
//----------------------------------------
void UpdateTime(void)
{
	int nTimePos[3];

	int nWork = 0;

	switch (g_TimeState)
	{
	case TIME_ON:
		if (g_nTime != 0)
		{//現在の時間が０じゃなかったら
			g_nCntTime--;
		}

		if (g_nCntTime <= 0)
		{//カウント数が０だったら
			g_nTime--;

			if (g_nTime % 10 == 0)
			{
				SetPos * pSetEnemyPos = GetSetPos();

				for (int i = 0; i < 4; i++)
				{
					SetEnemy(pSetEnemyPos->Setpos[i], D3DXVECTOR3(0.0f, 0.0f, 0.0f), TYPE_ENEMY_01, 1);
				}
			}

			g_nCntTime = 60;
		}

		nTimePos[0] = g_nTime % 1000 / 100;
		nTimePos[1] = g_nTime % 100 / 10;
		nTimePos[2] = g_nTime % 10;

		VERTEX_2D * pVtx;	//頂点情報へのポインタ

		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntT = 0; nCntT < 3; nCntT++)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.1f * nTimePos[nCntT], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f * nTimePos[nCntT] + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * nTimePos[nCntT], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f * nTimePos[nCntT] + 0.1f, 1.0f);

			pVtx += 4;
		}

		//頂点バッファをアンロックする
		g_pVtxBuffTime->Unlock();

		if (g_nTime <= 0)
		{//タイムが０以下になったら
			g_TimeState = TIME_OFF;
		}

		break;

	case TIME_OFF:
		if(g_nOneTimer == 0)
		{
			//モード設定(リザルト画面に移行)
			SetFade(MODE_RESULT);

			g_nOneTimer = 1;
		}

		break;
	}
}

//----------------------------------------
//  タイムの描画処理
//----------------------------------------
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	// Zバッファに関して
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTime);

		//ポリゴンの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntT * 4, 2);
	}

	// Zバッファを元に戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			//規定値：値が現在のピクセルの値以下の場合は、新しいピクセルを受け入れる。
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

//----------------------------------------
//  タイムの情報
//----------------------------------------
int * GetTime(void)
{
	return &g_nTime;
}

//----------------------------------------
//  タイムの加算
//----------------------------------------
void AddTime(int nTime)
{
	g_nTime += nTime;
}
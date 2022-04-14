//----------------------------------------
//	タイムの処理
//　Author：橋野幹生
//----------------------------------------
#include "time.h"
#include "fade.h"
#include "input.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;		//タイマーのテクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureStartTime = NULL;	//タイマーのテクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureStart = NULL;		//スタートのテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStartTime = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStart = NULL;
D3DXVECTOR3 g_posTime[3];	//タイムの数
START g_StartTime;			//スタートのタイム
START g_StartText;			//スタート
int g_nTime;				//現在のタイム
int g_nCntTime;				//カウントタイム
TIMESTATE g_TimeState;
bool g_bTimer = 0;
int g_clearTime;
int g_nMaxTime;

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

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number_123.png",
		&g_pTextureStartTime);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\start.png",
		&g_pTextureStart);

	//タイマーの初期化
	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		g_posTime[nCntT] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期
	}
	g_nTime = 0;					//タイムの初期化
	g_nCntTime = 60;				//フレーム数
	g_TimeState.state = TIME_OFF;	//タイマーの状態
	g_bTimer = false;	//一回だけ起動
	g_clearTime = 0;	//クリアタイム保存用
	g_nMaxTime = 0;		//タイマーの最大タイム数保存用

	//スタートカウントダウン
	g_StartTime.pos = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f);		//位置の初期
	g_StartTime.bUse = false;	//使っているかどうか
	g_StartTime.time = 2;		//使用時間

	//スタート文字
	g_StartText.pos = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f);		//位置の初期
	g_StartText.bUse = false;	//使っているかどうか
	g_StartText.time = 1;		//使用時間

	//頂点バッファの設定
	//タイマー
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);
	//スタートカウントダウン
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStartTime,
		NULL);
	//スタート文字
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStart,
		NULL);

	VERTEX_2D * pVtx;	//頂点情報へのポインタ

	{//タイマー
		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntT = 0; nCntT < 3; nCntT++)
		{
			g_posTime[nCntT] = D3DXVECTOR3(35.0f * nCntT + (SCREEN_WIDTH / 2) - 35.0f, TIME_HEIGHT, 0.0f);
		}

		for (int nCntT = 0; nCntT < 3; nCntT++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_posTime[nCntT].x - TIME_WIDTH, g_posTime[nCntT].y - TIME_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posTime[nCntT].x + TIME_WIDTH, g_posTime[nCntT].y - TIME_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posTime[nCntT].x - TIME_WIDTH, g_posTime[nCntT].y + TIME_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posTime[nCntT].x + TIME_WIDTH, g_posTime[nCntT].y + TIME_HEIGHT, 0.0f);

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

	{//スタートカウントダウン
		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffStartTime->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_StartTime.pos.x - STARTTIME_WIDTH, g_StartTime.pos.y - STARTTIME_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_StartTime.pos.x + STARTTIME_WIDTH, g_StartTime.pos.y - STARTTIME_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_StartTime.pos.x - STARTTIME_WIDTH, g_StartTime.pos.y + STARTTIME_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_StartTime.pos.x + STARTTIME_WIDTH, g_StartTime.pos.y + STARTTIME_HEIGHT, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2((1.0f / 3.0f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((1.0f / 3.0f), 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffStartTime->Unlock();
	}

	{//スタート文字
		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffStart->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_StartText.pos.x - 300.0f, g_StartText.pos.y - STARTTIME_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_StartText.pos.x + 300.0f, g_StartText.pos.y - STARTTIME_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_StartText.pos.x - 300.0f, g_StartText.pos.y + STARTTIME_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_StartText.pos.x + 300.0f, g_StartText.pos.y + STARTTIME_HEIGHT, 0.0f);

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
		g_pVtxBuffStart->Unlock();
	}
}

//----------------------------------------
//　タイムの終了処理
//----------------------------------------
void UninitTime(void)
{
	if (g_pTextureTime != NULL)
	{//テクスチャの破棄
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	if (g_pTextureStartTime != NULL)
	{//テクスチャの破棄
		g_pTextureStartTime->Release();
		g_pTextureStartTime = NULL;
	}

	if (g_pTextureStart != NULL)
	{//テクスチャの破棄
		g_pTextureStart->Release();
		g_pTextureStart = NULL;
	}

	if (g_pVtxBuffTime != NULL)
	{//頂点バッファの破棄
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}

	if (g_pVtxBuffStartTime != NULL)
	{//頂点バッファの破棄
		g_pVtxBuffStartTime->Release();
		g_pVtxBuffStartTime = NULL;
	}
}

//----------------------------------------
//  タイムの更新処理
//----------------------------------------
void UpdateTime(void)
{
	int nTimePos[3];
	int nStartTimePos;

	VERTEX_2D * pVtx;	//頂点情報へのポインタ

	switch (g_TimeState.state)
	{
	case TIME_ON:
		if (g_nTime != 0)
		{//現在の時間が０じゃなかったら
			g_nCntTime--;
		}
		else if (g_nTime <= 0)
		{
			if (!g_bTimer)
			{
				ClearTime();

				//モード設定(ゲーム画面に移行)
				SetFade(MODE_RESULT_OVER);

				g_bTimer = true;
			}
		}
		if (g_nCntTime <= 0)
		{//カウント数が０だったら
			g_nTime--;
			g_nCntTime = 60;
			g_clearTime++;
		}

		nTimePos[0] = g_nTime % 1000 / 100;
		nTimePos[1] = g_nTime % 100 / 10;
		nTimePos[2] = g_nTime % 10;

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

#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//モード設定(ゲーム画面に移行)
			SetFade(MODE_RESULT_OVER);
		}
#endif
		break;

	case TIME_OFF:
		g_StartTime.bUse = true;

		if (g_StartTime.time >= 0)
		{//現在の時間が０じゃなかったら
			g_nCntTime--;

			nStartTimePos = g_StartTime.time % 10;

			//頂点情報をロックし、頂点情報へのポインタを取得
			g_pVtxBuffStartTime->Lock(0, 0, (void**)&pVtx, 0);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2((1.0f / 3.0f) * nStartTimePos, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((1.0f / 3.0f) * nStartTimePos + (1.0f / 3.0f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2((1.0f / 3.0f) * nStartTimePos, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((1.0f / 3.0f) * nStartTimePos + (1.0f / 3.0f), 1.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffStartTime->Unlock();
		}
		else
		{
			g_StartTime.bUse = false;
			g_TimeState.state = TIME_START;
		}
		if (g_nCntTime <= 0)
		{//カウント数が０だったら

			g_StartTime.time--;
			g_nCntTime = 60;
		}

		break;

	case TIME_START:
		g_StartText.bUse = true;

		if (g_StartText.time != 0)
		{//現在の時間が０じゃなかったら
			g_nCntTime--;
		}
		else if (g_StartText.time <= 0)
		{
			g_StartText.bUse = false;
			g_TimeState.state = TIME_ON;
		}

		if (g_nCntTime <= 0)
		{//カウント数が０だったら
			g_StartText.time--;
			g_nCntTime = 60;
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

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTime);

	//ポリゴンの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTime);

		//ポリゴンの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntT * 4, 2);
	}


	if (g_StartTime.bUse == true)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffStartTime, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureStartTime);

		//ポリゴンの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	if (g_StartText.bUse == true)
	{//使用されていたら
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffStart, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureStart);

		//ポリゴンの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//----------------------------------------
//	タイマーの設定
//----------------------------------------
void SetTime(int nTime)
{
	g_nTime = nTime;
	g_nMaxTime = nTime;
}

//----------------------------------------
//	タイマーの状態情報
//----------------------------------------
TIMESTATE * GetStartTime(void)
{
	return &g_TimeState;
}

//----------------------------------------
//	タイマーの時間の情報
//----------------------------------------
int * GetTime(void)
{
	return &g_clearTime;
}

//----------------------------------------
//	クリアしたときのタイマーの処理
//----------------------------------------
void ClearTime(void)
{
	g_clearTime = (g_nMaxTime - g_clearTime);
}
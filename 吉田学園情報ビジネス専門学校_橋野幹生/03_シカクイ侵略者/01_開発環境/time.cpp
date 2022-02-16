#include "time.h"
#include "fade.h"
#include "enemy.h"
#include "input.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;
LPDIRECT3DTEXTURE9 g_pTextureTT = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTT = NULL;
D3DXVECTOR3 g_posTime[3];	//タイムの数
D3DXVECTOR3 g_posTT;
int g_nTime;				//現在のタイム
int g_nCntTime;				//カウントタイム
TIME g_TimeState;
int g_nCnt;					//一回だけ起動する用

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

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\TIME.png",
		&g_pTextureTT);

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		g_posTime[nCntT] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期
	}
	g_posTT = D3DXVECTOR3(1050.0f, 100.0f, 0.0f);
	g_nTime = 60;					//タイムの初期化
	g_nCntTime = 60;
	g_TimeState = TIME_ON;
	g_nCnt = 0;

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTT,
		NULL);

	VERTEX_2D * pVtx;	//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		g_posTime[nCntT] = D3DXVECTOR3(35.0f * nCntT + 990.0f, 170.0f, 0.0f);
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

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffTT->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posTT.x - 80.0f, g_posTT.y - 25.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posTT.x + 80.0f, g_posTT.y - 25.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posTT.x - 80.0f, g_posTT.y + 25.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posTT.x + 80.0f, g_posTT.y + 25.0f, 0.0f);

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
	g_pVtxBuffTT->Unlock();
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

	if (g_pTextureTT != NULL)
	{
		g_pTextureTT->Release();
		g_pTextureTT = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}

	if (g_pVtxBuffTT != NULL)
	{
		g_pVtxBuffTT->Release();
		g_pVtxBuffTT = NULL;
	}
}

//----------------------------------------
//  タイムの更新処理
//----------------------------------------
void UpdateTime(void)
{
	int nTimePos[3];

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

			g_nCntTime = 60;

			if (g_nTime == 55)
			{
				//敵の設定
				SetEnemy(D3DXVECTOR3(100.0f, 130.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(300.0f,  50.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(500.0f, 130.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(700.0f,  50.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(900.0f, 130.0f, 0.0f), ENEMY_TYPE_000);
			}

			if (g_nTime == 45)
			{
				//敵の設定
				SetEnemy(D3DXVECTOR3( 80.0f, 100.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(280.0f, 180.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(500.0f, 250.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(680.0f, 180.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(880.0f, 100.0f, 0.0f), ENEMY_TYPE_000);
			}

			if (g_nTime == 35)
			{
				//敵の設定
				SetEnemy(D3DXVECTOR3( 60.0f, 80.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(300.0f, 180.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(400.0f, 180.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(500.0f, 180.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(600.0f, 180.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(700.0f, 180.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(900.0f, 80.0f, 0.0f), ENEMY_TYPE_000);
			}

			if (g_nTime == 25)
			{
				//敵の設定
				SetEnemy(D3DXVECTOR3(100.0f, 130.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(300.0f, 50.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(500.0f, 130.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(700.0f, 50.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(900.0f, 130.0f, 0.0f), ENEMY_TYPE_000);
			}

			if (g_nTime == 15)
			{
				//敵の設定
				SetEnemy(D3DXVECTOR3( 80.0f, 150.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(280.0f, 80.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(500.0f, 80.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(680.0f, 80.0f, 0.0f), ENEMY_TYPE_000);
				SetEnemy(D3DXVECTOR3(880.0f, 150.0f, 0.0f), ENEMY_TYPE_000);
			}
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
		{
			g_TimeState = TIME_OFF;
		}

#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//モード設定(ゲーム画面に移行)
			SetFade(MODE_RESULT);
		}
#endif

		break;

	case TIME_OFF:
		if(g_nCnt == 0)
		{
			//モード設定(ゲーム画面に移行)
			SetFade(MODE_RESULT);

			g_nCnt = 1;
		}

		break;
	}

}//----------------------------------------
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

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTime);

		//ポリゴンの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntT * 4, 2);
	}

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTT, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTT);

	//ポリゴンの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

#include "stage.h"
#include "enemy.h"
#include "fade.h"
#include "explosion.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureStage = {};				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStage = NULL;		//頂点バッファへのポインタ
Stage g_Stage;

//----------------------------------------
//  ステージの初期化設定処理
//----------------------------------------
void InitStage(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\STAGE.png",
		&g_pTextureStage);

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStage,
		NULL);

	//初期化
	g_Stage.pos = D3DXVECTOR3(480.0f, SCREEN_HEIGHT - 40.0f, 0.0f);
	g_Stage.nLife = 10;
	g_Stage.state = STAGESTATE_NOMAL;
	g_Stage.bUse = false;
	g_Stage.nCounterState = 0;

	VERTEX_2D * pVtx;	//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Stage.pos.x - 480.0f, g_Stage.pos.y - 40.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Stage.pos.x + 480.0f, g_Stage.pos.y - 40.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Stage.pos.x - 480.0f, g_Stage.pos.y + 40.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Stage.pos.x + 480.0f, g_Stage.pos.y + 40.0f, 0.0f);

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

	//頂点バッファをアンロックする
	g_pVtxBuffStage->Unlock();
}

//----------------------------------------
//　ステージの終了処理
//----------------------------------------
void UninitStage(void)
{
	//テクスチャの破棄
	if (g_pTextureStage != NULL)
	{
		g_pTextureStage->Release();
		g_pTextureStage = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffStage != NULL)
	{
		g_pVtxBuffStage->Release();
		g_pVtxBuffStage = NULL;
	}
}

//----------------------------------------
//  ステージの更新処理
//----------------------------------------
void UpdateStage(void)
{
	//VERTEX_2D * pVtx;

	////頂点情報をロックし、頂点情報へのポインタを取得
	//g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

	//	if (g_Stage.bUse == true)
	//	{//ステージが使用されている
	//		switch (g_Stage.state)
	//		{
	//		case STAGESTATE_NOMAL:
	//			//頂点座標の設定
	//			pVtx[0].pos = D3DXVECTOR3(g_Stage.pos.x - 480.0f, g_Stage.pos.y - 40.0f, 0.0f);
	//			pVtx[1].pos = D3DXVECTOR3(g_Stage.pos.x + 480.0f, g_Stage.pos.y - 40.0f, 0.0f);
	//			pVtx[2].pos = D3DXVECTOR3(g_Stage.pos.x - 480.0f, g_Stage.pos.y + 40.0f, 0.0f);
	//			pVtx[3].pos = D3DXVECTOR3(g_Stage.pos.x + 480.0f, g_Stage.pos.y + 40.0f, 0.0f);

	//			break;

	//		case STAGESTATE_DAMAGE:
	//			g_Stage.nCounterState--;

	//			if (g_Stage.nCounterState <= 0)
	//			{
	//				g_Stage.state = STAGESTATE_NOMAL;

	//				//頂点カラーの設定
	//				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//			}

	//			break;
	//		}
	//	}

	////頂点バッファをアンロックする
	//g_pVtxBuffStage->Unlock();
}

//----------------------------------------
//  ステージの描画処理
//----------------------------------------
void DrawStage(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStage, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureStage);

	//ポリゴンの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//----------------------------------------
//  ステージのヒット処理
//----------------------------------------
void HitStage(int nDamage)
{
	g_Stage.nLife -= nDamage;

	if (g_Stage.nLife <= 0)
	{
		//モード設定(ゲーム画面に移行)
		//SetFade(MODE_RESULT);
	}
	else
	{
		g_Stage.state = STAGESTATE_DAMAGE;
		g_Stage.nCounterState = 5;

		VERTEX_2D * pVtx;

		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffStage->Unlock();
	}
}

//----------------------------------------
//  ステージの設定
//----------------------------------------
Stage * GetStage(void)
{
	return &g_Stage;
}


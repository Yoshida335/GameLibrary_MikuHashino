//----------------------------------------
//　チュートリアル画面の処理
//　Author：橋野幹生
//----------------------------------------
#include "rule.h"
#include "game.h"
#include "enemy.h"
#include "input.h"
#include "sound.h"
#include "fade.h"

LPDIRECT3DTEXTURE9 g_pTextureRule = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRule = NULL;		//頂点バッファへのポインタ
bool g_bRule = false;

//----------------------------------------
//  チュートリアル画面の初期化処理
//----------------------------------------
void InitRule(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\rule.png",
		&g_pTextureRule);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRule,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffRule->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffRule->Unlock();

	g_bRule = false;
}

//----------------------------------------
//  チュートリアル画面の終了処理
//----------------------------------------
void UninitRule(void)
{
	//サウンドの停止
	StopSound();

	//テクスチャの破棄
	if (g_pTextureRule != NULL)
	{
		g_pTextureRule->Release();
		g_pTextureRule = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRule != NULL)
	{
		g_pVtxBuffRule->Release();
		g_pVtxBuffRule = NULL;
	}
}

//----------------------------------------
//  チュートリアル画面の更新処理
//----------------------------------------
void UpdateRule(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (!g_bRule)
		{
			//モード設定(ゲーム画面に移行)
			SetFade(MODE_GAME);

			g_bRule = true;
		}
	}
}

//----------------------------------------
//  チュートリアル画面の描画処理
//----------------------------------------
void DrawRule(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRule, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRule);

	//ポリゴンの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

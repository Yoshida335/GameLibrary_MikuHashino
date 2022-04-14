#include "result.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

LPDIRECT3DTEXTURE9 g_pTextureResultClear = {};				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultClear = NULL;		//頂点バッファへのポインタ

void InitResultClear(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\result_clear.png",
		&g_pTextureResultClear);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultClear,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultClear->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffResultClear->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM_RESULT);
}

void UninitResultClear(void)
{
	//テクスチャの破棄
	if (g_pTextureResultClear != NULL)
	{
		g_pTextureResultClear->Release();
		g_pTextureResultClear = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResultClear != NULL)
	{
		g_pVtxBuffResultClear->Release();
		g_pVtxBuffResultClear = NULL;
	}
}

void UpdateResultClear(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		//モード設定(ゲーム画面に移行)
		SetFade(MODE_RANKING);
	}
}

void DrawResultClear(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultClear, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResultClear);

	//ポリゴンの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

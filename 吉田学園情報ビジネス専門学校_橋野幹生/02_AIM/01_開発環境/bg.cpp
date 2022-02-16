#include "bg.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBG[2] = {};			//テクスチャ(2枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG[2] = {};		//頂点バッファへのポインタ
float g_aPosTexV;									//テクスチャ座標の開始位置(V値)

//----------------------------------------
//  背景の初期化設定処理
//----------------------------------------
void InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_aPosTexV = 0.0f;

	//テクスチャの読み込み
	//D3DXCreateTextureFromFile(
	//	pDevice,
	//	"data\\TEXTURE\\sky000.jpg",
	//	&g_pTextureBG[0]);
	//
	//D3DXCreateTextureFromFile(
	//	pDevice,
	//	"data\\TEXTURE\\mountain000.png",
	//	&g_pTextureBG[1]);

	//頂点バッファの生成
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffBG[nCnt],
			NULL);
	}

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG[0]->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].tex = D3DXVECTOR2(g_aPosTexV, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_aPosTexV + 0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aPosTexV, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aPosTexV + 0.25f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffBG[0]->Unlock();

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG[1]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT - 200.0f, 0.0f);
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
	g_pVtxBuffBG[1]->Unlock();
}

//----------------------------------------
//  背景の終了処理
//----------------------------------------
void UninitBG(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureBG[nCnt] != NULL)
		{
			g_pTextureBG[nCnt]->Release();
			g_pTextureBG[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_pVtxBuffBG[nCnt] != NULL)
		{
			g_pVtxBuffBG[nCnt]->Release();
			g_pVtxBuffBG[nCnt] = NULL;
		}
	}
}

//----------------------------------------
//　背景の更新処理
//----------------------------------------
void UpdateBG(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG[0]->Lock(0, 0, (void**)&pVtx, 0);

	g_aPosTexV += 0.0001f;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_aPosTexV, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_aPosTexV + 0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aPosTexV, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aPosTexV + 0.25f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffBG[0]->Unlock();
}

//----------------------------------------
//  背景の描画処理
//----------------------------------------
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffBG[nCnt], 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBG[nCnt]);

		//ポリゴンの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

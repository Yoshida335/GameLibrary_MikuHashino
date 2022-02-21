#include "life.h"
#include "main.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;
LPDIRECT3DTEXTURE9 g_pTextureLifeT = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLifeT = NULL;
D3DXVECTOR3 g_posLife[3];	//タイムの数
D3DXVECTOR3 g_posLifeT;
int nLifeHP;

//----------------------------------------
//  タイムの初期化設定処理
//----------------------------------------
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number.png",
		&g_pTextureLife);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\Life.png",
		&g_pTextureLifeT);

	for (int nCnLifeT = 0; nCnLifeT < 3; nCnLifeT++)
	{
		g_posLife[nCnLifeT] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期
	}
	g_posLifeT = D3DXVECTOR3(1050.0f, 530.0f, 0.0f);
	nLifeHP = 10;

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLifeT,
		NULL);

	VERTEX_2D * pVtx;	//頂点情報へのポインタ

						//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnLifeT = 0; nCnLifeT < 3; nCnLifeT++)
	{
		g_posLife[nCnLifeT] = D3DXVECTOR3(35.0f * nCnLifeT + 990.0f, 600.0f, 0.0f);
	}

	for (int nCnLifeT = 0; nCnLifeT < 3; nCnLifeT++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posLife[nCnLifeT].x - 20.0f, g_posLife[nCnLifeT].y - 25.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posLife[nCnLifeT].x + 20.0f, g_posLife[nCnLifeT].y - 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posLife[nCnLifeT].x - 20.0f, g_posLife[nCnLifeT].y + 25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posLife[nCnLifeT].x + 20.0f, g_posLife[nCnLifeT].y + 25.0f, 0.0f);

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
	g_pVtxBuffLife->Unlock();

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffLifeT->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posLifeT.x - 80.0f, g_posLifeT.y - 25.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posLifeT.x + 80.0f, g_posLifeT.y - 25.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posLifeT.x - 80.0f, g_posLifeT.y + 25.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posLifeT.x + 80.0f, g_posLifeT.y + 25.0f, 0.0f);

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
	g_pVtxBuffLifeT->Unlock();
}

//----------------------------------------
//　タイムの終了処理
//----------------------------------------
void UninitLife(void)
{
	//テクスチャの破棄
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	if (g_pTextureLifeT != NULL)
	{
		g_pTextureLifeT->Release();
		g_pTextureLifeT = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}

	if (g_pVtxBuffLifeT != NULL)
	{
		g_pVtxBuffLifeT->Release();
		g_pVtxBuffLifeT = NULL;
	}
}

//----------------------------------------
//  タイムの更新処理
//----------------------------------------
void UpdateLife(void)
{
	int aPosTexU[3];					//各桁の数字を格納

	aPosTexU[0] = nLifeHP % 1000 / 100;
	aPosTexU[1] = nLifeHP % 100 / 10;
	aPosTexU[2] = nLifeHP % 10;

	VERTEX_2D * pVtx;	//頂点情報へのポインタ

						//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLife = 0; nCntLife < 3; nCntLife++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntLife], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntLife] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntLife], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntLife] + 0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();
}

//----------------------------------------
//  タイムの描画処理
//----------------------------------------
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnLifeT = 0; nCnLifeT < 3; nCnLifeT++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureLife);

		//ポリゴンの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnLifeT * 4, 2);
	}

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLifeT, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLifeT);

	//ポリゴンの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//----------------------------------------
//  スコアの設定処理
//----------------------------------------
void SetLife(int nLife)
{
	nLifeHP -= nLife;
}

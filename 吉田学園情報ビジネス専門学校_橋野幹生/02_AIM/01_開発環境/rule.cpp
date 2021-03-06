//----------------------------------------
//	ルールの処理
//　Author：橋野幹生
//----------------------------------------
#include "rule.h"
#include "input.h"
#include "fade.h"
#include "select.h"
#include "sound.h"

LPDIRECT3DTEXTURE9 g_pTextureRule[2] = {};				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRule = NULL;			//頂点バッファへのポインタ
bool g_bRule = false;

//----------------------------------------
//  ルールの初期化設定処理
//----------------------------------------
void InitRule(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	g_bRule = false;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\Rule_0.png",
		&g_pTextureRule[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\Rule_1.png",
		&g_pTextureRule[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRule,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
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
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRule->Unlock();
}

//----------------------------------------
//  ルールの終了処理
//----------------------------------------
void UninitRule(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_pTextureRule[nCnt] != NULL)
		{//テクスチャの破棄
			g_pTextureRule[nCnt]->Release();
			g_pTextureRule[nCnt] = NULL;
		}
	}

	if (g_pVtxBuffRule != NULL)
	{//頂点バッファの破棄
		g_pVtxBuffRule->Release();
		g_pVtxBuffRule = NULL;
	}
}

//----------------------------------------
//  ルールの更新設定処理
//----------------------------------------
void UpdateRule(void)
{
	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		if (!g_bRule)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_TITLE_BUTTON);

			//モード設定(セレクト画面に移行)
			SetFade(MODE_GAME);

			g_bRule = true;
		}
	}
}

//----------------------------------------
//  ルールの描画処理
//----------------------------------------
void DrawRule(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	STAGE_No * pSelect;
	pSelect = GetSelect();	//ステージの番号を取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRule, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRule[*pSelect]);

	//ポリゴンの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
}

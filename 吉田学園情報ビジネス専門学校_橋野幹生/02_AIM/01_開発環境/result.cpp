//----------------------------------------
//	リザルト画面の処理
//　Author：橋野幹生
//----------------------------------------
#include "result.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureResult[RESULT_TYPE_MAX] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//頂点バッファへのポインタ
Result_Type g_ResultType = RESULT_TYPE_OVER;		//リザルトの種類
bool g_bResult = false;		//一回だけ起動用

//----------------------------------------
//  リザルトの初期化処理
//----------------------------------------
void InitResult(Result_Type nResult)
{
	g_ResultType = nResult;	//種類を設定
	g_bResult = false;		//falseにする

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\result_over.png",
		&g_pTextureResult[RESULT_TYPE_OVER]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\result_clear.png",
		&g_pTextureResult[RESULT_TYPE_CLEAR]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffResult->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM_RESULT);
}

//----------------------------------------
//  リザルトの終了処理
//----------------------------------------
void UninitResult(void)
{
	//テクスチャの破棄
	for (int i = 0; i < RESULT_TYPE_MAX; i++)
	{
		if (g_pTextureResult[i] != NULL)
		{
			g_pTextureResult[i]->Release();
			g_pTextureResult[i] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//----------------------------------------
//  リザルトの更新処理
//----------------------------------------
void UpdateResult(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (!g_bResult)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_TITLE_BUTTON);

			//モード設定(ゲーム画面に移行)
			SetFade(MODE_RANKING);

			g_bResult = true;
		}
	}
}

//----------------------------------------
//  リザルトの描画処理
//----------------------------------------
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResult[g_ResultType]);

	//ポリゴンの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
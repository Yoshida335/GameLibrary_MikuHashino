//----------------------------------------
//	タイトル画面の処理
//	Author：橋野幹生
//----------------------------------------
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

LPDIRECT3DTEXTURE9 g_pTextureTitle[2] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle[2] = {};	//頂点バッファへのポインタ
D3DXVECTOR3 g_posText;
bool bTitle;	//一回だけ起動用

//----------------------------------------
//  タイトルの初期化設定処理
//----------------------------------------
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\title.png",
		&g_pTextureTitle[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\PRESSENTER.png",
		&g_pTextureTitle[1]);

	//位置初期化(PRESS ENTER)
	g_posText = D3DXVECTOR3((SCREEN_WIDTH / 2), 500.0f, 0.0f);
	bTitle = false;

	//頂点バッファの生成
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffTitle[nCnt],
			NULL);
	}

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//背景の頂点バッファ
	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle[0]->Lock(0, 0, (void**)&pVtx, 0);

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

	//頂点バッファをアンロックする
	g_pVtxBuffTitle[0]->Unlock();

	//テキストの頂点バッファ
	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle[1]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
	pVtx[0].pos = D3DXVECTOR3(g_posText.x - 150.0f, g_posText.y - 60.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posText.x + 150.0f, g_posText.y - 60.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posText.x - 150.0f, g_posText.y + 60.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posText.x + 150.0f, g_posText.y + 60.0f, 0.0f);

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
	g_pVtxBuffTitle[1]->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM_START);
}

//----------------------------------------
//  タイトルの終了処理
//----------------------------------------
void UninitTitle(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_pTextureTitle[nCnt] != NULL)
		{//テクスチャの破棄
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_pVtxBuffTitle[nCnt] != NULL)
		{//頂点バッファの破棄
			g_pVtxBuffTitle[nCnt]->Release();
			g_pVtxBuffTitle[nCnt] = NULL;
		}
	}
}

//----------------------------------------
//  タイトルの更新設定処理
//----------------------------------------
void UpdateTitle(void)
{
	//テキストの頂点
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle[1]->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		if (!bTitle)
		{//一回だけ起動
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_TITLE_BUTTON);

			//モード設定(セレクト画面に移行)
			SetFade(MODE_SELECT);

			bTitle = true;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle[1]->Unlock();
}

//----------------------------------------
//  タイトルの描画処理
//----------------------------------------
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffTitle[nCnt], 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCnt]);

		//ポリゴンの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

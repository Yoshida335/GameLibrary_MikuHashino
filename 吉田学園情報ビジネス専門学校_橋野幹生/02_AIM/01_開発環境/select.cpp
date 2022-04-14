//----------------------------------------
//	セレクトの処理
//　Author：橋野幹生
//----------------------------------------
#include "select.h"
#include "input.h"
#include "sound.h"
#include "fade.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureSelect[MAX_SELECT] = {};	//テクスチャ(2枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelect = NULL;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBGG = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBGG = {};		//頂点バッファへのポインタ
SELECT g_Select[MAX_SELECT];
STAGE_No g_nSelect;
bool g_bSelect = false;

//----------------------------------------
//  セレクトの初期化設定処理
//----------------------------------------
void InitSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	g_bSelect = false;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\stage_1.png",
		&g_pTextureSelect[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\stage_2.png",
		&g_pTextureSelect[1]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\BGG.png",
		&g_pTextureBGG);

	//初期化
	for (int nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
	{
		g_Select[nCntSelect].pos = D3DXVECTOR3((SCREEN_WIDTH / 2), 280.0f + (200.0f * nCntSelect), 0.0f);
		g_Select[nCntSelect].state = SELECT_OFF;
	}
	g_nSelect = STAGE_No_0;
	g_Select[0].state = SELECT_ON;

	//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SELECT,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffSelect,
			NULL);

		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SELECT,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffBGG,
			NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
	{
		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3(g_Select[nCntSelect].pos.x - (SELECT_WIDTH / 2), g_Select[nCntSelect].pos.y - (SELECT_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Select[nCntSelect].pos.x + (SELECT_WIDTH / 2), g_Select[nCntSelect].pos.y - (SELECT_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Select[nCntSelect].pos.x - (SELECT_WIDTH / 2), g_Select[nCntSelect].pos.y + (SELECT_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Select[nCntSelect].pos.x + (SELECT_WIDTH / 2), g_Select[nCntSelect].pos.y + (SELECT_HEIGHT / 2), 0.0f);

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
	g_pVtxBuffSelect->Unlock();

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffBGG->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffBGG->Unlock();
}

//----------------------------------------
//  セレクトの終了処理
//----------------------------------------
void UninitSelect(void)
{
	//サウンドの停止
	StopSound();

	for (int nCnt = 0; nCnt < MAX_SELECT; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureSelect[nCnt] != NULL)
		{
			g_pTextureSelect[nCnt]->Release();
			g_pTextureSelect[nCnt] = NULL;
		}
	}

	//テクスチャの破棄
	if (g_pTextureBGG != NULL)
	{
		g_pTextureBGG->Release();
		g_pTextureBGG = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSelect != NULL)
	{
		g_pVtxBuffSelect->Release();
		g_pVtxBuffSelect = NULL;
	}
}

//----------------------------------------
//　セレクトの更新処理
//----------------------------------------
void UpdateSelect(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//RETURNキーが押された
		if (!g_bSelect)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_TITLE_BUTTON);

			//モード設定(ゲーム画面に移行)
			SetFade(MODE_RULE);

			g_bSelect = true;
		}
	}

	if (GetKeyboardTrigger(DIK_W) == true)
	{//Wキーが押された
		switch (g_nSelect)
		{
		case 0:
			g_nSelect = STAGE_No_1;
			g_Select[0].state = SELECT_OFF;
			g_Select[STAGE_No_0].state = SELECT_ON;
			break;

		case 1:
			g_nSelect = STAGE_No_0;
			g_Select[1].state = SELECT_OFF;
			g_Select[STAGE_No_0].state = SELECT_ON;
			break;
		}
	}
	if (GetKeyboardTrigger(DIK_S) == true)
	{//Sキーが押された
		switch (g_nSelect)
		{
		case 0:
			g_nSelect = STAGE_No_1;

			g_Select[0].state = SELECT_OFF;
			g_Select[STAGE_No_1].state = SELECT_ON;
			break;

		case 1:
			g_nSelect = STAGE_No_0;

			g_Select[1].state = SELECT_OFF;
			g_Select[STAGE_No_0].state = SELECT_ON;
			break;
		}
	}
	
	for (int nCntSelect = 0; nCntSelect < MAX_SELECT; nCntSelect++)
	{
		switch (g_Select[nCntSelect].state)
		{
		case SELECT_OFF:
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			break;

		case SELECT_ON:
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}

		pVtx += 4;
	}

	if (GetKeyboardTrigger(DIK_F1) == true)
	{//Sキーが押された
		g_nSelect = STAGE_No_0;
		SetFade(MODE_GAME);
	}
	if (GetKeyboardTrigger(DIK_F2) == true)
	{//Sキーが押された
		g_nSelect = STAGE_No_1;
		SetFade(MODE_GAME);
	}
	if (GetKeyboardTrigger(DIK_F3) == true)
	{//Sキーが押された
		g_nSelect = STAGE_No_2;
		SetFade(MODE_GAME);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffSelect->Unlock();

}

//----------------------------------------
//  セレクトの描画処理
//----------------------------------------
void DrawSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBGG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBGG);

	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSelect, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_SELECT; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureSelect[nCnt]);

		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt * 4,
			2);
	}


}

//----------------------------------------
//  ステージ番号の情報
//----------------------------------------
STAGE_No * GetSelect(void)
{
	return &g_nSelect;
}
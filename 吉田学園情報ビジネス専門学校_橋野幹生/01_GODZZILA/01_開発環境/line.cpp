//----------------------------------------
//　ラインの処理
//　Author：橋野幹生
//----------------------------------------
#include "Line.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLine = NULL;		//頂点バッファへのポインタ
Line g_aLine[MAX_LINE];

//---------------------------------------------------
//	ラインの初期化
//---------------------------------------------------
void InitLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイス取得

	//ラインの各値初期化
	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		g_aLine[nCntLine].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine[nCntLine].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine[nCntLine].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aLine[nCntLine].start =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine[nCntLine].finish = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine[nCntLine].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * MAX_LINE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLine,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 2;
	}

	//頂点バッファのアンロック
	g_pVtxBuffLine->Unlock();
}

//---------------------------------------------------
//	ラインの終了処理
//---------------------------------------------------
void UninitLine(void)
{
	if (g_pVtxBuffLine != NULL)
	{
		g_pVtxBuffLine->Release();
		g_pVtxBuffLine = NULL;
	}
}

//---------------------------------------------------
//	ラインの更新処理
//---------------------------------------------------
void UpdateLine(void)
{

}

//---------------------------------------------------
//	ラインの描画処理
//---------------------------------------------------
void DrawLine(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		if (g_aLine[nCntLine].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aLine[nCntLine].mtxWorld);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aLine[nCntLine].pos.x, g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z);
			D3DXMatrixMultiply(&g_aLine[nCntLine].mtxWorld, &g_aLine[nCntLine].mtxWorld, &mtxTrans);

			//ライトを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aLine[nCntLine].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffLine, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_LINELIST,
				nCntLine * 2,
				1);

			//ライトを有効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}
}

//---------------------------------------------------
//	ラインの設定
//---------------------------------------------------
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 finish, D3DXCOLOR col)
{
	VERTEX_3D * pVtx;

	//頂点バッファをロック
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		if (g_aLine[nCntLine].bUse == false)
		{
			g_aLine[nCntLine].pos = pos;
			g_aLine[nCntLine].rot = rot;
			g_aLine[nCntLine].col = col;
			g_aLine[nCntLine].start = start;
			g_aLine[nCntLine].finish = finish;
			g_aLine[nCntLine].bUse = true;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(start.x, start.y, start.z);
			pVtx[1].pos = D3DXVECTOR3(finish.x, finish.y, finish.z);

			//頂点カラー
			pVtx[0].col = g_aLine[nCntLine].col;
			pVtx[1].col = g_aLine[nCntLine].col;

			break;
		}

		pVtx += 2;
	}

	//頂点バッファのアンロック
	g_pVtxBuffLine->Unlock();
}

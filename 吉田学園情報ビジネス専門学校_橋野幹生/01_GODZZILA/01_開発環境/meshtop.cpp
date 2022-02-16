//----------------------------------------
//　天井の処理
//　Author：橋野幹生
//----------------------------------------
#include "meshtop.h"
#include "meshsphere.h"

#define MESHTOP_X_BLOCK		(16)		// X軸のブロック数
#define MESHTOP_Z_BLOCK		(1)			// Z軸のブロック数

#define MESHTOP_VERTEX		((MESHTOP_X_BLOCK + 1) * (MESHTOP_Z_BLOCK + 1))								//メッシュの頂点
#define MESHTOP_INDEX		((MESHTOP_X_BLOCK  + 1) * 2 * MESHTOP_Z_BLOCK + (MESHTOP_Z_BLOCK - 1) * 2)	//インデックス数
#define MESHTOP_PRIMITIVE	((MESHTOP_X_BLOCK * MESHTOP_Z_BLOCK * 2) + (MESHTOP_Z_BLOCK - 1) * 4)		//ポリゴン数

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshTop = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3 g_posMeshTop;		//位置
D3DXVECTOR3 g_rotMeshTop;		//向き
D3DXMATRIX g_mtxWorldMeshTop;	//ワールドマトリックス

//---------------------------------------------------
//	天井の初期化
//---------------------------------------------------
void InitMeshTop(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;			//デバイス取得

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHTOP_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshTop,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffMeshTop->Lock(0, 0, (void**)&pVtx, 0);

	int nCnt = 0;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f,  50.0f);
	pVtx[1].pos = D3DXVECTOR3(	0.0f, 0.0f,  50.0f);
	pVtx[2].pos = D3DXVECTOR3( 50.0f, 0.0f,  50.0f);
	pVtx[3].pos = D3DXVECTOR3(-50.0f, 0.0f,   0.0f);
	pVtx[4].pos = D3DXVECTOR3(	0.0f, 0.0f,   0.0f);
	pVtx[5].pos = D3DXVECTOR3( 50.0f, 0.0f,   0.0f);
	pVtx[6].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[7].pos = D3DXVECTOR3(	0.0f, 0.0f, -50.0f);
	pVtx[8].pos = D3DXVECTOR3( 50.0f, 0.0f, -50.0f);

	//各頂点の法線の設定(ベクトルの大きさは１にする)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffMeshTop->Unlock();
}

//---------------------------------------------------
//	天井の終了処理
//---------------------------------------------------
void UninitMeshTop(void)
{
	//頂点バッファ破棄
	if (g_pVtxBuffMeshTop != NULL)
	{
		g_pVtxBuffMeshTop->Release();
		g_pVtxBuffMeshTop = NULL;
	}
}

//---------------------------------------------------
//	天井の更新処理
//---------------------------------------------------
void UpdateMeshTop(void)
{

}

//---------------------------------------------------
//	天井の描画処理
//---------------------------------------------------
void DrawMeshTop(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshTop);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotMeshTop.y, g_rotMeshTop.x, g_rotMeshTop.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshTop,
		&g_mtxWorldMeshTop, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshTop.x, g_posMeshTop.y, g_posMeshTop.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshTop, &g_mtxWorldMeshTop, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshTop);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshTop, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, MESHTOP_VERTEX, 0, MESHTOP_PRIMITIVE);

	pDevice->SetTexture(0, NULL);
}


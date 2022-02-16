//----------------------------------------
//　メッシュ(半円)の処理
//　Author：橋野幹生
//----------------------------------------
#include "meshsphere.h"

#define MESHSPHERE_X_BLOCK		(16)	// X軸のブロック数
#define MESHSPHERE_Z_BLOCK		(4)		// Z軸のブロック数

#define MESHSPHERE_VERTEX		((MESHSPHERE_X_BLOCK + 1) * (MESHSPHERE_Z_BLOCK + 1))									//メッシュの頂点
#define MESHSPHERE_INDEX		((MESHSPHERE_X_BLOCK  + 1) * 2 * MESHSPHERE_Z_BLOCK + (MESHSPHERE_Z_BLOCK - 1) * 2)		//インデックス数
#define MESHSPHERE_PRIMITIVE	((MESHSPHERE_X_BLOCK * MESHSPHERE_Z_BLOCK * 2) + (MESHSPHERE_Z_BLOCK - 1) * 4)			//ポリゴン数

#define MESHSPHERE_SIZE			(1000.0f)

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshSphere = NULL;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshSphere = NULL;			//メッシュフィールドのテクスチャ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshSphere = NULL;		//インデックスバッファへのポインタ
D3DXVECTOR3 g_posMeshSphere;		//位置
D3DXVECTOR3 g_rotMeshSphere;		//向き
D3DXVECTOR3 g_Rot;					//向き
D3DXMATRIX g_mtxWorldMeshSphere;	//ワールドマトリックス

//---------------------------------------------------
//	ポリゴンの初期化
//---------------------------------------------------
void InitMeshSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;			//デバイス取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\sky000.jpg",
		&g_pTextureMeshSphere);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHSPHERE_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshSphere,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHSPHERE_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshSphere,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffMeshSphere->Lock(0, 0, (void**)&pVtx, 0);

	int nCnt = 0;

	g_posMeshSphere = D3DXVECTOR3(0.0f, 20000.0f, 0.0f);
	g_rotMeshSphere = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点情報を設定(半円)
	for (int nCnt_V = 0; nCnt_V < MESHSPHERE_Z_BLOCK + 1; nCnt_V++)
	{
		for (int nCnt_H = 0; nCnt_H < MESHSPHERE_X_BLOCK + 1; nCnt_H++, nCnt++)
		{
			//角度計算
			g_Rot.y = ((D3DX_PI * 2) / MESHSPHERE_X_BLOCK) * nCnt_H;
			g_Rot.z = ((-D3DX_PI) / MESHSPHERE_Z_BLOCK) * nCnt_V;

			//角度の正規化
			if (g_Rot.y > D3DX_PI)
			{
				g_Rot.y -= D3DX_PI * 2;
			}
			else if (g_Rot.y < -D3DX_PI)
			{
				g_Rot.y += D3DX_PI * 2;
			}
			//角度の正規化
			if (g_Rot.z > D3DX_PI)
			{
				g_Rot.z -= D3DX_PI * 2;
			}
			else if (g_Rot.z < -D3DX_PI)
			{
				g_Rot.z += D3DX_PI * 2;
			}

			//頂点座標の設定
			pVtx[nCnt].pos.x = sinf(g_Rot.y) *  cosf(g_Rot.z) * MESHSPHERE_SIZE;			//(;へ;)< うわん99gg99gg >(;o;)< ぉんgg99gg99
			pVtx[nCnt].pos.y = sinf(g_Rot.z) * MESHSPHERE_SIZE;
			pVtx[nCnt].pos.z = cosf(g_Rot.y) * cosf(g_Rot.z) * MESHSPHERE_SIZE;

			//各頂点の法線の設定
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			//正規化する(大きさ1のベクトルにする)
			D3DXVec3Normalize(&pVtx[nCnt].nor, &pVtx[nCnt].nor);

			//頂点カラー
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標の設定
			pVtx[nCnt].tex = D3DXVECTOR2(1.0f - (1.0f / MESHSPHERE_X_BLOCK) * nCnt_H, 1.0f - (1.0f / MESHSPHERE_Z_BLOCK) * nCnt_V);
		}
	}

	//頂点バッファのアンロック
	g_pVtxBuffMeshSphere->Unlock();

	//インデックスバッファをロック
	WORD * pIdx;
	g_pIdxBuffMeshSphere->Lock(0, 0, (void**)&pIdx, 0);

	nCnt = 0;
	int nCntPlas = 0;

	//インデックスの設定
	for (int nCnt_Z = 0; nCnt_Z < MESHSPHERE_Z_BLOCK; nCnt_Z++)
	{
		for (int nCnt_X = 0; nCnt_X < MESHSPHERE_X_BLOCK + 1; nCnt_X++, nCnt++)
		{
			pIdx[nCnt] = (MESHSPHERE_X_BLOCK + 1) + nCntPlas;
			pIdx[nCnt + 1] = nCntPlas;

			nCnt++;
			nCntPlas++;
		}

		if (nCnt_Z != (MESHSPHERE_Z_BLOCK - 1))
		{
			pIdx[nCnt] = nCntPlas - 1;
			pIdx[nCnt + 1] = nCntPlas + (MESHSPHERE_X_BLOCK + 1);

			nCnt += 2;
		}
	}

	//インデックスバッファのアンロック
	g_pIdxBuffMeshSphere->Unlock();

	g_rotMeshSphere = D3DXVECTOR3(D3DX_PI, 0.0f, 0.0f);
}

//---------------------------------------------------
//	ポリゴンの終了処理
//---------------------------------------------------
void UninitMeshSphere(void)
{
	//頂点バッファ破棄
	if (g_pVtxBuffMeshSphere != NULL)
	{
		g_pVtxBuffMeshSphere->Release();
		g_pVtxBuffMeshSphere = NULL;
	}

	//テクスチャ破棄
	if (g_pTextureMeshSphere != NULL)
	{
		g_pTextureMeshSphere->Release();
		g_pTextureMeshSphere = NULL;
	}

	//インデックスバッファの解放
	if (g_pIdxBuffMeshSphere != NULL)
	{
		g_pIdxBuffMeshSphere->Release();
		g_pIdxBuffMeshSphere = NULL;
	}
}

//---------------------------------------------------
//	ポリゴンの更新処理
//---------------------------------------------------
void UpdateMeshSphere(void)
{

}

//---------------------------------------------------
//	ポリゴンの描画処理
//---------------------------------------------------
void DrawMeshSphere(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshSphere);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotMeshSphere.y, g_rotMeshSphere.x, g_rotMeshSphere.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshSphere,
		&g_mtxWorldMeshSphere, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshSphere.x, g_posMeshSphere.y, g_posMeshSphere.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshSphere, &g_mtxWorldMeshSphere, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshSphere);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshSphere, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshSphere);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshSphere);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHSPHERE_VERTEX, 0, MESHSPHERE_PRIMITIVE);

	pDevice->SetTexture(0, NULL);
}


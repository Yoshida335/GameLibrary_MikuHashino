//----------------------------------------
//　メッシュ(円柱)の処理
//　Author：橋野幹生
//----------------------------------------
#include "meshcylinder.h"
#include "model.h"

#define MESHCYLINDER_X_BLOCK		(8)		// X軸のブロック数
#define MESHCYLINDER_Z_BLOCK		(4)		// Z軸のブロック数

#define MESHCYLINDER_WIDHT			(10.0f)		//幅
#define MESHCYLINDER_HEIGHT			(20.0f)		//高さ

#define MESHCYLINDER_VERTEX			((MESHCYLINDER_X_BLOCK + 1) * (MESHCYLINDER_Z_BLOCK + 1))									//メッシュの頂点
#define MESHCYLINDER_INDEX			((MESHCYLINDER_X_BLOCK  + 1) * 2 * MESHCYLINDER_Z_BLOCK + (MESHCYLINDER_Z_BLOCK - 1) * 2)	//インデックス数
#define MESHCYLINDER_PRIMITIVE		((MESHCYLINDER_X_BLOCK * MESHCYLINDER_Z_BLOCK * 2) + (MESHCYLINDER_Z_BLOCK - 1) * 4)		//ポリゴン数

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;			//メッシュフィールドのテクスチャ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;		//インデックスバッファへのポインタ
Cylinder g_Cylinder[MAX_CYLINDER];

//---------------------------------------------------
//	メッシュ(円柱)の初期化
//---------------------------------------------------
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;			//デバイス取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\Shock_wave_ring001.png",
		&g_pTextureMeshCylinder);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHCYLINDER_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHCYLINDER_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCylinder = 0; nCntCylinder < MAX_CYLINDER; nCntCylinder++)
	{
		//位置設定
		g_Cylinder[nCntCylinder].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Cylinder[nCntCylinder].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Cylinder[nCntCylinder].bUse = false;
	}
	int nCnt = 0;

		//頂点情報を設定(円柱)
		for (int nCnt_V = 0; nCnt_V < MESHCYLINDER_Z_BLOCK + 1; nCnt_V++)
		{
			for (int nCnt_H = 0; nCnt_H < MESHCYLINDER_X_BLOCK + 1; nCnt_H++, nCnt++)
			{

				for (int nCntCylinder = 0; nCntCylinder < MAX_CYLINDER; nCntCylinder++)
				{
				//角度計算
				g_Cylinder[nCntCylinder].rot.y = ((D3DX_PI * 2) / MESHCYLINDER_X_BLOCK) * (float)nCnt_H;

				//角度の正規化
				if (g_Cylinder[nCntCylinder].rot.y > D3DX_PI)
				{
					g_Cylinder[nCntCylinder].rot.y -= D3DX_PI * 2;
				}
				else if (g_Cylinder[nCntCylinder].rot.y < -D3DX_PI)
				{
					g_Cylinder[nCntCylinder].rot.y += D3DX_PI * 2;
				}

				//長さが変わっていくのをしたかった跡
				//float nDara1 = MESHCYLINDER_WIDHT * cosf(g_Cylinder[nCntCylinder].rot.y);
				//float nDara2 = MESHCYLINDER_WIDHT * sinf(g_Cylinder[nCntCylinder].rot.y);


				//頂点座標の設定
				pVtx[nCnt].pos.x = sinf(g_Cylinder[nCntCylinder].rot.y) * MESHCYLINDER_WIDHT;
				pVtx[nCnt].pos.y = (MESHCYLINDER_HEIGHT / MESHCYLINDER_Z_BLOCK) * nCnt_V;
				pVtx[nCnt].pos.z = cosf(g_Cylinder[nCntCylinder].rot.y) * MESHCYLINDER_WIDHT;

				//各頂点の法線の設定
				pVtx[nCnt].nor = D3DXVECTOR3(0.0f, g_Cylinder[nCntCylinder].rot.y, 0.0f);

				//正規化する(大きさ1のベクトルにする)
				D3DXVec3Normalize(&pVtx[nCnt].nor, &pVtx[nCnt].nor);

				//頂点カラー
				pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//テクスチャ座標の設定
				pVtx[nCnt].tex = D3DXVECTOR2(1.0f - (1.0f / MESHCYLINDER_X_BLOCK) * nCnt_H, 1.0f - (1.0f / MESHCYLINDER_Z_BLOCK) * nCnt_V);
			}
		}
	}

	//頂点バッファのアンロック
	g_pVtxBuffMeshCylinder->Unlock();

	//インデックスバッファをロック
	WORD * pIdx;
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	nCnt = 0;
	int nCntPlas = 0;

	//インデックスの設定
	for (int nCnt_Z = 0; nCnt_Z < MESHCYLINDER_Z_BLOCK; nCnt_Z++)
	{
		for (int nCnt_X = 0; nCnt_X < MESHCYLINDER_X_BLOCK + 1; nCnt_X++, nCnt++)
		{
			pIdx[nCnt] = (MESHCYLINDER_X_BLOCK + 1) + nCntPlas;
			pIdx[nCnt + 1] = nCntPlas;

			nCnt++;
			nCntPlas++;
		}

		if (nCnt_Z != (MESHCYLINDER_Z_BLOCK - 1))
		{
			pIdx[nCnt] = nCntPlas - 1;
			pIdx[nCnt + 1] = nCntPlas + (MESHCYLINDER_X_BLOCK + 1);

			nCnt += 2;
		}
	}

	//インデックスバッファのアンロック
	g_pIdxBuffMeshCylinder->Unlock();
}

//---------------------------------------------------
//	メッシュ(円柱)の終了処理
//---------------------------------------------------
void UninitMeshCylinder(void)
{
	//頂点バッファ破棄
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	//テクスチャ破棄
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	//インデックスバッファの解放
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}
//---------------------------------------------------
//	メッシュ(円柱)の更新処理
//---------------------------------------------------
void UpdateMeshCylinder(void)
{
	for (int nCntCylinder = 0; nCntCylinder < MAX_CYLINDER; nCntCylinder++)
	{
		if (g_Cylinder[nCntCylinder].bUse == true)
		{
			//g_aBullet[nCntBullet].pos.x -= sinf(g_aBullet[nCntBullet].rot.y) * 1.0f;
			//g_aBullet[nCntBullet].pos.z -= cosf(g_aBullet[nCntBullet].rot.y) * 1.0f;

			//g_Cylinder[nCntCylinder].pos.x = sinf(g_Cylinder[nCntCylinder].rot.y) * -10.0f;
			//g_Cylinder[nCntCylinder].pos.z = cosf(g_Cylinder[nCntCylinder].rot.y) * -10.0f;

			//CollisionAttack(&g_Cylinder[nCntCylinder].pos, &g_Cylinder[nCntCylinder].posOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f));

			//回転させる
			//g_Cylinder[nCntCylinder].rot.y += 0.05f;

			//角度の正規化
			if (g_Cylinder[nCntCylinder].rot.y > D3DX_PI)
			{
				g_Cylinder[nCntCylinder].rot.y -= D3DX_PI * 2;
			}
			else if (g_Cylinder[nCntCylinder].rot.y < -D3DX_PI)
			{
				g_Cylinder[nCntCylinder].rot.y += D3DX_PI * 2;
			}
		}
	}
}

//---------------------------------------------------
//	メッシュ(円柱)の描画処理
//---------------------------------------------------
void DrawMeshCylinder(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス

	// Zバッファに関して
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	
	for (int nCntCylinder = 0; nCntCylinder < MAX_CYLINDER; nCntCylinder++)
	{
		if (g_Cylinder[nCntCylinder].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Cylinder[nCntCylinder].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Cylinder[nCntCylinder].rot.y, g_Cylinder[nCntCylinder].rot.x, g_Cylinder[nCntCylinder].rot.z);
			D3DXMatrixMultiply(&g_Cylinder[nCntCylinder].mtxWorld,
				&g_Cylinder[nCntCylinder].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Cylinder[nCntCylinder].pos.x, g_Cylinder[nCntCylinder].pos.y, g_Cylinder[nCntCylinder].pos.z);
			D3DXMatrixMultiply(&g_Cylinder[nCntCylinder].mtxWorld, &g_Cylinder[nCntCylinder].mtxWorld, &mtxTrans);

			//ライトを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Cylinder[nCntCylinder].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffMeshCylinder);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//αブレンディングを加算合成に設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureMeshCylinder);

			//ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHCYLINDER_VERTEX, 0, MESHCYLINDER_PRIMITIVE);

			//αブレンディングを元に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			//ライトを有効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			//テクスチャ情報をNULLにする
			pDevice->SetTexture(0, NULL);
		}
	}

	// Zバッファを元に戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			//規定値：値が現在のピクセルの値以下の場合は、新しいピクセルを受け入れる。
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

void SetMeshCylinder(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntCylinder = 0; nCntCylinder < MAX_CYLINDER; nCntCylinder++)
	{
		if (g_Cylinder[nCntCylinder].bUse == false)
		{
			g_Cylinder[nCntCylinder].pos = pos;
			g_Cylinder[nCntCylinder].rot = rot;
			g_Cylinder[nCntCylinder].bUse = true;

			break;
		}
	}
}
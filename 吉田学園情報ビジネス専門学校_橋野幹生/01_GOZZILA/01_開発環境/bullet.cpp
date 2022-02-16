//----------------------------------------
//　弾の処理
//　Author：橋野幹生
//----------------------------------------
#include "bullet.h"
#include "shadow.h"
#include "model.h"
#include "effect.h"
#include "Player.h"

//マクロ定義
#define Bullet_X		(3.0f)	// x方向への値	横幅
#define Bullet_Y		(3.0f)	// y方向への値	高さ
#define Bullet_Z		(3.0f)	// z方向への値	縦幅

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;
Bullet g_aBullet[MAX_BULLET];

//---------------------------------------------------
//	弾の初期化
//---------------------------------------------------
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイス取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\Bullet000.png",
		&g_pTextureBullet);

	//弾の各値初期化
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].posdis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-Bullet_X, Bullet_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Bullet_X, Bullet_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-Bullet_X, -Bullet_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Bullet_X, -Bullet_Y, 0.0f);

		//各頂点の法線の設定(ベクトルの大きさは１にする)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラー
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

	//頂点バッファのアンロック
	g_pVtxBuffBullet->Unlock();
}

//---------------------------------------------------
//	弾の終了処理
//---------------------------------------------------
void UninitBullet(void)
{
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}

//---------------------------------------------------
//	弾の更新処理
//---------------------------------------------------
void UpdateBullet(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//弾の位置移動
			g_aBullet[nCntBullet].pos.x -= sinf(g_aBullet[nCntBullet].rot.y) * 1.0f;
			g_aBullet[nCntBullet].pos.z -= cosf(g_aBullet[nCntBullet].rot.y) * 1.0f;

			//寿命を減らしていく
			g_aBullet[nCntBullet].nLife -= 1;

			if (g_aBullet[nCntBullet].nLife <= 0)
			{//弾の寿命が0になったらfalseにする
				g_aBullet[nCntBullet].bUse = false;
			}

			//プレイヤーの情報
			Player * pPlayer = GetPlayer();

			//プレイヤーとの差を求める
			g_aBullet[nCntBullet].posdis.x = pPlayer->pos.x - g_aBullet[nCntBullet].pos.x;
			g_aBullet[nCntBullet].posdis.z = pPlayer->pos.z - g_aBullet[nCntBullet].pos.z;

			//正規化する
			D3DXVec3Normalize(&g_aBullet[nCntBullet].posdis, &g_aBullet[nCntBullet].posdis);

			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].posdis * 1.0f;


			//エフェクト効果
			SetEffect(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].rot, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 40, D3DXVECTOR3(4.0f, 4.0f, 0.0f));
			SetEffect(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].rot, D3DXCOLOR(0.5f, 0.5f, 0.0f, 0.8f), 40, D3DXVECTOR3(2.0f, 2.0f, 0.0f));
		}
	}
}

//---------------------------------------------------
//	弾の描画処理
//---------------------------------------------------
void DrawBullet(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);

			D3DXMATRIX mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);	//ビューマトリックス取得

			//カメラの逆行性を設定
			g_aBullet[nCntBullet].mtxWorld._11 = mtxView._11;
			g_aBullet[nCntBullet].mtxWorld._12 = mtxView._21;
			g_aBullet[nCntBullet].mtxWorld._13 = mtxView._31;
			g_aBullet[nCntBullet].mtxWorld._21 = mtxView._12;
			g_aBullet[nCntBullet].mtxWorld._22 = mtxView._22;
			g_aBullet[nCntBullet].mtxWorld._23 = mtxView._32;
			g_aBullet[nCntBullet].mtxWorld._31 = mtxView._13;
			g_aBullet[nCntBullet].mtxWorld._32 = mtxView._23;
			g_aBullet[nCntBullet].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);

			//ライトを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBullet * 4,
				2);

			pDevice->SetTexture(0, NULL);

			//ライトを有効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
}

//---------------------------------------------------
//	弾の設定
//---------------------------------------------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].rot = rot;
			g_aBullet[nCntBullet].bUse = true;
			g_aBullet[nCntBullet].nLife = 100;

			break;
		}
	}
}

//---------------------------------------------------
//	弾の当たり判定処理
//---------------------------------------------------
void CollisionBullet(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size, D3DXVECTOR3 *move)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{//最大モデル数分確認
		if (g_aBullet[nCntModel].bUse == true)
		{// bUseがtrueだったら（モデルが使用されている状態の時

		 /**/
			if (pos->x - (size.x / 2) < g_aBullet[nCntModel].pos.x + (Bullet_X / 2.0f) &&
				pos->x + (size.x / 2) > g_aBullet[nCntModel].pos.x - (Bullet_X / 2.0f) &&
				pos->z - (size.z / 2) < g_aBullet[nCntModel].pos.z + (Bullet_Z / 2.0f) &&
				pos->z + (size.z / 2) > g_aBullet[nCntModel].pos.z - (Bullet_Z / 2.0f))
			{
				if (posOld->y + size.y <= g_aBullet[nCntModel].pos.y - (Bullet_Y / 2.0f) &&
					pos->y + size.y > g_aBullet[nCntModel].pos.y - (Bullet_Y / 2.0f))
				{//モデルの下からめり込んだ時の当たり判定
					g_aBullet[nCntModel].bUse = false;	//弾を消す
					HitModel(4);	//プレイヤーのヒット処理

				}
				if (posOld->y >= g_aBullet[nCntModel].pos.y + (Bullet_Y / 2.0f) &&
					pos->y < g_aBullet[nCntModel].pos.y + (Bullet_Y / 2.0f))
				{//モデルの上からめり込んだ時の当たり判定
					g_aBullet[nCntModel].bUse = false;	//弾を消す
					HitModel(4);	//プレイヤーのヒット処理

				}
			}
			if (pos->y < g_aBullet[nCntModel].pos.y + (Bullet_Y / 2.0f) &&
				pos->y + (size.y) > g_aBullet[nCntModel].pos.y - (Bullet_Y / 2.0f))
			{
				if (pos->z - (size.z / 2) < g_aBullet[nCntModel].pos.z + (Bullet_Z / 2.0f) &&
					pos->z + (size.z / 2) > g_aBullet[nCntModel].pos.z - (Bullet_Z / 2.0f))
				{// *posのz座標がモデルに重なっている時
					if (posOld->x + (size.x / 2) <= g_aBullet[nCntModel].pos.x - (Bullet_X / 2.0f) &&
						pos->x + (size.x / 2) >= g_aBullet[nCntModel].pos.x - (Bullet_X / 2.0f))
					{//左側からモデルにめり込んだ時
					 //*pos.xにモデルのpos.x(左側)を設定
						g_aBullet[nCntModel].bUse = false;	//弾を消す
						HitModel(4);	//プレイヤーのヒット処理

					}
					else if (posOld->x - (size.x / 2) >= g_aBullet[nCntModel].pos.x + (Bullet_X / 2.0f) &&
						pos->x - (size.x / 2) <= g_aBullet[nCntModel].pos.x + (Bullet_X / 2.0f))
					{//右側からモデルにめり込んだ時
					 //*pos.xにモデルのpos.x(右側)を設定
						g_aBullet[nCntModel].bUse = false;	//弾を消す
						HitModel(4);	//プレイヤーのヒット処理

					}
				}
				if (pos->x - (size.x / 2) < g_aBullet[nCntModel].pos.x + (Bullet_X / 2.0f) &&
					pos->x + (size.x / 2) > g_aBullet[nCntModel].pos.x - (Bullet_X / 2.0f))
				{// *posのx座標がモデルに重なっている時
					if (posOld->z - (size.z / 2) <= g_aBullet[nCntModel].pos.z - (Bullet_Z / 2.0f) &&
						pos->z + (size.z / 2) > g_aBullet[nCntModel].pos.z - (Bullet_Z / 2.0f))
					{//モデルの手前側からめり込んだ時
					 //*pos.zにモデルのpos.z(手前側)を設定
						g_aBullet[nCntModel].bUse = false;	//弾を消す
						HitModel(4);	//プレイヤーのヒット処理

					}
					else if (posOld->z + (size.z / 2) >= g_aBullet[nCntModel].pos.z + (Bullet_Z / 2.0f) &&
						pos->z - (size.z / 2) < g_aBullet[nCntModel].pos.z + (Bullet_Z / 2.0f))
					{//モデルの奥側からめり込んだ時
					 //*pos.zにモデルのpos.z(奥側)を設定
						g_aBullet[nCntModel].bUse = false;	//弾を消す
						HitModel(4);	//プレイヤーのヒット処理

					}
				}
			}
		}
	}

}
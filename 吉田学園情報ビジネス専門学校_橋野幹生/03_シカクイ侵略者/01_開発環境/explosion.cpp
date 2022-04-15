//----------------------------------------
//　爆発の処理
//　Author：橋野幹生
//----------------------------------------
#include "explosion.h"
#include "sound.h"

//マクロ定義
#define MAX_EXPLOSION		(128)	//爆発の最大数
#define EXPLOSION_SIZE		(50.0f)	//爆発のサイズ

//爆発構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	int nCounterAnim;		//アニメーションカウンター
	int nPatternAnim;		//アニメーションパターンNo.
	bool bUse;				//使用しているかどうか
	bool bExprosion;
}Explosion;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
Explosion g_aExplosion[MAX_EXPLOSION];		//爆発の情報

//----------------------------------------
//　爆発の初期化処理
//----------------------------------------
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion);

	//爆発の初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
		g_aExplosion[nCntExplosion].bExprosion = false;
	}

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE, 0.0f);

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

		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//----------------------------------------
//　爆発の終了処理
//----------------------------------------
void UninitExplosion(void)
{
	//テクスチャの破棄
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//----------------------------------------
//　爆発の更新処理
//----------------------------------------
void UpdateExplosion(void)
{
	int nCntExplosion;

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//爆発が使用されている
			g_aExplosion[nCntExplosion].nCounterAnim++;

			if ((g_aExplosion[nCntExplosion].nCounterAnim % 5) == 0)
			{
				//パターンNo.を更新する
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 8;

				if (g_aExplosion[nCntExplosion].nPatternAnim == 7)
				{
					g_aExplosion[nCntExplosion].bUse = false;
				}
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim + 0.125f, 1.0f);
			}

			if (g_aExplosion[nCntExplosion].bExprosion == false)
			{
				PlaySound(SOUND_LABEL_SE_EXPLOSION);

				g_aExplosion[nCntExplosion].bExprosion = true;
			}
		}

		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//----------------------------------------
//　爆発の描画処理
//----------------------------------------
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntExplosion;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//爆発が使用されている
		 //ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntExplosion * 4,
				2);
		}
	}
}

//----------------------------------------
//　爆発の設定処理
//----------------------------------------
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//爆発が使用されていない場合
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].bExprosion = false;

			//頂点座標更新
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE, 0.0f);

			pVtx += 4;			//頂点データのポインタを4つ分進める

			g_aExplosion[nCntExplosion].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			g_aExplosion[nCntExplosion].bUse = true;

			break;
		}

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}
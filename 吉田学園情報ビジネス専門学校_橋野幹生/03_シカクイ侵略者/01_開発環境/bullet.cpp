//----------------------------------------
//　弾処理
//　Author：橋野幹生
//----------------------------------------
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"

//マクロ定義
#define MAX_BULLET			(128)		//弾の最大数
#define BULLET_SIZE			(20.0f)		//弾のサイズ
#define BULLET_WIDTH		(30.0f)		//弾の幅
#define BULLET_HEIGHT		(30.0f)		//弾の高さ
#define BULLET_LIEF			(80)		//弾のライフ
#define ENEMY_MOVE2			(0.5f)		//敵の速度

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 rot;		//向き
	int nLife;				//寿命
	bool bUse;				//使用しているかどうか
}Bullet;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;
Bullet g_aBullet[MAX_BULLET];		//弾の情報
float g_fLengthBullet;				//対角線の長さ
float g_fAngleBullet;				//対角線の角度
float g_MoveCnt;

//----------------------------------------
//　弾の初期化処理
//----------------------------------------
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\BULLET.png",
		&g_pTextureBullet);

	//弾の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = BULLET_LIEF;
		g_aBullet[nCntBullet].bUse = false;
	}
	g_MoveCnt = 0;

	//対角線の長さ算出
	g_fLengthBullet = sqrtf(BULLET_WIDTH * BULLET_WIDTH + BULLET_HEIGHT * BULLET_HEIGHT) / 2.0f;

	//対角線の角度を算出する
	g_fAngleBullet = atan2f(BULLET_WIDTH, BULLET_HEIGHT);

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

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
	g_pVtxBuffBullet->Unlock();
}

//----------------------------------------
//　弾の終了処理
//----------------------------------------
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//----------------------------------------
//　弾の更新処理
//----------------------------------------
void UpdateBullet(void)
{
	int nCntBullet;

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている
			Enemy * pEnemy;
			int nCntEnemy;

			//敵の情報の取得
			pEnemy = GetEnemy();

			for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				
				if (pEnemy->bUse == true)
				{//敵が使用されている
					if (g_MoveCnt != 0)
					{
						pEnemy->move.y += ENEMY_MOVE2;

						g_MoveCnt = 1;
					}
					g_MoveCnt = 0;

					if (g_aBullet[nCntBullet].pos.x - 10.0f >= pEnemy->pos.x - 50.0f &&
						g_aBullet[nCntBullet].pos.x + 10.0f <= pEnemy->pos.x + 50.0f &&
						g_aBullet[nCntBullet].pos.y - 10.0f >= pEnemy->pos.y - 50.0f + pEnemy->move.y &&
						g_aBullet[nCntBullet].pos.y + 10.0f <= pEnemy->pos.y + 50.0f + pEnemy->move.y)
					{//敵と弾が当たった
 						HitEnemy(nCntEnemy, 1);

						g_aBullet[nCntBullet].bUse = false;
					}
				}
			}

			//位置を更新
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;

			//頂点座標設定
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

			if (g_aBullet[nCntBullet].pos.y < 0)
			{//画面の外に出たら
				g_aBullet[nCntBullet].bUse = false;
			}

			g_aBullet[nCntBullet].nLife -= 1;			//寿命のカウントダウン

			if (g_aBullet[nCntBullet].nLife == 0)
			{//寿命が尽きた
				//爆発の設定
				SetExplosion(g_aBullet[nCntBullet].pos, 255);

				g_aBullet[nCntBullet].bUse = false;
			}
		}

		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//----------------------------------------
//　弾の描画処理
//----------------------------------------
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBullet * 4,
				2);
		}
	}
}

//----------------------------------------
//　弾の設定処理
//----------------------------------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	int nCntBullet;

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//弾が使用されていない場合
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = BULLET_LIEF;
			g_aBullet[nCntBullet].bUse = true;

			break;
		}

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}
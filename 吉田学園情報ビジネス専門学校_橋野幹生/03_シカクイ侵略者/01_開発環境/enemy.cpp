#include "enemy.h"
#include "explosion.h"
#include "score.h"
#include "player.h"
#include "stage.h"
#include "bullet.h"

//マクロ定義
#define NUM_ENEMY			(3)			//敵の種類
#define ENEMY_SIZE			(40.0f)		//敵のサイズ
#define ENEMY_MOVE			(0.5f)		//敵の速度

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureEnemy[ENEMY_TYPE_MAX] = {};	//テクスチャ(4枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;				//頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];									//敵の情報
int g_BulletCnt, g_BulletCnt2;

//----------------------------------------
//　敵の初期化処理
//----------------------------------------
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block_000.png",
		&g_pTextureEnemy[ENEMY_TYPE_000]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block_001.png",
		&g_pTextureEnemy[ENEMY_TYPE_001]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\block_002.png",
		&g_pTextureEnemy[ENEMY_TYPE_002]);

	//敵の初期化
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = ENEMY_TYPE_000;
		g_aEnemy[nCntEnemy].nLife = 2;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	g_BulletCnt = 0;
	g_BulletCnt2 = 0;

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);

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
	g_pVtxBuffEnemy->Unlock();

}

//----------------------------------------
//　敵の終了処理
//----------------------------------------
void UninitEnemy(void)
{
	int nCnt;

	for (nCnt = 0; nCnt < ENEMY_TYPE_MAX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureEnemy[nCnt] != NULL)
		{
			g_pTextureEnemy[nCnt]->Release();
			g_pTextureEnemy[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//----------------------------------------
//　敵の更新処理
//----------------------------------------
void UpdateEnemy(void)
{
	int nCntEnemy;

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵が使用されている
			g_aEnemy[nCntEnemy].move.y += ENEMY_MOVE;
			g_BulletCnt += 1;

			//if (g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].move.y >= SCREEN_HEIGHT - 80.0f - ENEMY_SIZE)
			//{
			//	SetExplosion(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].move.y, 0.0f), 255);
			//	g_aEnemy[nCntEnemy].bUse = false;
			//	g_aEnemy[nCntEnemy].move.y = 0.0f;
			//}

			//敵が弾出す時の試行錯誤の結果
			//if (g_BulletCnt >= 240)
			//{
			//	for (int nCnt = 0; nCnt < 3; nCnt++)
			//	{
			//		if (g_BulletCnt >= 100)
			//		{
			//			SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].move, 0.0f), D3DXVECTOR3(0.0f, 4.0f, 0.0f));
			//		}
			//		g_BulletCnt2 = 0;
			//	}
			//	g_BulletCnt = 0;
			//}

			//ステージの当たり判定
			CollisionStage(g_aEnemy[nCntEnemy].pos, ENEMY_SIZE, g_aEnemy[nCntEnemy].move, &g_aEnemy[nCntEnemy].nLife);

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NOMAL:
				//頂点座標更新
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE + g_aEnemy[nCntEnemy].move.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE + g_aEnemy[nCntEnemy].move.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE + g_aEnemy[nCntEnemy].move.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE + g_aEnemy[nCntEnemy].move.y, 0.0f);

				break;

			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;

					//頂点カラーの設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}

				break;
			}
		}

		if (g_aEnemy[nCntEnemy].nLife <= 0)
		{
			g_aEnemy[nCntEnemy].move.y = 0.0f;

			g_aEnemy[nCntEnemy].bUse = false;
		}

		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//----------------------------------------
//　敵の描画処理
//----------------------------------------
void DrawEnemy(void)
{
	// デバイス関係
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	pDevice = GetDevice();			//デバイスの取得

	int nCntEnemy;

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵が使用されている
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureEnemy[g_aEnemy[nCntEnemy].nType]);

		 //ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEnemy * 4,
				2);
		}
	}
}

//----------------------------------------
//　敵の設定
// 引数
// [pos] 敵の位置
// [nType] 敵の種類
//----------------------------------------
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE nType)
{
	int nCntEnemy;

	VERTEX_2D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//敵が使用されていない場合
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].nLife = 5;
			g_aEnemy[nCntEnemy].bUse = true;

			//頂点座標更新
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE + g_aEnemy[nCntEnemy].move.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE + g_aEnemy[nCntEnemy].move.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE + g_aEnemy[nCntEnemy].move.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE + g_aEnemy[nCntEnemy].move.y, 0.0f);

			break;
		}

		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//----------------------------------------
//　敵の情報
//----------------------------------------
Enemy * GetEnemy(void)
{
	return g_aEnemy;
}

//----------------------------------------
//　敵のヒット処理
//----------------------------------------
void HitEnemy(int nCntEnemy, int nDamage)
{
  	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		SetExplosion(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].move.y, 0.0f), 255);

		AddScore(500);

		g_aEnemy[nCntEnemy].move.y = 0.0f;

		g_aEnemy[nCntEnemy].bUse = false;
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;

		VERTEX_2D * pVtx;

		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nCntEnemy * 4;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffEnemy->Unlock();
	}
}

//----------------------------------------
//　ブロックの当たり判定
//----------------------------------------
void CollisionBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pCol, D3DXVECTOR3 * pMove, float fWidth, float fHeight)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//ブロックが使用されている時
				if (pCol->x - (fWidth / 2) < g_aEnemy[nCntEnemy].pos.x + (ENEMY_SIZE / 2)
					&& pCol->x + (fWidth / 2) > g_aEnemy[nCntEnemy].pos.x - (ENEMY_SIZE / 2))
				{//プレイヤーのx座標がブロックに重なっている時
					if (pCol->y + (fHeight / 2 - g_aEnemy[nCntEnemy].move.y) <= g_aEnemy[nCntEnemy].pos.y - (ENEMY_SIZE / 2 + g_aEnemy[nCntEnemy].move.y)
						&& pPos->y + (fHeight / 2) >= g_aEnemy[nCntEnemy].pos.y - (ENEMY_SIZE / 2))
					{//ブロックにめり込んだ時(上側から)
						pPos->y = g_aEnemy[nCntEnemy].pos.y - (ENEMY_SIZE / 2) - (fHeight / 2);
						pMove->y = 0.0f;
					}
					else if (pCol->y - (fHeight / 2 + g_aEnemy[nCntEnemy].move.y) >= g_aEnemy[nCntEnemy].pos.y + (ENEMY_SIZE / 2 - g_aEnemy[nCntEnemy].move.y)
						&& pPos->y - (fHeight / 2) <= g_aEnemy[nCntEnemy].pos.y + (ENEMY_SIZE / 2))
					{//ブロックにめり込んだ時(下側から)
						pPos->y = g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE + (fHeight / 2);
						pMove->y = 0.0f;
					}
				}
				if (pPos->y - (fHeight / 2) <= g_aEnemy[nCntEnemy].pos.y + (ENEMY_SIZE / 2)
					&& pCol->y + (fHeight / 2) >= g_aEnemy[nCntEnemy].pos.y - (ENEMY_SIZE / 2))
				{//プレイヤーのy座標がブロックに重なっている時
					if (pCol->x + (fWidth / 2 - g_aEnemy[nCntEnemy].move.x) <= g_aEnemy[nCntEnemy].pos.x - (ENEMY_SIZE / 2 + g_aEnemy[nCntEnemy].move.x)
						&& pPos->x + (fWidth / 2) >= g_aEnemy[nCntEnemy].pos.x - (ENEMY_SIZE / 2))
					{//ブロックにめり込んだ時(左側から)
						pPos->x = g_aEnemy[nCntEnemy].pos.x - (ENEMY_SIZE / 2) - (fWidth / 2);
						pMove->x = 0.0f;
					}
					else if (pCol->x - (fWidth / 2 + g_aEnemy[nCntEnemy].move.x) >= g_aEnemy[nCntEnemy].pos.x + (ENEMY_SIZE / 2 - g_aEnemy[nCntEnemy].move.x)
						&& pPos->x - (fWidth / 2) <= g_aEnemy[nCntEnemy].pos.x + (ENEMY_SIZE / 2))
					{//ブロックにめり込んだ時(右側から)
						pPos->x = g_aEnemy[nCntEnemy].pos.x + (ENEMY_SIZE / 2) + (fWidth / 2);
						pMove->x = 0.0f;
					
				}
			}
		}
	}
}

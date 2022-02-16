#include "main.h"
#include "enemy.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
#include "time.h"

//マクロ定義
#define PLAYER_SIZE			(80.0f)	//プレイヤーのサイズ
#define PLAYER_WIDTH		(80.0f)	//プレイヤーの幅
#define PLAYER_HEIGHT		(80.0f)	//プレイヤーの高さ
#define PLAYER_MOVE			(7.0f)	//プレイヤーの移動距離
#define ATTACK_TIME			(10)	//弾の攻撃間隔の時間
#define BULLET_MOVE			(8.0f)

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePLAYER = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPLAYER = NULL;
LPDIRECT3DTEXTURE9 g_pTextureBR = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBR = NULL;
int g_nCounterAnimPlayer;						//アニメーションカウンター
int g_nPatternAnimPlayer;						//アニメーションパターンNo.
Player g_Player;
D3DXVECTOR3 g_posBR;
float g_fLengthPlayer;							//対角線の長さ
float g_fAnglePlayer;							//対角線の角度
int g_nCountAttack = 0;							//攻撃間隔のカウンター
int g_BulletRot;								//弾の発射向き

//----------------------------------------
//  プレイヤーの初期化設定処理
//----------------------------------------
void InitPLAYER(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\ちびまる2.png",
		&g_pTexturePLAYER);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\yazirusi.png",
		&g_pTextureBR);

	g_nCounterAnimPlayer = 0;		//カウンターを初期化
	g_nPatternAnimPlayer = 0;		//パターンNo.を初期化
	g_Player.pos = D3DXVECTOR3(500.0f, 600.0f, 0.0f);		//現在の位置初期化
	g_Player.posOld = D3DXVECTOR3(500.0f, 600.0f, 0.0f);	//前回の位置初期化
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量初期化
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き初期化
	g_Player.bUse = false;
	g_BulletRot = 2;
	g_posBR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//対角線の長さ算出
	g_fLengthPlayer = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_HEIGHT * PLAYER_HEIGHT) / 2.0f;

	//対角線の角度を算出する
	g_fAnglePlayer = atan2f(PLAYER_WIDTH, PLAYER_HEIGHT);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPLAYER,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBR,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffPLAYER->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
	pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[3].pos.z = 0.0f;

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
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//頂点バッファをアンロックする
	g_pVtxBuffPLAYER->Unlock();

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffBR->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posBR.x - 100.0f, g_posBR.y - 25.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posBR.x + 100.0f, g_posBR.y - 25.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posBR.x - 100.0f, g_posBR.y + 25.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posBR.x + 100.0f, g_posBR.y + 25.0f, 0.0f);

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
	g_pVtxBuffBR->Unlock();
}

//----------------------------------------
//  プレイヤーの終了処理
//----------------------------------------
void UninitPLAYER(void)
{
	//テクスチャの破棄
	if (g_pTexturePLAYER != NULL)
	{
		g_pTexturePLAYER->Release();
		g_pTexturePLAYER = NULL;
	}

	if (g_pTextureBR != NULL)
	{
		g_pTextureBR->Release();
		g_pTextureBR = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPLAYER != NULL)
	{
		g_pVtxBuffPLAYER->Release();
		g_pVtxBuffPLAYER = NULL;
	}

	if (g_pVtxBuffBR != NULL)
	{
		g_pVtxBuffBR->Release();
		g_pVtxBuffBR = NULL;
	}
}

//----------------------------------------
//  プレイヤーの更新処理
//----------------------------------------
void UpdatePLAYER(void)
{
	//位置保存
	g_Player.posOld = g_Player.pos;

	//エネミーとの当たり判定
	CollisionBlock(&g_Player.pos, &g_Player.posOld, &g_Player.move, PLAYER_WIDTH, PLAYER_HEIGHT);

	//プレイヤーの制御
	PlayerControl();
}

//----------------------------------------
//  プレイヤーの描画処理
//----------------------------------------
void DrawPLAYER(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPLAYER, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePLAYER);

	//ポリゴンの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	/*//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBR, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBR);

	//ポリゴンの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);*/
}

//----------------------------------------
//  プレイヤーの制御処理
//----------------------------------------
void PlayerControl(void)
{
	//プレイヤーの動作処理
	PlayerMove();

	//プレイヤーの攻撃(弾発射)処理
	PlayerAttack();
}

//----------------------------------------
//  プレイヤーの動作処理
//----------------------------------------
void PlayerMove(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffPLAYER->Lock(0, 0, (void**)&pVtx, 0);

	g_nCounterAnimPlayer++;			//カウンターを加算

	if (GetKeyboardPress(DIK_A) == true)
	{//Aキーが押された
		if (g_Player.pos.x >= PLAYER_SIZE)
		{
			//g_posPlayer.x += sinf(-D3DX_PI / 2.0f) * PLAYER_MOVE;
			//g_posPlayer.y += cosf(-D3DX_PI / 2.0f) * PLAYER_MOVE;

			g_Player.move.x += sinf(-D3DX_PI / 2.0f) * 0.8f;
			g_Player.move.y += cosf(-D3DX_PI / 2.0f) * 0.8f;
		}

		if ((g_nCounterAnimPlayer % 6) == 0)
		{//一定時間経過
		 //パターンNo.を更新する
			g_nPatternAnimPlayer = (g_nPatternAnimPlayer + 1) % 4;

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.25f * g_nPatternAnimPlayer + 0.25f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(0.25f * g_nPatternAnimPlayer, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.25f * g_nPatternAnimPlayer + 0.25f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.25f * g_nPatternAnimPlayer, 1.0f);
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//Dキーが押された
		if (g_Player.pos.x <= SCREEN_WIDTH - 340.0f - PLAYER_SIZE)
		{
				//g_posPlayer.x += sinf(D3DX_PI / 2.0f) * PLAYER_MOVE;
				//g_posPlayer.y += cosf(D3DX_PI / 2.0f) * PLAYER_MOVE;

				g_Player.move.x += sinf(D3DX_PI / 2.0f) * 0.8f;
				g_Player.move.y += cosf(D3DX_PI / 2.0f) * 0.8f;
		}

		if ((g_nCounterAnimPlayer % 12) == 0)
		{//一定時間経過
		 //パターンNo.を更新する
			g_nPatternAnimPlayer = (g_nPatternAnimPlayer + 1) % 4;

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.25f * g_nPatternAnimPlayer, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(0.25f * g_nPatternAnimPlayer + 0.25f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.25f * g_nPatternAnimPlayer, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.25f * g_nPatternAnimPlayer + 0.25f, 1.0f);
		}
	}
	else
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);
	}

		//位置を更新
		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;

		//移動量を更新(減衰させる)
		g_Player.move.x += (0.0f - g_Player.move.x) * 0.15f;
		g_Player.move.y += (0.0f - g_Player.move.y) * 0.15f;

		//頂点座標の設定
		pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[3].pos.z = 0.0f;

		//頂点バッファをアンロックする
		g_pVtxBuffPLAYER->Unlock();
}

//----------------------------------------
//  プレイヤーの攻撃処理(弾発射)処理
//----------------------------------------
void PlayerAttack(void)
{
	g_nCountAttack++;		//攻撃間隔のカウンター

	//どの角度か分かりやすくする
	if (GetKeyboardTrigger(DIK_RIGHT) == true)
	{//←キーを押す
		if (g_BulletRot == 0)
		{
			g_BulletRot = 5;
		}
		else
		{
			g_BulletRot -= 1;
		}
	}
	else if (GetKeyboardTrigger(DIK_LEFT) == true)
	{//→キーを押す
		if (g_BulletRot == 4)
		{
			g_BulletRot = 0;
		}
		else
		{
			g_BulletRot += 1;
		}
	}

	//if (g_nCountAttack > ATTACK_TIME)
	//{
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{//スペースキーを押す
	 //弾の設定
		switch (g_BulletRot)
		{
		case 0:
			SetBullet(g_Player.pos, D3DXVECTOR3(BULLET_MOVE, 0.0f, 0.0f));
			break;

		case 1:
			SetBullet(g_Player.pos, D3DXVECTOR3(BULLET_MOVE, -BULLET_MOVE, 0.0f));
			break;

		case 2:
			SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -BULLET_MOVE, 0.0f));
			break;

		case 3:
			SetBullet(g_Player.pos, -D3DXVECTOR3(BULLET_MOVE, BULLET_MOVE, 0.0f));
			break;

		case 4:
			SetBullet(g_Player.pos, -D3DXVECTOR3(BULLET_MOVE, 0.0f, 0.0f));
			break;
		}
		g_nCountAttack = 0;

		//サウンドの再生
		//PlaySound(SOUND_LABEL_SE_SHOT);
	}
	//}
}

//----------------------------------------
//  プレイヤーのヒット処理
//----------------------------------------
void HitPlayer(int nDamage)
{
	g_Player.nLife -= nDamage;

	if (g_Player.nLife == 0)
	{
		SetExplosion(g_Player.pos, 255);

		g_Player.bDisp = false;
		g_Player.state = PLAYERSTATE_DEATH;
		g_Player.nCounterState = 60;
	}
	else
	{
		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.nCounterState = 5;

		VERTEX_2D * pVtx;

		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffPLAYER->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffPLAYER->Unlock();
	}
}

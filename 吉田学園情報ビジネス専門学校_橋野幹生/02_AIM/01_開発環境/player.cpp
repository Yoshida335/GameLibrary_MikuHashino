//----------------------------------------
//	プレイヤーの処理
//　Author：橋野幹生
//----------------------------------------
#include "player.h"
#include "input.h"
#include "block.h"
#include "fade.h"
#include "ladder.h"
#include "goal.h"
#include "sound.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点バッファへのポインタ
Player g_Player;
bool g_PlayerItem[PLAYER_ITEM_MAX];

//----------------------------------------------
//	プレイヤーの初期化処理
//----------------------------------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_Player.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f);		//現在の位置の初期設定
	g_Player.posOld = g_Player.pos;									//前回の位置の初期設定
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//移動量の初期設定
	g_Player.nCounterAnim = 0;			//カウンター初期化
	g_Player.nPatternAnim = 0;			//パターン番号初期化
	g_Player.nDirectionMove = 0;		//向き
	g_Player.bIsJumping = false;		//ジャンプ中初期化
	g_Player.pItem = NULL;		//アイテム

	//アイテムを持っているかどうか
	g_PlayerItem[PLAYER_ITEM_COIN] = false;
	g_PlayerItem[PLAYER_ITEM_KEY] = false;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\ちびまる2.png",
		&g_pTexturePlayer);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_WIDTH / 2, g_Player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_WIDTH / 2, g_Player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_WIDTH / 2, g_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_WIDTH / 2, g_Player.pos.y, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2((1.0f / 4) * g_Player.nPatternAnim,		(1.0f / 1) * g_Player.nDirectionMove);
	pVtx[1].tex = D3DXVECTOR2((1.0f / 4) * (g_Player.nPatternAnim + 1), (1.0f / 1) * g_Player.nDirectionMove);
	pVtx[2].tex = D3DXVECTOR2((1.0f / 4) * g_Player.nPatternAnim,		(1.0f / 1) * g_Player.nDirectionMove + (1.0f / 2));
	pVtx[3].tex = D3DXVECTOR2((1.0f / 4) * (g_Player.nPatternAnim + 1), (1.0f / 1) * g_Player.nDirectionMove + (1.0f / 2));

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//----------------------------------------------
//	プレイヤーの終了処理
//----------------------------------------------
void UninitPlayer(void)
{
	if (g_pVtxBuffPlayer != NULL)
	{//頂点バッファの破棄
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}

	if (g_pTexturePlayer != NULL)
	{//テクスチャの破棄
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}

//----------------------------------------------
//	プレイヤーの更新処理
//----------------------------------------------
void UpdatePlayer(void)
{
	VERTEX_2D * pVtx;	//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//重力
	g_Player.move.y += 0.8f;

	//前回の位置を保存
	g_Player.posOld = g_Player.pos;

	//アイテム持ってるか
	PlayerItem();

	//プレイヤーの移動処理
	PlayerMove();

	//ブロックとの当たり判定
	CollisionBlock_P(&g_Player.pos, &g_Player.posOld, &g_Player.move, PLAYER_WIDTH, PLAYER_HEIGHT);

	//アイテムとの当たり判定
	CollisionItem(&g_Player.pos, PLAYER_WIDTH, PLAYER_HEIGHT, &g_Player.pItem);

	//梯子
	CollisionLadder(&g_Player.pos, &g_Player.posOld, &g_Player.move, PLAYER_WIDTH, PLAYER_HEIGHT);

	//ゴール
	CollisionGoal(&g_Player.pos, &g_Player.posOld, PLAYER_WIDTH, PLAYER_HEIGHT, g_PlayerItem[PLAYER_ITEM_KEY]);

	//ジャンプの可否
	g_Player.bIsJumping = !CollisionBlock_P(&g_Player.pos, &g_Player.posOld, &g_Player.move, PLAYER_WIDTH, PLAYER_HEIGHT);

	if (g_Player.pos.x - PLAYER_WIDTH / 2 >= SCREEN_WIDTH)
	{//画面外(右側)に出たら
		g_Player.pos = D3DXVECTOR3(0.0f - PLAYER_WIDTH / 2 + 0.01f, g_Player.pos.y, 0.0f);			//斜めすり抜け防止のため +0.01f してる
	}
	else if (g_Player.pos.x + PLAYER_WIDTH / 2 <= 0.0f)
	{//画面外(左側)に出たら
		g_Player.pos = D3DXVECTOR3(SCREEN_WIDTH + PLAYER_WIDTH / 2 - 0.01f, g_Player.pos.y, 0.0f);	//斜めすり抜け防止のため +0.01f してる
	}
	if (g_Player.pos.y >= SCREEN_HEIGHT)
	{//画面外(下側)に出たら 
		g_Player.pos.y = SCREEN_HEIGHT;
		g_Player.move.y = 0.0f;
		g_Player.bIsJumping = false;
	}

	//頂点座標設定
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_WIDTH / 2, g_Player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_WIDTH / 2, g_Player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_WIDTH / 2, g_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_WIDTH / 2, g_Player.pos.y, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2((1.0f / 4) * g_Player.nPatternAnim, (1.0f / 2) * g_Player.nDirectionMove);
	pVtx[1].tex = D3DXVECTOR2((1.0f / 4) * (g_Player.nPatternAnim + 1), (1.0f / 2) * g_Player.nDirectionMove);
	pVtx[2].tex = D3DXVECTOR2((1.0f / 4) * g_Player.nPatternAnim, (1.0f / 2) * g_Player.nDirectionMove + (1.0f / 2));
	pVtx[3].tex = D3DXVECTOR2((1.0f / 4) * (g_Player.nPatternAnim + 1), (1.0f / 2) * g_Player.nDirectionMove + (1.0f / 2));

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//----------------------------------------------
//	プレイヤーの描画処理
//----------------------------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	//ポリゴンの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//----------------------------------------------
//	プレイヤーの移動処理
//----------------------------------------------
void PlayerMove(void)
{
	g_Player.nCounterAnim += 1;

	//g_Player.bIsJumping = false;

	//左右移動
	if (GetKeyboardPress(DIK_A) == true)
	{//Aキーが押された
	 //左方向に移動
		g_Player.move.x -= PLAYER_SPEED;

		g_Player.nDirectionMove = 1;	//左向き
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//Dキーが押された
	 //右方向に移動
		g_Player.move.x += PLAYER_SPEED;

		g_Player.nDirectionMove = 0;	//右向き
	}

	//梯子での上下移動
	if (GetKeyboardPress(DIK_W) == true)
	{//Wキーが押された
		if (CollisionLadder(&g_Player.pos, &g_Player.posOld, &g_Player.move, PLAYER_WIDTH, PLAYER_HEIGHT) == true)
		{
			g_Player.move.y = -2.0f;
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//Sキーが押された
		if (CollisionLadder(&g_Player.pos, &g_Player.posOld, &g_Player.move, PLAYER_WIDTH, PLAYER_HEIGHT) == true)
		{
			g_Player.move.y = 2.0f;
		}
	}

	//ジャンプ
	if (GetKeyboardTrigger(DIK_SPACE) == true && g_Player.bIsJumping == false)
	{//スペースキーが押された
		g_Player.move.y -= PLAYER_JUMP;

		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_JUMP);

		g_Player.bIsJumping = true;

		if (g_Player.nPatternAnim == 0)
		{//プレイヤーが止まっているパターン番号の時
			g_Player.nPatternAnim += 1;
		}
	}

	if (g_Player.bIsJumping != true && GetKeyboardPress(DIK_F) != true)
	{//ジャンプ中じゃない時
		if (g_Player.move.x >= 1.0f || g_Player.move.x <= -1.0f)
		{//プレイヤーが動いている時
			if ((g_Player.nCounterAnim % 8) == 0)
			{//一定時間経過
			 //パターンNo.を更新する
				g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % 4;
			}
		}
		else
		{//プレイヤーが止まった時
			if (g_Player.nPatternAnim == 1)
			{//プレイヤーが進んでるパターン番号の時
				g_Player.nPatternAnim += 1;
			}
			if (g_Player.nPatternAnim == 2)
			{//プレイヤーが進んでるパターン番号の時
				g_Player.nPatternAnim += 2;
			}
			if (g_Player.nPatternAnim == 3)
			{//プレイヤーが進んでるパターン番号の時
				g_Player.nPatternAnim += 3;
			}
		}
	}

	if (g_Player.nPatternAnim >= 4)
	{
		g_Player.nPatternAnim = 0;		//パターン番号を０に戻す
	}

	//位置を更新
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;

	//移動量を更新(減衰させる)
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.2f;
}

//----------------------------------------------
//	プレイヤーのアイテム処理
//----------------------------------------------
void PlayerItem(void)
{
	if (g_Player.pItem != NULL)
	{
		switch (g_Player.pItem->type)
		{
		case ITEM_COIN:
			g_PlayerItem[PLAYER_ITEM_COIN] = true;
			break;

		case ITEM_KEY:
			g_PlayerItem[PLAYER_ITEM_KEY] = true;
			break;
		}
	}
}

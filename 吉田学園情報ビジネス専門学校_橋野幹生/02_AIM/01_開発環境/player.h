//----------------------------------------
//	プレイヤーのヘッダー
//	Author：橋野幹生
//----------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "item.h"

//プレイヤー構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 move;		//移動量
	int nCounterAnim;		//カウンター
	int nPatternAnim;		//パターン番号
	int nDirectionMove;		//向き　0：右向き　1：左向き
	bool bIsJumping;		//ジャンプ中
	ITEM * pItem;			//アイテムの情報
}Player;

//プレイヤーアイテムの定義
typedef enum
{
	PLAYER_ITEM_COIN = 0,	//コイン
	PLAYER_ITEM_KEY,		//鍵
	PLAYER_ITEM_MAX
}PLAYRE_ITEM;

//プロトタイプ宣言
void InitPlayer(void);		//プレイヤーの初期化処理
void UninitPlayer(void);	//プレイヤーの終了処理
void UpdatePlayer(void);	//プレイヤーの更新処理
void DrawPlayer(void);		//プレイヤーの描画処理
void PlayerMove(void);		//プレイヤーの移動処理
void PlayerItem(void);		//プレイヤーのアイテム所持処理

#endif

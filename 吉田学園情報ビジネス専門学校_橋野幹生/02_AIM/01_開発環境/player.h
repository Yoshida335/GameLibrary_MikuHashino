//----------------------------------------
//プレイヤー
//----------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "item.h"
#include "block.h"

//マクロ定義
#define PLAYER_WIDTH		(30.0f)			//プレイヤーの幅
#define PLAYER_HEIGHT		(30.0f)			//プレイヤーの高さ
#define PLAYER_SPEED		(0.8f)			//プレイヤーの移動の速さ
#define PLAYER_JUMP			(20.0f)			//プレイヤーのジャンプ力

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
	bool bIsCatching;
	ITEM * pItem;
	BLOCK * pBlock;
}Player;

//プレイヤーアイテムの定義
typedef enum
{
	PLAYER_ITEM_COIN = 0,
	PLAYER_ITEM_JUMPSHOSE,
	PLAYER_ITEM_KEY,
	PLAYER_ITEM_SPEEDSHOSE,
	PLAYER_ITEM_MAX
}PLAYRE_ITEM;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void PlayerMove(void);
void PlayerItem(void);

#endif

//----------------------------------------
//　ブロックのヘッダー
//　Author：橋野幹生
//----------------------------------------
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//マクロ定義
#define MAX_BLOCK			(256)		//最大ブロック数
#define BLOCK_WIDTH			(40.0f)		//ブロックの幅
#define BLOCK_HEIGHT		(40.0f)		//ブロックの高さ
#define BLOCK_MOVE			(0.2f)		//ブロックの動くスピード	
#define BLOCK_MOVE_LIFE		(200)		//動くブロックの寿命
#define BLOCK_ITEM_LIFE		(1)			//動くブロックの寿命

//ブロックの種類
typedef enum
{
	BLOCKTYPE_NOMAL = 0,	//通常ブロック
	BLOCKTYPE_UP,			//上方向に動くブロック
	BLOCKTYPE_ITEM,			//アイテムブロック
	BLOCKTYPE_MAX
}BLOCKTYPE;

//ブロックの状態
typedef enum
{
	BLOCKSTATE_NOMAL = 0,	//通常状態
	BLOCKSTATE_UP,			//上向きに移動
	BLOCKSTATE_MOVE,		//動いている状態
	BLOCKSTATE_ITEM,		//アイテム状態
	BLOCKSTATE_MAX
}BLOCKSTATE;

//ブロックの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 rot;		//角度
	D3DXVECTOR3 move;		//移動量
	float fWidth;			//幅
	float fHeight;			//高さ
	bool bUse;				//使用しているかどうか
	BLOCKTYPE type;			//ブロックの種類
	float rot2;				//新たな角度
	float flength;			//斜め長さ
	BLOCKSTATE state;		//状態
}BLOCK;

//プロトタイプ宣言
void InitBlock(void);		//ブロックの初期化処理
void UninitBlock(void);		//ブロックの終了処理
void UpdateBlock(void);		//ブロックの更新処理
void DrawBlock(void);		//ブロックの描画処理
void SetBlock(D3DXVECTOR3 pos, BLOCKTYPE type,BLOCKSTATE state, float fWidth, float fHeight);	//ブロックの設定
bool CollisionBlock_P(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight);	//プレイヤーの当たり判定	// , BLOCK ** pblock
void CollisionBlock_B(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, float fWidth, float fHeight);			//ブロックとの当たり判定
BLOCK * GetBlock(void);		//ブロックの情報

#endif

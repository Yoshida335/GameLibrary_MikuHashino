#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//マクロ定義
#define MAX_BLOCK			(128)		//最大ブロック数
#define BLOCK_WIDTH			(40.0f)		//ブロックの幅
#define BLOCK_HEIGHT		(40.0f)		//ブロックの高さ
#define BLOCK_MOVE			(0.2f)		//ブロックの動くスピード	
#define BLOCK_MOVE_LIFE		(200)		//動くブロックの寿命
#define BLOCK_ITEM_LIFE		(1)			//動くブロックの寿命

//ブロックの種類
typedef enum
{
	BLOCKTYPE_NOMAL = 0,
	BLOCKTYPE_UP,
	BLOCKTYPE_ITEM,
	BLOCKTYPE_ACT,
	BLOCKTYPE_MAX
}BLOCKTYPE;

//ブロックの状態
typedef enum
{
	BLOCKSTATE_NOMAL = 0,
	BLOCKSTATE_UP,
	BLOCKSTATE_MOVE,
	BLOCKSTATE_ITEM,
	BLOCKSTATE_ACT,
	BLOCKSTATE_RL,
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
	int nLife;
}BLOCK;

//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, BLOCKTYPE type,BLOCKSTATE state, float fWidth, float fHeight, int life);
bool CollisionBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight, BLOCK ** pblock);
void CollisionBlock2(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight, BLOCKSTATE state);
bool ActBlock(D3DXVECTOR3 * pos, float fWidth, float fHeight);
BLOCK * GetBlock(void);

#endif

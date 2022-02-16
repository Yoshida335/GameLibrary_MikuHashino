#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//マクロ定義
#define MAX_ITEM			(128)		//最大アイテム数
#define ITEM_WIDTH			(30.0f)		//アイテムの幅
#define ITEM_HEIGHT			(30.0f)		//アイテムの高さ

//アイテムの種類
typedef enum
{
	ITEM_TYPE_0 = 0,		//コイン
	ITEM_TYPE_1,			//靴(ジャンプ力アップ)
	ITEM_TYPE_3,			//鍵
	ITEM_TYPE_4,			//靴(スピードアップ)
	ITEM_TYPE_MAX
}ITEM_TYPE;

//ブロックの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	float fWidth;			//幅
	float fHeight;			//高さ
	int nCounterAnim;		//カウンター
	int nPatternAnim;		//パターン番号
	ITEM_TYPE type;			//種類
	bool bUse;				//使用しているかどうか
}ITEM;

//プロトタイプ宣言
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, ITEM_TYPE type);
ITEM * GetItem(void);
bool CollisionItem(D3DXVECTOR3 * pos, float fWidth, float fHeight, ITEM ** item);
void DeleteItem(int nCntItem);
int Coin(void);

#endif

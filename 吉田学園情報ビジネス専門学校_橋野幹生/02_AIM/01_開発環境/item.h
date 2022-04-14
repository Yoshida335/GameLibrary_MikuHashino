//----------------------------------------
//	アイテムのヘッダー
//　Author：橋野幹生
//----------------------------------------
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//マクロ定義
#define MAX_ITEM		(128)	//最大アイテム数
#define ITEM_WIDTH		(30.0f)	//アイテムの幅
#define ITEM_HEIGHT		(30.0f)	//アイテムの高さ

//アイテムの種類
typedef enum
{
	ITEM_COIN = 0,	//コイン
	ITEM_KEY,		//鍵
	ITEM_TYPE_MAX
}ITEM_TYPE;

//ブロックの構造体
typedef struct
{
	D3DXVECTOR3 pos;	//現在の位置
	float fWidth;		//幅
	float fHeight;		//高さ
	int nCounterAnim;	//カウンター
	int nPatternAnim;	//パターン番号
	ITEM_TYPE type;		//種類
	bool bUse;			//使用しているかどうか
}ITEM;

//プロトタイプ宣言
void InitItem(void);	//アイテムの初期化処理
void UninitItem(void);	//アイテムの終了処理
void UpdateItem(void);	//アイテムの更新処理
void DrawItem(void);	//アイテムの描画処理
void SetItem(D3DXVECTOR3 pos, ITEM_TYPE type);	//アイテムの設定
ITEM * GetItem(void);	//アイテムの情報
void CollisionItem(D3DXVECTOR3 * pos, float fWidth, float fHeight, ITEM ** item);	//アイテムの当たり判定
void DeleteItem(int nCntItem);	//アイテムの消去
int GetNumCoin(void);	//コインの枚数情報

#endif

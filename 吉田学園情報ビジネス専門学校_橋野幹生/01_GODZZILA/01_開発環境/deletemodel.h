//----------------------------------------
//　モデル
//----------------------------------------
#ifndef _DELETEMODEL_H_
#define _DELETEMODEL_H_

#include "main.h"

//マクロ定義
#define MAX_DELETEMODEL			(126)	//モデルの最大数

//モデルの種類
typedef enum
{
	TYPE_DELETEBILL_01 = 0,
	TYPE_DELETEBILL_02,
	TYPE_DLETEMAX
}DELETEMODELTYPE;

//モデルの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXCOLOR col;			//色
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	bool bUse;				//使っているかどうか
	DELETEMODELTYPE type;	//種類
}DeleteModel;

//プロトタイプ宣言
void InitDeleteModel(void);		//モデルの初期化
void UninitDeleteModel(void);		//モデルの終了
void UpdateDeleteModel(void);		//モデルの更新
void DrawDeleteModel(void);		//モデルの描画
void SetDeleteModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//モデルの設定

#endif


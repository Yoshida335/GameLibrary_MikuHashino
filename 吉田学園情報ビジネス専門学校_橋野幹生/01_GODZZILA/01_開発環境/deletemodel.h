//----------------------------------------
//　モデル(破壊後)
//　Author：橋野幹生
//----------------------------------------
#ifndef _DELETEMODEL_H_
#define _DELETEMODEL_H_

#include "main.h"

//マクロ定義
#define MAX_DELETEMODEL			(126)	//モデル(破壊後)の最大数

//モデル(破壊後)の種類
typedef enum
{
	TYPE_DELETEBILL_01 = 0,
	TYPE_DELETEBILL_02,
	TYPE_DLETEMAX
}DELETEMODELTYPE;

//モデル(破壊後)の構造体
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
void InitDeleteModel(void);		//モデル(破壊後)の初期化
void UninitDeleteModel(void);	//モデル(破壊後)の終了
void UpdateDeleteModel(void);	//モデル(破壊後)の更新
void DrawDeleteModel(void);		//モデル(破壊後)の描画
void SetDeleteModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//モデル(破壊後)の設定

#endif


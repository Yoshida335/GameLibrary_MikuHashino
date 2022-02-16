//----------------------------------------
//　メッシュ　(円柱)
//----------------------------------------
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

#include "main.h"

//マクロ定義
#define MAX_CYLINDER	(256)	//円柱の最大数

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;			//現在の位置
	D3DXVECTOR3 posOld;			//前回の位置
	D3DXVECTOR3 rot;			//向き
	D3DXCOLOR col;				//カラー
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	bool bUse;					//使用しているかどうか
}Cylinder;

//プロトタイプ宣言
void InitMeshCylinder(void);		//円柱の初期化処理
void UninitMeshCylinder(void);		//円柱の終了処理
void UpdateMeshCylinder(void);		//円柱の更新処理
void DrawMeshCylinder(void);		//円柱の描画処理
void SetMeshCylinder(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//円柱の描画処理

#endif
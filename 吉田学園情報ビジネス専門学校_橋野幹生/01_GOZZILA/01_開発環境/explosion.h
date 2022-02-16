//----------------------------------------
//　爆発
//----------------------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//マクロ定義
#define MAX_EXPLOSION	(256)	//ビルボードの最大数

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//向き
	D3DXCOLOR col;				//カラー
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	bool bUse;					//使用しているかどうか
	int nCntAnim;				//アニメーションカウンター
	int nPatternAnim;			//アニメーションパターンNo.
}Explosion;

//プロトタイプ宣言
void InitExplosion(void);				//ビルボードの初期化処理
void UninitExplosion(void);				//ビルボードの終了処理
void UpdateExplosion(void);				//ビルボードの更新処理
void DrawExplosion(void);				//ビルボードの描画処理
void SetExplosion(D3DXVECTOR3 pos);		//ビルボードの設定

#endif

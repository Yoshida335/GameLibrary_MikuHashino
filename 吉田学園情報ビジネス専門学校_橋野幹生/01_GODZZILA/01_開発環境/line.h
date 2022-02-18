//----------------------------------------
//　ライン
//　Author：橋野幹生
//----------------------------------------
#ifndef _LINE_H_
#define _LINE_H_

#include "main.h"

//マクロ定義
#define MAX_LINE		(256)		//ラインの最大数

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//角度
	D3DXCOLOR col;			//カラー
	D3DXVECTOR3 start;		//ラインの始まりの位置
	D3DXVECTOR3 finish;		//ラインの終わりの位置
	D3DXMATRIX mtxWorld;	//ワールドマトリクス
	bool bUse;
}Line;

//プロトタイプ宣言
void InitLine(void);	//ラインの初期化
void UninitLine(void);	//ラインの終了
void UpdateLine(void);	//ラインの更新
void DrawLine(void);	//ラインの描画
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 finish, D3DXCOLOR col);	//ラインの設定

#endif

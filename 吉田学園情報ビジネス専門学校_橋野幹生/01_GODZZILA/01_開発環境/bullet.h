//----------------------------------------
//　弾
//　Author：橋野幹生
//----------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//マクロ定義
#define MAX_BULLET	(128)	//弾の最大数

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXCOLOR col;			//カラー
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int nIdxShadow;			//影用
	bool bUse;				//使用しているかどうか
	int nLife;				//寿命
	D3DXVECTOR3 posdis;
}Bullet;

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void CollisionBullet(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size, D3DXVECTOR3 *move);

#endif


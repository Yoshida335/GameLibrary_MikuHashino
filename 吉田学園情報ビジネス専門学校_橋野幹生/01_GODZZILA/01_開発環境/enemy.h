//----------------------------------------
//　敵
//----------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//マクロ定義
#define MAX_ENEMY			(126)	//モデルの最大数
#define ENEMY_SPEED			(1.0f)	//モデルの移動速度

//モデルの種類
typedef enum
{
	TYPE_ENEMY_01 = 0,
	TYPE_ENEMY_MAX
}ENEMYTYPE;

//モデルの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	D3DXVECTOR3 diff;		//差分用
	D3DXVECTOR3 rotDest;	//目的の角度
	int IdxShadow;			//影用
	bool bUse;				//使っているかどうか
	D3DXVECTOR3 vtxMin;		//頂点の最小値を取得用
	D3DXVECTOR3 vtxMax;		//頂点の最大値を取得用
	ENEMYTYPE nType;		//モデルの種類
	int nLife;				//体力
	D3DXVECTOR3 posdis;		//プレイヤーとの差を求める
	D3DXVECTOR3 size;		//サイズ保存
	bool bAttack;
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);		//モデルの初期化
void UninitEnemy(void);		//モデルの終了
void UpdateEnemy(void);		//モデルの更新
void DrawEnemy(void);		//モデルの描画
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ENEMYTYPE type, int life);	//モデルの設定
void CollisionEnemy(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size);
void HitEnemyl(int nCntModel, int nDamage);
void CollisionENEMY(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size, D3DXVECTOR3 *move);

#endif


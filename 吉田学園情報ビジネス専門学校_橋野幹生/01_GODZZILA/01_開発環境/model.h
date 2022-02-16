//----------------------------------------
//　モデル
//----------------------------------------
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//マクロ定義
#define MAX_MODEL			(126)	//モデルの最大数
#define MODEL_SPEED			(1.0f)	//モデルの移動速度

//モデルの種類
typedef enum
{
	TYPE_BILL_01 = 0,
	TYPE_BILL_02,
	TYPE_MAX
}MODELTYPE;

//モデルの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXCOLOR col;			//色
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	float diff;				//差分用
	float rotDestModel;		//目的の角度
	int IdxShadow;			//影用
	bool bUse;				//使っているかどうか
	D3DXVECTOR3 vtxMin;		//頂点の最小値を取得用
	D3DXVECTOR3 vtxMax;		//頂点の最大値を取得用
	MODELTYPE nType;		//モデルの種類
	int nLife;				//体力
	bool bHit;				//攻撃が当たっているかどうか
	int nCntTime;
}Model;

typedef struct
{
	float nModelP;
	float nMaxLife;
	float nMax;
}Parcent;

//プロトタイプ宣言
void InitModel(void);		//モデルの初期化
void UninitModel(void);		//モデルの終了
void UpdateModel(void);		//モデルの更新
void DrawModel(void);		//モデルの描画
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE type, int life);	//モデルの設定
bool CollisionModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size, D3DXVECTOR3 *move);	//モデルの当たり判定
void CollisionAttack(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size);	//モデルの当たり判定
void HitModel(int nCntModel, int nDamage);
Parcent * GetModeParcent(void);
void SaveParcent(void);
void LoadP(void);

#endif

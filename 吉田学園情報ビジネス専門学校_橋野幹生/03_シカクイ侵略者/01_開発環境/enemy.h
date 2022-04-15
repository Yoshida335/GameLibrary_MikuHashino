#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include <stdlib.h>
#include <time.h>

//マクロ定義
#define MAX_ENEMY				(128)	//敵の最大数

//敵の種類
typedef enum
{
	ENEMY_TYPE_000 = 0,			//通常
	ENEMY_TYPE_001,				//頑丈
	ENEMY_TYPE_002,				//アイテム
	ENEMY_TYPE_MAX
}ENEMYTYPE;

//敵の状態
typedef enum
{
	ENEMYSTATE_NOMAL = 0,		//通常状態
	ENEMYSTATE_DAMAGE,			//ダメージ状態
	ENEMYSTATE_MAX
}ENEMYSTATE;

//敵構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	ENEMYTYPE nType;		//種類
	ENEMYSTATE state;		//状態
	int nCounterState;		//状態カウンター
	int nLife;				//体力
	bool bUse;				//使用しているかどうか
	D3DXVECTOR3 move;		//移動量
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE nType);
Enemy * GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);
void CollisionEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pCol, D3DXVECTOR3 * pMove, float fWidth, float fHeight);

#endif
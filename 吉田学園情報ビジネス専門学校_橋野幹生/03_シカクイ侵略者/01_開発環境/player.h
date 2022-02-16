#ifndef _PLAYER_H_				//このマクロが定義されてなかったら
#define _PLAYER_H_				//２重インクルード防止のマクロ定義

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_APPEAR = 0,		//出現状態(点滅)
	PLAYERSTATE_NOMAL,			//通常状態
	PLAYERSTATE_DAMAGE,			//ダメージ状態
	PLAYERSTATE_DEATH,			//死亡状態
	PLAYERSTATE_MAX
}PLAYERSTATE;

//敵構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 rot;		//向き
	bool bUse;				//使用しているかどうか
	PLAYERSTATE state;		//プレイヤーの状態
	int direction;			//弾の向き
	int nCounterState;		//状態管理カウンター
	int nLife;				//体力
	bool bDisp;				//表示するかしないか
}Player;

//プロトタイプ宣言
void InitPLAYER(void);
void UninitPLAYER(void);
void UpdatePLAYER(void);
void DrawPLAYER(void);
void PlayerControl(void);
void PlayerMove(void);
void PlayerAttack(void);
void HitPlayer(int nDamage);

#endif

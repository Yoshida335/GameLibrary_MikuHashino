//----------------------------------------
//　ゲーム画面の処理
//　Author：橋野幹生
//----------------------------------------
#include "game.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "score.h"
#include "player.h"
#include "fade.h"
#include "time.h"
#include "stage.h"
#include "sound.h"
#include "life.h"

//----------------------------------------
//　ゲーム画面の初期化処理
//----------------------------------------
void InitGame(void)
{
	//背景の初期化設定
	InitBG();

	//ポリゴンの初期化設定
	InitPLAYER();

	//敵の初期化設定
	InitEnemy();

	//ステージの初期化設定
	InitStage();

	//弾の初期化設定
	InitBullet();

	//弾の初期化設定
	InitExplosion();

	//スコアの初期化設定
	InitScore();

	//タイムの初期化設定
	InitTime();

	//ライフの初期化設定
	InitLife();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM001);
}

//----------------------------------------
//　ゲーム画面の終了処理
//----------------------------------------
void UninitGame(void)
{
	//サウンドの停止
	StopSound();

	//背景の終了処理
	UninitBG();

	//ポリゴンの終了処理
	UninitPLAYER();

	//敵の終了処理
	UninitEnemy();

	//ステージの終了設定
	UninitStage();

	//弾の終了処理
	UninitBullet();

	//弾の終了処理
	UninitExplosion();

	//スコアの終了処理
	UninitScore();

	//ライフの終了処理
	UninitLife();

	//タイムの終了処理
	UninitTime();
}

//----------------------------------------
//　ゲーム画面の更新処理
//----------------------------------------
void UpdateGame(void)
{
	//背景の更新処理
	UpdateBG();

	//ポリゴンの更新処理
	UpdatePLAYER();

	//敵の更新処理
	UpdateEnemy();

	//ステージの更新設定
	UpdateStage();

	//弾の更新処理
	UpdateBullet();

	//弾の更新処理
	UpdateExplosion();

	//スコアの更新処理
	UpdateScore();

	//タイムの更新処理
	UpdateTime();

	//ライフの更新処理
	UpdateLife();
}

//----------------------------------------
//　ゲーム画面の描画処理
//----------------------------------------
void DrawGame(void)
{
	//背景の描画処理
	DrawBG();

	//弾の描画処理
	DrawBullet();

	//ステージの描画設定
	DrawStage();

	//爆発の描画処理
	DrawExplosion();

	//敵の描画処理
	DrawEnemy();

	//ポリゴンの描画処理
	DrawPLAYER();

	//スコアの描画処理
	DrawScore();

	//タイムの描画処理
	DrawTime();

	//ライフの描画処理
	DrawLife();
}
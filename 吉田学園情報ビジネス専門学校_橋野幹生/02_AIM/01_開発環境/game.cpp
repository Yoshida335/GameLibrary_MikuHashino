//----------------------------------------
//　ゲーム画面の処理
//　Author：橋野幹生
//----------------------------------------
#include "game.h"
#include "input.h"
#include "bg.h"
#include "player.h"
#include "block.h"
#include "fade.h"
#include "item.h"
#include "time.h"
#include "score.h"
#include "ladder.h"
#include "goal.h"
#include "sound.h"
#include "stage.h"
#include "select.h"
#include "map.h"
#include "pause.h"

//グローバル変数宣言
bool g_bPause = false;		//ポーズ中かどうか

//----------------------------------------
//　ゲーム画面の初期化処理
//----------------------------------------
void InitGame(void)
{
	//ポーズ画面の初期化処理
	InitPause();

	//背景の初期化設定
	InitBG();

	//タイムの初期化設定
	InitTime();

	//スコアの初期化設定
	InitScore();

	//プレイヤーの初期化処理
	InitPlayer();

	//アイテムの初期化処理
	InitItem();

	//ゴールの初期化処理
	InitGoal();

	//梯子の初期化処理
	InitLadder();

	//ブロックの初期化処理
	InitBlock();

	STAGE_No * pSelect;
	pSelect = GetSelect();

	SelectStage(*pSelect);

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM_GAME);

	g_bPause = false;		//ポーズ解除
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

	//タイムの終了処理
	UninitTime();

	//スコアの終了設定
	UninitScore();

	//プレイヤーの終了処理
	UninitPlayer();

	//アイテムの終了処理
	UninitItem();

	//ゴールの終了処理
	UninitGoal();

	//梯子の終了処理
	UninitLadder();

	//ブロックの終了処理
	UninitBlock();

	//ポーズ画面の終了処理
	UninitPause();
}

//----------------------------------------
//　ゲーム画面の更新処理
//----------------------------------------
void UpdateGame(void)
{
	TIMESTATE * pST;
	pST = GetStartTime();

	if (GetKeyboardTrigger(DIK_P) == true)
	{//ポースキー(Pキー)が押された
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == true)
	{
		//ポーズ画面の更新処理
		UpdatePause();
	}

	if (g_bPause == false)
	{//ポーズ中でなければ
		//タイムの更新処理
		UpdateTime();

		//背景の更新処理
		UpdateBG();

		//スコアの更新設定
		UpdateScore();

		if (pST->state == TIME_ON)
		{
			//プレイヤーの更新処理
			UpdatePlayer();
		}

		//アイテムの更新処理
		UpdateItem();

		//ゴールの更新処理
		UpdateGoal();

		//ブロックの更新処理
		UpdateBlock();

		//梯子の更新処理
		UpdateLadder();

		//ステージの更新処理
		UpdateStage();
	}
}

//----------------------------------------
//　ゲーム画面の描画処理
//----------------------------------------
void DrawGame(void)
{
	//背景の描画処理
	DrawBG();

	//ゴールの描画処理
	DrawGoal();

	//ブロックの描画処理
	DrawBlock();

	//アイテムの描画処理
	DrawItem();

	//梯子の描画処理
	DrawLadder();

	//タイムの描画処理
	DrawTime();

	//プレイヤーの描画処理
	DrawPlayer();

	if (g_bPause)
	{
		//ポーズ画面の描画処理
		DrawPause();
	}
}

//---------------------------------------------------
//	ポーズの情報
//---------------------------------------------------
bool * GetPause(void)
{
	return &g_bPause;
}
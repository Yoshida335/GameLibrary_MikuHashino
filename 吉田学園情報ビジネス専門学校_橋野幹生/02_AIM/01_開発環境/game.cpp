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
#include "button.h"
#include "goal.h"
#include "sound.h"
#include "stage.h"
#include "select.h"

//グローバル変数宣言
bool g_bPause = false;		//ポーズ中かどうか

void InitGame(void)
{
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

	//ボタンの初期化処理
	InitButton();

	STAGE_No * pSelect;
	pSelect = GetSelect();

	Stage(*pSelect);

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM_GAME);

	g_bPause = false;		//ポーズ解除
}

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

	//ボタンの終了処理
	UninitButton();
}

void UpdateGame(void)
{
	STARTTIME * pST;
	pST = GetStartTime();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		//モード設定(ゲーム画面に移行)
		//SetFade(MODE_RESULT);
	}
	else
	{
		if (GetKeyboardTrigger(DIK_P) == true)
		{//ポースキー(Pキー)が押された
			g_bPause = g_bPause ? false : true;
		}

		if (g_bPause == false)
		{//ポーズ中でなければ
			//タイムの更新処理
			UpdateTime();

			if (pST->state == TIME_ON)
			{
				//背景の更新処理
				UpdateBG();

				//スコアの更新設定
				UpdateScore();

				//プレイヤーの更新処理
				UpdatePlayer();

				//アイテムの更新処理
				UpdateItem();

				//ゴールの更新処理
				UpdateGoal();

				//梯子の更新処理
				UpdateLadder();

				//ブロックの更新処理
				UpdateBlock();

				//ボタンの更新処理
				UpdateButton();

				UpdateStage();
			}
		}
	}
}

void DrawGame(void)
{
	//背景の描画処理
	DrawBG();

	//ゴールの描画処理
	DrawGoal();

	//ブロックの描画処理
	DrawBlock();

	//梯子の描画処理
	DrawLadder();

	//アイテムの描画処理
	DrawItem();

	//ボタンの描画処理
	DrawButton();

	//タイムの描画処理
	DrawTime();

	//スコアの描画設定
	//DrawScore();

	//プレイヤーの描画処理
	DrawPlayer();
}


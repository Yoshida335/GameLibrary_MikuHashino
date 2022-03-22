//----------------------------------------
//　ゲーム画面の処理
//　Author：橋野幹生
//----------------------------------------
#include "game.h"
#include "input.h"
#include "fade.h"
#include "time.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "polygon.h"
#include "input.h"
#include "model.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "bullet.h"
#include "meshfield.h"
#include "meshcylinder.h"
#include "meshsphere.h"
#include "effect.h"
#include "particle.h"
#include "player.h"
#include "line.h"
#include "enemy.h"
#include "collision.h"
#include "map.h"
#include "gage.h"
#include "scoregage.h"
#include "deletemodel.h"
#include "explosion.h"
#include "mouse.h"
#include "pause.h"

//グローバル変数宣言
bool g_bPause = false;		//ポーズ中かどうか

//---------------------------------------------------
//	ゲーム画面の初期化処理
//---------------------------------------------------
void InitGame(void)
{
	//ポーズ画面の初期化処理
	InitPause();

	//カメラの初期設定
	InitCamera();

	//ライトの初期設定
	InitLight();

	//タイマーの初期設定
	InitTime();

	//ポリゴンの初期設定
	InitPolygon();

	//エフェクトの初期設定
	InitEffect();

	//パーティクルの初期設定
	InitParticle();

	//メッシュフィールド(平面)の初期設定
	InitMeshfield();

	//メッシュ(円柱)の初期設定
	InitMeshCylinder();

	//メッシュ(半球)の初期設定
	InitMeshSphere();

	//影の初期設定
	InitShadow();

	//ラインの初期設定
	InitLine();

	//ライフゲージの初期設定
	InitGage();

	//スコアゲージの初期設定
	InitScoreGage();

	//爆発の初期設定
	InitExplosion();

	//破壊後モデルの初期設定
	InitDeleteModel();

	//モデルの初期設定
	InitModel();

	//敵の初期設定
	InitEnemy();

	//プレイヤーの初期設定
	InitPlayer();

	//当たり判定の初期設定
	InitCollision();

	//ビルボードの初期設定
	InitBillboard();

	//弾の初期設定
	InitBullet();

	//壁の初期設定
	InitWall();

	//マップの設定
	SetMap();

	g_bPause = false;		//ポーズ解除

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM_GAME);
}

//---------------------------------------------------
//	ゲーム画面の終了処理
//---------------------------------------------------
void UninitGame(void)
{
	//サウンドの停止
	StopSound();

	//爆発の終了処理
	UninitExplosion();

	//ビルボードの終了処理
	UninitBillboard();

	//ライフゲージの終了処理
	UninitGage();

	//スコアゲージの終了処理
	UninitScoreGage();

	//弾の終了処理
	UninitBullet();

	//壁の終了処理
	UninitWall();

	//影の終了処理
	UninitShadow();

	//モデルの終了処理
	UninitModel();

	//破壊後モデルの終了処理
	UninitDeleteModel();

	//敵の終了処理
	UninitEnemy();

	//ラインの終了処理
	UninitLine();

	//当たり判定の終了処理
	UninitCollision();

	//プレイヤーの終了処理
	UninitPlayer();

	//ポリゴンの終了処理
	UninitPolygon();

	//メッシュフィールドの終了処理
	UninitMeshfield();

	//メッシュ(円柱)の終了処理
	UninitMeshCylinder();

	//メッシュ(半球)の終了処理
	UninitMeshSphere();

	//パーティクルの終了処理
	UninitParticle();

	//エフェクトの終了処理
	UninitEffect();

	//タイマーの終了処理
	UninitTime();

	//ライトの終了処理
	UninitLight();

	//カメラの終了処理
	UninitCamera();

	//マウスの終了処理
	UninitMouse();

	//ポーズ画面の終了処理
	UninitPause();
}

//---------------------------------------------------
//	ゲーム画面の更新処理
//---------------------------------------------------
void UpdateGame(void)
{
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
		//カメラの更新処理
		UpdateCamera();

		//ライトの更新処理
		UpdateLight();

		//タイマーの更新処理
		UpdateTime();

		//ポリゴンの更新処理
		UpdatePolygon();

		//エフェクトの更新処理
		UpdateEffect();

		//パーティクルの更新処理
		UpdateParticle();

		//メッシュフィールドの更新処理
		UpdateMeshfield();

		//メッシュ(円柱)の更新処理
		UpdateMeshCylinder();

		//メッシュ(半球)の更新処理
		UpdateMeshSphere();

		//プレイヤーの更新処理
		UpdatePlayer();

		//敵の更新処理
		UpdateEnemy();

		//爆発の更新処理
		UpdateExplosion();

		//当たり判定の更新処理
		UpdateCollision();

		//モデルの更新処理
		UpdateModel();

		//破壊後モデルの更新処理
		UpdateDeleteModel();

		//ラインの更新処理
		UpdateLine();

		//影の更新処理
		UpdateShadow();

		//ビルボードの更新処理
		UpdateBillboard();

		//ライフゲージの更新処理
		UpdateGage();

		//スコアゲージの更新処理
		UpdateScoreGage();

		//弾の更新処理
		UpdateBullet();

		//壁の更新処理
		UpdateWall();
	}

	//マウスの更新処理
	UpdateMouse();
}

//---------------------------------------------------
//	ゲーム画面の描画処理
//---------------------------------------------------
void DrawGame(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVIEWPORT9 viewport;		//ビューポート

	pDevice->GetViewport(&viewport);

	//カメラの情報取得
	CAMERA * pCamera = GetCamera();

	for (int i = 0; i < 2; i++)
	{
		//ビューポートの設定
		pDevice->SetViewport(&pCamera[i].viewport);

		//画面クリア
		pDevice->Clear(0, NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(0, 0, 0, 0),
			1.0f, 0);

		//カメラの描画処理
		SetCamera(i);

		//マウスの描画処理
		DrawMouse();

		//ポリゴンの描画処理
		//DrawPolygon();

		//メッシュフィールドの描画処理
		DrawMeshfield();

		//破壊後モデルの描画処理
		DrawDeleteModel();

		//モデルの描画処理
		DrawModel();

		//ラインの描画処理
		DrawLine();

		//プレイヤーの描画処理
		DrawPlayer();

		//敵の描画処理
		DrawEnemy();

		//当たり判定の描画処理
		DrawCollision();

		//影の描画処理
		DrawShadow();

		//メッシュ(円柱)の描画処理
		DrawMeshCylinder();

		//メッシュ(半球)の描画処理
		DrawMeshSphere();

		//壁の描画処理
		DrawWall();

		//ビルボードの描画処理
		DrawBillboard();

		//ライフゲージの描画処理
		DrawGage();

		//スコアゲージの描画処理
		DrawScoreGage();

		//爆発の描画処理
		DrawExplosion();

		//弾の描画処理
		DrawBullet();

		//エフェクトの描画処理
		DrawEffect();

		//パーティクルの描画処理
		DrawParticle();

		//タイマーの描画処理
		DrawTime();

		if (g_bPause == true)
		{
			//ポーズ画面の描画処理
			DrawPause();
		}
	}

	pDevice->SetViewport(&viewport);
}

//---------------------------------------------------
//	ポーズ中かどうかの情報
//---------------------------------------------------
bool * GetPause(void)
{
	return &g_bPause;
}

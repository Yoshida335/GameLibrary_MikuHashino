//----------------------------------------
//　キーボードの入力処理のヘッダー
//----------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//キーボードの初期化処理
void UninitKeyboard(void);			//キーボードの終了処理
void UpdateKeyboard(void);			//キーボードの更新処理
bool GetKeyboardPress(int nKey);	//キーボードのプレス処理
bool GetKeyboardTrigger(int nKey);	//キーボードのトリガー処理

#endif
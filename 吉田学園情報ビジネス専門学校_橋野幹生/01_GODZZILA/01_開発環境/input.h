//----------------------------------------
//　キーボードの入力
//　Author：橋野幹生
//----------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//キーボードの初期化
void UninitKeyboard(void);				//キーボードの終了
void UpdateKeyboard(void);				//キーボードの更新
bool GetKeyboardPress(int nKey);		//キーボードのプレス情報
bool GetKeyboardTrigger(int nKey);		//キーボードのトリガー情報

#endif
//----------------------------------------
//　マップのヘッダー
//　Author：橋野幹生
//----------------------------------------
#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 Setpos[10];
}SetPos;

void SetMap(void);	//マップの設定
SetPos * GetSetPos(void);

#endif


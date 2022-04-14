//----------------------------------------
//	マップのヘッダー
//	Author：橋野幹生
//----------------------------------------
#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"

//マップの種類
typedef enum
{
	MAP_01 = 0,	//マップ1
	MAP_02		//マップ2
}STAGE_NUMBER;

void SetMap(int nSelect);	//マップの設定

#endif
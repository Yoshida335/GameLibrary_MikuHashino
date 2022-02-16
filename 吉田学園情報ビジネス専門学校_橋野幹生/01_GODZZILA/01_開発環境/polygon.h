//----------------------------------------
//　ポリゴン
//----------------------------------------
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

//マクロ定義
#define POLIGON_X	(50.0f)	// x方向への値	横幅
#define POLIGON_Y	(0.0f)	// y方向への値	高さ
#define POLIGON_Z	(50.0f)	// z方向への値	縦幅

//プロトタイプ宣言
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);

#endif


//----------------------------------------
//@wi
//@AuthorF΄μ²Ά
//----------------------------------------
#ifndef _BG_H_
#define _BG_H_

#include "main.h"

//}Nθ`
#define MAX_BG	(3)	//wiΜΕεeNX`

typedef enum
{
	BG_TITLE = 0,
	BG_RESULT,
	BG_SCORE
}BG_TYPE;

//vg^CvιΎ
void InitBg(void);			//wiΜϊ»
void UninitBg(void);		//wiΜIΉ
void UpdateBg(void);		//wiΜXV
void DrawBg(void);			//wiΜ`ζ
void SetBg(BG_TYPE type);	//wiΜέθ

#endif

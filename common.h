#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

#define DEBUG_H				1
#define DEBUG_PATH			"H:\\SGMap\\clr_image\\1920x1080-dark_souls_artorias-30406.jpg"
#define DEBUG_PATH_LIMIT	0x100


typedef struct double_byte {
	char high_byte;
	char low_byte;
} WORD, *P_WORD;

typedef char IMAGE;
#endif 

/*
 * 4x4_matrix_key_pad.h
 *
 *  Created on: 21.04.2018
 *      Author: Marcus
 */

#ifndef _4X4_MATRIX_KEY_PAD_H_
#define _4X4_MATRIX_KEY_PAD_H_

#include "main.h"
#include "tim.h"
#include "stm32f4xx_hal.h"
#include "dma.h"

typedef enum keyPad {
	key_0,
	key_1,
	key_2,
	key_3,
	key_4,
	key_5,
	key_6,
	key_7,
	key_8,
	key_9,
	key_x,
	key_y,
	key_z,
	key_w,
	key_abs,
	key_dia,
	no_key
}keyPad_t;

void Init_Matrix_Key_Pad(void);
keyPad_t Get_Key(void);



#endif /* 4X4_MATRIX_KEY_PAD_H_ */

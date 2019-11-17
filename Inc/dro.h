/*
 * dro.h
 *
 *  Created on: 10.03.2018
 *      Author: Marcus
 */

#ifndef DRO_H_
#define DRO_H_

#include "ssd2119_LCD.h"
#include "main.h"
#include "tim.h"
#include "stm32f4xx_hal.h"
#include "dma.h"


#define NUMBER_OF_TOOLS 10


typedef enum axis{
	X_Axis,
	Y_Axis,
	Z_Axis,
	W_Axis
}axis_t;

typedef struct position{
	uint16_t x;
	uint16_t y;
	uint16_t z;
	uint16_t w;
}position_t;


typedef enum options{
	absolut,
	relative,
	diameter,
	radius

}options_t;

void Init_DRO(void);
void Init_Encoders(void);
void Update_Abs_Axis_Position(void);
void Update_Display(void);
void Show_StartUp_Dysplay(void);
void Set_Axis_Value(void);
void Abs_Zeroing_Axis(axis_t axis);
void Rel_Zeroing_Axis(axis_t axis);
void Set_Aktive_Tool(uint16_t toolNumber);
void Update_Display(void);
void Read_KeyPad_Value(void);
void Sel_Funktion(void);




#endif /* DRO_H_ */

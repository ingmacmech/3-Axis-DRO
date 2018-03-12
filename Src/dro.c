/*
 * dro.c
 *
 *  Created on: 10.03.2018
 *      Author: Marcus
 */
#include "dro.h"


#define STARTUP_TEXT_X_AXIS "X-Axis  = 000.000 mm"
#define STARTUP_TEXT_Y_AXIS "Y-Axis  = 000.000 mm"
#define STARTUP_TEXT_Z_AXIS "Z-Axis  = 000.000 mm"
#define STARTUP_TEXT_TS_AXIS "TS-Axis = 000.000 mm"
#define STARTUP_TEXT_TOOL "Tool Nr. = 0"

void Show_StartUp_Dysplay(void){

	  LCD_DisplayStringLine(LINE(2), (uint8_t *)STARTUP_TEXT_X_AXIS);
	  LCD_DisplayStringLine(LINE(3), (uint8_t *)STARTUP_TEXT_Y_AXIS);
	  LCD_DisplayStringLine(LINE(4), (uint8_t *)STARTUP_TEXT_Z_AXIS);
	  LCD_DisplayStringLine(LINE(5), (uint8_t *)STARTUP_TEXT_TS_AXIS);
	  LCD_DisplayStringLine(LINE(7), (uint8_t *)STARTUP_TEXT_TOOL);

}

void Enable_Encoders(void){

}



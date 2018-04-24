/*
 * dro.c
 *
 *  Created on: 10.03.2018
 *      Author: Marcus
 */



#include "dro.h"
#include "main.h"
#include "tim.h"

#define STARTUP_TEXT_X_AXIS  "X =  000.000 mm"
#define STARTUP_TEXT_Y_AXIS  "Y =  000.000 mm"
#define STARTUP_TEXT_Z_AXIS  "Z =  000.000 mm"
#define STARTUP_TEXT_TS_AXIS "W =  000.000 mm"
#define STARTUP_TEXT_TOOL    "Tool Nr. = 0"
#define X_AXIS_LINE 1
#define Y_AXIS_LINE 2
#define Z_AXIS_LINE 3
#define W_AXIS_LINE 4
#define TOOL_NUMBER_LINE 6

#define CHARACTER_PER_LINE 21
#define INTEGER_PART(v) ((int32_t)v)
#define DECIMAL_PART(v) ((int32_t)((v - (double)(int32_t)v) * DECIMAL_DIGITS))

#define DECIMAL_DIGITS 1000
#define TIM_X_AXIS TIM4
#define TIM_Y_AXIS TIM1
#define TIM_Z_AXIS TIM3


void Unlock_Encoders(void);

typedef struct absAxisPositions{
	int32_t x;
	int32_t y;
	int32_t z;
	int32_t w;
}absAxisPositions_t;


typedef struct toolOffsets{

	int32_t xAbsOffset;
	int32_t yAbsOffste;
	int32_t zAbsOffset;

	int32_t xRelOffset;
	int32_t yRelOffste;
	int32_t zRelOffset;

} toolOffsets_t;

typedef struct displayPositionValue{

	int32_t  xIntegerPart;
	int32_t xDecimalPart;

	int32_t  yIntegerPart;
    int32_t yDecimalPart;

    int32_t  zIntegerPart;
    int32_t zDecimalPart;

    int32_t  wIntegerPart;
    int32_t wDecimalPart;

}displayPositionValue_t;

toolOffsets_t *offsets[NUMBER_OF_TOOLS];

uint16_t aktiveTool = 0;
int32_t xOverflowCounter=0;
int32_t yOverflowCounter=0;
int32_t zOverflowCounter=0;
int32_t wOverflowCounter=0;
absAxisPositions_t absolutPositions;
displayPositionValue_t posToDislay;
void Init_Encoders(void){

	/* x-Axis*/
	__HAL_TIM_URS_ENABLE(&htim4);
	TIM4->CNT = TIMER_OFFSET_16BIT;
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
	HAL_TIM_Base_Start_IT(&htim4);

    /* y-Axis */
	__HAL_TIM_URS_ENABLE(&htim1) ;
	TIM1->CNT = TIMER_OFFSET_16BIT;
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);


	/* z-Axis */
	__HAL_TIM_URS_ENABLE(&htim3);
	TIM3->CNT = TIMER_OFFSET_16BIT;
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	HAL_TIM_Base_Start_IT(&htim3);

	/* w-Axis */
	//TODO: Implement Init w-Axis

	/* Unlock all Encoders */
	Unlock_Encoders();

}

void Update_Abs_Axis_Position(void){

	/* x-Axis */
	absolutPositions.x = (TIM4->CNT - TIMER_OFFSET_16BIT + xOverflowCounter * TIMER_OFFSET_16BIT);

    /* y-Axis */
	absolutPositions.y = (TIM1->CNT - TIMER_OFFSET_16BIT + yOverflowCounter * TIMER_OFFSET_16BIT);

	/* z-Axis */
	absolutPositions.z = (TIM3->CNT - TIMER_OFFSET_16BIT + zOverflowCounter * TIMER_OFFSET_16BIT);

	/* w-Axis */
	absolutPositions.w = 0;
	//TODO: Implement w-Axis

}


void Show_StartUp_Dysplay(void){

	  LCD_DisplayStringLine(LINE(X_AXIS_LINE), (uint8_t *)STARTUP_TEXT_X_AXIS);
	  LCD_DisplayStringLine(LINE(Y_AXIS_LINE), (uint8_t *)STARTUP_TEXT_Y_AXIS);
	  LCD_DisplayStringLine(LINE(Z_AXIS_LINE), (uint8_t *)STARTUP_TEXT_Z_AXIS);
	  LCD_DisplayStringLine(LINE(W_AXIS_LINE), (uint8_t *)STARTUP_TEXT_TS_AXIS);
	  LCD_DisplayStringLine(LINE(TOOL_NUMBER_LINE), (uint8_t *)STARTUP_TEXT_TOOL);

}

void Set_Axis_Value(void){

	float tempPosition = 0.0;

	/* x-Axis */
	tempPosition = (float)(absolutPositions.x * 2.0 / 1024);
	posToDislay.xIntegerPart = INTEGER_PART(tempPosition);
	posToDislay.xDecimalPart = DECIMAL_PART(tempPosition);
	if(posToDislay.xDecimalPart < 0) posToDislay.xDecimalPart *= -1;

	/* y-Axis */
	tempPosition = (float)(absolutPositions.y * 2.0 / 1024);
	posToDislay.yIntegerPart = INTEGER_PART(tempPosition);
	posToDislay.yDecimalPart = DECIMAL_PART(tempPosition);
	if(posToDislay.yDecimalPart < 0) posToDislay.yDecimalPart *= -1;

	/* z-Axis */
	tempPosition = (float)(absolutPositions.z * 2.0 / 1024);
	posToDislay.zIntegerPart = INTEGER_PART(tempPosition);
	posToDislay.zDecimalPart = DECIMAL_PART(tempPosition);
	if(posToDislay.zDecimalPart < 0) posToDislay.zDecimalPart *= -1;

	/* w-Axis */
	tempPosition = (float)(absolutPositions.w * 2.0 / 1024);
	posToDislay.wIntegerPart = INTEGER_PART(tempPosition);
	posToDislay.wDecimalPart = DECIMAL_PART(tempPosition);
	if(posToDislay.wDecimalPart < 0) posToDislay.wDecimalPart *= -1;

}

void Unlock_Encoders(void){

	HAL_GPIO_WritePin(CSn_GPIO_Port, CSn_Pin, GPIO_PIN_RESET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(CSn_GPIO_Port, CSn_Pin, GPIO_PIN_SET);

}

void Abs_Zeroing_Axis(axis_t axis){

	switch (axis) {
		case X_Axis:
			TIM_X_AXIS->CNT = TIMER_OFFSET_16BIT;
			xOverflowCounter = 0;
			break;
		case Y_Axis:
			TIM_Y_AXIS->CNT = TIMER_OFFSET_16BIT;
			yOverflowCounter = 0;
			break;
		case Z_Axis:
			TIM_Z_AXIS->CNT = TIMER_OFFSET_16BIT;
			zOverflowCounter = 0;
			break;
		case W_Axis:
			//TODO: w-Axis
			break;
		default:
			break;
	}
}

void Rel_Zeroing_Axis(axis_t axis){
	switch (axis) {
			case X_Axis:

				break;
			case Y_Axis:

				break;
			case Z_Axis:

				break;
			case W_Axis:

				break;
			default:
				break;
		}
}


void Set_Aktive_Tool(uint16_t toolNumber){
	aktiveTool = toolNumber;
}

void Update_Display(void){

	char xBuffer[CHARACTER_PER_LINE];
	char yBuffer[CHARACTER_PER_LINE];
	char zBuffer[CHARACTER_PER_LINE];
	char wBuffer[CHARACTER_PER_LINE];

	Update_Abs_Axis_Position();
	Set_Axis_Value();


	snprintf(xBuffer, CHARACTER_PER_LINE, "X = %4ld.%03ld", posToDislay.xIntegerPart, posToDislay.xDecimalPart);
	snprintf(yBuffer, CHARACTER_PER_LINE, "Y = %4ld.%03ld", posToDislay.yIntegerPart, posToDislay.yDecimalPart);
	snprintf(zBuffer, CHARACTER_PER_LINE, "Z = %4ld.%03ld", posToDislay.zIntegerPart, posToDislay.zDecimalPart);
	snprintf(wBuffer, CHARACTER_PER_LINE, "W = %4ld.%03ld", posToDislay.wIntegerPart, posToDislay.wDecimalPart);

	LCD_DisplayStringLine(LINE(X_AXIS_LINE), (uint8_t *)xBuffer);
	LCD_DisplayStringLine(LINE(Y_AXIS_LINE), (uint8_t *)yBuffer);
	LCD_DisplayStringLine(LINE(Z_AXIS_LINE), (uint8_t *)zBuffer);
	LCD_DisplayStringLine(LINE(W_AXIS_LINE), (uint8_t *)wBuffer);


}

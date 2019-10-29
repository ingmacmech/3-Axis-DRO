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
#define TIM_W_AXIS TIM2


void Unlock_Encoders(void);

typedef struct axisPositions{
	int32_t x;
	int32_t y;
	int32_t z;
	int32_t w;
}axisPositions_t;


typedef struct offsets{

	int32_t x;
	int32_t y;
	int32_t z;
	int32_t w;

} offsets_t;

typedef struct displayPositionValue{

	int32_t xIntegerPart;
	int32_t xDecimalPart;
	char xNegSign;

	int32_t yIntegerPart;
    int32_t yDecimalPart;
    char yNegSign;

    int32_t zIntegerPart;
    int32_t zDecimalPart;
    char zNegSign;

    int32_t wIntegerPart;
    int32_t wDecimalPart;
    char wNegSign;

}displayPositionValue_t;

typedef struct droOptions{
	options_t coordinate;
	options_t xAxis;

}droOptions_t;

offsets_t *toolOffsets[NUMBER_OF_TOOLS];

uint16_t aktiveTool = 0;
int32_t xOverflowCounter=0;
int32_t yOverflowCounter=0;
int32_t zOverflowCounter=0;
int32_t wOverflowCounter=0;
axisPositions_t absolutPositions;
axisPositions_t relativePositions;
offsets_t relativeOffsets;
char selectedAxis[4] = {'<',' ',' ',' '};
uint8_t newSelAxisCounter = 0;
uint8_t oldSelAxisCounter = 0;
uint8_t toolNumber = 0;
displayPositionValue_t posToDisplay;
droOptions_t options;

void Init_DRO(void){

	/* Init Options */
	options.coordinate = absolut;
	options.xAxis = radius;

	Init_Encoders();
}

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
	HAL_TIM_Base_Start_IT(&htim1);


	/* z-Axis */
	__HAL_TIM_URS_ENABLE(&htim3);
	TIM3->CNT = TIMER_OFFSET_16BIT;
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	HAL_TIM_Base_Start_IT(&htim3);

	/* w-Axis */
	__HAL_TIM_URS_ENABLE(&htim2);
	TIM2->CNT = TIMER_OFFSET_16BIT;
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	HAL_TIM_Base_Start_IT(&htim2);

	/* Unlock all Encoders */
	Unlock_Encoders();

}


void Update_Abs_Axis_Position(void){

	/* x-Axis */
	absolutPositions.x = (TIM_X_AXIS->CNT - TIMER_OFFSET_16BIT + xOverflowCounter * TIMER_OFFSET_16BIT);

    /* y-Axis */
	absolutPositions.y = (TIM_Y_AXIS->CNT - TIMER_OFFSET_16BIT + yOverflowCounter * TIMER_OFFSET_16BIT);

	/* z-Axis */
	absolutPositions.z = (TIM_Z_AXIS->CNT - TIMER_OFFSET_16BIT + zOverflowCounter * TIMER_OFFSET_16BIT);

	/* w-Axis */
	absolutPositions.w = (TIM_W_AXIS->CNT - TIMER_OFFSET_16BIT + wOverflowCounter * TIMER_OFFSET_16BIT);

}

void Update_Rel_Axis_Position(void){

	/* x-Axis */
	relativePositions.x = (TIM_X_AXIS->CNT - TIMER_OFFSET_16BIT + xOverflowCounter * TIMER_OFFSET_16BIT) - relativeOffsets.x;

	/* y- Axis */
	relativePositions.y = (TIM_Y_AXIS->CNT - TIMER_OFFSET_16BIT + yOverflowCounter * TIMER_OFFSET_16BIT) - relativeOffsets.y;

	/* z-Axis */
	relativePositions.z = (TIM_Z_AXIS->CNT - TIMER_OFFSET_16BIT + zOverflowCounter * TIMER_OFFSET_16BIT) - relativeOffsets.z;

	/* w-Axis */
	relativePositions.w = (TIM_W_AXIS->CNT - TIMER_OFFSET_16BIT + wOverflowCounter * TIMER_OFFSET_16BIT) - relativeOffsets.w;


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
	if(options.coordinate == absolut){
		tempPosition = (float)(absolutPositions.x * 2.0 / 1024);
	}
	else{
		tempPosition = (float)(relativePositions.x * 2.0 / 1024);
	}
	posToDisplay.xIntegerPart = INTEGER_PART(tempPosition);
	posToDisplay.xDecimalPart = DECIMAL_PART(tempPosition);

	if(posToDisplay.xDecimalPart < 0){
		posToDisplay.xDecimalPart *= -1;
		posToDisplay.xIntegerPart *= -1;
		posToDisplay.xNegSign = '-';
	}
	else{
		posToDisplay.xNegSign = ' ';
	}

	/* y-Axis */
	if(options.coordinate == absolut){
		tempPosition = (float)(absolutPositions.y * 2.0 / 1024);
	}
	else{
		tempPosition = (float)(relativePositions.y * 2.0 / 1024);
	}
	posToDisplay.yIntegerPart = INTEGER_PART(tempPosition);
	posToDisplay.yDecimalPart = DECIMAL_PART(tempPosition);
	if(posToDisplay.yDecimalPart < 0){
		posToDisplay.yDecimalPart *= -1;
		posToDisplay.yIntegerPart *= -1;
		posToDisplay.yNegSign = '-';
	}
	else{
		posToDisplay.yNegSign = ' ';
	}

	/* z-Axis */
	if(options.coordinate == absolut){
		tempPosition = (float)(absolutPositions.z * 2.0 / 1024);
	}
	else{
		tempPosition = (float)(relativePositions.z * 2.0 / 1024);
	}
	posToDisplay.zIntegerPart = INTEGER_PART(tempPosition);
	posToDisplay.zDecimalPart = DECIMAL_PART(tempPosition);
	if(posToDisplay.zDecimalPart < 0){
		posToDisplay.zDecimalPart *= -1;
		posToDisplay.zIntegerPart *= -1;
		posToDisplay.zNegSign = '-';
	}
	else{
		posToDisplay.zNegSign = ' ';
	}

	/* w-Axis */
	if(options.coordinate == absolut){
		tempPosition = (float)(absolutPositions.w * 2.0 / 1024);
	}
	else{
		tempPosition = (float)(relativePositions.w * 2.0 / 1024);
	}
	posToDisplay.wIntegerPart = INTEGER_PART(tempPosition);
	posToDisplay.wDecimalPart = DECIMAL_PART(tempPosition);
	if(posToDisplay.wDecimalPart < 0){
		posToDisplay.wDecimalPart *= -1;
		posToDisplay.wIntegerPart *= -1;
		posToDisplay.wNegSign = '-';
	}
	else{
		posToDisplay.wNegSign = ' ';
	}
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
			TIM_W_AXIS->CNT = TIMER_OFFSET_16BIT;
			wOverflowCounter = 0;
			break;
		case ALL_Axis:
			TIM_X_AXIS->CNT = TIMER_OFFSET_16BIT;
			xOverflowCounter = 0;

			TIM_Y_AXIS->CNT = TIMER_OFFSET_16BIT;
			yOverflowCounter = 0;

			TIM_Z_AXIS->CNT = TIMER_OFFSET_16BIT;
			zOverflowCounter = 0;

			TIM_W_AXIS->CNT = TIMER_OFFSET_16BIT;
			wOverflowCounter = 0;
			break;
		default:
			break;
	}
}

void Rel_Zeroing_Axis(axis_t axis){
	switch (axis) {
			case X_Axis:
				relativeOffsets.x = (TIM_X_AXIS->CNT - TIMER_OFFSET_16BIT + xOverflowCounter * TIMER_OFFSET_16BIT);
				break;
			case Y_Axis:
				relativeOffsets.y = (TIM_Y_AXIS->CNT - TIMER_OFFSET_16BIT + yOverflowCounter * TIMER_OFFSET_16BIT);
				break;
			case Z_Axis:
				relativeOffsets.z = (TIM_Z_AXIS->CNT - TIMER_OFFSET_16BIT + zOverflowCounter * TIMER_OFFSET_16BIT);
				break;
			case W_Axis:
				relativeOffsets.w = (TIM_W_AXIS->CNT - TIMER_OFFSET_16BIT + wOverflowCounter * TIMER_OFFSET_16BIT);
				break;
			case ALL_Axis:
				relativeOffsets.x = (TIM_X_AXIS->CNT - TIMER_OFFSET_16BIT + xOverflowCounter * TIMER_OFFSET_16BIT);
				relativeOffsets.y = (TIM_Y_AXIS->CNT - TIMER_OFFSET_16BIT + yOverflowCounter * TIMER_OFFSET_16BIT);
				relativeOffsets.z = (TIM_Z_AXIS->CNT - TIMER_OFFSET_16BIT + zOverflowCounter * TIMER_OFFSET_16BIT);
				relativeOffsets.w = (TIM_W_AXIS->CNT - TIMER_OFFSET_16BIT + wOverflowCounter * TIMER_OFFSET_16BIT);
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
	char toolBuffer[CHARACTER_PER_LINE];
	char coordinateAbs[4] = {'a','b','s','\n'};
 	char coordinateInc[4] = {'i','n','c','\n'};


	Update_Abs_Axis_Position();
	Update_Rel_Axis_Position();
	Set_Axis_Value();


	snprintf(xBuffer, CHARACTER_PER_LINE, "X = %c%ld.%03ld mm %c   ", posToDisplay.xNegSign, posToDisplay.xIntegerPart, posToDisplay.xDecimalPart, selectedAxis[0]);
	snprintf(yBuffer, CHARACTER_PER_LINE, "Y = %c%ld.%03ld mm %c   ", posToDisplay.yNegSign, posToDisplay.yIntegerPart, posToDisplay.yDecimalPart, selectedAxis[1]);
	snprintf(zBuffer, CHARACTER_PER_LINE, "Z = %c%ld.%03ld mm %c   ", posToDisplay.zNegSign, posToDisplay.zIntegerPart, posToDisplay.zDecimalPart, selectedAxis[2]);
	snprintf(wBuffer, CHARACTER_PER_LINE, "W = %c%ld.%03ld mm %c   ", posToDisplay.wNegSign, posToDisplay.wIntegerPart, posToDisplay.wDecimalPart, selectedAxis[3]);
	if(options.coordinate == absolut){
		snprintf(toolBuffer, CHARACTER_PER_LINE, "Tool Nr. = %02u %s", toolNumber, coordinateAbs);
	}
	else{
		snprintf(toolBuffer, CHARACTER_PER_LINE, "Tool Nr. = %02u %s", toolNumber, coordinateInc);
	}

	LCD_DisplayStringLine(LINE(X_AXIS_LINE), (uint8_t *)xBuffer);
	LCD_DisplayStringLine(LINE(Y_AXIS_LINE), (uint8_t *)yBuffer);
	LCD_DisplayStringLine(LINE(Z_AXIS_LINE), (uint8_t *)zBuffer);
	LCD_DisplayStringLine(LINE(W_AXIS_LINE), (uint8_t *)wBuffer);
	LCD_DisplayStringLine(LINE(TOOL_NUMBER_LINE), (uint8_t *)toolBuffer);


}

void Read_KeyPad_Value(void){

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	switch (GPIO_Pin) {
		case BUTTON_X_ZERRO_Pin:

			if(options.coordinate == absolut){
				Abs_Zeroing_Axis(X_Axis);
			}
			else{
				Rel_Zeroing_Axis(X_Axis);
			}
			break;

		case BUTTON_Y_ZERRO_Pin:

			if(options.coordinate == absolut){
				Abs_Zeroing_Axis(Y_Axis);
			}
			else{
				Rel_Zeroing_Axis(Y_Axis);
			}
			break;

		case BUTTON_Z_ZERRO_Pin:

			if(options.coordinate == absolut){
				Abs_Zeroing_Axis(Z_Axis);
			}
			else{
				Rel_Zeroing_Axis(Z_Axis);
			}
			break;

		case BUTTON_W_ZERRO_Pin:

			if(options.coordinate == absolut){
				Abs_Zeroing_Axis(W_Axis);
			}
			else{
				Rel_Zeroing_Axis(W_Axis);
			}
			break;

		case BUTTON_SEL_Pin:

			selectFlag = 1;

			break;

		case BUTTON_SET_Pin:

			setFlag = 1;

			break;

		case BUTTON_ENTER_Pin:

			enterFlag = 1;

		break;

		/*case BUTTON_AXIS_Pin:

			if(newSelAxisCounter != 3){
				newSelAxisCounter++;
			}
			else{
				newSelAxisCounter = 0;
			}
			selectedAxis[newSelAxisCounter] = '<';
			selectedAxis[oldSelAxisCounter] = ' ';

			if(oldSelAxisCounter != 3){
				oldSelAxisCounter++;
			}
			else{
				oldSelAxisCounter = 0;
			}
			break;

		case BUTTON_UP_Pin:

			if(toolNumber != NUMBER_OF_TOOLS){
				toolNumber++;
			}
			else{
				toolNumber = 0;
			}
			break;

		case BUTTON_DOWN_Pin:

			if(toolNumber != 0){
				toolNumber--;
			}
			else{
				toolNumber = NUMBER_OF_TOOLS;
			}
			break;*/

		case BUTTON_ABS_Pin:
			if(options.coordinate == absolut){
				options.coordinate = relative;
			}
			else{
				options.coordinate = absolut;
			}

			break;

		default:
			break;
	}
}


void Sel_Function(void){

	selectFlag = 0;

	while(enterFlag != 1){

	}

	enterFlag = 0;
}


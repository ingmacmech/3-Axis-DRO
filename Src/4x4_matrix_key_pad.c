/*
 * 4x4_matrix_key_pad.c
 *
 *  Created on: 21.04.2018
 *      Author: Marcus
 */
#include "4x4_matrix_key_pad.h"

#define NUMBER_OF_ROWS 4
#define NUMBER_OF_COLUMS 4
#define COLUMN_0 0x0001
#define COLUMN_1 0x0002
#define COLUMN_2 0x0004
#define COLUMN_3 0x0008

extern DMA_HandleTypeDef hdma_tim8_up;
extern DMA_HandleTypeDef hdma_tim8_ch2;

// Last index is not filled with data to interpret
volatile uint16_t pinStateInput[] = {0xF000, 0xF000, 0xF000, 0xF000, 0xF000};

// Bit sequence to set each row to high
volatile uint32_t pinStateOutput[] = {0x00000040,	//Reset     / Set PC6
									  0x00400080,	//Reset PC6 / Set PC7
									  0x00800100,	//Reset PC7 / Set PC8
									  0x01000200,   //Reset PC8 / Set PC9
									  0x02000000};	//Reset PC9 / Set

keyPad_t keyMatrix[4][4] = {{key_7,key_8,key_9,key_x},
						    {key_4,key_5,key_6,key_y},
						    {key_1,key_2,key_3,key_z},
						    {key_abs,key_0,key_dia,key_w}};

void Init_Matrix_Key_Pad(void){

	HAL_TIMEx_PWMN_Start(&htim8,TIM_CHANNEL_2);
	HAL_DMA_Start(&hdma_tim8_up,(uint32_t)pinStateOutput, (uint32_t)&GPIOC->BSRR,5);
	HAL_DMA_Start(&hdma_tim8_ch2,(uint32_t)&GPIOB->IDR, (uint32_t)pinStateInput,5);
	__HAL_TIM_ENABLE_DMA(&htim8, TIM_DMA_UPDATE);
	__HAL_TIM_ENABLE_DMA(&htim8, TIM_DMA_CC2);
	__HAL_TIM_ENABLE(&htim8);

}

keyPad_t Get_Key(void){

	uint16_t tempPinState;
	int8_t tempRow = -1;
	int8_t tempColumn = -1;
	keyPad_t tempKey = no_key;

	for (uint8_t i = 0; i < NUMBER_OF_ROWS; i++){
		tempPinState = pinStateInput[i+1] << 1;
		tempPinState = tempPinState >> 12;

		if (tempPinState != 0){
			tempRow = i;

			switch (tempPinState) {
				case COLUMN_0:
					tempColumn = 0;
					break;
				case COLUMN_1:
					tempColumn = 1;
					break;
				case COLUMN_2:
					tempColumn = 2;
					break;
				case COLUMN_3:
					tempColumn = 3;
					break;
				default:
					break;
			}
		}
	}

	if(tempRow != -1 && tempColumn != -1){
		tempKey = keyMatrix[tempColumn][tempRow];
	}

	return tempKey;

}


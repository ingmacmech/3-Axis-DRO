/*
 * 4x4_matrix_key_pad.c
 *
 *  Created on: 21.04.2018
 *      Author: Marcus
 */
#include "4x4_matrix_key_pad.h"

extern DMA_HandleTypeDef hdma_tim8_up;
extern DMA_HandleTypeDef hdma_tim8_ch2;

volatile uint16_t pinStateInput[] = {0xF000, 0xF000, 0xF000, 0xF000, 0xF000};

// Bit sequence to set each row to high
volatile uint32_t pinStateOutput[] = {0x00000040,	//Reset     / Set PC6
									  0x00400080,	//Reset PC6 / Set PC7
									  0x00800100,	//Reset PC7 / Set PC8
									  0x01000200,   //Reset PC8 / Set PC9
									  0x02000000};	//Reset PC9 / Set

void Init_Matrix_Key_Pad(){

	HAL_TIMEx_PWMN_Start(&htim8,TIM_CHANNEL_2);
	HAL_DMA_Start(&hdma_tim8_up,(uint32_t)pinStateOutput, (uint32_t)&GPIOC->BSRR,5);
	HAL_DMA_Start(&hdma_tim8_ch2,(uint32_t)&GPIOB->IDR, (uint32_t)pinStateInput,5);
	__HAL_TIM_ENABLE_DMA(&htim8, TIM_DMA_UPDATE);
	__HAL_TIM_ENABLE_DMA(&htim8, TIM_DMA_CC2);
	__HAL_TIM_ENABLE(&htim8);

}




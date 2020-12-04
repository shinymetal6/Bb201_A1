/*
 * control_init.c
 *
 *  Created on: Dec 3, 2020
 *      Author: fil
 */
#include "main.h"

__attribute__ ((aligned (4))) uint16_t		control_buf[CONTROLBUF_LEN];
uint16_t	control_ready;
uint32_t	ain0,ain1,ain2,ain3,ain4,ain5;

void ControlInit(void)
{
	HAL_ADCEx_Calibration_Start(CONTROL_ADC, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(CONTROL_ADC, (uint32_t* )&control_buf , CONTROLBUF_LEN);
	HAL_LPTIM_Counter_Start_IT(CONTROL_LOOP_TIMER,3125);
}

/*
 * dma_mngmt.c
 *
 *  Created on: Nov 21, 2020
 *      Author: fil
 */

#include "main.h"

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
	if (( hadc == AUDIO_0_2_ADC) ||( hadc == AUDIO_1_3_ADC))
	{
		half_in = 1;
		audioin_buffer_ready=1;
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	if (( hadc == AUDIO_0_2_ADC) ||( hadc == AUDIO_1_3_ADC))
	{
		half_in = 0;
		audioin_buffer_ready=1;
	}
	if ( hadc == CONTROL_ADC)
		control_ready = 1;
}

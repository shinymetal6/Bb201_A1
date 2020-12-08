/*
 * port.c
 *
 *  Created on: Dec 5, 2020
 *      Author: fil
 */
#include "main.h"

void audio_timer_start(void)
{
	/*
	HAL_LPTIM_Counter_Start_IT(AUDIO_0_2_LOOP_TIMER,KHZ176400);
	HAL_LPTIM_Counter_Start_IT(AUDIO_1_3_LOOP_TIMER,AUDIO_LOOP_44KHZ);
	*/
	HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_Base_Start_IT(&htim6);

}

void control_timer_start(void)
{
	HAL_LPTIM_Counter_Start_IT(CONTROL_LOOP_TIMER,3125);

}

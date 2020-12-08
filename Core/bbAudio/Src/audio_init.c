/*
 * audio_init.c
 *
 *  Created on: Nov 21, 2020
 *      Author: fil
 */

#include "main.h"
/* Timers :
 * lptim1 & lptim2
 * 			clock = 56.4 from pll3r x94 /4 , value = 10 or 5
 * 			value = 10 -> 44100 ( 44062.5 )
 * 			value =  5 -> 88200 ( 88125   )
 */

void AudioCh0Init(void)
{
	HAL_ADCEx_Calibration_Start(AUDIO_0_2_ADC, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
	HAL_OPAMP_SelfCalibrate(&hopamp1);
	HAL_ADC_Start_DMA(AUDIO_0_2_ADC, (uint32_t* )&audio_buf_0_2_in , AUDIOBUF_LEN);
	HAL_DAC_Start_DMA(AUDIO_0_DAC, OUTCHANNEL_0, (uint32_t* )&audio_buf_0_out, NUMBER_OF_AUDIO_SAMPLES, DAC_ALIGN_12B_R);
	HAL_OPAMP_Start(&hopamp1);
}

#ifdef DUAL
void AudioCh1Init(void)
{
	HAL_ADCEx_Calibration_Start(AUDIO_1_3_ADC, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
	HAL_OPAMP_SelfCalibrate(&hopamp2);
	HAL_ADC_Start_DMA(AUDIO_1_3_ADC, (uint32_t* )&audio_buf_1_3_in , AUDIOBUF_LEN);
	HAL_DAC_Start_DMA(AUDIO_1_DAC, OUTCHANNEL_1, (uint32_t* )&audio_buf_1_out, NUMBER_OF_AUDIO_SAMPLES, DAC_ALIGN_12B_R);
	HAL_OPAMP_Start(&hopamp2);
}
#endif
void AudioInit(void)
{
	half_in = 0;
	audioin_buffer_ready=0;
	AudioCh0Init();
	#ifdef DUAL
	AudioCh1Init();
	#endif
	audio_timer_start();
}

/*
 * fir.c
 *
 *  Created on: Dec 5, 2020
 *      Author: fil
 */

#include "main.h"
#include "arm_math.h"

#define BLOCK_SIZE            64
#define NUM_TAPS_MAX          64
extern	uint16_t	NumTaps;
extern	float fFIRCoef[NUM_TAPS_MAX];

#define FRAC16(x) 32768*x
#define LOG2TAPS(x) 	1/log2(x)

static q15_t 	firState[NUM_TAPS_MAX+BLOCK_SIZE];
int16_t			output[BLOCK_SIZE];
arm_fir_instance_q15	S;
int16_t FIRCoef[NUM_TAPS_MAX];
uint32_t ready=0;

uint32_t FirInit(float fFIRCoef[NUM_TAPS_MAX])
{
uint16_t		i;
	for(i=0;i<NumTaps;i++)
		FIRCoef[i] = FRAC16(fFIRCoef[i]);
	if ( arm_fir_init_q15(&S, NumTaps, FIRCoef, firState, BLOCK_SIZE) == ARM_MATH_SUCCESS )
	{
		ready=1;
		return 0;
	}
	return 1;
}

void do_workbuf_out(void)
{
uint16_t	start;
	HAL_GPIO_WritePin(LOG_GPIO_Port, LOG_Pin, GPIO_PIN_SET);
	if ( ready == 1 )
	{
			start = half_in == 1 ? 0 : HALF_NUMBER_OF_AUDIO_SAMPLES;
			arm_fir_fast_q15(&S, (q15_t *)&audio_workbuf_0in[start] , (q15_t *)&audio_buf_0_out[start], BLOCK_SIZE);
	}
	HAL_GPIO_WritePin(LOG_GPIO_Port, LOG_Pin, GPIO_PIN_RESET);
}


/*
 * fir.c
 *
 *  Created on: Dec 5, 2020
 *      Author: fil
 */

#include "main.h"
#include "arm_math.h"

#define	__int16	int16_t
#define	__int32	int32_t

/**************************************************************
WinFilter version 0.8
http://www.winfilter.20m.com
akundert@hotmail.com

Filter type: Band Pass
Filter model: Raised Cosine
Roll Off Factor: 0.500000
Sampling Frequency: 44 KHz
Fc1 and Fc2 Frequencies: 1.000000 KHz and 3.500000 KHz
Coefficents Quantization: float
***************************************************************/
#define Ntap 64
    float FIRCoef[Ntap] = {
        0.00731680507391965860,
        0.01076754587000610500,
        0.01340811930332255600,
        0.01443867842384391100,
        0.01333705688200633900,
        0.01003185102873968000,
        0.00497882704444570570,
        -0.00089202023175091088,
        -0.00636128067146328990,
        -0.01020503314857175800,
        -0.01151811761939514400,
        -0.00999670724569286590,
        -0.00610214522334025670,
        -0.00104903110526674190,
        0.00340178778312991280,
        0.00531819716179623980,
        0.00306813732388338790,
        -0.00421573652987442160,
        -0.01629044292229121400,
        -0.03167175466370372700,
        -0.04777264391022742500,
        -0.06130846292720475800,
        -0.06890494455013318500,
        -0.06779391431725637100,
        -0.05645304650705040100,
        -0.03504799380802129500,
        -0.00556898921694990840,
        0.02838651855846491300,
        0.06216071473987779000,
        0.09081665813878959900,
        0.11000625795497546000,
        0.11675493417420535000,
        0.11000625795497546000,
        0.09081665813878959900,
        0.06216071473987779000,
        0.02838651855846491300,
        -0.00556898921694990840,
        -0.03504799380802129500,
        -0.05645304650705040100,
        -0.06779391431725637100,
        -0.06890494455013318500,
        -0.06130846292720475800,
        -0.04777264391022742500,
        -0.03167175466370372700,
        -0.01629044292229121400,
        -0.00421573652987442160,
        0.00306813732388338790,
        0.00531819716179623980,
        0.00340178778312991280,
        -0.00104903110526674190,
        -0.00610214522334025670,
        -0.00999670724569286590,
        -0.01151811761939514400,
        -0.01020503314857175800,
        -0.00636128067146328990,
        -0.00089202023175091088,
        0.00497882704444570570,
        0.01003185102873968000,
        0.01333705688200633900,
        0.01443867842384391100,
        0.01340811930332255600,
        0.01076754587000610500,
        0.00731680507391965860,
        0.00391559364625231920
    };

    int16_t FIRCoefInt[Ntap] = {
             1918,
             2822,
             3514,
             3785,
             3496,
             2629,
             1305,
             -233,
            -1667,
            -2675,
            -3019,
            -2620,
            -1599,
             -274,
              891,
             1394,
              804,
            -1105,
            -4270,
            -8302,
            -12523,
            -16071,
            -18063,
            -17771,
            -14798,
            -9187,
            -1459,
             7441,
            16295,
            23807,
            28837,
            30606,
            28837,
            23807,
            16295,
             7441,
            -1459,
            -9187,
            -14798,
            -17771,
            -18063,
            -16071,
            -12523,
            -8302,
            -4270,
            -1105,
              804,
             1394,
              891,
             -274,
            -1599,
            -2620,
            -3019,
            -2675,
            -1667,
             -233,
             1305,
             2629,
             3496,
             3785,
             3514,
             2822,
             1918,
             1026
        };

q15_t FIRCoefuInt[Ntap];

static float x[Ntap]; //input samples
float fir(float NewSample) {
float y=0;            //output sample
int n;

    //shift the old samples
    for(n=Ntap-1; n>0; n--)
       x[n] = x[n-1];

    //Calculate the new output
    x[0] = NewSample;
    for(n=0; n<Ntap; n++)
        y += FIRCoef[n] * x[n];

    return y+32768;
}
/*
 *
 *
 *
 */

#define TEST_LENGTH_SAMPLES  64
#define BLOCK_SIZE            64
#define NUM_TAPS              64

static q15_t firState[BLOCK_SIZE + NUM_TAPS - 1];

void fir_cmsis(void)
{
arm_fir_instance_q15	S;
q15_t  *input, *output;
  /* Initialize input and output buffer pointers */
  input = (q15_t *)&audio_workbuf_0in[0];
  output = (q15_t *)&audio_buf_0_out[0];
  arm_fir_init_q15(&S, NUM_TAPS, (int16_t *)&FIRCoefuInt[0], &firState[0], BLOCK_SIZE);
  arm_fir_fast_q15(&S, input , output, BLOCK_SIZE);
}

#define	CMSIS_FIR


void do_workbuf_out(void)
{
	HAL_GPIO_WritePin(LOG_GPIO_Port, LOG_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LOG_GPIO_Port, LOG_Pin, GPIO_PIN_SET);
#ifdef	CMSIS_FIR
	fir_cmsis();
#else
uint16_t	i,start,end;

		if ( half_in == 1)
		{
			start=0;
			end = HALF_NUMBER_OF_AUDIO_SAMPLES;
		}
		else
		{
			start=HALF_NUMBER_OF_AUDIO_SAMPLES;
			end = NUMBER_OF_AUDIO_SAMPLES;

		}
		for ( i=start;i<end;i++)
		{
			audio_buf_0_out[i] = (uint16_t)(fir(audio_workbuf_0in[i]));
			audio_buf_0_out[i] >>= 4;
		}
#endif
	HAL_GPIO_WritePin(LOG_GPIO_Port, LOG_Pin, GPIO_PIN_RESET);
}

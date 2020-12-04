/*
 * bbAudio.h
 *
 *  Created on: Nov 21, 2020
 *      Author: fil
 */

#ifndef BBAUDIO_INC_BBAUDIO_H_
#define BBAUDIO_INC_BBAUDIO_H_

/* Controls */
extern	LPTIM_HandleTypeDef hlptim3;
/* Audio timers */
extern	LPTIM_HandleTypeDef hlptim1;
extern	LPTIM_HandleTypeDef hlptim2;

#define	INCHANNEL_0		0
#define	INCHANNEL_1		1
#define	OUTCHANNEL_0	0
#define	OUTCHANNEL_1	1
#define	CHANNEL_0		OUTCHANNEL_0
#define	CHANNEL_1		OUTCHANNEL_1
#define	AUDIO_0_2_LOOP_TIMER	&hlptim1
#define	AUDIO_1_3_LOOP_TIMER	&hlptim2
#define	CONTROL_LOOP_TIMER		&hlptim3
#define	AUDIO_LOOP_88KHZ	5
#define	AUDIO_LOOP_44KHZ	10
#define	KHZ352800			499
#define	KHZ176400			997
#define	KHZ88200			1994
#define	KHZ44100			3989
#define	KHZ22050			7980

/* Audio channels */
extern	ADC_HandleTypeDef hadc1;
extern	ADC_HandleTypeDef hadc3;
extern	DMA_HandleTypeDef hdma_adc1;
extern	DMA_HandleTypeDef hdma_adc3;
extern	DAC_HandleTypeDef hdac1;
extern	DMA_HandleTypeDef hdma_dac1_ch1;
extern	DMA_HandleTypeDef hdma_dac1_ch2;
extern	OPAMP_HandleTypeDef hopamp1;
extern	OPAMP_HandleTypeDef hopamp2;



extern	void reset_mdma(void);

/* Controls */
#define		CONTROLBUF_LEN					6
extern	ADC_HandleTypeDef hadc2;
extern	__attribute__ ((aligned (4))) uint16_t		control_buf[CONTROLBUF_LEN];
extern	uint32_t							ain0,ain1,ain2,ain3,ain4,ain5;

uint16_t	control_ready;
#define		CONTROL_ADC				&hadc2
#define		AIN0					0
#define		AIN1					1
#define		AIN2					2
#define		AIN3					3
#define		AIN4					4
#define		AIN5					5
/* Controls Functions */
extern	void ControlInit(void);

/* Audio */
#define		AUDIO_0_2_ADC			&hadc3
#define		AUDIO_1_3_ADC			&hadc1
#define		AUDIO_0_DAC				&hdac1
#define		AUDIO_1_DAC				&hdac1

/* Audio Functions */
extern	void AudioInit(void);


#endif /* BBAUDIO_INC_BBAUDIO_H_ */

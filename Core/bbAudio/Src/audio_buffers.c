/*
 * audio_buffers.c
 *
 *  Created on: Nov 21, 2020
 *      Author: fil
 */
#include "main.h"

__attribute__ ((aligned (4))) uint16_t		audio_buf_0_2_in[AUDIOBUF_LEN];
__attribute__ ((aligned (4))) uint16_t		audio_buf_1_3_in[AUDIOBUF_LEN];

__attribute__ ((aligned (4))) uint16_t		audio_workbuf_0in[NUMBER_OF_AUDIO_SAMPLES];
__attribute__ ((aligned (4))) uint16_t		audio_workbuf_1in[NUMBER_OF_AUDIO_SAMPLES];
__attribute__ ((aligned (4))) uint16_t		audio_workbuf_0out[NUMBER_OF_AUDIO_SAMPLES];
__attribute__ ((aligned (4))) uint16_t		audio_workbuf_1out[NUMBER_OF_AUDIO_SAMPLES];

__attribute__ ((aligned (4))) uint16_t		audio_buf_0_out[NUMBER_OF_AUDIO_SAMPLES];
__attribute__ ((aligned (4))) uint16_t		audio_buf_1_out[NUMBER_OF_AUDIO_SAMPLES];

uint8_t	half_in=0 , audioin_buffer_ready=0, mdma_end_flag , mdma_count;

#define	USE_MDMA_OUT
//#define	USE_MDMA_IN

#ifdef	USE_MDMA_IN

extern	MDMA_HandleTypeDef hmdma_mdma_channel41_sw_0;	/* input */

static void move_block_in(uint32_t DstAddress, uint32_t SrcAddress, uint32_t BlockDataLength)
{
	mdma_end_flag=mdma_count=0;
	HAL_MDMA_Start_IT(&hmdma_mdma_channel41_sw_0, SrcAddress, DstAddress, BlockDataLength, 1);
	while(mdma_end_flag == 0)
		mdma_count++;

}

void do_workbuf_in(void)
{
uint32_t DstAddress, SrcAddress;
	if ( half_in == 1)
	{
		SrcAddress=(uint32_t )&audio_buf_0_2_in[0];
		DstAddress=(uint32_t )&audio_workbuf_0in[0];
	}
	else
	{
		SrcAddress=(uint32_t )&audio_buf_0_2_in[HALF_NUMBER_OF_AUDIO_SAMPLES];
		DstAddress=(uint32_t )&audio_workbuf_0in[HALF_NUMBER_OF_AUDIO_SAMPLES];
	}
	move_block_in(DstAddress, SrcAddress, NUMBER_OF_AUDIO_SAMPLES);
}

#else
void do_workbuf_in(void)
{
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
		audio_workbuf_0in[i] = audio_buf_0_2_in[i*2];
		audio_workbuf_1in[i] = audio_buf_0_2_in[(i*2)+1];
	}
}
#endif

#ifdef	USE_MDMA_OUT

extern	MDMA_HandleTypeDef hmdma_mdma_channel40_sw_0;	/* output */

static void move_block_out(uint32_t DstAddress, uint32_t SrcAddress, uint32_t BlockDataLength)
{
	mdma_end_flag=mdma_count=0;
	HAL_MDMA_Start_IT(&hmdma_mdma_channel40_sw_0, SrcAddress, DstAddress, BlockDataLength, 1);
	while(mdma_end_flag == 0)
		mdma_count++;
}

__weak void do_workbuf_out(void)
{
uint32_t DstAddress, SrcAddress;
	if ( half_in == 1)
	{
		SrcAddress=(uint32_t )&audio_workbuf_0in[0];
		DstAddress=(uint32_t )&audio_buf_0_out[0];
	}
	else
	{
		SrcAddress=(uint32_t )&audio_workbuf_0in[HALF_NUMBER_OF_AUDIO_SAMPLES];
		DstAddress=(uint32_t )&audio_buf_0_out[HALF_NUMBER_OF_AUDIO_SAMPLES];
	}
	move_block_out(DstAddress, SrcAddress, NUMBER_OF_AUDIO_SAMPLES);
}
#else
__weak void do_workbuf_out(void)
{
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
		audio_buf_0_out[i] = audio_workbuf_0in[i]>>4;
		audio_buf_1_out[i] = audio_workbuf_1in[i]>>4;
	}
}
#endif

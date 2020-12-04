/*
 * audio_buffers.h
 *
 *  Created on: Nov 21, 2020
 *      Author: fil
 */

#ifndef BBAUDIO_INC_AUDIO_BUFFERS_H_
#define BBAUDIO_INC_AUDIO_BUFFERS_H_

#define		NUMBER_OF_AUDIO_SAMPLES			128
#define		HALF_NUMBER_OF_AUDIO_SAMPLES	NUMBER_OF_AUDIO_SAMPLES/2
#define		AUDIOBUF_LEN					NUMBER_OF_AUDIO_SAMPLES*2

extern	__attribute__ ((aligned (4))) uint16_t		audio_buf_0_2_in[AUDIOBUF_LEN];
extern	__attribute__ ((aligned (4))) uint16_t		audio_buf_1_3_in[AUDIOBUF_LEN];

extern	__attribute__ ((aligned (4))) uint16_t		audio_workbuf_0in[NUMBER_OF_AUDIO_SAMPLES];
extern	__attribute__ ((aligned (4))) uint16_t		audio_workbuf_1in[NUMBER_OF_AUDIO_SAMPLES];
extern	__attribute__ ((aligned (4))) uint16_t		audio_workbuf_0out[NUMBER_OF_AUDIO_SAMPLES];
extern	__attribute__ ((aligned (4))) uint16_t		audio_workbuf_1out[NUMBER_OF_AUDIO_SAMPLES];

extern	__attribute__ ((aligned (4))) uint16_t		audio_buf_0_out[NUMBER_OF_AUDIO_SAMPLES];
extern	__attribute__ ((aligned (4))) uint16_t		audio_buf_1_out[NUMBER_OF_AUDIO_SAMPLES];

extern	uint8_t		half_in,audioin_buffer_ready,mdma_end_flag;
extern	void do_workbuf_in(void);
extern	void do_workbuf_out(void);


#endif /* BBAUDIO_INC_AUDIO_BUFFERS_H_ */

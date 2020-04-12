/*
 * Dio.h
 *
 *  Created on: Jul 2, 2019
 *      Author: mark
 */
#include "../../utils/custom_types.h"
#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_
typedef enum
{


	Dio_channel_b0=0,
	Dio_channel_b1,
	Dio_channel_b2,
	Dio_channel_b3,
	Dio_channel_b4,
	Dio_channel_b5,
	Dio_channel_b6,
	Dio_channel_b7=7,

	Dio_channel_c0=8,
	Dio_channel_c1,
	Dio_channel_c2,
	Dio_channel_c3,
	Dio_channel_c4,
	Dio_channel_c5,
	Dio_channel_c6,
	Dio_channel_c7,

	Dio_channel_d0=16,
	Dio_channel_d1,
	Dio_channel_d2,
	Dio_channel_d3,
	Dio_channel_d4,
	Dio_channel_d5,
	Dio_channel_d6,
	Dio_channel_d7,

	Dio_channel_a0=24,
	Dio_channel_a1,
	Dio_channel_a2,
	Dio_channel_a3,
	Dio_channel_a4,
	Dio_channel_a5,
	Dio_channel_a6,
	Dio_channel_a7,
}Dio_channel_t;

typedef enum
{
	Dio_portb=0,
	Dio_portc,
	Dio_portd,
	Dio_porta
}Dio_port_t;

typedef enum
{
    low=0,
	high,
	toggle
}Dio_ch_state_t;

typedef enum
{
    input=0,
	output,
	input_pullup
}Dio_ch_dir_t;

void dio_channel_config(Dio_channel_t channel , Dio_ch_dir_t dir);
void dio_channel_set(Dio_channel_t channel , Dio_ch_state_t state);
Dio_ch_state_t dio_channel_read(Dio_channel_t channel);
void dio_port_config(Dio_port_t port , u8_t dir);
void dio_port_set(Dio_port_t port , u8_t state);
#endif /* MCAL_DIO_DIO_H_ */

/*
 * dio_atmega328p_registers.h
 *
 *  Created on: Jul 2, 2019
 *      Author: mark
 */
#include "../../utils/custom_types.h"
#ifndef MCAL_DIO_DIO_ATMEGA328P_REGISTERS_H_
#define MCAL_DIO_DIO_ATMEGA328P_REGISTERS_H_
//port b
#define DDRB  (*(volatile u8_t*) 0x37)
#define PORTB (*(volatile u8_t*) 0x38)
#define PINB  (*(volatile u8_t*) 0x36)
//port c
#define DDRC  (*(volatile u8_t*) 0x34)
#define PORTC (*(volatile u8_t*) 0x35)
#define PINC  (*(volatile u8_t*) 0x33)

//port d
#define DDRD  (*(volatile u8_t*) 0x31)
#define PORTD (*(volatile u8_t*) 0x32)
#define PIND  (*(volatile u8_t*) 0x30)
//port a
#define DDRA  (*(volatile u8_t*) 0x3B)
#define PORTA (*(volatile u8_t*) 0x3A)
#define PINA  (*(volatile u8_t*) 0x39)

#endif /* MCAL_DIO_DIO_ATMEGA328P_REGISTERS_H_ */

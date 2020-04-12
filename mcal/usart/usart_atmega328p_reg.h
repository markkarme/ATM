/*
 * usart_atmega328p_reg.h
 *
 *  Created on: Jul 21, 2019
 *      Author: mohamed
 */
#include "../../utils/custom_types.h"
#ifndef MCAL_USART_USART_ATMEGA328P_REG_H_
#define MCAL_USART_USART_ATMEGA328P_REG_H_
/*USART I/O Data Register*/
#define UDR0  *((volatile u8_t *)0x2C)
/* control registers*/
#define RXC0   7
#define TXC0   6
#define UDRE0  5
#define FE0    4
#define DOR0   3
#define UPE0   2
#define U2X0   1
#define MPCM0  0
#define UCSR0A  *((volatile u8_t *)0x2B)

#define RXCIE0 7
#define TXCIE0 6
#define UDRIE0 5
#define RXEN0  4
#define TXEN0  3
#define UCSZ02 2
#define RXB80  1
#define TXB80  0
#define UCSR0B  *((volatile u8_t *)0x2A)
/* baudrate register*/
#define UBRR0L  *((volatile u8_t *)0x29)
#define UBRR0H  *((volatile u8_t *)0x40)

#define UMSEL1 7
#define UMSEL0 6
#define UPM1  5
#define UPM0  4
#define USBS  3
#define UCSZ1 2
#define UCSZ0 1
#define UCPOL 0
#define UCSR0C  *((volatile u8_t *)0x40)
#endif /* MCAL_USART_USART_ATMEGA328P_REG_H_ */

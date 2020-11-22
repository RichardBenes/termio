/*
 * termio.h
 *
 *  Created on: Nov 20, 2020
 *      Author: amper
 */

#ifndef TERMIO_H_
#define TERMIO_H_

#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef enum {
	TioAppendTerminator,
	TioDontAppendTerminator
}TioAppendingTerminator_e;

typedef enum {
	TioSendEcho,
	TioDontSendEcho
}TioSendingEcho_e;


void tioSetup(
    void (*txFun)(uint8_t), 
    uint8_t (*rxFun)(void),
    void (*clearBufferFn)(void));

void tioGetNChars(
		char * buf,
		uint8_t maxNOfBytes,
		TioAppendingTerminator_e appendTerminator,
		TioSendingEcho_e echo);

uint32_t tioGetNDigitNum(
		uint8_t nOfDigits,
		TioSendingEcho_e echo);

/* __io_getchar is not implemented,
 * because there were trouble with
 * both scanf sscanf, probably
 * fgets too.
*/
int __io_putchar(int ch);

#endif /* STM32_PRINTF_H_ */

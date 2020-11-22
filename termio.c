/*
 * termio.c
 *
 *  Created on: Nov 20, 2020
 *      Author: amper
 */

#include "termio.h"

static void (*transmitFunction)(uint8_t);
static uint8_t (*receiveFunction)(void);
static void (*clear_rx_buffer)(void);

void tioSetup(
    void (*txFun)(uint8_t), 
    uint8_t (*rxFun)(void),
    void (*clearBufferFn)(void)
    ) {
    transmitFunction = txFun;
    receiveFunction = rxFun;
    clear_rx_buffer = clearBufferFn;
    setvbuf( stdin, NULL, _IONBF, 0 );
}

int __io_putchar(int ch) {
    transmitFunction((uint8_t)ch);
    return 0;
}

/* This function fills the input buffer with
 * maximum `max_number_of_bytes` received bytes.
 * In case of appending NULL terminator,
 * buffer hat to be at least
 * `max_number_of_bytes` + 1 bytes long */
void tioGetNChars(
		char * buf,
		uint8_t maxNOfBytes,
		TioAppendingTerminator_e appendTerminator,
		TioSendingEcho_e echo)
{
	clear_rx_buffer();

	for (uint32_t i = 0U; i < maxNOfBytes; i++ ) {
		buf[i] = receiveFunction();

		if(echo == TioSendEcho) {
			transmitFunction(buf[i]);
		}
		if(isspace(buf[i])) {
			break;
		}
	}

	if(appendTerminator == TioAppendTerminator) {
		buf[maxNOfBytes] = '\0';
	}
}

/* uint32_t must be the same as
 * unsigned long int */
uint32_t tioGetNDigitNum(
		uint8_t nOfDigits,
		TioSendingEcho_e echo)
{
	char buf[nOfDigits + 1];
	tioGetNChars(buf, nOfDigits, TioDontAppendTerminator, echo);
	return (uint32_t)strtoul(buf, NULL, 10);
}
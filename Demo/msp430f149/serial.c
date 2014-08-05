/*
    FreeRTOS V7.1.1 - Copyright (C) 2012 Real Time Engineers Ltd.
	

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!
    
    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?                                      *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    
    http://www.FreeRTOS.org - Documentation, training, latest information, 
    license and contact details.
    
    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool.

    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell 
    the code with commercial support, indemnification, and middleware, under 
    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
    provide a safety engineered and independently SIL3 certified version under 
    the SafeRTOS brand: http://www.SafeRTOS.com.
*/


/* BASIC INTERRUPT DRIVEN SERIAL PORT DRIVER.
 *
 * This is not a proper UART driver.  It only supports one port, uses loopback
 * mode, and is used to test interrupts that use the FreeRTOS API as part of 
 * a wider test suite.  Nor is it intended to show an efficient implementation
 * of a UART interrupt service routine as queues are used to pass individual
 * characters one at a time!
 */

/* Standard includes. */
#include <stdlib.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

/* Demo application includes. */
#include "serial.h"
#include "stdarg.h"

/* Misc. constants. */
#define serNO_BLOCK				( ( portTickType ) 0 )

/* The queue used to hold received characters. */
static xQueueHandle xRxedChars;

/* The queue used to hold characters waiting transmission. */
static xQueueHandle xCharsForTx;

/*-----------------------------------------------------------*/

xComPortHandle xSerialPortInitMinimal( unsigned portLONG ulWantedBaud, unsigned portBASE_TYPE uxQueueLength )
{
unsigned portLONG ulBaudRateCount;

	/* Initialise the hardware. */

	/* Generate the baud rate constants for the wanted baud rate. */
	ulBaudRateCount = configCPU_CLOCK_HZ / ulWantedBaud;

	portENTER_CRITICAL();
	{
		/* Create the queues used by the com test task. */
		xRxedChars = xQueueCreate( uxQueueLength, ( unsigned portBASE_TYPE ) sizeof( signed char ) );
		xCharsForTx = xQueueCreate( uxQueueLength, ( unsigned portBASE_TYPE ) sizeof( signed char ) );
		#if 0
		/* Reset UART. */
		UCA1CTL1 |= UCSWRST;

		/* Use SMCLK. */
		UCA1CTL1 = UCSSEL0 | UCSSEL1;
		
		/* Setup baud rate low byte. */
		UCA1BR0 = ( unsigned portCHAR ) ( ulBaudRateCount & ( unsigned long ) 0xff );

		/* Setup baud rate high byte. */
		ulBaudRateCount >>= 8UL;
		UCA1BR1 = ( unsigned portCHAR ) ( ulBaudRateCount & ( unsigned long ) 0xff );

		/* UCLISTEN sets loopback mode! */
		UCA1STAT = UCLISTEN;

		/* Enable interrupts. */
		UCA1IE |= UCRXIE;
		
		/* Take out of reset. */
		UCA1CTL1 &= ~UCSWRST;
		#endif
		P3SEL |= BIT7 + BIT6;        
		P3DIR &= ~BIT7;              // P3.7：USCI_A1 RXD
		P3DIR |= BIT6;               // P3.6：USCI_A1 TXD
		UCTL1 &= ~SYNC;        // CLK = MCLK
		//UBR01 = 0X34;              // 16MHz-9600 
		UBR01 = ( unsigned portCHAR ) ( ulBaudRateCount & ( unsigned long ) 0xff );
		//UBR11 = 0x00;              // 65+3*256=833   
		ulBaudRateCount >>= 8UL;
		UBR11 = ( unsigned portCHAR ) ( ulBaudRateCount & ( unsigned long ) 0xff );
		UTCTL1 = (SSEL0 | SSEL1);// Modulation UCBRSx = 2
		UCTL1 &= ~SWRST;        // Initialize USCI state machine
		U1IE |= URXIE1;           // 允许接收中断
	}
	portEXIT_CRITICAL();
	
	/* Note the comments at the top of this file about this not being a generic
	UART driver. */
	return NULL;
}
/*-----------------------------------------------------------*/

signed portBASE_TYPE xSerialGetChar( xComPortHandle pxPort, signed portCHAR *pcRxedChar, portTickType xBlockTime )
{
	/* Get the next character from the buffer.  Return false if no characters
	are available, or arrive before xBlockTime expires. */
	if( xQueueReceive( xRxedChars, pcRxedChar, xBlockTime ) )
	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	}
}
/*-----------------------------------------------------------*/

signed portBASE_TYPE xSerialPutChar( xComPortHandle pxPort, signed portCHAR cOutChar, portTickType xBlockTime )
{
signed portBASE_TYPE xReturn;

	/* Send the next character to the queue of characters waiting transmission,
	then enable the UART Tx interrupt, just in case UART transmission has already
	completed and switched itself off. */
	xReturn = xQueueSend( xCharsForTx, &cOutChar, xBlockTime );
	//UCA1IE |= UCTXIE;
	U1IE |= UTXIE1;   
	return xReturn;
}
/*-----------------------------------------------------------*/

/* The implementation of this interrupt is provided to demonstrate the use
of queues from inside an interrupt service routine.  It is *not* intended to
be an efficient interrupt implementation.  A real application should make use
of the DMA.  Or, as a minimum, transmission and reception could use a simple
RAM ring buffer, and synchronise with a task using a semaphore when a complete
message has been received or transmitted. */
static void
__attribute__((__interrupt__(UART1RX_VECTOR)))
prvUSCI_A1_ISR( void )
{
signed char cChar;
portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	if( ( U1IFG & URXIFG1 ) != 0 )
	{
		/* Get the character from the UART and post it on the queue of Rxed
		characters. */
		cChar = RXBUF1;
		xQueueSendFromISR( xRxedChars, &cChar, &xHigherPriorityTaskWoken );
	}	
	else if( ( U1IFG & UTXIFG1 ) != 0 )
	{
		/* The previous character has been transmitted.  See if there are any
		further characters waiting transmission. */
		if( xQueueReceiveFromISR( xCharsForTx, &cChar, &xHigherPriorityTaskWoken ) == pdTRUE )
		{
			/* There was another character queued - transmit it now. */
			TXBUF1 = cChar;
		}
		else
		{
			/* There were no other characters to transmit - disable the Tx
			interrupt. */
			U1IE &= ~UTXIE1;
		}
	}
	
	__bic_SR_register_on_exit( SCG1 + SCG0 + OSCOFF + CPUOFF );
	
	/* If writing to a queue caused a task to unblock, and the unblocked task
	has a priority equal to or above the task that this interrupt interrupted,
	then lHigherPriorityTaskWoken will have been set to pdTRUE internally within
	xQueuesendFromISR(), and portEND_SWITCHING_ISR() will ensure that this
	interrupt returns directly to the higher priority unblocked task. 
	
	THIS MUST BE THE LAST THING DONE IN THE ISR. */	
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

/**
 * puts() is used by printf() to display or send a string.. This function
 *     determines where printf prints to. For this case it sends a string
 *     out over UART, another option could be to display the string on an
 *     LCD display.
 **/
void puts(char *s) {
	char c;

	// Loops through each character in string 's'
	while (c = *s++) {
		xSerialPutChar(NULL,c,serNO_BLOCK);
	}
}
/**
 * puts() is used by printf() to display or send a character. This function
 *     determines where printf prints to. For this case it sends a character
 *     out over UART.
 **/
void putc(unsigned b) {
	xSerialPutChar(NULL,b,serNO_BLOCK);
}
static const unsigned long dv[] = {
//  4294967296      // 32 bit unsigned max
		1000000000,// +0
		100000000, // +1
		10000000, // +2
		1000000, // +3
		100000, // +4
//       65535      // 16 bit unsigned max
		10000, // +5
		1000, // +6
		100, // +7
		10, // +8
		1, // +9
		};

static void xtoa(unsigned long x, const unsigned long *dp) {
	char c;
	unsigned long d;
	if (x) {
		while (x < *dp)
			++dp;
		do {
			d = *dp++;
			c = '0';
			while (x >= d)
				++c, x -= d;
			putc(c);
		} while (!(d & 1));
	} else
		putc('0');
}

static void puth(unsigned n) {
	static const char hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
			'9', 'A', 'B', 'C', 'D', 'E', 'F' };
	putc(hex[n & 15]);
}

void printf(char *format, ...)
{
	char c;
	int i;
	long n;

	va_list a;
	va_start(a, format);
	while(c = *format++) {
		if(c == '%') {
			switch(c = *format++) {
				case 's': // String
					puts(va_arg(a, char*));
					break;
				case 'c':// Char
					putc(va_arg(a, char));
				break;
				case 'i':// 16 bit Integer
				case 'u':// 16 bit Unsigned
					i = va_arg(a, int);
					if(c == 'i' && i < 0) i = -i, putc('-');
					xtoa((unsigned)i, dv + 5);
				break;
				case 'l':// 32 bit Long
				case 'n':// 32 bit uNsigned loNg
					n = va_arg(a, long);
					if(c == 'l' && n < 0) n = -n, putc('-');
					xtoa((unsigned long)n, dv);
				break;
				case 'x':// 16 bit heXadecimal
					i = va_arg(a, int);
					puth(i >> 12);
					puth(i >> 8);
					puth(i >> 4);
					puth(i);
				break;
				case 0: return;
				default: goto bad_fmt;
			}
		} else
			bad_fmt: putc(c);
	}
	va_end(a);
}

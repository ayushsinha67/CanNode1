/*
 * CAN_NODE_1.c
 * 
 * Status: NODE 1
 * 
 * Created: 01-06-2012 AM 11:11:52
 *  Author: Ayush Sinha
 */ 
#define  F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <avr/wdt.h>
#include "global.h"
#include "timer.h"
#include "uart.h"
#include "spi.h"
#include "adc.h"
#include "uart.h"
#include "mcp2515.h"
#include "can.h"

#ifdef TERMINAL
#include "terminal.h"
#endif

/************************************************************************
 *	MAIN
 */

int main(void)
{	 
	ExtINT_Init();										/* External Interrupt */
	Timer_Init();										/* Timers */
	UART_Init();										/* UART */											
	SPI_Init();											/* SPI */
	ADC_Init();											/* ADC */
	GPIO_Init();										/* GPIO */
	sei();												/* Enable Global Interrupts */
															
	enum MCP2515_STATUS res = CAN_Init(CAN_SPEED);		/* Start CAN */	
	
#ifdef TERMINAL		
	term_Start(res);									/* Start Terminal */
#endif
	
	Msg_Init();											/* Construct Data to be sent */

/* ---------------------------*/
	while(1){
		
		wdt_enable(WDTO_2S);							/* Enable Watchdog Timer for 1 second */
		/* ------------------ */
		
		SensorData();									/* Get Data from Sensors */
		
		Msg_Send();										/* Send Messages */
		
		/* ------------------------------------------ */		
		
		/* Receive Messages */
		Msg_Recv();
				
		
		
		/* ------------------------------------------ */
		wdt_reset();									/* Reset Watchdog */
		wdt_disable();
		
		
		
		


#ifdef TERMINAL											
	term_Main();										/* TERMINAL FOR DEBUGGING */
#endif

    }
	return 0;
}
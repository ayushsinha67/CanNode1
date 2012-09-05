#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "global.h"
#include "timer.h"

/************************************************************************
 *	GLOBAL VARIABLES
 */
volatile uint16_t	ms_tick = 0,
					tick_msg1 = 0, 
					tick_msg2 = 0,
					tick_msg3 = 0,
					tick_msg4 = 0,
					tick_msg5 = 0,
					tick_msg6 = 0,
					tick_msg7= 0;
					
extern volatile enum MSG_STATE	msg1_state, msg2_state, msg3_state, msg4_state, 
								msg5_state, msg6_state, msg7_state;
/************************************************************************
 *	INITIALIZE TIMER
 *  
 *  TIMER0 - CTC MODE, F_CPU: 16Mhz, PS: 64, Frequency: 1 KHz, Period: 1 ms 
 */
void Timer_Init(void)
{
    TCCR0 |= (1<<WGM01) | (1<<CS01) | (1<<CS00);    /* CTC, PS: 64 */
    TIMSK |= (1<<OCIE0);                            /* Enable Interrupt */
    OCR0 = 250;
}

/************************************************************************
 *	CHECK TIMER 
 */
uint16_t ChkTimer	(void)
{
	uint8_t tick_copy;

	ATOMIC_BLOCK( ATOMIC_FORCEON ){
		tick_copy = ms_tick;
	}
	return tick_copy;
}

/************************************************************************
 *	SET TIMER
 */
void SetTimer (uint16_t t)
{
	ATOMIC_BLOCK( ATOMIC_FORCEON ){
		ms_tick = t;
	}
}

/************************************************************************
 *	TIMER0 INTERRUPT 
 */ 
 ISR(TIMER0_COMP_vect)
{
	if( ms_tick > 0 )								/* Decrement Ticker */
		ms_tick--;
		
	if( tick_msg1++ >= RATE_MSG1 ){					/* Message Tickers */
		tick_msg1 = 0;	msg1_state = SEND;
	}	
	
	if( tick_msg2++ >= RATE_MSG2 ){
		tick_msg2 = 0;	msg2_state = SEND;
	}
	
	if( tick_msg3++ >= RATE_MSG3 ){
		tick_msg3 = 0;	msg3_state = SEND;
	}	
	
	if( tick_msg4++ >= RATE_MSG4 ){
		tick_msg4 = 0;	msg4_state = SEND;
	}	
	
	if( tick_msg5++ >= RATE_MSG5 ){
		tick_msg5 = 0;	msg5_state = SEND;
	}	
	
	if( tick_msg6++ >= RATE_MSG6 ){
		tick_msg6 = 0;	msg6_state = SEND;
	}	
	
	if( tick_msg7++ >= RATE_MSG7 ){
		tick_msg7 = 0;	msg7_state = SEND;
	}		
}

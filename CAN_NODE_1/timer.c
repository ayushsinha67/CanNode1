#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "messages.h"
#include "timer.h"

/************************************************************************
 *	GLOBAL VARIABLES
 */
extern volatile uint16_t	ms_tick;
							
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


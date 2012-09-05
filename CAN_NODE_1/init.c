#include <avr/io.h>
#include <avr/interrupt.h>
#include "init.h"

/************************************************************************
 *	INITIALIZE GPIO
 */
void GPIO_Init (void)
{
	
}

/************************************************************************
 *	INITIALZE EXTERNAL INTERRUPT
 */
void ExtINT_Init(void)
{	
	GICR = (1 << INT0); 
	MCUCR = 0x00;								/*Trigger INT0 on Low Level */
}
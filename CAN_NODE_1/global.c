#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <avr/wdt.h>
#include "global.h"
#include "terminal.h"
#include "can.h"
#include "mcp2515.h"
#include "adc.h"
#include "uart.h"

/************************************************************************
 *	GLOBAL VARIABLES
 */

/* CAN Messages */
CanMessage throttle, pot;
volatile CanMessage buffer;

/* Message States */
volatile enum MSG_STATE		msg1_state = WAIT,
							msg2_state = WAIT,
							msg3_state = WAIT,
							msg4_state = WAIT,
							msg5_state = WAIT,
							msg6_state = WAIT,
							msg7_state = WAIT,
							msg_state_recv = WAIT;

#ifdef TERMINAL								
extern volatile enum MSGSTRM_STATE	strm;
#endif

/************************************************************************
 *	INITIALIZE GPIO
 */
void GPIO_Init (void)
{
	
}

/************************************************************************
 *	EXTERNAL INTERRUPT
 */
ISR(INT0_vect)
{
	msg_state_recv = RECV;	
}

/************************************************************************
 *	INITIALZE EXTERNAL INTERRUPT
 */
void ExtINT_Init(void)
{	
	GICR = (1 << INT0); 
	MCUCR = 0x00;								/*Trigger INT0 on Low Level */
}


/************************************************************************
 *	INITIALIZE MESSAGE TO BE SENT
 */
void Msg_Init(void)
{
	throttle.ext = 0;
	throttle.dlc = 6;
	throttle.id =  0x03;
	throttle.data[0] = 0x54;
	throttle.data[1] = 0x89;
	throttle.data[2] = 0xFA;
	throttle.data[3] = 0xCE;
	
	pot.ext = 0;
	pot.dlc = 2;
	pot.id =  0x06;
	pot.data[0] = 0xBA;
	pot.data[1] = 0xFA;

}

/************************************************************************
 *	SENSOR DATA
 */
void SensorData (void)
{
	uint16_t val = ADC_read(0);
	pot.data[0] = (uint8_t) ( val >> 8 );
	pot.data[1] = (uint8_t) val;
}

/************************************************************************
 *	RECEIVE MESSAGE
 */
void Msg_Recv (void)
{
	enum MSG_STATE	msg_state_recv_copy;						/* local variable */
	
	ATOMIC_BLOCK( ATOMIC_FORCEON ){								/* Read Interrupt variables */
		msg_state_recv_copy = msg_state_recv;
	}
	
	/* --------------------------------- */
	
	if( msg_state_recv_copy == RECV ){
		
		CAN_ReadMsg(&buffer);									/* Read CAN Message */
		msg_state_recv_copy = WAIT;		
			
#ifdef TERMINAL
		if( strm == MS_STREAM )									/* Enable Terminal Message Stream */
			term_RxMsg(&buffer);
#endif						
	}

	/* --------------------------------- */
	ATOMIC_BLOCK( ATOMIC_FORCEON ){								/* Read Interrupt variables */
		msg_state_recv = msg_state_recv_copy;
	}
		
}

/************************************************************************
 *	SEND MESSAGE
 */
void Msg_Send (void)
{
	enum MSG_STATE	msg1_state_copy, msg2_state_copy,	/* local variables */
					msg3_state_copy, msg4_state_copy,
					msg5_state_copy, msg6_state_copy,
					msg7_state_copy;			
	
	ATOMIC_BLOCK( ATOMIC_FORCEON ){						/* Read Interrupt variables */
			msg1_state_copy = msg1_state;
			msg2_state_copy = msg2_state;
			msg3_state_copy = msg3_state;
			msg4_state_copy = msg4_state;
			msg5_state_copy = msg5_state;
			msg6_state_copy = msg6_state;
			msg7_state_copy = msg7_state;
		}
		
		/* ------------------------------------- */
		if(	msg1_state_copy == SEND ){					/* Message 1 */
			CAN_SendMsg(&throttle);	
			msg1_state_copy = WAIT;
		}		
									
		if(	msg2_state_copy == SEND ){					/* Message 2 */
			CAN_SendMsg(&pot);
			msg2_state_copy = WAIT;
		}	
		
		if(	msg3_state_copy == SEND ){					/* Message 3 */
			//CAN_SendMsg(&pot);
			msg3_state_copy = WAIT;
		}	
		
		if(	msg4_state_copy == SEND ){					/* Message 4 */
			//CAN_SendMsg(&pot);
			msg4_state_copy = WAIT;
		}	
		
		if(	msg5_state_copy == SEND ){					/* Message 5 */
			//CAN_SendMsg(&pot);
			msg5_state_copy = WAIT;
		}	
		
		if(	msg6_state_copy == SEND ){					/* Message 6 */
			//CAN_SendMsg(&pot);
			msg6_state_copy = WAIT;
		}	
		
		if(	msg7_state_copy == SEND ){					/* Message 7 */
			//CAN_SendMsg(&pot);
			msg7_state_copy = WAIT;
		}	
		
		/* ------------------------------------- */
		ATOMIC_BLOCK( ATOMIC_FORCEON ){					/* Rewrite Interrupt variables */		
			msg1_state = msg1_state_copy;
			msg2_state = msg2_state_copy;
			msg3_state = msg3_state_copy;
			msg4_state = msg4_state_copy;
			msg5_state = msg5_state_copy;
			msg6_state = msg6_state_copy;
			msg7_state = msg7_state_copy;
		}		
}


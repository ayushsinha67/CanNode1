#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <avr/wdt.h>
#include "init.h"
#include "messages.h"
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
CanMessage buffer;

/* Message States */
volatile MSG_STATE		msg_state1 = WAIT,
						msg_state2 = WAIT,
						msg_state3 = WAIT,
						msg_state4 = WAIT,
						msg_state5 = WAIT,
						msg_state6 = WAIT,
						msg_state7 = WAIT,
						msg_state_recv = WAIT;

#ifdef TERMINAL								
extern volatile MSGSTRM_STATE	strm;
#endif

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
 *	EXTERNAL INTERRUPT (RECEIVED MESSAGE)
 */
ISR(INT0_vect)
{
	msg_state_recv = RECV;	
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
	MSG_STATE	msg_state_recv_copy;							/* local variable */
	
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
	MSG_STATE	msg_state1_copy, msg_state2_copy,		/* local variables */
				msg_state3_copy, msg_state4_copy,
				msg_state5_copy, msg_state6_copy,
				msg_state7_copy;			
	
	ATOMIC_BLOCK( ATOMIC_FORCEON ){						/* Read Interrupt variables */
			msg_state1_copy = msg_state1;
			msg_state2_copy = msg_state2;
			msg_state3_copy = msg_state3;
			msg_state4_copy = msg_state4;
			msg_state5_copy = msg_state5;
			msg_state6_copy = msg_state6;
			msg_state7_copy = msg_state7;
		}
		
		/* ------------------------------------- */
		if(	msg_state1_copy == SEND ){					/* Message 1 */
			CAN_SendMsg(&throttle);	
			msg_state1_copy = WAIT;
		}		
									
		if(	msg_state2_copy == SEND ){					/* Message 2 */
			CAN_SendMsg(&pot);
			msg_state2_copy = WAIT;
		}	
		
		if(	msg_state3_copy == SEND ){					/* Message 3 */
			//CAN_SendMsg(&pot);
			msg_state3_copy = WAIT;
		}	
		
		if(	msg_state4_copy == SEND ){					/* Message 4 */
			//CAN_SendMsg(&pot);
			msg_state4_copy = WAIT;
		}	
		
		if(	msg_state5_copy == SEND ){					/* Message 5 */
			//CAN_SendMsg(&pot);
			msg_state5_copy = WAIT;
		}	
		
		if(	msg_state6_copy == SEND ){					/* Message 6 */
			//CAN_SendMsg(&pot);
			msg_state6_copy = WAIT;
		}	
		
		if(	msg_state7_copy == SEND ){					/* Message 7 */
			//CAN_SendMsg(&pot);
			msg_state7_copy = WAIT;
		}	
		
		/* ------------------------------------- */
		ATOMIC_BLOCK( ATOMIC_FORCEON ){					/* Rewrite Interrupt variables */		
			msg_state1 = msg_state1_copy;
			msg_state2 = msg_state2_copy;
			msg_state3 = msg_state3_copy;
			msg_state4 = msg_state4_copy;
			msg_state5 = msg_state5_copy;
			msg_state6 = msg_state6_copy;
			msg_state7 = msg_state7_copy;
		}		
}


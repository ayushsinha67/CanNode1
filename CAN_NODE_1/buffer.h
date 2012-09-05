#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <avr/io.h>
#include "can.h"

/************************************************************************
 *	DEFINES
 */
#define CAN_TX_BUFFER_SIZE		5		

/************************************************************************
 *	DATA TYPES
 */
typedef struct 
{
	CanMessage	*buffer;
	uint8_t		head;
	uint8_t		tail;
	uint8_t		size;
		
} CanBuffer;

/************************************************************************
 *	ENUMERATIONS
 */
typedef enum 
{
	BUFFER_FULL = 0,
	BUFFER_EMPTY
	
} BufferState;

/************************************************************************
 *	FUNCTIONS
 */
void		CAN_BufInit ( CanBuffer *buf, uint8_t size );
BufferState CAN_BufEnq  ( CanBuffer *buf, CanMessage *msg );
BufferState CAN_BufDeq  ( CanBuffer *buf, CanMessage *msg );



#endif 
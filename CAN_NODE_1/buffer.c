#include <avr/io.h>
#include "mcp2515.h"
#include "can.h"
#include "buffer.h"

/************************************************************************
 *	BUFFER INITIALIZATION
 */
void CAN_BufInit ( CanBuffer *buf, uint8_t size )
{
	buf->size = size;
	buf->head = 0;
	buf->tail = 0;
}

/************************************************************************
 *	BUFFER ENQUEUE
 */
void CAN_BufEnq ( CanBuffer *buf )
{
	//buf->buffer[ buf->tail ] = *msg;					/* Add to tail */
	
	if( buf->tail == ( buf->size - 1) )					/* Loop around */
		buf->tail = 0;
	else
		buf->tail = buf->tail + 1;						/* Increment tail pointer */
}


/************************************************************************
 *	BUFFER DEQUEUE
 */
void CAN_BufDeq ( CanBuffer *buf )
{
	//*msg = buf->buffer[ buf->head ];					/* Copy from Head */
	
	if( buf->head == ( buf->size - 1 ) )				/* Loop around */
		buf->head = 0;
	else 
		buf->head = buf->head + 1;						/* Increment tail pointer */
}
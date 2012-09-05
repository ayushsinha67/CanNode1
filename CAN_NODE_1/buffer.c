#include <avr/io.h>
#include "buffer.h"
//#include "can.h"

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
BufferState CAN_BufEnq ( CanBuffer *buf, CanMessage *msg )
{
	buf->buffer[ buf->tail ] = *msg;					/* Add to tail */
	
	if( buf->tail == ( buf->size - 1) )					/* Loop around */
		buf->tail = 0;
	else
		buf->tail = buf->tail + 1;						/* Increment tail pointer */
}


/************************************************************************
 *	BUFFER DEQUEUE
 */
BufferState CAN_BufDeq ( CanBuffer *buf, CanMessage *msg )
{
	*msg = buf->buffer[ buf->head ];					/* Copy from Head */
	
	if( buf->head == ( buf->size - 1 ) )				/* Loop around */
		buf->head = 0;
	else 
		buf->head = buf->head + 1;						/* Increment tail pointer */

}
#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <avr/io.h>
#include "can.h"

/************************************************************************
 *	DEFINES
 */
#define CAN_TX_BUFFER_SIZE		8	
#define CAN_RX_BUFFER_SIZE		8	

/************************************************************************
 *	DATA TYPES
 */
typedef struct
{
	CanMessage	*buffer;
	uint8_t		size;
	uint8_t     head;
	uint8_t     tail;
	uint8_t		count;

} CanBuffer;

/************************************************************************
 *	ENUMERATIONS
 */
typedef enum 
{
	BUFFER_FULL = 0,
	BUFFER_MID,
	BUFFER_EMPTY
	
} BufferState;

/************************************************************************
 *	FUNCTIONS
 */
void		    CAN_BufInit ( CanBuffer *buf, uint8_t size );
void    		CAN_BufEnq  ( CanBuffer *buf, CanMessage *msg  );
void	        CAN_BufDeq  ( CanBuffer *buf, CanMessage *msg );
BufferState     CAN_BufState( CanBuffer *buf  );

#endif 
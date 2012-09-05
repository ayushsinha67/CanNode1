#ifndef _CAN_H
#define _CAN_H

#include <avr/io.h>
#include "mcp2515.h"

/************************************************************************
 *	DEFINES
 */

#define CAN_SPEED		CAN_250KBPS				/* Bus Speed */
#define FILTER_ENABLE	1						/* Enable Filter */

#define MASK0			0x7FF					/* Filter Settings */
#define MASK1			0x7FF
#define FILTER0			0x01
#define FILTER1			0x02
#define FILTER2			0x03
#define FILTER3			0x04
#define FILTER4			0x05
#define FILTER5			0x06

/************************************************************************
 *	DATA TYPES
 */
typedef struct 
{
	uint32_t id; 
	uint8_t  ext;								/* 0 = SID, 1 = EXIDE */
	uint8_t  rtr;								/* 0 = NO RTR, 1 = RTR */
	uint8_t  dlc;
	uint8_t  data[8];	
	
} CanMessage;

/************************************************************************
 *	ENUMERATIONS
 */
typedef enum
{
	CAN_OK = 0,
	CAN_FAILED

} CanStatus;

/************************************************************************
 *	FUNCTION PROTOTYPES
 */
CanStatus CAN_Init		( uint8_t can_rate );
CanStatus CAN_SendMsg	( const CanMessage *msg );
CanStatus CAN_ReadMsg	( CanMessage *msg );

#endif
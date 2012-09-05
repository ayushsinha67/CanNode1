#ifndef _CAN_H
#define _CAN_H

#include <avr/io.h>

/************************************************************************
 *	DEFINES
 */
/* Bus Speed */
#define CAN_SPEED		CAN_250KBPS

/* Filter Settings */
#define FILTER_ENABLE	1
#define MASK0			0x7FF		
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
typedef struct {
	uint32_t id; 
	uint8_t  ext;
	uint8_t  rtr; 
	uint8_t  dlc;
	uint8_t  data[8];
} CanMessage;

/************************************************************************
 *	FUNCTION PROTOTYPES
 */
enum MCP2515_STATUS CAN_Init			( uint8_t can_rate );
enum MCP2515_STATUS	CAN_SendMsg			( const	   CanMessage *msg );
enum MCP2515_STATUS CAN_ReadMsg			( volatile CanMessage *msg );

#endif
#ifndef GLOBAL_H
#define GLOBAL_H

#include <avr/io.h>

/************************************************************************
 *	DEFINES AND CONSTANTS
 */

/* Message transmission Rate (in milliseconds) */				
#define RATE_MSG1		100
#define RATE_MSG2		10
#define RATE_MSG3		300
#define RATE_MSG4		400
#define RATE_MSG5		100
#define RATE_MSG6		100
#define RATE_MSG7		100

/* Message IDE */
//#define ENGINE_COOLANT_TEMP 0x05
//#define ENGINE_RPM          0x0C
//#define VEHICLE_SPEED       0x0D
//#define MAF_SENSOR          0x10
//#define O2_VOLTAGE          0x14
//#define THROTTLE			  0x11
//

/* Message Identifiers */
//#define PID_REQUEST         0x7DF
//#define PID_REPLY			  0x7E8

/************************************************************************
 *	FUNCTIONS
 */
void Msg_Init    (void);
void SensorData	 (void);

#endif


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <avr/wdt.h>
#include "mcp2515.h"
#include "can.h"
#include "init.h"
#include "messages.h"
#include "terminal.h"
#include "adc.h"
#include "buffer.h"

/************************************************************************
 *	GLOBAL VARIABLES
 */
/* CAN Messages */
extern CanMessage throttle, pot;

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


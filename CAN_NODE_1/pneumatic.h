#ifndef PNEUMATIC_H_
#define PNEUMATIC_H_

/************************************************************************
 *	DEFINES
 */
/* Shift Buttons */
#define DDR_SHIFT_BUTTON_UP		DDRD
#define DDR_SHIFT_BUTTON_DOWN	DDRB
#define PIN_SHIFT_BUTTON_UP		PIND
#define PIN_SHIFT_BUTTON_DOWN	PINB					
#define PIN_SHIFT_UP			PD3								/* INT1 */		
#define PIN_SHIFT_DOWN			PB2								/* INT2 */

/* DEBOUNCE */
#define DEBOUNCE_TIME			100

/************************************************************************
 *	ENUMERATION
 */
typedef enum
{
	BUTTON_RELEASED = 0,
	BUTTON_PRESSED,
	BUTTON_CHECK_PRESSED,
	BUTTON_CHECK_RELEASED
			
} ButtonState;

/************************************************************************
 *	FUNCTION PROTOTYPES
 */
void Debounce_UpShift	( void );
void Debounce_Downshift	( void );
void DebTimer_Upshift	( void );
void DebTimer_Downshift	( void );

#endif /* PNEUMATIC_H_ */
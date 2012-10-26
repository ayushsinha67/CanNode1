#include <avr/io.h>
#include <avr/pgmspace.h>
#include "pneumatic.h"
#include "message.h"
#include "init.h"

#if ( TERMINAL == 1 )
#include "uart.h"
#include "terminal.h"
#endif 


/************************************************************************
 *	GLOBAL VARIABLES
 */
extern volatile uint16_t debounce_ticker1;
extern volatile uint16_t debounce_ticker2;
extern volatile ButtonState button_int1;
extern volatile ButtonState button_int2;

/************************************************************************
 *	DEBOUNCE UPSHIFT
 */
void Debounce_UpShift	( void )
{
	/* Noise detected, since next edge is less than debounce time. */
	if( ( button_int1 == BUTTON_CHECK_PRESSED ) && ( debounce_ticker1 < DEBOUNCE_TIME ) ){
		button_int1 = BUTTON_RELEASED;
	}
	
	/* Noise detected, since next edge is less than debounce time */
	if( ( button_int1 == BUTTON_CHECK_RELEASED ) && ( debounce_ticker1 < DEBOUNCE_TIME ) ){
		button_int1 = BUTTON_PRESSED;
	}
	
	/* Start incrementing timer if key was released and is now pressed. This can be noise or valid */
	if( button_int1 == BUTTON_RELEASED ){
		debounce_ticker1 = 0;
		button_int1 = BUTTON_CHECK_PRESSED;
	}
	
	/* Start incrementing timer if key was pressed. This is the trailing noise edge. */
	if( button_int1 == BUTTON_PRESSED ){
		debounce_ticker1 = 0;
		button_int1 = BUTTON_CHECK_RELEASED;
	}
}

/************************************************************************
 *	DEBOUNCE DOWNSHIFT
 */
void Debounce_Downshift	( void )
{
	/* Noise detected, since next edge is less than debounce time. */
	if( ( button_int2 == BUTTON_CHECK_PRESSED ) && ( debounce_ticker2 < DEBOUNCE_TIME ) ){
		button_int2 = BUTTON_RELEASED;
	}
	
	/* Noise detected, since next edge is less than debounce time */
	if( ( button_int2 == BUTTON_CHECK_RELEASED ) && ( debounce_ticker2 < DEBOUNCE_TIME ) ){
		button_int2 = BUTTON_PRESSED;
	}
	
	/* Start incrementing timer if key was released and is now pressed. This can be noise or valid */
	if( button_int2 == BUTTON_RELEASED ){
		debounce_ticker2 = 0;
		button_int2 = BUTTON_CHECK_PRESSED;
	}
	
	/* Start incrementing timer if key was pressed. This is the trailing noise edge. */
	if( button_int2 == BUTTON_PRESSED ){
		debounce_ticker2 = 0;
		button_int2 = BUTTON_CHECK_RELEASED;
	}	
}

/************************************************************************
 *	DEBOUNCE TIMER UPSHIFT
 */
void DebTimer_Upshift	( void )
{
	/* DEBOUNCE INT1 -------------------------------------------- */
	
	/* Increment ticker if signal is high and in "pressed" check state */
	if( ( button_int1 == BUTTON_CHECK_PRESSED ) && ( CHK( PIN_SHIFT_BUTTON_UP, 1<<PIN_SHIFT_UP ) ) ){
		debounce_ticker1++;
	}
	
	/* Increment ticker if signal is low and in "released" check state */
	if( ( button_int1 == BUTTON_CHECK_RELEASED ) && ( !CHK( PIN_SHIFT_BUTTON_UP, 1<<PIN_SHIFT_UP ) ) ){
		debounce_ticker1++;
	}
	
	/* If there was no trailing noise edge on button release */
	if( ( button_int1 == BUTTON_PRESSED ) && ( !CHK( PIN_SHIFT_BUTTON_UP, 1<<PIN_SHIFT_UP ) ) ){
		
		button_int1 = BUTTON_CHECK_RELEASED;
		debounce_ticker1 = 0;
	}
	
	/* A valid button press is detected */
	if( ( button_int1 == BUTTON_CHECK_PRESSED ) && ( debounce_ticker1 >= DEBOUNCE_TIME ) ){
		
		button_int1 = BUTTON_PRESSED;
		debounce_ticker1 = 0;
		
		/* BUTTON IS PRESSED */
#if ( TERMINAL == 1 )
		UART_TxStr_p( PSTR("UP SHIFT\n") );
#endif
		Pneumatic_SendMsg ( PNEUM_MSG_UPSHIFT );					/* Send Message */
	}
	
	/* A valid button release is detected */
	if( ( button_int1 == BUTTON_CHECK_RELEASED ) && ( debounce_ticker1 >= DEBOUNCE_TIME ) ){
		button_int1 = BUTTON_RELEASED;
	}
}

/************************************************************************
 *	DEBOUNCE TIMER DOWNSHIFT
 */
void DebTimer_Downshift	( void )
{
	/* DEBOUNCE INT2 ----------------------------------------- */
	
	/* Increment ticker if signal is high and in "pressed" check state */
	if( ( button_int2 == BUTTON_CHECK_PRESSED ) && ( CHK( PIN_SHIFT_BUTTON_DOWN, 1<<PIN_SHIFT_DOWN ) ) ){
		debounce_ticker2++;
	}
	
	/* Increment ticker if signal is low and in "released" check state */
	if( ( button_int2 == BUTTON_CHECK_RELEASED ) && ( !CHK( PIN_SHIFT_BUTTON_DOWN, 1<<PIN_SHIFT_DOWN ) ) ){
		debounce_ticker2++;
	}
	
	/* If there was no trailing noise edge on button release */
	if( ( button_int2 == BUTTON_PRESSED ) && ( !CHK( PIN_SHIFT_BUTTON_DOWN, 1<<PIN_SHIFT_DOWN ) ) ){
		button_int2 = BUTTON_CHECK_RELEASED;
		debounce_ticker2 = 0;
	}
	
	/* A valid button press is detected */
	if( ( button_int2 == BUTTON_CHECK_PRESSED ) && ( debounce_ticker2 >= DEBOUNCE_TIME ) ){
		
		button_int2 = BUTTON_PRESSED;
		debounce_ticker2 = 0;
		
		/* BUTTON IS PRESSED */
#if ( TERMINAL == 1 )
		UART_TxStr_p( PSTR("DOWN SHIFT\n") );
#endif
		Pneumatic_SendMsg( PNEUM_MSG_DOWNSHIFT );					/* Send Message */
	}
	
	/* A valid button release is detected */
	if( ( button_int2 == BUTTON_CHECK_RELEASED ) && ( debounce_ticker2 >= DEBOUNCE_TIME ) ){
		button_int2 = BUTTON_RELEASED;
	}	
}
#ifndef _TERMINAL_H
#define _TERMINAL_H

#include "can.h"

/************************************************************************
 *	ENUMERATIONS
 */
enum TERM_STATE
{
	TERM_CANINIT = 0,
	TERM_CTRLREG,
	TERM_RXSTAT,
	TERM_READSTAT,
	TERM_INTFLAG,
	TERM_ERRFLAG,
	TERM_TXBUF,
	TERM_RXBUF,
	TERM_MASK,
	TERM_FILT,
	TERM_MSGSTREAM,
	TERM_LOOPBACK,
	TERM_HELP,
	TERM_DISABLE	
};

enum CFG_STATE
{
	CFG_NORMAL = 0,
	CFG_LOOPBACK
};

enum MSGSTRM_STATE
{
	MS_STREAM = 0,
	MS_DISABLE
};

/************************************************************************
 *	FUNCTION PROTOTYPES
 */
void			term_Main			(void);
void			term_Start			(enum MCP2515_STATUS res );
void			term_Commands		(void);
void			term_CtrlReg		(void);
void			term_ReadStatus		(void);
void			term_RxStatus		(void);
void			term_IntFlag		(void);
void			term_ErrorFlag		(void);
void			term_TxBuffer		(void);
void			term_BufTab			(uint8_t addr, uint8_t *data );
void			term_RxMsg			(volatile CanMessage *msg);
void			term_RxBuffer		(void);
void			term_Filt			(void);
void			term_Mask			(void);

#endif
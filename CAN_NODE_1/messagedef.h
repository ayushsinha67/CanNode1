#ifndef MESSAGEDEF_H_
#define MESSAGEDEF_H_

/************************************************************************
 *	MESSAGE IDS
 */
/* Pneumatic Shift*/
#define PNEUM_SHIFT_ID			0x001
#define PNEUM_SHIFT_DLC			1
#define PNEUM_MSG_UPSHIFT		0xFF
#define PNEUM_MSG_DOWNSHIFT		0x00

/* Pneumatic On line */
#define PNEUM_ONLINE_ID			0x008
#define PNEUM_ONLINE_DLC		1
#define PNEUM_ONLINE			0xFF
#define PNEUM_OFFLINE			0x00

/* OIL */
#define OIL_ID					0x002
#define OIL_DLC					4

/* BRAKE */
#define BRAKE_ID				0x003
#define BRAKE_DLC				2

#endif /* MESSAGEDEF_H_ */
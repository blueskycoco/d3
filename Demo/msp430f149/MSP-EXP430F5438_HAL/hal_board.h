/**********************************************************************//**
    Filename: hal_board.h

    Copyright 2010 Texas Instruments, Inc.
***************************************************************************/
#ifndef HAL_BOARD_H
#define HAL_BOARD_H


/*----------------------------------------------------------------
 *                  Function Prototypes
 *----------------------------------------------------------------
 */
static void halBoardGetSystemClockSettings(unsigned char systemClockSpeed, 
                                           unsigned char *setDcoRange,
                                           unsigned char *setVCore,
                                           unsigned int  *setMultiplier);

extern void halBoardInit(void);
void hal430SetSystemClock(unsigned long req_clock_rate, unsigned long ref_clock_rate);

#endif /* HAL_BOARD_H */

/*******************************************************************************
    Filename: hal_buttons.h

    Copyright 2010 Texas Instruments, Inc.
***************************************************************************/
#ifndef HAL_BUTTONS_H
#define HAL_BUTTONS_H

#define BUTTON_PORT_DIR   P3DIR
#define BUTTON_PORT_SEL   P3SEL
#define BUTTON_PORT_OUT   P3OUT
//#define BUTTON_PORT_REN   P2REN
#define BUTTON_PORT_IE    P4IE
#define BUTTON_PORT_IES   P4IES
#define BUTTON_PORT_IFG   P4IFG
#define BUTTON_PORT_IN    P4IN

#define BUTTON_SELECT     BIT3
#define BUTTON_DOWN       BIT2
#define BUTTON_UP         BIT1
#define BUTTON_RIGHT      BIT0
#define BUTTON_LEFT       BIT1 
#define BUTTON_S1         BIT6 
#define BUTTON_S2         BIT7 
#define BUTTON_ALL        0xFE

#define BUTTON_OUTPUT_SEL P3SEL
#define BUTTON_INPUT_SEL P4SEL
#define BUTTON_OUTPUT_DIR   P3DIR
#define BUTTON_INPUT_DIR   P4DIR
#define BUTTON_INPUT_IN    P4IN
#define BUTTON_OUTPUT_OUT    P3OUT
#define BUTTON_OUTPUT_CONFIG_SEL 0xf0
#define BUTTON_INPUT_CONFIG_SEL 0xf0
#define BUTTON_OUTPUT_CONFIG_DIR 0x0f
#define BUTTON_INPUT_CONFIG_DIR 0xf0

extern volatile unsigned char buttonsPressed;

/*-------------------------------------------------------------
 *                  Function Prototypes 
 * ------------------------------------------------------------*/ 
extern void halButtonsInit();
extern unsigned short halButtonsPressed(void);

#endif /* HAL_BUTTONS_H */

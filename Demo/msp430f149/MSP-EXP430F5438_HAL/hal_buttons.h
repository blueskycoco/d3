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

#define BUTTON_MATL 	0x7fff
#define BUTTON_HARD 	0xf7ff
#define BUTTON_DIREC 	0xff7f
#define BUTTON_TIMES 	0xfff7
#define BUTTON_SAVE 	0xbfff
#define BUTTON_UP 	0xfbff
#define BUTTON_DEL 	0xffbf
#define BUTTON_AVE 	0xfffb
#define BUTTON_LEFT 	0xdfff
#define BUTTON_MENU 	0xfdff
#define BUTTON_RIGHT 	0xffdf
#define BUTTON_BACKLIGHT 0xfffd
#define BUTTON_ESC 	0xefff
#define BUTTON_DOWN 	0xfeff
#define BUTTON_ENTER 	0xffef


#define BUTTON_OUTPUT_SEL 		P3SEL
#define BUTTON_INPUT_SEL 		P4SEL
#define BUTTON_OUTPUT_DIR   		P3DIR
#define BUTTON_INPUT_DIR   		P4DIR
#define BUTTON_INPUT_IN    		P4IN
#define BUTTON_OUTPUT_OUT    		P3OUT
#define BUTTON_OUTPUT_CONFIG_SEL 	0xf0
#define BUTTON_INPUT_CONFIG_SEL 	0xe1
#define BUTTON_OUTPUT_CONFIG_DIR 	0x0f
#define BUTTON_INPUT_CONFIG_DIR 	0xe1

extern volatile unsigned char buttonsPressed;

/*-------------------------------------------------------------
 *                  Function Prototypes 
 * ------------------------------------------------------------*/ 
extern void halButtonsInit();
extern unsigned short halButtonsPressed(void);

#endif /* HAL_BUTTONS_H */

/** 
 * @file  hal_buttons.c
 * 
 * Copyright 2010 Texas Instruments, Inc.
***************************************************************************/
#include "msp430.h"
#include "hal_MSP-EXP430F5438.h"

/**********************************************************************//**
 * @brief  Initializes the GPIO ports to act as buttons.
 * 
 * @param  buttonsMask The mask that specifies the button pins.
 * 
 * @return none
 *************************************************************************/   
void halButtonsInit()
{  
	BUTTON_OUTPUT_SEL &= BUTTON_OUTPUT_CONFIG_SEL;//gpio mode
	BUTTON_INPUT_SEL &= BUTTON_INPUT_CONFIG_SEL;//gpio mode
	BUTTON_OUTPUT_DIR |=BUTTON_OUTPUT_CONFIG_DIR;//config p3.3,2,1,0 output
	BUTTON_INPUT_DIR &=BUTTON_INPUT_CONFIG_DIR;//config p4.3,2,1,0 input
	BUTTON_OUTPUT_OUT &=0xf0;//output 0 to p3.3,2,1,0
}

/**********************************************************************//**
 * @brief  Returns LOW for the buttons pressed.
 * 
 * @param  none
 * 
 * @return The buttons that have been pressed, identified by a bit = 0. 
 *************************************************************************/
unsigned char halButtonsPressed(void)
{
  unsigned char value;
  value = BUTTON_INPUT_IN;
  return (0xFF - value)&0x0f;                    //Low==ButtonPressed
}


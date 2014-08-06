/** 
 * @file  hal_buttons.c
 * 
 * Copyright 2010 Texas Instruments, Inc.
***************************************************************************/
#include "msp430.h"
#include "hal_MSP-EXP430F5438.h"
#include <stdio.h>
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
	BUTTON_INPUT_DIR &=BUTTON_INPUT_CONFIG_DIR;//config p4.4,3,2,1 input
	BUTTON_OUTPUT_OUT &=0xf0;//output 0 to p3.3,2,1,0
}

/**********************************************************************//**
 * @brief  Returns LOW for the buttons pressed.
 * 
 * @param  none
 * 
 * @return The buttons that have been pressed, identified by a bit = 0. 
 *************************************************************************/
unsigned short halButtonsPressed(void)
{
  unsigned int value1=0x00;
  unsigned short value2=0x0000;
  BUTTON_OUTPUT_OUT |=0x0f;
  BUTTON_OUTPUT_OUT &=0xfe;
  value1 = BUTTON_INPUT_IN;
//  printf("1 value is %d\r\n",value1);
  if((value1&0x02)==0x02)
  	value2|=0x01;
  if((value1&0x04)==0x04)
  	value2|=0x02;
  if((value1&0x08)==0x08)
  	value2|=0x04;
  if((value1&0x10)==0x10)
  	value2|=0x08;
BUTTON_OUTPUT_OUT |=0x0f;
  BUTTON_OUTPUT_OUT &=0xfd;
  value1 = BUTTON_INPUT_IN;
 // printf("2 value is %d\r\n",value1);
  if((value1&0x02)==0x02)
  	value2|=0x10;
  if((value1&0x04)==0x04)
  	value2|=0x20;
  if((value1&0x08)==0x08)
  	value2|=0x40;
  if((value1&0x10)==0x10)
  	value2|=0x80;
BUTTON_OUTPUT_OUT |=0x0f;
  BUTTON_OUTPUT_OUT &=0xfb;
  value1 = BUTTON_INPUT_IN;
//  printf("3 value is %d\r\n",value1);
  if((value1&0x02)==0x02)
  	value2|=0x0100;
  if((value1&0x04)==0x04)
  	value2|=0x0200;
  if((value1&0x08)==0x08)
  	value2|=0x0400;
  if((value1&0x10)==0x10)
  	value2|=0x0800;
 BUTTON_OUTPUT_OUT |=0x0f;
  BUTTON_OUTPUT_OUT &=0xf7;
  value1 = BUTTON_INPUT_IN;
//  printf("4 value is %d\r\n",value1);
  if((value1&0x02)==0x02)
  	value2|=0x1000;
  if((value1&0x04)==0x04)
  	value2|=0x2000;
  if((value1&0x08)==0x08)
  	value2|=0x4000;
  if((value1&0x10)==0x10)
  	value2|=0x8000;

//printf("End value is %x\r\n",value2);

  //value = BUTTON_INPUT_IN;
  return value2;//(value1<<8)|value2;//(0xFF - value)&0x0f;                    //Low==ButtonPressed
}


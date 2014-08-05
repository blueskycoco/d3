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
unsigned short halButtonsPressed(void)
{
  unsigned char value1=0x00,value2=0x00;
  BUTTON_OUTPUT_OUT |=0xfe;
  BUTTON_OUTPUT_OUT &=0xfe;
  value1 = BUTTON_INPUT_IN;
  printf("1 value is %d\r\n",value1);
  if((BUTTON_INPUT_IN&0x01)==0x00)
  	value1|=0x01;
  if((BUTTON_INPUT_IN&0x02)==0x02)
  	value1|=0x02;
  if((BUTTON_INPUT_IN&0x04)==0x04)
  	value1|=0x04;
  if((BUTTON_INPUT_IN&0x08)==0x08)
  	value1|=0x08;
  BUTTON_OUTPUT_OUT |=0xfd;
  BUTTON_OUTPUT_OUT &=0xfd;
  value1 = BUTTON_INPUT_IN;
  printf("2 value is %d\r\n",value1);
  if((BUTTON_INPUT_IN&0x01)==0x00)
  	value1|=0x10;
  if((BUTTON_INPUT_IN&0x02)==0x02)
  	value1|=0x20;
  if((BUTTON_INPUT_IN&0x04)==0x04)
  	value1|=0x40;
  if((BUTTON_INPUT_IN&0x08)==0x08)
  	value1|=0x80;
  BUTTON_OUTPUT_OUT |=0xfb;
  BUTTON_OUTPUT_OUT &=0xfb;
  value2 = BUTTON_INPUT_IN;
  printf("3 value is %d\r\n",value2);
  if((BUTTON_INPUT_IN&0x01)==0x00)
  	value2|=0x01;
  if((BUTTON_INPUT_IN&0x02)==0x02)
  	value2|=0x02;
  if((BUTTON_INPUT_IN&0x04)==0x04)
  	value2|=0x04;
  if((BUTTON_INPUT_IN&0x08)==0x08)
  	value2|=0x08;
  BUTTON_OUTPUT_OUT |=0xf7;
  BUTTON_OUTPUT_OUT &=0xf7;
  value2 = BUTTON_INPUT_IN;
  printf("4 value is %d\r\n",value2);
  if((BUTTON_INPUT_IN&0x01)==0x00)
  	value2|=0x10;
  if((BUTTON_INPUT_IN&0x02)==0x02)
  	value2|=0x20;
  if((BUTTON_INPUT_IN&0x04)==0x04)
  	value2|=0x40;
  if((BUTTON_INPUT_IN&0x08)==0x08)
  	value2|=0x80;

//printf("value is %d\r\n",BUTTON_INPUT_IN);

  //value = BUTTON_INPUT_IN;
  return (value1<<8)|value2;//(0xFF - value)&0x0f;                    //Low==ButtonPressed
}


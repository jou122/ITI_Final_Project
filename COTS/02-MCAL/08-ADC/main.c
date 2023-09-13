/*
 * main.c
 *
 *  Created on: Sep 13, 2023
 *  Author: Gehad
 *
 *  Description: ADC Test
 *
 */

#include "COTS/01-LIB/01-STD_TYPES/STD_TYPES.h"
#include "COTS/01-LIB/02-BIT_MATH/BIT_MATH.h"

#include "COTS/02-MCAL/01-RCC/RCC_interface.h"
#include "COTS/02-MCAL/02-GPIO/GPIO_interface.h"
#include "COTS/02-MCAL/06-STK/STK_interface.h"
#include "COTS/02-MCAL/08-ADC/ADC_interface.h"

#include "COTS/03-HAL/01-LED/LED_interface.h"
#include "COTS/03-HAL/02-SWITCH/SWITCH_interface.h"
#include "COTS/03-HAL/03-LCD/LCD_interface.h"
#include "COTS/03-HAL/04-Keypad/Keypad_interface.h"


void main()
{
	/*initialize clocks*/
	MRCC_voidInitSysClock();

	/*Enable GPIOA,B, ADC1 clock */
	MRCC_voidEnableClock(RCC_AHB1,GPIOA_EN);
	MRCC_voidEnableClock(RCC_AHB1,GPIOB_EN);
	MRCC_voidEnableClock(RCC_APB2,8);

	MGPIO_VoidSetPinMode(GPIO_B, PIN0, ANALOG);

	/* Initialization */
	MSTK_voidInit();
	//HLCD_voidInitialize();
	MADC1_voidInit();
	MADC1_voidStartConversion(8,1);



	while(1)
	{

	}
}

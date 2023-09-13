/*
 * main.c
 *
 *  Created on: Sep 13, 2023
 *  Author: Gehad
 *
 *  Description: LCD Test
 *
 */

#include "COTS/01-LIB/01-STD_TYPES/STD_TYPES.h"
#include "COTS/01-LIB/02-BIT_MATH/BIT_MATH.h"

#include "COTS/02-MCAL/01-RCC/RCC_interface.h"
#include "COTS/02-MCAL/02-GPIO/GPIO_interface.h"
#include "COTS/02-MCAL/06-STK/STK_interface.h"

#include "COTS/03-HAL/01-LED/LED_interface.h"
#include "COTS/03-HAL/02-SWITCH/SWITCH_interface.h"
#include "COTS/03-HAL/03-LCD/LCD_interface.h"


void main()
{
	/*initialize clocks*/
	MRCC_voidInitSysClock();

	/*Enable GPIOA,B clock */
	MRCC_voidEnableClock(RCC_AHB1,GPIOA_EN);
	MRCC_voidEnableClock(RCC_AHB1,GPIOB_EN);

	/* Initialization */
	MSTK_voidInit();
	MSTK_voidSetBusyWait(1000000);
	HLCD_voidInitialize();
	MSTK_voidSetBusyWait(1000000);

	HLCD_voidNumbers(1);


	while(1);
}

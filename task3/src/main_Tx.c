/*
 * main.c
 *
 *  Created on: Aug 28, 2023
 *  Author: Gehad
 *
 *  Description: - Depending on the state of a button, a motor is turned on or off.
 *  			 - When the button is pressed, Motor ON (the car is moving), if not, then the motor is OFF
 *  			   (the car has stopped).
 *  			 - The state of the motor is always sent to another microcontroller to check if the car door
 *  			    is open or not for car safety.
 *  			 - If the door is opened, a buzzer will be turned on...
 *  			   (that will be handled in the RX script).
 *
 *  Pin used:     A5 	--> Button
 *  		   	  B6    --> Motor
 *  		   A9 & A10 --> USART
 */

#include "COTS/01-LIB/01-STD_TYPES/STD_TYPES.h"
#include "COTS/01-LIB/02-BIT_MATH/BIT_MATH.h"

#include "COTS/02-MCAL/01-RCC/RCC_interface.h"
#include "COTS/02-MCAL/02-GPIO/GPIO_interface.h"
#include "COTS/02-MCAL/03-NVIC/NVIC_interface.h"
#include "COTS/02-MCAL/04-EXTI/EXTI_interface.h"
#include "COTS/02-MCAL/05-SYSCFG/SYSCFG_interface.h"
#include "COTS/02-MCAL/06-STK/STK_interface.h"
#include "COTS/02-MCAL/07-USART1/USART_interface.h"


#include "COTS/03-HAL/01-LED/LED_interface.h"
#include "COTS/03-HAL/02-SWITCH/SWITCH_interface.h"


#define SWITCH 	0
#define IN1 	1
#define IN2 	2
#define EN 		3


void main()
{
	/*initialize clocks*/
	MRCC_voidInitSysClock();

	/*Enable GPIOA clock */
	MRCC_voidEnableClock(RCC_AHB1,GPIOA_EN);
	MRCC_voidEnableClock(RCC_AHB1,GPIOB_EN);

	/* switch */
	HSWITCH_VoidInit(GPIO_A,SWITCH,PULL_UP);

	/* DC Motor */
	MGPIO_VoidSetPinMode(GPIO_A,EN,OUTPUT);
	MGPIO_VoidSetPinOutputType(GPIO_A,EN,OUTPUT_PP);

	MGPIO_VoidSetPinMode(GPIO_A,IN1,OUTPUT);
	MGPIO_VoidSetPinOutputType(GPIO_A,IN1,OUTPUT_PP);

	MGPIO_VoidSetPinMode(GPIO_A,IN2,OUTPUT);
	MGPIO_VoidSetPinOutputType(GPIO_A,IN2,OUTPUT_PP);


	/*set motor direction */
	MGPIO_VoidSetPinValue(GPIO_A,IN1,HIGH);
	MGPIO_VoidSetPinValue(GPIO_A,IN2,LOW);

	/* Initialize USART */
	MUSART1_voidInit();
	MUSART1_voidEnable();

	u8 prev_state = HSWITCH_u8GetSwitchState(GPIO_A, SWITCH);
	u8 current_state;

	while(1)
	{
		/* Get the state of the button */
		current_state = HSWITCH_u8GetSwitchState(GPIO_A,SWITCH);


		if(current_state != prev_state)
				{
					if(current_state == 1)
					{
						MGPIO_VoidSetPinValue(GPIO_A,EN,LOW);
						MUSART1_voidSendData(current_state);
					}

					else
					{
						MGPIO_VoidSetPinValue(GPIO_A,EN,HIGH);
						MUSART1_voidSendData(current_state);
					}
					prev_state = current_state;
				}
			}
}

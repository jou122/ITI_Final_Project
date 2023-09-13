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
#include "COTS/02-MCAL/07-USART1/MUSART_Interface.h"


#include "COTS/03-HAL/01-LED/LED_interface.h"
#include "COTS/03-HAL/02-SWITCH/SWITCH_interface.h"

#define CLKWISE		4
#define ANTICLKWISE 5
#define SWITCH 	0
#define IN1 	1
#define IN2 	2
#define EN 		3

#define IN4 	13
#define IN3 	12
#define EN2 	11


#define TX		9
#define RX		10




void MoveClk(){
	/*set motor direction */
	MGPIO_VoidSetPinValue(GPIO_A,IN3,HIGH);
	MGPIO_VoidSetPinValue(GPIO_A,IN4,LOW);
	MGPIO_VoidSetPinValue(GPIO_A,EN2,HIGH);

}
void MoveAntiClk(){
	/*set motor direction */
	MGPIO_VoidSetPinValue(GPIO_A,IN3,LOW);
	MGPIO_VoidSetPinValue(GPIO_A,IN4,HIGH);
	MGPIO_VoidSetPinValue(GPIO_A,EN2,HIGH);

}

void StopMotor(){
	MGPIO_VoidSetPinValue(GPIO_A,EN2,LOW);
}




void main()
{
	/*initialize clocks*/
	MRCC_voidInitSysClock();

	/*Enable USART clock */
	MRCC_voidEnableClock(RCC_APB2,USART1_EN);

	/*Enable GPIOA clock */
	MRCC_voidEnableClock(RCC_AHB1,GPIOA_EN);
	MRCC_voidEnableClock(RCC_AHB1,GPIOB_EN);

	/* switch */
	HSWITCH_VoidInit(GPIO_A,SWITCH,PULL_UP);

	/* Clkwise button */
	HSWITCH_VoidInit(GPIO_A,SWITCH,PULL_UP);
	/* AntiClkwise button */
	HSWITCH_VoidInit(GPIO_A,SWITCH,PULL_UP);

	/* DC Motor for engine*/
	MGPIO_VoidSetPinMode(GPIO_A,EN,OUTPUT);
	MGPIO_VoidSetPinOutputType(GPIO_A,EN,OUTPUT_PP);

	MGPIO_VoidSetPinMode(GPIO_A,IN1,OUTPUT);
	MGPIO_VoidSetPinOutputType(GPIO_A,IN1,OUTPUT_PP);

	MGPIO_VoidSetPinMode(GPIO_A,IN2,OUTPUT);
	MGPIO_VoidSetPinOutputType(GPIO_A,IN2,OUTPUT_PP);

	/*set motor direction */
	MGPIO_VoidSetPinValue(GPIO_A,IN1,HIGH);
	MGPIO_VoidSetPinValue(GPIO_A,IN2,LOW);


	/* DC Motor for window*/
	MGPIO_VoidSetPinMode(GPIO_A,EN2,OUTPUT);
	MGPIO_VoidSetPinOutputType(GPIO_A,EN2,OUTPUT_PP);

	MGPIO_VoidSetPinMode(GPIO_A,IN3,OUTPUT);
	MGPIO_VoidSetPinOutputType(GPIO_A,IN3,OUTPUT_PP);

	MGPIO_VoidSetPinMode(GPIO_A,IN4,OUTPUT);
	MGPIO_VoidSetPinOutputType(GPIO_A,IN4,OUTPUT_PP);


	/* Initialize USART */

	MGPIO_VoidSetPinMode(GPIO_A, TX, AF);
	MGPIO_VoidSetPinMode(GPIO_A, RX, AF);

	MGPIO_VoidSetPinAlternativeFunction(GPIO_A, TX, AF7);
	MGPIO_VoidSetPinAlternativeFunction(GPIO_A, RX, AF7);


	MUSART_voidInit();

	u8 prev_state = HSWITCH_u8GetSwitchState(GPIO_A, SWITCH);
	u8 current_state;


	if (prev_state==1)
	{prev_state=0;}
	else{prev_state=1;}


	while(1)
	{
		/* Get the state of the button */
		current_state = HSWITCH_u8GetSwitchState(GPIO_A,SWITCH);


		if(current_state != prev_state)
				{
					if(current_state == 1)
					{
						MGPIO_VoidSetPinValue(GPIO_A,EN,LOW);
						MUSART_voidSendData(current_state);
					}

					else
					{
						MGPIO_VoidSetPinValue(GPIO_A,EN,HIGH);
						MUSART_voidSendData(current_state);
					}
					prev_state = current_state;
				}

		if(HSWITCH_u8GetSwitchState(GPIO_A,CLKWISE)==0){
			MoveClk();
		}
		else if (HSWITCH_u8GetSwitchState(GPIO_A,ANTICLKWISE)==0){
			MoveAntiClk();
		}
		else{
			StopMotor();
		}


			}
}

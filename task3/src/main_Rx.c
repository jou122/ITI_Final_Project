/*
 * main.c
 *
 *  Created on: Aug 28, 2023
 *  Author: Gehad
 *
 *  Description: In this RX script :
 *  			 - check if the car door is open or not by getting the state of a button.
 *  			 - Button ON means that car door is open (not safe if car is moving "if received 1 from
 *  			 	first micro-controller" so a buzzer is ON if that happened).
 *  			 - Button OFF: Car door is close (safe whether the car is moving or not).
 *
 *  Pin used:  	  B2 	--> Button
 *  		   	  B7 	--> Buzzer
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


#define BUZZ 	15

#define DOOR1 	5
#define DOOR2 	6
#define DOOR3 	7
#define DOOR4 	8

#define EXTI5_9 23
#define USART_INT 37



u8 motor_state = 0;
u8 door1_state = 0;
u8 door2_state = 0;
u8 door3_state = 0;
u8 door4_state = 0;




void Door1Interrupt(){
	door1_state = HSWITCH_u8GetSwitchState(GPIO_B, DOOR1);

}


void Door2Interrupt(){
	door2_state = HSWITCH_u8GetSwitchState(GPIO_B, DOOR1);

}


void Door3Interrupt(){
	door3_state = HSWITCH_u8GetSwitchState(GPIO_B, DOOR1);

}


void Door4Interrupt(){
	door4_state = HSWITCH_u8GetSwitchState(GPIO_B, DOOR1);

}

void motorInterrupt(){
	motor_state = MUSART1_u8ReceiveData();

}







void (*Door1Ptr)(void)=&Door1Interrupt;
void (*Door2Ptr)(void)=&Door2Interrupt;
void (*Door3Ptr)(void)=&Door3Interrupt;
void (*Door4Ptr)(void)=&Door4Interrupt;

void (*motorPtr)(void)=&motorInterrupt;




void main1()
{



	/*initialize clocks*/
	MRCC_voidInitSysClock();

	/*Enable GPIOA clock */
	MRCC_voidEnableClock(RCC_AHB1,GPIOB_EN);

	/* Initialize USART */ 	/*Enable SYSCNF clock*/ 	/*Enable PortA */
	MUSART1_voidInit();
	MUSART1_voidEnable();




	/* switch */
	HSWITCH_VoidInit(GPIO_B,DOOR1,PULL_UP);
	HSWITCH_VoidInit(GPIO_B,DOOR2,PULL_UP);
	HSWITCH_VoidInit(GPIO_B,DOOR3,PULL_UP);
	HSWITCH_VoidInit(GPIO_B,DOOR4,PULL_UP);

	/* Buzzer */
	MGPIO_VoidSetPinMode(GPIO_A,BUZZ,OUTPUT);
	MGPIO_VoidSetPinOutputType(GPIO_A,BUZZ,OUTPUT_PP);




	/*Enable Interrupts*/
	MEXTI_voidEnableEXTI(DOOR1);
	MEXTI_voidEnableEXTI(DOOR2);
	MEXTI_voidEnableEXTI(DOOR3);
	MEXTI_voidEnableEXTI(DOOR4);

	/*Select signal latch*/
	MEXTI_voidSetSignalLatch(DOOR1 , ON_CHANGE);
	MEXTI_voidSetSignalLatch(DOOR2 , ON_CHANGE);
	MEXTI_voidSetSignalLatch(DOOR3 , ON_CHANGE);
	MEXTI_voidSetSignalLatch(DOOR4 , ON_CHANGE);


	/*NVIC Enable*/
	MNVIC_voidEnableInterrupt(EXTI5_9);

	/*Set Interrupt to port B*/
	MSYSCFG_voidSetEXTIConfiguration(DOOR1,SYSCFG_B);
	MSYSCFG_voidSetEXTIConfiguration(DOOR2,SYSCFG_B);
	MSYSCFG_voidSetEXTIConfiguration(DOOR3,SYSCFG_B);
	MSYSCFG_voidSetEXTIConfiguration(DOOR4,SYSCFG_B);


	/*Set EXTI callback*/
	MEXTI_voidSetCallBack(Door1Ptr,DOOR1);
	MEXTI_voidSetCallBack(Door2Ptr,DOOR2);
	MEXTI_voidSetCallBack(Door3Ptr,DOOR3);
	MEXTI_voidSetCallBack(Door4Ptr,DOOR4);


	/*USART Interrupt*/
	MNVIC_voidEnableInterrupt(USART_INT);
	MUSART1_VoidSetCallBack(motorInterrupt);



	while(1);
}








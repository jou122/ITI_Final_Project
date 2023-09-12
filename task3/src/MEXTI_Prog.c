/*
 * MEXTI_Config.h
 *
 *  Created on: Aug 15, 2023
 *      Author: Youssef
 *      Version: V1
 */
#include"BIT_Math.h"
#include"STD_Types.h"
#include "MEXTI_int.h"
#include "MEXTI_config.h"
#include "MEXTI_private.h"



/*Pointer to function*/

static void(*EXIT_CallBack_Arr[16])(void);

void MEXTI_ClearPendingReg(u8 Copy_u8Line ){
	SET_BIT(MEXTI->PR,Copy_u8Line);
}

void MEXTI_voidEnableEXTI(u8 Copy_u8Line)
{
	SET_BIT(MEXTI->IMR , Copy_u8Line);
}
void MEXTI_voidDisableEXTI(u8 Copy_u8Line)
{
	CLR_BIT(MEXTI->IMR , Copy_u8Line);
}


void MEXTI_voidEventMaskEnable(u8 Copy_u8Line){
	SET_BIT(MEXTI->EMR , Copy_u8Line);
}
void MEXTI_voidEventMaskDisable(u8 Copy_u8Line){
	CLR_BIT(MEXTI->EMR , Copy_u8Line);
}


void MEXTI_voidSetSoftware(u8 Copy_u8Line)
{
	SET_BIT(MEXTI -> SWIER , Copy_u8Line);
}


void MEXTI_voidSelectTrigger(u8 Copy_u8Line , u8 Copy_u8Mode)
{
	switch(Copy_u8Mode)
	{
		case RISING 	:	SET_BIT(MEXTI -> RTSR , Copy_u8Line);
							CLR_BIT(MEXTI -> FTSR , Copy_u8Line); 	break;
		case FALLING	:	SET_BIT(MEXTI -> FTSR , Copy_u8Line);
							CLR_BIT(MEXTI -> RTSR , Copy_u8Line); 	break;
		case ON_CHANGE 	:	SET_BIT(MEXTI -> RTSR , Copy_u8Line);
							SET_BIT(MEXTI -> FTSR , Copy_u8Line); 	break;
	}
}


/*Gamed*/
void MEXTI_voidInerruptSetPort(u8 Copy_u8Line,u8 Copy_u8Port){

	SYSCFG->EXTICR[Copy_u8Line/4] &= ~(0b1111<<(4*(Copy_u8Line%4)));
	SYSCFG->EXTICR[Copy_u8Line/4] |= Copy_u8Port<<(4*(Copy_u8Line%4));
}



void MEXIT_voidSetCallback(u8 Copy_u8InNum,void(*ptr)(void))
{
	EXIT_CallBack_Arr[Copy_u8InNum] = ptr;
}

void EXTI0_IRQHandler(void){
	EXIT_CallBack_Arr[0]();
	MEXTI_ClearPendingReg(MEXTI_LINE0);
}

void EXTI1_IRQHandler(void){
	EXIT_CallBack_Arr[1]();
	MEXTI_ClearPendingReg(MEXTI_LINE1);
}

void EXTI2_IRQHandler(void){
	EXIT_CallBack_Arr[2]();
	MEXTI_ClearPendingReg(MEXTI_LINE2);
}


void EXTI3_IRQHandler(void){
	EXIT_CallBack_Arr[3]();
	MEXTI_ClearPendingReg(MEXTI_LINE3);
}


void EXTI4_IRQHandler(void){
	EXIT_CallBack_Arr[4]();
	MEXTI_ClearPendingReg(MEXTI_LINE4);
}

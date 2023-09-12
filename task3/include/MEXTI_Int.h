/*
 * MEXTI_Config.h
 *
 *  Created on: Aug 15, 2023
 *      Author: Youssef
 *      Version: V1
 */

#ifndef MCAL_MEXTI_MEXTI_INT_H_
#define MCAL_MEXTI_MEXTI_INT_H_


#define MEXTI_LINE0  0
#define MEXTI_LINE1  1
#define MEXTI_LINE2  2
#define MEXTI_LINE3  3
#define MEXTI_LINE4  4
#define MEXTI_LINE5  5
#define MEXTI_LINE6  6
#define MEXTI_LINE7  7
#define MEXTI_LINE8  8
#define MEXTI_LINE9  9
#define MEXTI_LINE10 10
#define MEXTI_LINE11 11
#define MEXTI_LINE12 12
#define MEXTI_LINE13 13
#define MEXTI_LINE14 14
#define MEXTI_LINE15 15


#define MEXTI_PORTA 0
#define MEXTI_PORTB 1
#define MEXTI_PORTC 2
#define MEXTI_PORTD 3
#define MEXTI_PORTE 4
#define MEXTI_PORTH 7


#define NULL  0


#define			RISING				0
#define			FALLING				1
#define			ON_CHANGE			2

void MEXTI_voidEnableEXTI(u8 Copy_u8Line);
void MEXTI_voidDisableEXTI(u8 Copy_u8Line);

void MEXTI_voidSetSoftware(u8 Copy_u8Line);

void MEXTI_voidSelectTrigger(u8 Copy_u8Line , u8 Copy_u8Mode);


void MEXTI_voidEventMaskEnable(u8 Copy_u8Line);
void MEXTI_voidEventMaskDisable(u8 Copy_u8Line);

void MEXTI_ClearPendingReg(u8 Copy_u8Line );

void MEXIT_voidSetCallback(u8 Copy_u8Line,void(*ptr)(void));
void MEXTI_voidInerruptSetPort(u8 Copy_u8Line,u8 Copy_u8Port);


#endif /* MCAL_MEXTI_MEXTI_INT_H_ */

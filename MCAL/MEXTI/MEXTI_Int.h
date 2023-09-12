/*
 * MEXTI_Config.h
 *
 *  Created on: Aug 15, 2023
 *      Author: Youssef
 *      Version: V1
 */

#ifndef MCAL_MEXTI_MEXTI_INT_H_
#define MCAL_MEXTI_MEXTI_INT_H_

#define LINE0  0
#define LINE1  1
#define LINE2  2
#define LINE3  3
#define LINE4  4
#define LINE5  5
#define LINE6  6
#define LINE7  7
#define LINE8  8
#define LINE9  9
#define LINE10 10
#define LINE11 11
#define LINE12 12
#define LINE13 13
#define LINE14 14
#define LINE15 15


#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTH 7


#define NULL  0


#define			RISING				0
#define			FALLING				1
#define			ON_CHANGE			2

void MEXTI_voidEnableEXTI(u8 Copy_u8Line);
void MEXTI_voidDisableEXTI(u8 Copy_u8Line);
void MEXTI_voidSetSoftware(u8 Copy_u8Line);
void MEXTI_voidSelectTrigger(u8 Copy_u8Line , u8 Copy_u8Mode);
void MEXIT_voidSetCallback(u8 Copy_u8Line,void(*ptr)(void));
void MEXTI_voidEventMaskEnable(u8 Copy_u8Line);
void MEXTI_voidEventMaskDisable(u8 Copy_u8Line);
void MEXTI_ClearPendingReg(u8 Copy_u8Line );
void MEXTI_voidInerruptSetPort(u8 Copy_u8Line,u8 Copy_u8Port);


#endif /* MCAL_MEXTI_MEXTI_INT_H_ */

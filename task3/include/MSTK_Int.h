/*
 * MSTK_Int.h
 *
 *  Created on: Aug 15, 2023
 *      Author: user
 */

#ifndef MCAL_MSTK_MSTK_INT_H_
#define MCAL_MSTK_MSTK_INT_H_

#define MSTK_ENABLE 0
#define MSTK_TICKINT 1
#define MSTK_CLKSOURCE 2
#define MSTK_COUNTFLAG 16

#define NULL 0

typedef enum{
	MSTK_INT_ENABLE,
	MSTK_INT_DISABLE
}MSTK_INT_STATE_t;

/*need more comments */
void MSTK_vInit(void) ;
void MSTK_vCount(u32 Copy_Value);
void MSTK_vSetIntState(MSTK_INT_STATE_t Copy_State);
u32 MSTK_u32GetElabsedTime(void);
u32 MSTK_u32GetRemainingTime(void);
void MSTK_voidSetCallBack( void (*ptr)(void) );
u8 MSTK_u8GetFlag(void);
void MSTK_vDelay_us(u32 Copy_u32ValueUs);
void MSTK_vDelay_ms(u32 Copy_u32ValueMs);
void MSTK_vSetInterval_single(u32 Copy_Value);
#endif /* MCAL_MSTK_MSTK_INT_H_ */

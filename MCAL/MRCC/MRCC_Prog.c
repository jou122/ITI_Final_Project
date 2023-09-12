/* Author  : Youssef Mohammed							  */
/* Version : V1											  */
/* Date : 11/8/2023										  */

#include"BIT_Math.h"
#include"STD_Types.h"
#include "MRCC_Int.h"
#include "MRCC_Config.h"
#include "MRCC_Private.h"

void MRCC_vInit(void)
{
#if MRCC_SYS_CLK_SRC == HSI

	/* Enable HSI */
	SET_BIT(RCC->CR, HSION);

	/* Select HSI As Clock Source */
	CLR_BIT(RCC->CFGR, SW0);
	CLR_BIT(RCC->CFGR, SW1);


#elif MRCC_SYS_CLK_SRC == HSE

		/* Enable HSE */
		SET_BIT(RCC->CR, HSEON);

		#if MRCC_HSE_SRC == RC
		/* Enable Bypass */
		SET_BIT(RCC->CR, HSEBYP);

		#elif MRCC_HSE_SRC == CRYSTAL
		/* Disable Bypass */
		CLR_BIT(RCC->CR, HSEBYP);
		#endif

		/* Select HSE As Clock Source */
		SET_BIT(RCC->CFGR, SW0);
		CLR_BIT(RCC->CFGR, SW1);

		#elif MRCC_CLOCK_SRC == MRCC_PLL

		#else
			#error "Wrong Clock Source"

#endif





}

void MRCC_vEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
/******************** Assignment *******************************/
	switch (Copy_u8BusId)
	{
	case RCC_AHB1 : SET_BIT(RCC -> AHB1ENR,Copy_u8PerId); break ;
	case RCC_AHB2 : SET_BIT(RCC -> AHB2ENR,Copy_u8PerId); break ;
	case RCC_APB1 : SET_BIT(RCC -> APB1ENR,Copy_u8PerId); break ;
	case RCC_APB2 : SET_BIT(RCC -> APB2ENR,Copy_u8PerId); break ;

	}


}

void MRCC_vDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
/******************** Assignment *******************************/
		switch (Copy_u8BusId)
		{
		case RCC_AHB1 : CLR_BIT(RCC -> AHB1ENR,Copy_u8PerId); break ;
		case RCC_AHB2 : CLR_BIT(RCC -> AHB2ENR,Copy_u8PerId); break ;
		case RCC_APB1 : CLR_BIT(RCC -> APB1ENR,Copy_u8PerId); break ;
		case RCC_APB2 : CLR_BIT(RCC -> APB2ENR,Copy_u8PerId); break ;


		}
}

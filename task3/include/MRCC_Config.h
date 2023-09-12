/* Author  : Youssef Mohammed							  */
/* Version : V1											  */
/* Date : 11/8/2023										  */

#ifndef MCAL_MRCC_CONFIG_H_
#define MCAL_MRCC_CONFIG_H_

#define MRCC_HSE_ENABLE		ENABLE
#define MRCC_HSI_ENABLE		DISABLE
#define MRCC_PLL_ENABLE		DISABLE

#define MRCC_CSS_ENABLE		ENABLE


 /* Options: 	RCC_HSE
  * 			RCC_HSI
  * 			RCC_PLL	*/
#define MRCC_SYS_CLK_SRC	RCC_HSI

/*Options: CRYSTAL
 * 			 RC 		*/
#define MRCC_HSE_SRC	    CRYSTAL

/*Options:
 * 			  		*/
#define MRCC_PLL_SRC		HSE

#define MRCC_HSE_FREQ		25000000UL

#endif /* MCAL_MRCC_CONFIG_H_ */

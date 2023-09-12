/*
 * MGPIO_Private.h
 *
 *  Created on: Aug 10, 2023
 *      Author: Mostafa Ashraf
 */

#ifndef MCAL_MGPIO_MGPIO_PRIVATE_H_
#define MCAL_MGPIO_MGPIO_PRIVATE_H_


/***************************** GPIO BASE ADDRESS  **********************/
#define MGPIOA_BASE_ADDR  0x40020000
#define MGPIOB_BASE_ADDR  0x40020400
#define MGPIOC_BASE_ADDR  0x40020800

typedef struct{

	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;

}GPIO_MemMap_t;

#define GPIOA ((volatile GPIO_MemMap_t*)(MGPIOA_BASE_ADDR))
#define GPIOB ((volatile GPIO_MemMap_t*)(MGPIOB_BASE_ADDR))
#define GPIOC ((volatile GPIO_MemMap_t*)(MGPIOC_BASE_ADDR))


#endif /* MCAL_MGPIO_MGPIO_PRIVATE_H_ */

/* Author  : Youssef Mohammed							  */
/* Version : V1											  */
/* Date : 11/8/2023										  */

#ifndef MCAL_MRCC_INT_H_
#define MCAL_MRCC_INT_H_

/*CR register*/
#define HSEON   16
#define HSERDY  17
#define HSEBYP  18

#define CSSON   19

#define HSION   0
#define HSIRDY  1

#define PLLON   24
#define PLLRDY  25

/*CFGR Register*/
#define SW0     0
#define SW1     1


/*AHB1ENR*/
#define GPIOAEN 0
#define GPIOBEN 1
#define GPIOCEN 2
#define GPIODEN 3
#define GPIOEEN 4
#define GPIOHEN 7
#define CRCEN   12
#define DMA1EN  21
#define DMA2EN  22


/*AHB2ENR*/
#define OTGFS 7

/*APB1ENR*/
#define TIM2EN 0
#define TIM3EN 1
#define TIM4EN 2
#define TIM5EN 3
#define WWDGEN 11
#define SPI2EN 14
#define SPI3EN 15
#define USART2EN 17
#define I2C1EN 21
#define I2C2EN 22
#define I2C3EN 23
#define PWREN  28


/*APB2ENR*/
#define TIM1EN 0
#define USART1EN 4
#define USART6EN 5
#define ADC1EN 8
#define SDIOEN 11
#define SPI1EN 12
#define SPI4EN 13
#define SYSCFGEN 14
#define TIM9EN 16
#define TIM10EN 17
#define TIM11EN 18

/*BUS select*/
#define MRCC_AHB1  0
#define MRCC_AHB2  1
#define MRCC_APB1  2
#define MRCC_APB2  3


void MRCC_vInit(void) ;
void MRCC_vEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId);
void MRCC_vDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId);


#endif /* MCAL_MRCC_INT_H_ */

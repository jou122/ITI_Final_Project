/*
 * MEXTI_Config.h
 *
 *  Created on: Aug 15, 2023
 *      Author: Youssef
 *      Version: V1
 */

#ifndef MCAL_MEXTI_MEXTI_PRIVATE_H_
#define MCAL_MEXTI_MEXTI_PRIVATE_H_


#define EXTI_BASE_ADDR  0x40013C00
#define SYSCFG_BASE_ADRESS 0x40013800


typedef struct{
	u32 IMR;
	u32 EMR;
	u32 RTSR;
	u32 FTSR;
	u32 SWIER;
	u32 PR;
}MEXTI_t;


typedef struct
{
	u32 MEMRMP;
	u32 PMC;
	u32 EXTICR[4];
	u32 Reserved[2];
	u32 CMPCR;

}MSYSCFG_t;


#define MEXTI 		((volatile MEXTI_t *) EXTI_BASE_ADDR )
#define SYSCFG      ((volatile MSYSCFG_t*)SYSCFG_BASE_ADRESS)




#endif /* MCAL_MEXTI_MEXTI_PRIVATE_H_ */

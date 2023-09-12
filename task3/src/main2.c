#include"STD_TYPES.h"
#include"BIT_MATH.h"



#include"MRCC_Int.h"
#include"MGPIO_Int.h"
#include"MUSART_Int.h"
#include"MEXTI_Int.h"

#define BUZZ 	0

#define DOOR 	1

#define TX 		9
#define RX 		10



void EnableBuzz(void){

	 u8 running = MUSART_u8ReadData();
	 u8 door	=	1;


	 while (door==1 && running==0){
		MGPIO_vSetPinVal(MGPIO_PORTA,BUZZ,MGPIO_HIGH);

		running = MUSART_u8ReadData();
		door = MGPIO_u8GetPinValue(MGPIO_PORTA,DOOR);
	 }

		MGPIO_vSetPinVal(MGPIO_PORTA,BUZZ,MGPIO_HIGH);

}





int main(void)
{


		void (*fun_ptr)(void)=&EnableBuzz;


	/* Initialize UART and GPIO */
		MRCC_vInit();
		MRCC_vEnableClock(MRCC_AHB1, GPIOAEN);
		MRCC_vEnableClock(MRCC_APB2, USART1EN); //Enable CLK Of UART1   At APB2
		MRCC_vEnableClock(MRCC_APB2,SYSCFGEN);


		MGPIO_vSetPinMode(MGPIO_PORTA, TX, MGPIO_MODE_ALTFUN);     //TX-->UART1
		MGPIO_vSetPinMode(MGPIO_PORTA, RX, MGPIO_MODE_ALTFUN);    //RX-->UART1

		MGPIO_vSetAlternativeFunction(MGPIO_PORTA, TX, MGPIO_AF7);      //TX-->UART1
		MGPIO_vSetAlternativeFunction(MGPIO_PORTA, RX, MGPIO_AF7);     //RX-->UART1

	    /* Configure button pin as input*/
		MGPIO_vSetPinMode(MGPIO_PORTA, DOOR, MGPIO_MODE_INPUT);
		MGPIO_vSetPinInputPull(MGPIO_PORTA, DOOR,MGPIO_PULL_UP);

	    /* Configure motor pin as output*/
		MGPIO_vSetPinMode(MGPIO_PORTA, BUZZ, MGPIO_MODE_OUTPUT);
		MGPIO_vSetPinOutputType(MGPIO_PORTA, BUZZ ,MGPIO_PUSHPULL);


		/*EXTI for PIN 1 In port A*/
		MEXTI_voidEnableEXTI(MEXTI_LINE1);
		MEXTI_voidSelectTrigger(MEXTI_LINE1,RISING);
		MEXIT_voidSetCallback(MEXTI_LINE1,fun_ptr);


		MNVIC_VoidEnableInterrupt(7);


		MEXTI_voidInerruptSetPort(MEXTI_LINE1,MEXTI_PORTA);

		/* Initialize USART and STK*/
    	MUSART_voidInit();
    	MSTK_vInit();





  while (1)
    {

		MGPIO_vSetPinVal(MGPIO_PORTA, BUZZ, MGPIO_LOW);

    }

  return 0;
}


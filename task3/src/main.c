#include"STD_TYPES.h"
#include"BIT_MATH.h"



#include"MRCC_Int.h"
#include"MGPIO_Int.h"
#include"MUSART_Int.h"

#define SWITCH 	0
#define IN1 	1
#define IN2 	2
#define EN 		3

#define TX 		9
#define RX 		10


int main2(void)
{

	/* Initialize UART and GPIO */
		MRCC_vInit();
		MRCC_vEnableClock(MRCC_AHB1, GPIOAEN);
		MRCC_vEnableClock(MRCC_APB2, USART1EN); //Enable CLK Of UART1   At APB2


		MGPIO_vSetPinMode(MGPIO_PORTA, TX, MGPIO_MODE_ALTFUN);     //TX-->UART1
		MGPIO_vSetPinMode(MGPIO_PORTA, RX, MGPIO_MODE_ALTFUN);    //RX-->UART1

		MGPIO_vSetAlternativeFunction(MGPIO_PORTA, TX, MGPIO_AF7);      //TX-->UART1
		MGPIO_vSetAlternativeFunction(MGPIO_PORTA, RX, MGPIO_AF7);     //RX-->UART1

	    /* Configure button pin as input*/
		MGPIO_vSetPinMode(MGPIO_PORTA, SWITCH, MGPIO_MODE_INPUT);
		MGPIO_vSetPinInputPull(MGPIO_PORTA, SWITCH,MGPIO_PULL_UP);

	    /* Configure motor pin as output*/
		MGPIO_vSetPinMode(MGPIO_PORTA, IN1, MGPIO_MODE_OUTPUT);
		MGPIO_vSetPinOutputType(MGPIO_PORTA, IN1,MGPIO_PULL_UP);

		MGPIO_vSetPinMode(MGPIO_PORTA, IN2, MGPIO_MODE_OUTPUT);
		MGPIO_vSetPinOutputType(MGPIO_PORTA, IN2,MGPIO_PULL_UP);

		MGPIO_vSetPinMode(MGPIO_PORTA, EN, MGPIO_MODE_OUTPUT);
		MGPIO_vSetPinOutputType(MGPIO_PORTA, EN,MGPIO_PUSHPULL);


		/*set motor direction */
    	MGPIO_vSetPinVal(MGPIO_PORTA,IN1,MGPIO_HIGH);
    	MGPIO_vSetPinVal(MGPIO_PORTA,IN2,MGPIO_LOW);



		/* Initialize USART and STK*/
    	MUSART_voidInit();



		u8 volatile buttonValue = 0 ;
		u8 volatile dataToSend = buttonValue;


  while (1)
    {
	  	  	  /* Read the value of the button */
      	  buttonValue = MGPIO_u8GetPinValue(MGPIO_PORTA,SWITCH);
      	  dataToSend = buttonValue;

      	  MUSART_voidSendData(&dataToSend, 1); // Send data to the second microcontroller

      	  if (buttonValue==1){
      		  MGPIO_vSetPinVal(MGPIO_PORTA,EN,MGPIO_LOW);
      	  }
      	  else{
      		  MGPIO_vSetPinVal(MGPIO_PORTA,EN,MGPIO_HIGH);
      	  }


    }

  return 0;
}


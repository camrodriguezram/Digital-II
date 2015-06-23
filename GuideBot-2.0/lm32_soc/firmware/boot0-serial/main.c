/*****************************************************************************
 * Tipos de datos manejados por la UART

typedef unsigned int  uint32_t;    //Entero sin signo de 32 Bit
typedef signed   int   int32_t;    //Entero con signo de 32 Bit

typedef unsigned char  uint8_t;    // Caracter sin signo de 8 Bit
typedef signed   char   int8_t;    // Caracter con signo de 8 Bit

/****************************************************************************

*/


#include "soc-hw.h"
#include <string.h>
#include <stdlib.h>



int main(int argc, char **argv){ ////Main Fuction

	uint8_t c;
	uint8_t GPIO_INITIAL = 0;
	//uint8_t o1;
	//uint8_t o2;
	
	
	
	for(;;){
	uart_putstr("Empezamos\r\n");
	uart_putstr(" Ingresa w para adelante, s para parar, d para derecha, a para izquierda\r\n");
	
		c = uart_getchar();
		uart_putstr("\r\n");
		uart_putstr("Letra Prueba: ");
		uart_putchar(c);
		uart_putstr("\r\n");
	        gpio0->w_dir = 0xff;
		
		switch (c) {
		
		
		
    		case 'w':  //Suma
    			uart_putstr("Adelante\r\n");
    			gpio_write(0x05); // (0000|0101)
    			uart_putstr("Escribi\r\n");
    			uart_putstr((char *)gpio0->write);
    			sleep(3000);          
    			gpio_write(GPIO_INITIAL);

    			
			break;
			
		case 's': // multi
			uart_putstr("Parar\r\n");
			gpio_write(0x00); // (0000|0000)
			uart_putstr("Escribi\r\n");
			uart_putstr((char *)gpio0->write);
			sleep(3000);          
    		gpio_write(GPIO_INITIAL);
			break;
    			
    		case 'd': // div
			
			uart_putstr("Derecha\r\n");
			gpio_write(0x01); // (0000|0001)
			uart_putstr("Escribi\r\n");
			uart_putstr((char *)gpio0->write);
			sleep(3000);          
    		gpio_write(GPIO_INITIAL);
			
			break;  

		case 'a': // resta
			
			uart_putstr("Izquierda\r\n");
			gpio_write(0x04); // (0000|0100)
			uart_putstr("Escribi\r\n");
			uart_putstr((char *)gpio0->write);
			sleep(3000);          
    		gpio_write(GPIO_INITIAL);
			break;  

		default:
			uart_putstr("Programa terminado!! \r\n");
			return 0;
			break;
		
		
		}
		
		
	}
	
	return 0;
}


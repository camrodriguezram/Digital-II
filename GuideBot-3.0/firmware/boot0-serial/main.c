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

inline void writeint(uint32_t val);

int main(int argc, char **argv){ ////Main Fuction

	uint8_t c;
	uint8_t GPIO_INITIAL = 0;
	//uint8_t o1;
	//uint8_t o2;
	
	gpio_init();
	
	for(;;){
	uart_putstr("Empezamos\r\n");
	uart_putstr(" Ingresa w para adelante, s para parar, d para derecha, a para izquierda\r\n");
	
		c = uart_getchar();
		uart_putstr("\r\n");
		uart_putstr("Letra Prueba: ");
		uart_putchar(c);
		uart_putstr("\r\n");
	
		
		switch (c) {
		
		
		
    	case 'w':  //Suma
			uart_putstr("Adelante\r\n");
			int i=0;
			for(i==0; i<10;i++)
			{
				gpio_write(0x01); // (0000|0001)
				sleep(10);
				gpio_write(0x04); // (0000|0100)
				sleep(10);
		    }         
			gpio_write(GPIO_INITIAL);   			
    			
			break;
			
		case 's': // multi
			uart_putstr("Parar\r\n");
			gpio_write(0x00); // (0000|0000)
			sleep(500);          
    		gpio_write(GPIO_INITIAL);
			break;
    			
    	case 'a': // div
			
			uart_putstr("Derecha\r\n");
			gpio_write(0x01); // (0000|0001)
			sleep(200);          
    		gpio_write(GPIO_INITIAL);
			
			break;  

		case 'd': // resta
			
			uart_putstr("Izquierda\r\n");
			gpio_write(0x04); // (0000|0100)
			sleep(200);          
    		gpio_write(GPIO_INITIAL);
			break;
			
		case 'p': ;// prueba
			
				int f;
				f = 8/8;
				char h;
				h = (char)f;
				uart_putstr("\r\nresultado = ");
				uart_putstr(h);
				uart_putstr("\r\n");
				const char *prueba;
				uart_putstr("\r\nprueba antes\r\n");
				prueba = (char)uart_readString();
				uart_putstr("\r\nprueba despues\r\n");
				uart_putstr(prueba);
				//uart_putstr("SPI STATUS\r\n");
				//uart_putstr((char *)spi_readStatus());
				//spi_init();
				//spi_test();
    			break;

		default:
			uart_putstr("Vuelve a intentarlo \r\n");
			//return 0;
			break;
		
		
		}
		
		
	}
	
	return 0;
}

inline void writeint(uint32_t val)
{
	uint32_t i, digit;

	for (i=0; i<8; i++) 
	{
		digit = (val & 0xf0000000) >> 28;
		if (digit >= 0xA) uart_putchar('A'+digit-10);
		else uart_putchar('0'+digit);
		val <<= 4;
	}
}



#include "soc-hw.h"

uart_t   *uart0  = (uart_t *)   0x20000000;
timer_t  *timer0 = (timer_t *)  0x30000000;
gpio_t   *gpio0  = (gpio_t *)   0x40000000;
//uint32_t *sram0  = (uint32_t *) 0x80000000;
spi_t *spi0 = (spi_t *) 0x50000000; //-------> Modificación

uint32_t msec = 0;

/***************************************************************************
 * General utility functions
 */
void sleep(int msec){
	uint32_t tcr;

	// Use timer0.1
	timer0->compare1 = (FCPU/1000)*msec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN | TIMER_IRQEN;
	//uart_putstr("Hola, estoy en el timer");
	//uart_putstr(compare1);
	do {
		//halt();
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}

void tic_init()
{
	// Setup timer0.0
	timer0->compare0 = (FCPU/1000);
	timer0->counter0 = 0;
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;
}

/***************************************************************************
 * UART Functions
 */
void uart_init()
{
	//uart0->ier = 0x00;  // Interrupt Enable Register
	//uart0->lcr = 0x03;  // Line Control Register:    8N1
	//uart0->mcr = 0x00;  // Modem Control Register

	// Setup Divisor register (Fclk / Baud)
	//uart0->div = (FCPU/(57600*16));
}

char uart_getchar(){   
	while (! (uart0->ucr & UART_DR)) ;
	return uart0->rxtx;
}

const char* uart_readString(void){
	static char rxstr[RX_BUFF];
	//uint8_t rxstr[RX_BUFF];
	static char* temp;
	temp = rxstr;
 uart_putstr("\r\nprueba durante\r\n");
 int i;
 i=0;
	while((temp[i]= uart_getchar()) != ';')
	{
		uart_putstr("\r\nentre al while\r\n");
		temp[i] = rxstr;
		++i;
		uart_putstr(temp[i]); // Prueba
	}
	uart_putstr("\r\n me sali del while\r\n");
	uart_putstr((char)temp);
	return temp;
}


void uart_putchar(char c){
	while (uart0->ucr & UART_BUSY) ;
	uart0->rxtx = c;
}

void uart_putstr(char *str){
	char *c = str;
	while(*c) {
		uart_putchar(*c);
		c++;
	}
}


/***************************************************************************
 * GPIO Functions
 */
 
uint8_t gpio_read(){ // Read a 8 bit "order" from the outside

	return (uint8_t)gpio0->read; //Para el proyecto no sirve... jaja
	
}
void gpio_write(uint8_t dataout){// , uint8_t whichdir){ // Write a 8 bit order to the outside 
	gpio0->write = (uint32_t)dataout; //Le mando la información a dichos pines

}
void gpio_wdir(uint8_t dirout){

	gpio0->w_dir = (uint32_t)dirout; // Desconecto los pines w_dir[i] = 0

}

void gpio_init(){
	
		uint8_t initial = 0x00;
		uint8_t defaults = 0xff;
		
		gpio0->w_dir = initial;
		gpio0->read = initial;
		gpio0->write = initial;

		sleep(10);

		gpio0->w_dir = defaults;
		gpio0->write  = defaults;

		sleep(100);
		gpio0->write  = initial;

	}
 
 /***************************************************************************
 * SPI Functions
 *//**************************************************************************/

void spi_init(void){
	
	int32_t init = 0xff;
	int32_t def = 0x00;

	spi0->rxr = init;
    spi0->txr = init;
    spi0->sr = init;
    spi0->cr = init;
    spi0->ssr = init;
    sleep(100);
    spi0->rxr = def;
    spi0->txr = def;
    spi0->cr = 0x01;
	}

void spi_test(void)
{
	/*int32_t test = 0xAA;
	int32_t init = 0x00;
	//spi0->ssr = 0x00;
	for(;;){
	uart_putstr("Entré al for \r\n");
	spi0->txr = test;
	uart_putstr("Asigné test \r\n");
	uart_putstr(test);
	sleep(1000);
	spi0->txr = init;
	if(!(uart0->ucr & UART_DR)) break;
	}
	*/
	uart_putstr("Prueba del SPI \n");
	//int i;
	int32_t aux_read, aux_write;
	
	spi0->ssr=0;
	spi0->txr = 0x000AffAB; // Probado en el osciloscopio
	//for(i = 0;i<30;i++){	
	aux_read = spi0->rxr;
	aux_write = spi0->txr;
	writeint(aux_read);
	writeint(aux_write);
	uart_putstr("\n Fin de la prueba del SPI \n");
	//}
}

uint8_t spi_readStatus(void){

	return spi0-> sr;

	}


#include "soc-hw.h"

uart_t  *uart0  = (uart_t *)   0x20000000;
timer_t *timer0 = (timer_t *)  0x30000000;
gpio_t  *gpio0  = (gpio_t *)   0x40000000;
//uart_t  *uart1  = (uart_t *)   0x20000000;
spi_t   *spi0   = (spi_t *)    0x50000000;
//i2c_t   *i2c0   = (i2c_t *)    0x70000000;

isr_ptr_t isr_table[32];

void prueba()
{
	   uart0->rxtx=30;
	   timer0->tcr0 = 0xAA;
	   //gpio0->ctrl=0x55;
	   //spi0->rxtx=1;
	   //spi0->nop1=2;
	   //spi0->cs=3;
	   //spi0->divisor=4;
	   //spi0->nop2=5;

}
void tic_isr();
/***************************************************************************
 * IRQ handling
 */
void isr_null()
{
}

void irq_handler(uint32_t pending)
{
	int i;

	for(i=0; i<32; i++) {
		if (pending & 0x01) (*isr_table[i])();
		pending >>= 1;
	}
}

void isr_init()
{
	int i;
	for(i=0; i<32; i++)
		isr_table[i] = &isr_null;
}

void isr_register(int irq, isr_ptr_t isr)
{
	isr_table[irq] = isr;
}

void isr_unregister(int irq)
{
	isr_table[irq] = &isr_null;
}

/**************************************************************************
* SPI
*/
void spi_init(uint32_t constdiv){
	spi0->DEVIDE = constdiv;
	spi0->CTRL |= 0x0A << CHAR_LEN; //Dejandolo en 09 se reciben 7 bits de lectura.
	spi0->CTRL |= 0x00 << GO_BSY;
	spi0->CTRL |= 0x00 << Rx_NEG;
	spi0->CTRL |= 0x00 << Tx_NEG;
	spi0->CTRL |= 0x00 << LSB;
	spi0->CTRL |= 0x00 << IE;
	spi0->CTRL |= 0x00 << ASS;
}

uint32_t spi_readByte(uint8_t cs){
	spi0->SS = cs;
	//spi0->Tx0=0xAA;
	spi0->CTRL |= EN << GO_BSY;
	while((spi0->CTRL >> GO_BSY) & EN);
	spi0->SS = 0;
	return spi0->RxTx0;
	
}

/*************************************************************************
* GPIO Functions
*/
void gpio_init()
{
	gpio0->dir=0x0ff; //---------ORIGINAL 0x0ff ------ Profesor dice 0x00ff
}

uint8_t gpio_read()
{
	return gpio0->read;
}


/****************************************************************************************
 * TIMER Functions
 */
void msleep(uint32_t msec)
{
	uint32_t tcr;

	// Use timer0.1
	timer0->compare1 = (FCPU/1000)*msec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;

	do {
		//halt();
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}

void nsleep(uint32_t nsec)
{
	uint32_t tcr;

	// Use timer0.1
	timer0->compare1 = (FCPU/1000000)*nsec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;

	do {
		//halt();
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}


uint32_t tic_msec;

void tic_isr()
{
	tic_msec++;
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;
}

void tic_init()
{
	tic_msec = 0;

	// Setup timer0.0
	timer0->compare0 = (FCPU/10000);
	timer0->counter0 = 0;
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;

	isr_register(1, &tic_isr);
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

char uart_getchar()
{   
	while (! (uart0->ucr & UART_DR)) ;
	return uart0->rxtx;
}

void uart_putchar(char c)
{
	while (uart0->ucr & UART_BUSY) ;
	uart0->rxtx = c;
}

void uart_putstr(char *str)
{
	char *c = str;
	while(*c) {
		uart_putchar(*c);
		c++;
	}
}


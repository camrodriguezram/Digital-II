#ifndef SPIKEHW_H
#define SPIKEHW_H

#define PROMSTART 0x00000000
#define RAMSTART  0x00000800
#define RAMSIZE   0x400
#define RAMEND    (RAMSTART + RAMSIZE)

#define RAM_START 0x40000000
#define RAM_SIZE  0x04000000

#define FCPU      100000000

#define UART_RXBUFSIZE 32


/****************************************************************************
 * Types
 */
typedef unsigned int  uint32_t;    // 32 Bit
typedef signed   int   int32_t;    // 32 Bit

typedef unsigned char  uint8_t;    // 8 Bit
typedef signed   char   int8_t;    // 8 Bit

/****************************************************************************
 * Interrupt handling
 */
typedef void(*isr_ptr_t)(void);

void     irq_enable();
void     irq_disable();
void     irq_set_mask(uint32_t mask);
uint32_t irq_get_mak();

void     isr_init();
void     isr_register(int irq, isr_ptr_t isr);
void     isr_unregister(int irq);

/****************************************************************************
 * General Stuff
 */
void     halt();
void     jump(uint32_t addr);


/****************************************************************************
 * Timer
 */
#define TIMER_EN     0x08    // Enable Timer
#define TIMER_AR     0x04    // Auto-Reload
#define TIMER_IRQEN  0x02    // IRQ Enable
#define TIMER_TRIG   0x01    // Triggered (reset when writing to TCR)

typedef struct {
	volatile uint32_t tcr0;
	volatile uint32_t compare0;
	volatile uint32_t counter0;
	volatile uint32_t tcr1;
	volatile uint32_t compare1;
	volatile uint32_t counter1;
} timer_t;

void msleep(uint32_t msec);
void nsleep(uint32_t nsec);

void prueba();
void tic_init();


/***************************************************************************
 * GPIO0
 */
typedef struct {
	volatile uint32_t read;
	volatile uint32_t write;
	volatile uint32_t dir;
} gpio_t;

void gpio_init();
uint8_t gpio_read();


/***************************************************************************
 * UART0
 */
#define UART_DR   0x01                    // RX Data Ready
#define UART_ERR  0x02                    // RX Error
#define UART_BUSY 0x10                    // TX Busy

typedef struct {
   volatile uint32_t ucr;
   volatile uint32_t rxtx;
} uart_t;

void uart_init();
void uart_putchar(char c);
void uart_putstr(char *str);
char uart_getchar();

/***************************************************************************
 * SPI0
 */
//Bits of CTRL register
#define CHAR_LEN 0x00
#define GO_BSY	 0x08
#define Rx_NEG	 0x09
#define Tx_NEG	 0x0A
#define LSB		 0x0B
#define IE		 0x0C
#define ASS		 0x0D

#define EN		 0x01
#define OFF		 0x00

typedef struct {
   volatile uint32_t RxTx0;
   volatile uint32_t RxTx1;
   volatile uint32_t RxTx2;
   volatile uint32_t RxTx3;
 //  volatile uint32_t Tx0;
  // volatile uint32_t Tx1;
  // volatile uint32_t Tx2;
   //volatile uint32_t Tx3;
   volatile uint32_t CTRL;
   volatile uint32_t DEVIDE;
   volatile uint32_t SS;
} spi_t;

void prueba();
void spi_init(uint32_t constdiv);
uint32_t spi_readByte(uint8_t cs);
void spi_writeByte(uint8_t data, uint8_t cs);

/***************************************************************************
 * Pointer to actual components
 */
extern timer_t  *timer0;
extern uart_t   *uart0; 
extern gpio_t   *gpio0; 
extern spi_t	*spi0;
extern uint32_t *sram0; 

#endif // SPIKEHW_H

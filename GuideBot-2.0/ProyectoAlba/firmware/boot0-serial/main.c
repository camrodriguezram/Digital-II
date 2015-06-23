#include "soc-hw.h"

uart_t   *uart0  = (uart_t *)   0xF0000000;
timer_t  *timer0 = (timer_t *)  0xF0010000;
gpio_t 	*gpio0 = (gpio_t *)	0xF0020000;
blink_t  *blink0 = (blink_t *)  0xF0030000;
puls_t  *puls0 = (puls_t *)     0XF0040000; 

	int LCD_EN=0x80;
        int LCD_RS=0x20;

void lcd_reset()
{

	gpio0->out = 0xFF;
	sleep(20);
	gpio0->out = 0x03+LCD_EN;
	gpio0->out = 0x03;
	sleep(10);
	gpio0->out = 0x03+LCD_EN;
	gpio0->out = 0x03;
	sleep(1);
	gpio0->out = 0x03+LCD_EN;
	gpio0->out = 0x03;
	sleep(1);
	gpio0->out = 0x02+LCD_EN;
	gpio0->out = 0x02;
	sleep(1);
}
 
void lcd_init ()
{
	lcd_reset(); // Call LCD reset
	lcd_cmd(0x28); // 4-bit mode - 2 line - 5x7 font.
	lcd_cmd(0x0C); // Display no cursor - no blink.
	lcd_cmd(0x06); // Automatic Increment - No Display shift.
	lcd_cmd(0x80); // Address DDRAM with 0 offset 80h.
 }

void lcd_cmd (char cmd)
{
	gpio0->out = ((cmd >> 4) & 0x0F)|LCD_EN;
	gpio0->out = ((cmd >> 4) & 0x0F);
	 
	gpio0->out = (cmd & 0x0F)|LCD_EN;
	gpio0->out = (cmd & 0x0F);
	 
	sleep(200);
	sleep(200);
}
 
void lcd_data (unsigned char dat)
{
	gpio0->out = (((dat >> 4) & 0x0F)|LCD_EN|LCD_RS);
	gpio0->out = (((dat >> 4) & 0x0F)|LCD_RS);
	gpio0->out = ((dat & 0x0F)|LCD_EN|LCD_RS);
	gpio0->out = ((dat & 0x0F)|LCD_RS);
	 
	sleep(200);
	sleep(200);
}

void lcd_puts(char *str)
{
                unsigned int i=0;
                for(;str[i]!=0;i++)
                                lcd_data(str[i]);
}

int main (int argc, char **argv)
{
	int a=0;
	a=puls0->in;	
 	lcd_init();
	lcd_cmd(0X80);      // Start Cursor From First Line
        lcd_puts("Cuanta cantidad?");  //Print HELLO on LCD
        lcd_cmd(0XC0);         // Start Cursor From Second Line
        lcd_puts("a100 b200"); //Print HELLO on LCD

while(1)
{
	a=puls0->in;
	if (a==1)
	{
		blink0->out=0x00000001;
		sleep(1100);
		blink0->out=0x00000000;
                sleep(5000);
                blink0->out=0x00000002;
		sleep(1100);
		blink0->out=0x00000000;
	a=0;
	}
	if (a==2)
	{
		blink0->out=0x00000001;
		sleep(1100);
		blink0->out=0x00000000;
                sleep(10000);
                blink0->out=0x00000002;
		sleep(1100);
		blink0->out=0x00000000;
	a=0;
	}
}
return 0;
}

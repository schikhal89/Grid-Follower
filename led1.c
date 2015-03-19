#include<avr/io.h>
#include<util/delay.h>
#include<LCD_mega16.h>
#define sw1 (!(PIND&(1<<PD2)))
#define sw2 (!(PIND&(1<<PD3)))
#define sw3 (!(PIND&(1<<PB5)))
#define FOSC 16000000
#define BAUD 38400
#define data1 FOSC/16/BAUD-1
#include<motorcontrol.h>
#define self_address   0
#define remote_address 0
#define channel        0


unsigned int count=0;
void init_CC2500(void);
void init_CC2500(void)
{
usart_transmit(self_address);
_delay_ms(1000);
usart_transmit(remote_address);
_delay_ms(1000);
usart_transmit(channel);
_delay_ms(1000);
}


void usart_init(unsigned char ubrr);
void serial_init(void);

void serial_init(void)
{
usart_init(data1);
}



void usart_init(unsigned char ubrr)
{
UBRRH=0;
UBRRL=ubrr;
UCSRB|=(1<<4)|(1<<3)|(1<<7);
UCSRC|=(1<<1)|(1<<2)|(1<<7);

}






void usart_transmit(unsigned char data);
void usart_transmit(unsigned char data)
{
while(!(UCSRA&(1<<UDRE)));
UDR=data;
}






unsigned char usart_receive(void);
unsigned char usart_receive(void)
{
while(!(UCSRA &(1<<RXC)));
 return UDR;
 }



void print_string(unsigned char *Mystr_ptr);
void print_string(unsigned char *Mystr_ptr)
	{
		while((*Mystr_ptr) != '\0')	/* print char from str pointer and point to next location */
				usart_transmit((*Mystr_ptr++));
	}



void led_brightness(unsigned int brightness);
void led_brightness(unsigned int brightness)
{
PORTB|=(1<<4);
_delay_us(brightness);
PORTB&=~(1<<4);
_delay_ms(10);
}

int main()
{
 unsigned int ton,t=0,start_time,end_time;
unsigned char read;
DDRB|=(1<<PB4);
serial_init();
_delay_ms(100);
lcd_init();
PORTC|=(1<<1);
//lcd_string(" sexy shalin!!!!");
init_CC2500();
while(1)
{
read=usart_receive();
lcd_char(read);

if(read=='a')
{
fwd(100);
}
if(read=='b')
{
bck(100);
}
if(read=='c')
{
led_brightness(100);
}

}
}


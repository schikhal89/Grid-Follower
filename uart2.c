#include<avr/io.h>
#include<util/delay.h>
#define FOSC 16000000
#define BAUD 9600
#define data1 FOSC/16/BAUD-1
#include<motorcontrol.h>	



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
UCSRB|=(1<<4)|(1<<3);
UCSRC|=(1<<1)|(1<<2)|(1<<7);

}






void usart_transmit(unsigned char data);
void usart_transmit(unsigned char data)
{
while(!(UCSRA&(1<<UDRE)));
UDR=data;
}


void buzzer(unsigned int time);
void buzzer(unsigned int time)
{
DDRC|=(1<<3);
PORTC|=(1<<3);
_delay_ms(time);
PORTC&=~(1<<3);
_delay_ms(time);
}

void buzzer_off(void);
void buzzer_off(void)
{
DDRC=0x00;
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

unsigned char readch;

int main()
{
serial_init();
unsigned char read;
while(1)
{
read=usart_receive();
usart_transmit(read);

if(read=='w')
{
fwd(500);
buzzer(100);
}


if(read=='a')
{
left_fwd(500);
buzzer(100);
}
if(read=='d')
{
right_fwd(500);
buzzer(100);
}
if(read=='s')
{
bck(500);
buzzer(100);
}

}
}

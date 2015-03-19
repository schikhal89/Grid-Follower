#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#define s1 (!(PINA&(1<<PA0)))
#define s2 (!(PINA&(1<<PA7)))
#define s4 (!(PINA&(1<<PA2)))
#define s5 (!(PINA&(1<<PA1)))
#define s3 (!(PINA&(1<<PA6)))
#define junction (!(s1))&&(!(s2))&&(!(s3))&&(!(s4))&&(!(s5))
#include<motorcontrol.h>
#include<avr/eeprom.h>
//#include<LCD_mega128.h>
#define FOSC 16000000
#define BAUD 38400
#define data1 FOSC/16/BAUD-1
#define self_address   0
#define remote_address 0
#define channel        0
#define sw1 (!(PIND&(1<<PD2)))
#define sw2 (!(PIND&(1<<PD3)))
#define sw3 (!(PIND&(1<<PB5)))
#include <LCD_mega16.h>
unsigned int self_address,remote_address,channel;

unsigned int count=0;
void init_CC2500(void);
void init_CC2500(void)
{
usart_transmit(self_address);
_delay_ms(400);
usart_transmit(remote_address);
_delay_ms(400);
usart_transmit(channel);
_delay_ms(400);
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
PORTC=0x00;
}

void eeprom_write(unsigned int address, unsigned int data);
void eeprom_write(unsigned int address, unsigned int data)
{
while(EECR&(1<<EEWE));
EEAR=address;
EEDR=data;
EECR|=(1<<EEMWE);
EECR|=(1<<EEWE);
}

unsigned char eeprom_read(unsigned int address);
unsigned char eeprom_read(unsigned int address)
{
while(EECR&(1<<EEWE));
EEAR=address;
EECR|=(1<<EERE);
return EEDR;

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

unsigned char readch;

int xaxis=0,yaxis=0;

void initialize(void);
void initialize(void)
{
readch=usart_receive();
if(readch=='a')
{
print_string("enter xaxis\r");
xaxis=usart_receive();
usart_transmit(xaxis);
print_string("\nenter yaxis\n");
yaxis=usart_receive();
usart_transmit(yaxis);
}	
else
{
print_string("enter codes\n");
}	

}
volatile unsigned char temp='0';
ISR(USART_RXC_vect)
{


temp=UDR;
UDR=temp;

_delay_ms(5);
lcd_char((temp));
_delay_ms(5);

}

void lin_fl(void)
{
if((!s2)&&(!s4))
{
fwd(100);
}
if(s4&&(!s2))
{
left_fwd(100);
}
if((!s4)&&s2)
{
right_fwd(100);
}
if((!s4)&&(!s2)&&(!s3))
{

halt();
count++;
}

}

int main()

{
int i=0,data,read;
unsigned char read123;
DDRA&=~((1<<7)|(1<<6)|(1<<2)|(1<<1)|(1<<0));
DDRB|=(1<<4)|(1<<6);
DDRC=0xff;
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<1);
//PORTA=0xff;
DDRD&=~((1<<2)|(1<<3));
DDRB&=~(1<<5);
lcd_init();                                                                                                                                                                                                                                                                               
//PORTD^=(1<<4)|(1<<6);
int xaxis=0,yaxis=0;
serial_init();
_delay_ms(400);
init_CC2500();
print_string("Test");
PORTC|=(1<<1);
DDRD&=~(1<<2);
PORTD|=(1<<2);
sei();
while(1)
{

//lin_fl();

if(!sw1)
{
usart_transmit('a');

}
if(temp=='a')
{
buzzer(1);
}

}
return 0;
}





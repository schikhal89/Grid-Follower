#include<avr/io.h>
#include<util/delay.h>
#define s1 (!(PINA&(1<<PA0)))
#define s2 (!(PINA&(1<<PA7)))
#define s4 (!(PINA&(1<<PA2)))
#define s5 (!(PINA&(1<<PA1)))
#define s3 (!(PINA&(1<<PA6)))
#define junction (s1&&s2&&s3&&s4&&s5)
#include<motorcontrol.h>
#include<avr/eeprom.h>
#include<LCD_mega128.h>
#define FOSC 16000000
#define BAUD 9600
#define data1 FOSC/16/BAUD-1
//#include <gridmake.h>


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
void gridpoints1(void);
void gridpoints1(void)
{
fwd(500);

}
void gridpoints(volatile unsigned char xcoord,volatile unsigned char ycoord);
void gridpoints(volatile unsigned char xcoord,volatile unsigned char ycoord)
{
int x1,y1,count=0,xinit,yinit;
unsigned char readch,read;
unsigned char xread,yread;
volatile unsigned char yaxis,xaxis;
buzzer(100);
while(1)
{


print_string("\renter x-axis\n");
xaxis=usart_receive();
usart_transmit(xaxis);
print_string("\renter y-axis\n");
yaxis=usart_receive();
usart_transmit(yaxis);

xcoord=xaxis;
ycoord=yaxis;
buzzer(100);
while(!junction)
{
fwd(500);
}

if(junction&&count==0)
{
x1++;
buzzer(10);
PORTC=0xff;
}
PORTC=0x00;
if(x1==xcoord)
{
halt();
buzzer(200);
right_align();
count=1;
}

if(count==1&&junction)
{
y1++;
buzzer(10);
}

if(y1==ycoord)
{
halt();
buzzer(200);
left_align();
}

if(x1==xcoord&&y1==ycoord)
{
xinit=x1;
yinit=y1;
count=0;
}
}

}





int main()

{
int i=0,data,xcount,ycount;
DDRA&=~((1<<7)|(1<<6)|(1<<2)|(1<<1)|(1<<0));

unsigned char xaxis=2,yaxis;
int x2=0,y2,var,xinit=0,xcoord=0,yinit,ycoord,xfinal,yfinal;
//DDRA=0;
//DDRB|=(1<<4)|(1<<6);
DDRC=0xff;
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
//PORTA=0xff;
//lcd_init();
//PORTD^=(1<<4)|(1<<6);
serial_init();
while(1)
{
halt();
while(junction&&x2<xaxis)
{
fwd(500);
halt();
x2++;
buzzer(10);

}
if(x2==xaxis&&junction)
{
halt();
right_align();
y2++;
buzzer(10);
	

}

} 	
}


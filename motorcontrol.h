#define s1 (!(PINA&(1<<PA0)))
#define s2 (!(PINA&(1<<PA7)))
#define s4 (!(PINA&(1<<PA2)))
#define s5 (!(PINA&(1<<PA1)))
#define s3 (!(PINA&(1<<PA6)))
#include<util/delay.h>
#include<avr/io.h>



void fwd(unsigned int speed);
void fwd(unsigned int speed)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD|=(1<<4)|(1<<6);
_delay_ms(speed);
PORTD&=~((1<<4)|(1<<6));
_delay_ms(5);

}





void bck(unsigned int speed);
void bck(unsigned int speed)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD|=(1<<5)|(1<<7);
_delay_ms(speed);
PORTD=0x00;
_delay_ms(5);

}



void right_fwd(unsigned int speed);
void right_fwd(unsigned int speed)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD|=(1<<4);
PORTD&=~((1<<5)|(1<<6)|(1<<7));
_delay_ms(speed);
PORTD=0x00;
_delay_ms(5);

}

void right_bck(unsigned int speed);
void right_bck(unsigned int speed)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD|=(1<<5);
PORTD&=~((1<<4)|(1<<6)|(1<<7));
_delay_ms(speed);
PORTD=0x00;
_delay_ms(5);

}

void left_fwd(unsigned int speed);
void left_fwd(unsigned int speed)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD|=(1<<6);
PORTD&=~((1<<5)|(1<<4)|(1<<7));
_delay_ms(speed);
PORTD=0x00;
_delay_ms(5);

}

void left_bck(unsigned int speed);
void left_bck(unsigned int speed)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD|=(1<<7);
PORTD&=~((1<<5)|(1<<4)|(1<<6));
_delay_ms(speed);
PORTD=0x00;
_delay_ms(5);

}

void halt(void);
void halt(void)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD=0x00;
}

void right_align(void);
void right_align(void)
{
right_fwd(1);
if((s2&&(s4==1)))
{
halt();
}

}

void left_align(void);
void left_align(void)
{

if(!((s1))&&((s2))&&(!(s3))&&((s4))&&((s5)))
{
left_fwd(50);
}
halt();
}


void uturn(void);
void uturn(void)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);

PORTD|=((1<<7)|(1<<4));
PORTD&=~((1<<6)|(1<<5));

}





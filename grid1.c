#include<avr/io.h>
#include<util/delay.h>
#define s1 (!(PINA&(1<<PA0)))
#define s2 (!(PINA&(1<<PA7)))
#define s4 (!(PINA&(1<<PA2)))
#define s5 (!(PINA&(1<<PA1)))
#define s3 (!(PINA&(1<<PA6)))



void fwd(unsigned int speed);
void fwd(unsigned int speed)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD=0x50;
_delay_ms(speed);
PORTD=0x00;
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



void right(unsigned int speed);
void right(unsigned int speed)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD|=(1<<4);
PORTD&=~((1<<5)|(1<<6)|(1<<7));
_delay_ms(speed);
PORTD=0x00;
_delay_ms(5);

}


void left(unsigned int speed);
void left(unsigned int speed)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD|=(1<<6);
PORTD&=~((1<<5)|(1<<4)|(1<<7));
_delay_ms(speed);
PORTD=0x00;
_delay_ms(5);

}

int main()

{
int i=0;
DDRA&=~((1<<7)|(1<<6)|(1<<2)|(1<<1)|(1<<0));
DDRB|=(1<<4);
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
//PORTA=0xff;

//PORTD^=(1<<4)|(1<<6);
int xaxis=0,yaxis=0;
while(1)
{
if(s1&&s2&&(!(s3))&&s4&&s5)
{
fwd(500);
}

if(s1&&s2&&s3&&(!(s4))&&s5)
{
right(500);
}
if(s1&&(!(s2))&&(!(s3))&&s4&&s5)
{
left(500);
}

}
}


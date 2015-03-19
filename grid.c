#include<avr/io.h>
#include<util/delay.h>
#define s1 (!(PINA&(1<<PA0)))
#define s2 (!(PINA&(1<<PA7)))
#define s4 (!(PINA&(1<<PA2)))
#define s5 (!(PINA&(1<<PA1)))
#define s3 (!(PINA&(1<<PA6)))



void halfspeed_fwd(void);
void halfspeed_fwd(void)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD=0x50;
_delay_ms(10);
PORTD=0x00;
_delay_ms(10);

}


void fullspeed_fwd(void);
void fullspeed_fwd(void)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD|=(1<<4)|(1<<6);
PORTD&=~((1<<5)|(1<<7));
}


void halfspeed_bck(void);
void halfspeed_bck(void)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD|=(1<<5)|(1<<7);
_delay_ms(10);
PORTD=0x00;
_delay_ms(10);

}

void fullspeed_bck(void);
void fullspeed_bck(void)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD|=(1<<5)|(1<<7);
PORTD&=~((1<<4)|(1<<6));
}

void halfspeed_right(void);
void halfspeed_right(void)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD|=(1<<4);
PORTD&=~((1<<5)|(1<<6)|(1<<7));
_delay_ms(10);
PORTD=0x00;
_delay_ms(10);

}

void fullspeed_right(void);
void fullspeed_right(void)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD|=(1<<4);
PORTD&=~((1<<5)|(1<<6)|(1<<7));

}

void halfspeed_left(void);
void halfspeed_left(void)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD|=(1<<6);
PORTD&=~((1<<5)|(1<<4)|(1<<7));
_delay_ms(10);
PORTD=0x00;
_delay_ms(10);

}

void fullspeed_left(void);
void fullspeed_left(void)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD|=(1<<6);
PORTD&=~((1<<5)|(1<<4)|(1<<7));
}

void checkpin(unsigned int pin);
void checkpin(unsigned int pin)
{


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

if(s1&&s2&&s3&&s4&&s5)
{
xaxis++;
halfspeed_fwd();
}				


if(s3&&(!(s2))&&(!s1))
{
fullspeed_fwd();
}
if((!(s3))&&(!(s2))&&(!s1))
{
halfspeed_right();
		if(s3&&(!(s2))&&(!s1))
			{
			halfspeed_fwd();
				if(s1&&s2&&s3&&s4&&s5)
					{
						halfspeed_left();
							if(s3&&(!(s2))&&(!s1))
							{
							fullspeed_fwd();
								if(s1&&s2&&s3&&s4&&s5)
									{
									yaxis++;
									halfspeed_fwd();
									
									}
							
							}
					
					}
				
				
				
				
			}


}
}
}



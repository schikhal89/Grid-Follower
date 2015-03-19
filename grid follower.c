#include<avr/io.h>
#include<util/delay.h>

void halfspeed(void);
void halfspeed(void)
{
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
PORTD=0x50;
_delay_ms(100);

}
int main()

{
while(1)
{
halfspeed();
}

}
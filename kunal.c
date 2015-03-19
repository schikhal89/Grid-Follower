#include<avr/io.h>
#include<util/delay.h>
#include"homo.h"
#include<avr/interrupt.h>
volatile unsigned char k;
#define  self_adress    '0'
#define  remote_adress  '0'
#define  chanel_adress  '0'
#define  buzzer_init    DDRC|=(1<<3)
#define  buzzer_on      PORTC|=(1<<3)
#define  buzzer_off     PORTC&=~(1<<3)
#define  status_sw1     (PIND&(1<<2))
#define  status_sw2     (PIND&(1<<3))
#define  status_sw3     (PINB&(1<<5))
void sw_init(void);   
void cc2500_init(void);
void cc2500_init(void)
{

uart_tx(self_adress);
_delay_ms(1000);
uart_tx(self_adress);
_delay_ms(1000);
uart_tx(self_adress);
_delay_ms(1000);
}
void sw_init(void)
{


DDRD&=~((1<<2)|(1<<3));
PORTD|=(1<<2)|(1<<3);

DDRB&=~(1<<5);
PORTB|=(1<<5);


}



ISR(USART_RXC_vect)

{


k=UDR;
UDR=k;

}
int main()
{
int d;
sw_init();
buzzer_init ;
sei();
uart_init();
cc2500_init();
sei();
while(1)
{
d=UBRRH;
uart_tx(d);
/*
//uart_tx('k');
if(!status_sw1)
{
uart_tx('a');



}


else if(!status_sw2)
{
uart_tx('b');



}

else if(!status_sw3)
{
uart_tx('c');



}

if(k=='a')
{
buzzer_on ;
}



else if(k=='b')
{
buzzer_off ;
}
else if(k=='c')
{
buzzer_off ;
}
*/
}
return 0;

}

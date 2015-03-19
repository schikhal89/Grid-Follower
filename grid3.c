#include<avr/io.h>
#include<util/delay.h>
#define s1 (!(PINA&(1<<PA0)))
#define s2 (!(PINA&(1<<PA7)))
#define s4 (!(PINA&(1<<PA2)))
#define s5 (!(PINA&(1<<PA1)))
#define s3 (!(PINA&(1<<PA6)))
#define junction (!(s1))&&(!(s2))&&(!(s3))&&(!(s4))&&(!(s5))
#include<motorcontrol.h>
#include<avr/eeprom.h>
#include<LCD_mega128.h>

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
int main()

{
int i=0,data,read;
DDRA&=~((1<<7)|(1<<6)|(1<<2)|(1<<1)|(1<<0));
DDRB|=(1<<4)|(1<<6);
DDRC=0xff;
DDRD|=(1<<4)|(1<<5)|(1<<6)|(1<<7);
//PORTA=0xff;
lcd_init();
//PORTD^=(1<<4)|(1<<6);
int xaxis=0,yaxis=0;
while(1)
{
			lcd_init();
				if((!(s1))&&(!(s2))&&((s3))&&(!(s4))&&(!(s5)))
				{
				fwd(10);
				}
PORTB=0x00;
buzzer_off();
halt();


				if(((s1))&&(!(s2))&&((!s3))&&(!(s4))&&(!(s5)))  //A
				{
				right_fwd(10);
				eeprom_write(0x0000,data|=(1<<0));
				buzzer(10);
				}
PORTB=0x00;
buzzer_off();
halt();


				if((!(s1))&&(!(s2))&&(!(s3))&&(!(s4))&&(!(s5)))
				{
				uturn();
				
				eeprom_write(0x0000,data|=(1<<1));
				
				buzzer(10);
				
				}
				
PORTB=0x00;
buzzer_off();
halt();



				if((!(s1))&&(!(s2))&&((!s3))&&(!(s4))&&((s5)))  //B
				{
				left_fwd(10);
				eeprom_write(0x0000,data|=(1<<2));
				PORTB|=(1<<4);
				
				buzzer(10);
				
				}
PORTB=0x00;
buzzer_off();
halt();
				if((s1)&&(!(s2))&&((!s3))&&(!(s4))&&(!(s5)))  
				{
				eeprom_write(0x0000,data|=(1<<3));
				right_fwd(10);
				PORTB|=(1<<6);
				buzzer(10);
				
				}
PORTB=0x00;
buzzer_off();
halt();


}
}




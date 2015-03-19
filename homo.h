//uart.h............
#include<avr/io.h>
#include<util/delay.h>


void uart_init();
void uart_tx(unsigned char data);
void uart_tx_string(unsigned char *data);
void uart_tx_num(int num);
unsigned char uart_rx();
void uart_rx_string();
unsigned char b[100];
unsigned int i=0,j=0,temp[10];
unsigned int rec_num,p;

void uart_init()
{
UBRRL=25;
UCSRB|=(1<<3)|(1<<4);
//UCSRC|=(1<<1)|(1<<2);
//UBRRL=25;
}

void uart_tx(unsigned char data)
{
while(!(UCSRA&(1<<UDRE)));
UDR=data;
//while(!(UCSRA&(1<<TXC)));
//UCSRA|=(1<<TXC);
}
void uart_tx_string(unsigned char *data)
{
while(*data)
{
uart_tx(*(data++));
}


}
void uart_tx_num(int num)
{
unsigned char data[10];
sprintf(data,"%d",num);

uart_tx_string(data);
}

unsigned char uart_rx()
{
while(!(UCSRA&(1<<RXC)));
return UDR;
}


void uart_rx_string()

{
do
{
 
b[i]=uart_rx();
i++;

}
while(b[i-1]!='\r');
b[i]='\0';


for(i=0;i<=100;i++)
{
uart_tx(b[i]);
}
i=0;
}
unsigned int UART_rx_num()
{
    unsigned char num[10],rxcount=0,rxnum;
    

    while((rxnum = uart_rx())!= '\r')
    {
            num[rxcount] = rxnum - 0x30;
            rxcount++;
    }
    if(rxcount == 1)
    {
        num[2] = num[0];
        num[1] = 0 ;
        num[0] = 0;
    }
    if(rxcount == 2)
    {
        num[2] = num[1];
        num[1] = num[0];
        num[0] = 0;
    }
    rec_num = (num[0]*100 )+(num[1]*10)+num[2];
    return rec_num;
    
}

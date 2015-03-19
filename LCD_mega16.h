/* ---------------------------------------------------------
LCD Header 

PC0 -->  RS pin
PC1 -->  LED 2 ( Active High )
PC2 -->  E pin
PC3 -->  Buzzer
PC4-PC7 -->  Data Pins Of LCD ( 4 Bit Mode )

-----------------------------------------------------------*/

#define CHECKBIT(x,b)	(x&(1<<b))		//Checks bit status
#define SETBIT(x,b)		x|=(1<<b)		//Sets the particular bit
#define CLEARBIT(x,b)	x&=~(1<<b)		//Sets the particular bit
#define TOGGLEBIT(x,b)	x^=(1<<b)		//Toggles the particular bit

#define LINE1	0x80
#define LINE2	0xC0

unsigned char k=0,j=0;

void delay_us(unsigned int tim);
void lcd_init(void);
void lcd_cmd(unsigned char cmd);
void toggleE(void);
void lcd_char(unsigned char single);
void lcd_string(unsigned char str[32]);
void lcd_showvalue(unsigned char num);
void lcd_gotoxy1(unsigned char pos);
void lcd_gotoxy2(unsigned char pos);
void WaitMs(unsigned int ms);

void delay_us(unsigned int time)
{
	for(j=0;j<time;j++)
	{
		for(k=0;k<10;k++)
		{};
	}
}

void toggleE(void)
{
delay_us(100);
SETBIT(PORTC,2);
delay_us(100);
CLEARBIT(PORTC,2);
}

void lcd_cmd(unsigned char cmd)
{
	CLEARBIT(PORTC,0+2);    // RS to 0 means select COmmand register, E to 0 ..
	PORTC=(cmd&0xF0)|(PORTC&(1<<3))|(PORTC&(1<<1));			
	toggleE();
	PORTC=((cmd&(0x0F))*16)|(PORTC&(1<<3))|(PORTC&(1<<1));	
	toggleE();
}

void lcd_init(void)	//init the lcd 
{	
	DDRC=0xFF;		// declare it as an o/p port
	WaitMs(15);		// Given in datasheet ( Cmd for selecting 4 bit mode )
	lcd_cmd(0x03);
	WaitMs(45);
	lcd_cmd(0x02);
	WaitMs(15);
	CLEARBIT(PORTC,0+2);   // RS to 0 means select COmmand register, E to 0 ..
	lcd_cmd(0x01);     // Cmd for clear display
	lcd_cmd(0x0F);		// Cmd for display ON and cursor blinking
	lcd_cmd(0x02);		// Cmd for returning home
	lcd_cmd(LINE1);
	WaitMs(15);
}

void lcd_putchar(unsigned char sig)
{
	PORTC=(sig&0xF0)|(PORTC&(1<<3))|(PORTC&(1<<1));						
	SETBIT(PORTC,0);		// selects data register RS=1
	toggleE();
	PORTC=((sig&(0x0F))*16)|(PORTC&(1<<3))|(PORTC&(1<<1));
	SETBIT(PORTC,0);		// selects data register RS=1
	toggleE();
}

void lcd_char(unsigned char single)
{
	int i;
	if(single =='\t')
	{
		for(i =0 ; i<2 ; i++)
		{	
		lcd_putchar(' ');
		}
	}
	else if(single=='\n')
	{
		lcd_gotoxy2(0);	
	}
	else 
	{
		lcd_putchar(single);
	}
}

void lcd_string(unsigned char str[32])
{
	unsigned char k=0;
	CLEARBIT(PORTC,2);      // Disable the LCD
	while(str[k]!='\0')	//Till null character is encountered
		{
			if(k==16)
			{
			lcd_cmd(LINE2);
			}
			PORTC=((str[k])&0xF0)|(PORTC&(1<<3))|(PORTC&(1<<1));
			SETBIT(PORTC,0);			// selects data register RS=1
			toggleE();
			PORTC=((str[k]&(0x0F))*16)|(PORTC&(1<<3))|(PORTC&(1<<1));
			SETBIT(PORTC,0);			// selects data register RS=1
			toggleE();
			k++;
		}
}

void lcd_showvalue(unsigned char num)	//prints the decimal 3digit value of num
{
	unsigned char H=0,T=0,O=0;
	H=num/100;
	T=(num - (H*100))/10;
	O=(num - (H*100) - (T*10));
	
	lcd_char(H+0x30);
	lcd_char(T+0x30);
	lcd_char(O+0x30);
}

void lcd_gotoxy1(unsigned char pos)
{
	lcd_cmd(LINE1+pos);     // write pos=0 if u want to select 1st location
}

void lcd_gotoxy2(unsigned char pos)
{
	lcd_cmd(LINE2+pos);		 // write pos=0 if u want to select 1st location
}

/* waits (pauses) for ms milliseconds (assumes clock at 16MHz) */
void WaitMs(unsigned int ms)
{
	int i;

	while (ms-- > 0)
	{
		/* 16384 (16k) clock cycles for 1ms; each time through loop
		   is 5 cycles (for loop control + nop) */
		for (i = 0; i < 3276; ++i)
			asm("nop");
	}
}


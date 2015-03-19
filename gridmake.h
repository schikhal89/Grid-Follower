#include<avr/io.h>
#include<util/delay.h>
#define s1 (!(PINA&(1<<PA0)))
#define s2 (!(PINA&(1<<PA7)))
#define s4 (!(PINA&(1<<PA2)))
#define s5 (!(PINA&(1<<PA1)))
#define s3 (!(PINA&(1<<PA6)))
#define junction ((s1))&&((s2))&&(s3))&&((s4))&&((s5))
#include<motorcontrol.h>



void gridpoints(unsigned int xcoord,unsigned int ycoord);
void gridpoints(unsigned int xcoord,unsigned int ycoord)
{
int x1,y1,count=0,xinit,yinit;

while(!junction)
{
fwd(500);
}

if(junction&&count==0)
{
x1++;
buzzer(10);
}

if(x1=xcoord)
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

if(y1=ycoord)
{
halt();
buzzer(200);
left_align();
}

if(x1=xcoord&&y1=ycoord)
{
xinit=x1;
yinit=y1;
count=0;
}
}
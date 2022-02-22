#include<rtx51tny.h>
#include<reg52.h>
#include<absacc.h>
#define u8 unsigned char

sbit beep=P1^5;	  //·äÃùÆ÷±¨¾¯



void delay(unsigned int z)
{
    unsigned int x,y;
    for(x = z;x > 0;x--){
        for(y =110;y > 0;y--);
    }
}


void sound1()//·äÃùÆ÷¸ßÆµ
{
	u8 i=50;
	while(i--)
	{
		beep=!beep;
		delay(10);
	}
}

void sound2()//·äÃùÆ÷µÍÆµ
{
	u8 i=50;
	while(i--)
	{
		beep=!beep;
		delay(1000);
	}
}

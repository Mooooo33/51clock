#include<rtx51tny.h>
#include<reg52.h>
#include<absacc.h>
#define u8 unsigned char
sbit RS=P2^6;	//LCD数据/命令选择端
sbit RW=P2^5;	//LCD读/写端
sbit EN=P2^7;	//LCD使能端

/***************LCD****************/
void write_com(unsigned com)//写操作
{
   EN=0;RS=0;RW=0;
   P0=com;
   delay_50us(1);
   EN=1;
   delay_50us(5);
   EN=0;
}
void write_data(unsigned char dat)//写数据
{
   EN=0;RS=1;RW=0;
   P0=dat;
   delay_50us(1);
   EN=1;
   delay_50us(5);
   EN=0;
}
void Init_LCD(void)//初始化
{
  delay_50us(5);
  write_com(0x38);//写指令38H 不检测忙信号
  delay_50us(1);
  write_com(0x38);
  delay_50us(1);
  write_com(0x38);//不检测忙信号，之后每次写指令、读/写数据操作前均需检测忙信
  write_com(0x38);//显示模式设置
  write_com(0x08); //只开显示
  write_com(0x01); //清屏
  write_com(0x06);//地址加1，当写入数据的时候光标右移
  write_com(0x0C); //开显示，不显示光标
}
//初始化显示
void display0()//显示welcome to use TEMP Monitoring
{
	unsigned char i,w,h=0x8f,i1,w1,h1=0xcf,w2,i2,h2,g=2;
	Init_LCD();
    for(w=0;w<16;w++)  //显示welcome to use
	{
		write_com(h--);//第一行自减左移
		for(i=0;i<16;i++)
		{
			write_data(huany[i]);
			delay_50us(15);
		}
	}
	for(w1=0;w1<16;w1++)//显示TEMP Monitoring
	{
		write_com(h1--);//第二行自减左移
		for(i1=0;i1<16;i1++)
		{
			write_data(tt[i1]);
			delay_50us(15);
		}
	}
	delay_50us(5000);//显示loading
	Init_LCD();
	write_com(0x80);
	for(w2=0;w2<16;w2++)//向右显示
	{
		write_data(duqu[w2]);
		delay_50us(200); 
	}
	while(g--)//小数点循环亮灭
	{
		write_com(0x8a);
		for(i2=0;i2<3;i2++)
		{
			write_data(duqu[i2]);
		}
		write_com(0x8a);
		for(h2=10;h2<14;h2++)
		{
			delay_50us(300);
			write_data(duqu[h2]);
			delay_50us(300);
		}
	}
}
void display1()//显示框架
{
	unsigned char p,q;
	Init_LCD();//全局清零
	write_com(0x80);
	for(q=0;q<16;q++)//显示TMHL
	{
		write_data(tab1[q]);
	}
	write_com(0xc1);
	for(p=0;p<16;p++)
	write_data(tab2[p]);
}


void delay_50us(unsigned int t)//延时
{
	unsigned int j,k;
	for (;t>0;t--)
	{
		for(j=10;j>0;j--)
		{
		 for(k=1;k>0;k--);
		}
	}
}
void delay(unsigned int i)//全局延时
{
  while(i--);
}

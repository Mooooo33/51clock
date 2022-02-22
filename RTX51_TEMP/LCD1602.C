#include<rtx51tny.h>
#include<reg52.h>
#include<absacc.h>
#define u8 unsigned char
sbit RS=P2^6;	//LCD����/����ѡ���
sbit RW=P2^5;	//LCD��/д��
sbit EN=P2^7;	//LCDʹ�ܶ�

/***************LCD****************/
void write_com(unsigned com)//д����
{
   EN=0;RS=0;RW=0;
   P0=com;
   delay_50us(1);
   EN=1;
   delay_50us(5);
   EN=0;
}
void write_data(unsigned char dat)//д����
{
   EN=0;RS=1;RW=0;
   P0=dat;
   delay_50us(1);
   EN=1;
   delay_50us(5);
   EN=0;
}
void Init_LCD(void)//��ʼ��
{
  delay_50us(5);
  write_com(0x38);//дָ��38H �����æ�ź�
  delay_50us(1);
  write_com(0x38);
  delay_50us(1);
  write_com(0x38);//�����æ�źţ�֮��ÿ��дָ���/д���ݲ���ǰ������æ��
  write_com(0x38);//��ʾģʽ����
  write_com(0x08); //ֻ����ʾ
  write_com(0x01); //����
  write_com(0x06);//��ַ��1����д�����ݵ�ʱ��������
  write_com(0x0C); //����ʾ������ʾ���
}
//��ʼ����ʾ
void display0()//��ʾwelcome to use TEMP Monitoring
{
	unsigned char i,w,h=0x8f,i1,w1,h1=0xcf,w2,i2,h2,g=2;
	Init_LCD();
    for(w=0;w<16;w++)  //��ʾwelcome to use
	{
		write_com(h--);//��һ���Լ�����
		for(i=0;i<16;i++)
		{
			write_data(huany[i]);
			delay_50us(15);
		}
	}
	for(w1=0;w1<16;w1++)//��ʾTEMP Monitoring
	{
		write_com(h1--);//�ڶ����Լ�����
		for(i1=0;i1<16;i1++)
		{
			write_data(tt[i1]);
			delay_50us(15);
		}
	}
	delay_50us(5000);//��ʾloading
	Init_LCD();
	write_com(0x80);
	for(w2=0;w2<16;w2++)//������ʾ
	{
		write_data(duqu[w2]);
		delay_50us(200); 
	}
	while(g--)//С����ѭ������
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
void display1()//��ʾ���
{
	unsigned char p,q;
	Init_LCD();//ȫ������
	write_com(0x80);
	for(q=0;q<16;q++)//��ʾTMHL
	{
		write_data(tab1[q]);
	}
	write_com(0xc1);
	for(p=0;p<16;p++)
	write_data(tab2[p]);
}


void delay_50us(unsigned int t)//��ʱ
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
void delay(unsigned int i)//ȫ����ʱ
{
  while(i--);
}
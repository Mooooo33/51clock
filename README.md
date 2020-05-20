//矩阵键盘说明：[4.1]设置时间，[4,2]保存设置，[4,3]设置闹钟，[4,4]关闭闹钟
//[1,1]~[3,2]按钮分别代表数字0~9，按下数字自动进一位

#include<reg52.h>
#define uchar unsigned char
sbit beep=P2^3;//蜂鸣器
sbit dula=P2^6;//段选
sbit wela=P2^7;//位选

uchar s,f,m,key,temp;	//时，分，秒，键盘数字，矩阵键盘
uchar modify,wei,clock,change,one_min;//修改，位选变量，定时，模式切换，一分钟定时
uchar shi20,shi10,fen20,fen10,miao20,miao10,a1,a0,b1,b0,c1,c0;//中间变量
unsigned int time;	//定时器
unsigned char code table[]={
0x3F,0x06,0x5B,0x4F,
0x66,0x6D,0x7D,0x07,
0x7F,0x6F,0x40};//0123456789-   共阴极

void delay(unsigned int z)//delay定时函数
{
    unsigned int x,y;
    for(x = z;x > 0;x--){
        for(y =110;y > 0;y--);
    }
}

void init()//初始化函数
{
	TMOD = 0x01;//设置定时器0为工作方式1
	TH0 = (65536-46080)/256;//装入初值   频率为11.0592MHz时46080
	TL0 = (65536-46080)%256;//装入初值	 如果频率为12MHz改为50000
	EA = 1;//开总中断
	ET0 = 1;//开定时器0中断
	TR0 = 1;//开启定时器0
	
	modify=1;//1为确认，0为修改
}

void display(uchar shi2,uchar shi1,uchar separate2,uchar fen2,uchar fen1,uchar separate1,uchar miao2,uchar miao1)//00-00-00，时-分-秒
{
	dula=1;
	P0=table[shi2];
    dula=0;
    P0=0xff;
    wela=1;
	P0=0xfe;
    wela=0;
    delay(1);
   
	dula=1;
	P0=table[shi1];
    dula=0;
    P0=0xff;
    wela=1;
	P0=0xfd;
    wela=0;
    delay(1);

	dula=1;
	P0=table[separate2];
    dula=0;
    P0=0xff;
    wela=1;
	P0=0xfb;
    wela=0;
    delay(1);
   
	dula=1;
	P0=table[fen2];
    dula=0;
    P0=0xff;
    wela=1;
	P0=0xf7;
    wela=0;
    delay(1);
   
	dula=1;
	P0=table[fen1];
    dula=0;
    P0=0xff;
    wela=1;
	P0=0xef;
    wela=0;
    delay(1);
   
	dula=1;
	P0=table[separate1];
    dula=0;
    P0=0xff;
    wela=1;
	P0=0xdf;
    wela=0;
    delay(1);

	dula=1;
	P0=table[miao2];
    dula=0;
    P0=0xff;
    wela=1;
	P0=0xbf;
    wela=0;
    delay(1);

	dula=1;
	P0=table[miao1];
    dula=0;
    P0=0xff;
    wela=1;
	P0=0x7f;
    wela=0;
    delay(1);

}

void keyscan0()//判断调整开关函数
{
	P3 = 0xf7;
	temp = P3;
	temp = temp & 0xf0;
	if(temp != 0xf0)
	{
		delay(10);
		temp = P3;
		temp = temp & 0xf0;
		if(temp != 0xf0)
		{
			temp = P3;
			switch(temp)
			{
				case 0xe7:		//[4,1]
				   modify = 0;	//开始调整时间
				   change = 1;	//1：时钟模式，2：闹钟模式
					break;
				case 0xd7:		//[4,2]
				   modify = 1;	//结束调整时间
				   change = 0;	//设置闹钟模式
				   clock = 0;		//结束设置闹钟
					break;
				case 0xb7:		//[4,3]
				   modify = 0;	//调整闹钟时间
				   clock = 1;		//开始设置闹钟
					break;
				case 0x77:		//[4,4]
					one_min = 0;	 //结束一分钟闹铃
					break;
			}
		
		}
	}
}

void keyscan()//矩阵键盘扫描
{
  {	
    P3=0xfe;
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delay(10);
      if(temp!=0xf0)
      {	
        temp=P3;
        switch(temp)
        {
          case 0xee:		//[1,1]
               key=0;
			   wei++;
               break;

          case 0xde:		//[1,2]
               key=1;
			   wei++;
               break;

          case 0xbe:		//[1,3]
               key=2;
			   wei++;
               break;

          case 0x7e:		//[1,4]
               key=3;
			   wei++;
               break;
         }
         while(temp!=0xf0) 
        {
           temp=P3;
           temp=temp&0xf0;
           beep=0;
         }
         beep=1;
      }
    }
	
    P3=0xfd;
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delay(10);
      if(temp!=0xf0)
      {
        temp=P3;
        switch(temp)
        {
          case 0xed:		//[2,1]
               key=4;
			   wei++;
               break;

          case 0xdd:		//[2,2]
               key=5;
			   wei++;
               break;

          case 0xbd:		//[2,3]
               key=6;
			   wei++;
               break;

          case 0x7d:		//[2,4]
               key=7;
			   wei++;
               break;
         }
         while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
           beep=0;
         }
         beep=1;
      }
      }
	
    P3=0xfb;
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delay(10);
      if(temp!=0xf0)
      {
        temp=P3;
        switch(temp)
        {
          case 0xeb:		//[3,1]
               key=8;
			   wei++;
               break;

          case 0xdb:		//[3,2]
               key=9;
			   wei++;
               break;
         }
        while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
           beep=0;
         }
         beep=1;
      }
      }
}
}

void main()
{
	init();
	
	while(1)
	{
		keyscan0();
		
		if(modify==1)
		{
			TR0=1;
			wei=0;
		
			a0=s%10;
			a1=s/10;
			b0=f%10;
			b1=f/10;
			c0=m%10;
			c1=m/10;
			display(a1,a0,10,b1,b0,10,c1,c0);
		}
		else//(modify == 0)
		{
			if(change==1)
			{
				TR0=0;
				keyscan();
				
				switch(wei)
				{
					case 1: if(key<3)		//小时最高位为2
							a1=key;
							else
							wei--;
							break;
					case 2: if(a1==1|a1==0)
							a0=key;
							else
							if(key<5)
							a0=key;		   //当小时最高位为2时，低位最高为4
							break;
					case 3: if(key<6)		//分钟最高位为5
							b1=key;
							else
							wei--;
							break;
					case 4: b0=key; break;
					case 5: if(key<6)		//秒最高位为5
							c1=key; 
							else
							wei--;
							break;
					case 6: c0=key; break;
				}

				m=c1*10+c0;
				f=b1*10+b0;
				s=a1*10+a0;
				display(a1,a0,10,b1,b0,10,c1,c0);
			}
			if(clock==1)
			{
				TR0=0;
				display(shi20,shi10,10,fen20,fen10,10,miao20,miao10);	
				keyscan();

				switch(wei)
				{
					case 1: if(key<3)		//小时最高位为2
							shi20=key;
							else
							wei--;
							break;
					case 2: if(a1==1|a1==0)
							shi10=key;
							else
							if(key<5)
							a0=key;		   //当小时最高位为2时，低位最高为4
							break;
					case 3: if(key<6)		//分钟最高位为5
							fen20=key;
							else
							wei--;
							break;
					case 4: fen10=key; break;
					case 5: if(key<6)		//秒最高位为5
							miao20=key; 
							else
							wei--;
							break;
					case 6: miao10=key; break;
				}
				one_min=1;
				display(shi20,shi10,10,fen20,fen10,10,miao20,miao10);	
			}	
		}
		if(one_min==1)//闹铃
		{
			if((a1==shi20)&&(a0==shi10)&&(b1==fen20)&&(b0==fen10)&&(c1==miao20)&&(c0==miao10))
				beep=0;
		}
		if(((a1==shi20)&&(a0==shi10)&&(b1==fen20)&&(b0==fen10+1)&&(c1==miao20)&&(c0==miao10))||(one_min==0))//一分钟报时提示，修报时时间在这
			beep=1;
	}//while
}

void time0() interrupt 1
{	TH0=(65536-46080)/256;
	TL0=(65536-46080)%256;
	time++;

	if(time==20)
	{
		time=0;
		m++;
		if(m==60)
		{
			m=0;
			f++;
			if(f==60)
			{
				f=0;
				s++;
				if(s==24)  //为24h一个循环，若要12h，只需在此改为12即可。，并改下面为s=1；
					s=0;
			}
		}
	}

}

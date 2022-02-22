#include<rtx51tny.h>
#include<reg52.h>
#include<absacc.h>
#define u8 unsigned char

unsigned char ii=0;
sbit k3=P3^2;	//�����¶�������   
sbit k1=P3^1;	//��			   
sbit k2=P3^0;	//��			  

sbit led=P2^4; //����ָʾ��



char set_templ=22,set_temph=40;  //�趨�¶�������Ĭ��ֵ
unsigned short temp_val;  //����ʵ���¶�
unsigned char mode;  //�¶�ģʽ


void delay(unsigned int z)
{
    unsigned int x,y;
    for(x = z;x > 0;x--){
        for(y =110;y > 0;y--);
    }
}

void Temp_DataPros()
{
	short temp;
	unsigned char temp_buf[5];
	temp=Ds18b20ReadTemp();
	temp_val=temp;	
	if(temp<0)
	{
		temp=-temp;
		LCD_Dispstring(2+5,0,"-");
	}
	else
	{
		LCD_Dispstring(2+5,0," ");
	}

	temp_buf[0]=temp/100+0x30;
	temp_buf[1]=temp%100/10+0x30;
	temp_buf[2]='.';
	temp_buf[3]=temp%100%10+0x30;
	temp_buf[4]='\0';
	LCD_Dispstring(2+6,0,temp_buf);		 //��ʾ�����¶�xx.x

	temp_buf[0]=set_temph/10+0x30;
   	temp_buf[1]=set_temph%10+0x30;
	temp_buf[2]='\0';
	LCD_Dispstring(5,1,temp_buf);	  //��ʾ�趨���¶�����ֵxx

	temp_buf[0]=set_templ/10+0x30;
   	temp_buf[1]=set_templ%10+0x30;
	temp_buf[2]='\0';
	LCD_Dispstring(14,1,temp_buf);	 //��ʾ�趨���¶�����ֵxx
}



#define  K1_MODE  1
#define  K2_ADD  2
#define  K3_DEC  3

//mode:  0-����ɨ��   1-����ɨ��
unsigned char KEY_Scan(u8 mode)
{
	static u8 key=1;
	if(key&&(k1==0||k2==0||k3==0))
	{
		delay(1000);   //����
		key=0;
		if(k3==0)
		{
			return K3_DEC;
		}
		else if(k1==0)
		{
			return K1_MODE;
		}
		else if(k2==0)
		{
			return K2_ADD;	
		}
	}
	else if(k1==1&&k2==1&&k3==1)
	{
		key=1;	
	}
	if(mode)
	{
		key=1;
	}
	return 0;	
}

void KEY_Pros()
{
	u8 key;
	u8 temph_buf[3];

	key=KEY_Scan(0);
	
	if(key==K1_MODE)   //ģʽѡ��
	{
		mode++;
		LCD_Clear();

		if(mode==1)
		{
			LCD_Dispstring(0,0,"SETH:   C");		
		}
		else if(mode==2)
		{
			LCD_Dispstring(0,1,"SETL:   C");	
		}
		else 
		{
			mode=0;
			LCD_Dispstring(2,0,"Temp:     C");
			LCD_Dispstring(0,1,"SETH:  ");
			LCD_Dispstring(9,1,"SETL:  ");	
		}
	}
	if(mode==1)	 //�¶���������
	{
		switch(key)	
		{
			case K2_ADD: 	   //��
						set_temph++;
						if(set_temph>=80)set_temph=80;
						break;
			case K3_DEC: 	 //��
						set_temph--;
						if(set_temph<=0)set_temph=0;
						break;
		}

		temph_buf[0]=set_temph/10+0x30;
		temph_buf[1]=set_temph%10+0x30;
		temph_buf[2]='\0';
	   	LCD_Dispstring(6,0,temph_buf);
		At24c02Write(0,set_temph);
	}

	else if(mode==2)  //�¶���������
	{
		switch(key)	
		{
			case K2_ADD: 	   //��
						set_templ++;
						if(set_templ>=80)set_templ=80;
						break;
			case K3_DEC: 	 //��
						set_templ--;
						if(set_templ<=0)set_templ=0;
						break;
		}

		temph_buf[0]=set_templ/10+0x30;
		temph_buf[1]=set_templ%10+0x30;
		temph_buf[2]='\0';
	   	LCD_Dispstring(6,1,temph_buf);
		At24c02Write(2,set_templ);
	}
}

void TempData_Compare()
{
	if(temp_val>set_temph*10)	//ʵ���¶ȸ�������ֵ   ����  
	{
		led=1;
		moto=1;
		relay=1;
		sound1();		
	}
	else if(temp_val<set_templ*10)	 //ʵ���¶ȵ�������ֵ   ����  
	{
		led=1;
		moto=0;
		relay=0;
		sound2();		
	}
	else	//ʵ���¶�������ֵ������ֵ֮��   ȡ������  
	{
		moto=0;
		led=0;
		relay=1;
	}
}

void kai_display()
{
	if(At24c02Read(255)!=18)
	{
		At24c02Write(0,set_temph);
		At24c02Write(2,set_templ);
		At24c02Write(255,18);	
	}
	else
	{
		set_temph=At24c02Read(0);
		set_templ=At24c02Read(2);	
	}

	LCD_Dispstring(2,0,"Temp:     C");
	LCD_Dispstring(0,1,"SETH:  ");
	LCD_Dispstring(9,1,"SETL:  ");
}

job0()_task_ 0	//��������
{
	os_create_task(1);
	os_create_task(2);
	os_create_task(3);
	while(1)
	{
		for(ii=0; ii<3; ii++)
		{
			os_send_signal(ii);
			os_wait2(K_IVL,10);
		}
	}
			//os_delete_task(0);
}

job1()_task_ 1	 //����1
{
	moto=0;
	led=0;
	relay=1;
}

job2()_task_ 2	//����2
{
	LCD_Init();
	kai_display();
	while(1)
	{
		if(mode==0)
		Temp_DataPros();
		KEY_Pros();	
		TempData_Compare();				
	}
}

/*NET 51实验8: 键盘显示控制器8279 应用实验*/
/*NET 51实验8: 键盘显示控制器8279 应用实验*/
#include <reg51.h>
#include <ABSACC.H>
#define C8279 XBYTE[0xE001]
#define D8279 XBYTE[0xE000]

unsigned char  mybuffer[8];
void delay(unsigned char i1);
void disp8279(void);
void init8279(void);
unsigned char getkey(void);

void delay(unsigned char i1)
{
   unsigned char ii;
   unsigned int jj;
   for (ii=0;ii<i1;ii++)
      for (jj=0;jj<0x180;jj++);
}

unsigned char code key[16]={0x23,0x2b,0x33,0x3b,0x22,0x2a,0x32,0x3a,
                            0x21,0x29,0x31,0x39,0x20,0x28,0x30,0x38};

unsigned char code table[24]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,  //0~7
                              0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,  //8~f
                              0x73,0x3e,0x40,0x6e,0x76,0x38,0x00,0x80};  //P(10),U(11),-(12),Y(13),H(14),L(15),关(16) ,.(17)
void disp8279(void)
{
	unsigned char i,j;
	while(i==0x80) 
	{
		j=C8279;
		i=0x80&j;
	} 
	for(i=0;i<8;i++)
	{
		j=mybuffer[i];
		D8279=table[j];
	}
}
void init8279(void)
{
	C8279=0;    //8279方式字
	C8279=0X2A;  //8279分频系数 10分频
	C8279=0xD0;   //清显示
	C8279=0x90;    //设置从左边开始写入
}

unsigned char getkey(void)
{
	unsigned char i,temp,kk;
	temp=C8279;
	if(temp&0x07)
	{
		temp=D8279;
		for(i=0;i<16;i++)
		{
			if (temp==key[i])
			{
				kk=i;
				break;
			}  
		}
		return kk;
	}
	return 16;
}











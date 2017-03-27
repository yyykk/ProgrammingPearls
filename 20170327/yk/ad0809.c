/*NET 51实验5: ad0809数模转换 应用实验*/
#include <ABSACC.H>
#include<8279.h>
#include <intrins.h>
#define AD0809 XBYTE[0X8000]
#define DA0832 XBYTE[0x9000]
#define  uchar unsigned char /*宏定义*/
#define  uint  unsigned int
#define  ZLG7290  0x70    /*端口位定义*/
#define  _Nop()  _nop_()        /*定义空指令*/
char EndFlag = 0;

bit ack;	         /*应答标志位*/   
sbit SDA=P3^1;            /*模拟I2C数据传送位*/
sbit SCL=P3^0;            /*模拟I2C时钟控制位*/  
sbit Pdd=P1^2; 
sbit KEYINT=P1^0;             /*状态标志*/
unsigned counter = 0;
unsigned KeyManageFlag = 0;
unsigned char SLA,SUBA,NUMBYTE,MTD[1],MRD[1],i,k;    //SLA器件从地址，SUBA器件子地址
unsigned char mybuffer[8];
unsigned char End[2], Start[2];
unsigned int f = 0;
			 
void InitDISP(){
	 mybuffer[0]=0;
	 mybuffer[1]=0;
	 mybuffer[2]=0;
	 mybuffer[3]=0;
	 mybuffer[4]=0;
	 mybuffer[5]=0x0f;
}


void InitDISP0(){
	 mybuffer[0]=0;
	 mybuffer[1]=0;
	 mybuffer[2]=0;
	 mybuffer[3]=0;
	 mybuffer[4]=0;
	 mybuffer[5]=0;
}

void InitClock(){
	TMOD = 0x10;
	TH0 = (8192-4607)/32;
	TL0 = (8192-4607)%32;
	ET0 = 1;
	TR0 = 1;
}

void InitClock1(){
	TMOD = 0x10;
	TH1 = 0;
	TL1 = 0;
	ET1 = 1;
	TR1 = 0;
}

void KeyManage(){
	char i;
	InitDISP0();
	disp8279();	
	for(i = 0; i < 6; ++i){
		mybuffer[i] = getkey();
		
	}
	End[0] = mybuffer[0];
	End[1] = mybuffer[1];
	Start[0] = mybuffer[2];
	Start[1] = mybuffer[3];
}

unsigned char ADDA(){
	   unsigned char k;
	   AD0809=0;
	   delay(10);
	   k=AD0809;
	   if(k >= 0xA0){
	   	   TR1 = 1;
		   f = 0x2B0 * (0xFF - k);

	   }else{
	   	   TR1 = 0;
		   Pdd = 1;
	   }
	   if(EndFlag == 0){
	       if(mybuffer[5] != 0x0F){
		       DA0832 = 0x80 + mybuffer[5] * 12;
	       }else if(k>=0x80){
		       DA0832=k;
		   }else{
		       DA0832=0x80;
		   }
	   }else{
	       DA0832 = 0x80;
	   }
	   return k;
}

void main(void)
{
  IE=0xFF;
  InitDISP();
  InitClock1();
  disp8279();
 while(1)	    
  {
   if(KeyManageFlag == 0){
       unsigned char k = ADDA();
	   mybuffer[6]=k&0x0f;
	   k=k>>4;
	   mybuffer[7]=k&0x0f;
	   disp8279();
   }else{
    TR0 = 0;
   	KeyManage();
	KeyManageFlag = 0;
	if(mybuffer[4] != 0){
	    InitClock();
	}
   }
 }
}

void KeyFlag()interrupt 2 using 1
{
	KeyManageFlag = 1;
	DA0832 = 0x80;
}

void Time()interrupt 1
{
	TH0 = (8192-4607)/32;
	TL0 = (8192-4607)%32;
	counter++;
	if(counter == 200 && EndFlag == 0){
	       if(mybuffer[0] >= 0){
		       if(mybuffer[0] == 0){
				   if(mybuffer[1] > 0){
				       mybuffer[0] = 0x0F;
				       mybuffer[1] -= 1;
				   }
			   }else{
			       mybuffer[0] -= 1;
			   }
		   }
		   counter = 0;
		   if(mybuffer[0] == 0 && mybuffer[1] == 0){
		       EndFlag = 1;
		   }
	 }
	 if(counter == 200 && EndFlag == 1){
	       if(mybuffer[2] >= 0){
		       if(mybuffer[2] == 0){
				   if(mybuffer[3] > 0){
				       mybuffer[2] = 0x0F;
				       mybuffer[3] -= 1;
				   }
			   }else{
			       mybuffer[2] -= 1;
			   }
		   }
		   counter = 0;
		   if(mybuffer[2] == 0 && mybuffer[3] == 0){
		       EndFlag = 0;
			   mybuffer[0] = End[0];
			   mybuffer[1] = End[1];
			   mybuffer[2] = Start[0];
			   mybuffer[3] = Start[1];
		   }
	 }
	 disp8279();
}

void Time2()interrupt 3
{
	TH1 = f & 0xFF00;
	TL1 = f & 0x00FF;
	Pdd = ~Pdd;
}

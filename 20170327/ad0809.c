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

//void delay(unsigned char i);
void DISP (void);
void Start_I2c(void);
void Stop_I2c(void);
void  SendByte(uchar c);
unsigned char   RcvByte(void);
unsigned char buffer[8];
void Ack_I2c(bit a);
bit ISendStr(uchar sla,uchar suba,uchar *s,uchar no);
bit IRcvStr(uchar sla,uchar suba,uchar *s,uchar no);//从sla中的suba地址读取no个字节到s中

bit ack;	         /*应答标志位*/   
sbit SDA=P3^1;            /*模拟I2C数据传送位*/
sbit SCL=P3^0;            /*模拟I2C时钟控制位*/  
sbit Pdd=P1^2; 
sbit KEYINT=P1^0;             /*状态标志*/
sbit FLAG = P1^3;
unsigned char SLA,SUBA,NUMBYTE,MTD[1],MRD[1],i,k,    //SLA器件从地址，SUBA器件子地址
              mybuffer[8];
unsigned char code TABKEY[16]={0x1d,0x15,0x0d,0x05,0x1e,0x16,0x0e,0x06,
                               0x1f,0x17,0x0f,0x07,0x20,0x18,0x10,0x08};

unsigned char KeyManageFlag = 0;							 
       
  //******显示子程序*************************
void DISP (void)
{ 
	unsigned char Myi,Myj,MyData[2]; 
    MyData[0]=0x60;
    MyData[1]=mybuffer[Myi];//i == 0
    Myj=0x60;
    for(Myi=0;Myi<8;Myi++)
    { 
       MyData[0]=Myj;
       MyData[1]=mybuffer[Myi];
       Myj++;//0110_0000 -> 0110_1000 按位下载数据且译码指令
      SLA=ZLG7290;
      SUBA=0x07;//CmdBuf0
      NUMBYTE=0x02;//2个字节
      ISendStr(SLA,SUBA,MyData,NUMBYTE); 
	  //向器件地址sla的子地址suba发送s指向的内容no个字节  
    }
}





/*******************************************************************
                     起动总线函数               
函数原型: void  Start_I2c();  
功能:       启动I2C总线,即发送I2C起始条件.
  
********************************************************************/
void Start_I2c(void)
{
  SDA=1;   /*发送起始条件的数据信号*/
  _Nop();
  SCL=1;
  _Nop();    /*起始条件建立时间大于4.7us,延时*/
  _Nop();
  _Nop();
  _Nop();
  _Nop();    
  SDA=0;   /*发送起始信号*/
  _Nop();    /* 起始条件锁定时间大于4μs*/
  _Nop();
  _Nop();
  _Nop();
  _Nop();       
  SCL=0;   /*钳住I2C总线，准备发送或接收数据 */
  _Nop();
  _Nop();
}




/*******************************************************************
                      结束总线函数               
函数原型: void  Stop_I2c();  
功能:       结束I2C总线,即发送I2C结束条件.
  
********************************************************************/
void Stop_I2c(void)
{
  SDA=0;  /*发送结束条件的数据信号*/
  _Nop();   /*发送结束条件的时钟信号*/
  SCL=1;  /*结束条件建立时间大于4μs*/
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  SDA=1;  /*发送I2C总线结束信号*/
  _Nop();
  _Nop();
  _Nop();
  _Nop();
}




/*******************************************************************
                 字节数据传送函数               
函数原型: void  SendByte(uchar c);
功能:  将数据c发送出去,可以是地址,也可以是数据,发完后等待应答,并对
     此状态位进行操作.(不应答或非应答都使ack=0 假)     
     发送数据正常，ack=1; ack=0表示被控器无应答或损坏。
********************************************************************/
void  SendByte(uchar c)
{
 uchar BitCnt;
 
 for(BitCnt=0;BitCnt<8;BitCnt++)  /*要传送的数据长度为8位*/
    {
     if((c<<BitCnt)&0x80)SDA=1;   /*判断发送位*/
       else  SDA=0;                
     _Nop();
     SCL=1;               /*置时钟线为高，通知被控器开始接收数据位*/
      _Nop(); 
      _Nop();               /*保证时钟高电平周期大于4μs*/
      _Nop();
      _Nop();
      _Nop();         
     SCL=0; 
    }
    
    _Nop();
    _Nop();
    SDA=1;               /*8位发送完后释放数据线，准备接收应答位*/
    _Nop();
    _Nop();   
    SCL=1;
    _Nop();
    _Nop();
    _Nop();
    if(SDA==1)ack=0;     
       else ack=1;        /*判断是否接收到应答信号*/
    SCL=0;
    _Nop();
    _Nop();
}






/*******************************************************************
                 字节数据传送函数               
函数原型: uchar  RcvByte();
功能:  用来接收从器件传来的数据,并判断总线错误(不发应答信号)，
     发完后请用应答函数。  
********************************************************************/	
uchar  RcvByte()
{
  uchar retc;
  uchar BitCnt;
  
  retc=0; 
  SDA=1;             /*置数据线为输入方式*/
  for(BitCnt=0;BitCnt<8;BitCnt++)
      {
        _Nop();           
        SCL=0;       /*置时钟线为低，准备接收数据位*/
        _Nop();
        _Nop();         /*时钟低电平周期大于4.7μs*/
        _Nop();
        _Nop();
        _Nop();
        SCL=1;       /*置时钟线为高使数据线上数据有效*/
        _Nop();
        _Nop();
        retc=retc<<1;
        if(SDA==1)retc=retc+1; /*读数据位,接收的数据位放入retc中 */
        _Nop();
        _Nop(); 
      }
  SCL=0;    
  _Nop();
  _Nop();
  return(retc);
}




/********************************************************************
                     应答子函数
原型:  void Ack_I2c(bit a);
 
功能:主控器进行应答信号,(可以是应答或非应答信号)
********************************************************************/
void Ack_I2c(bit a)
{
  
  if(a==0)SDA=0;     /*在此发出应答或非应答信号 */
        else SDA=1;
  _Nop();
  _Nop();
  _Nop();      
  SCL=1;
    _Nop();
    _Nop();              /*时钟低电平周期大于4μs*/
    _Nop();
    _Nop();
    _Nop();  
 SCL=0;                /*清时钟线，钳住I2C总线以便继续接收*/
    _Nop();
    _Nop();    
}









/*******************************************************************
                    向有子地址器件发送多字节数据函数               
函数原型: bit  ISendStr(uchar sla,uchar suba,ucahr *s,uchar no);  
功能:     从启动总线到发送地址，子地址,数据，结束总线的全过程,从器件
          地址sla，子地址suba，发送内容是s指向的内容，发送no个字节。
           如果返回1表示操作成功，否则操作有误。
注意：    使用前必须已结束总线。
********************************************************************/
bit ISendStr(uchar sla,uchar suba,uchar *s,uchar no)
{
   uchar i;

   Start_I2c();               /*启动总线*/
   SendByte(sla);            /*发送器件地址*/
     if(ack==0)return(0);
   SendByte(suba);            /*发送器件子地址*/
     if(ack==0)return(0);

   for(i=0;i<no;i++)
    {   
     SendByte(*s);               /*发送数据*/
       if(ack==0)return(0);
     s++;
    } 
 Stop_I2c();                 /*结束总线*/ 
  return(1);
}


/*******************************************************************
                    向有子地址器件读取多字节数据函数               
函数原型: bit  ISendStr(uchar sla,uchar suba,ucahr *s,uchar no);  
功能:     从启动总线到发送地址，子地址,读数据，结束总线的全过程,从器件
          地址sla，子地址suba，读出的内容放入s指向的存储区，读no个字节。
           如果返回1表示操作成功，否则操作有误。
注意：    使用前必须已结束总线。
********************************************************************/
bit IRcvStr(uchar sla,uchar suba,uchar *s,uchar no)
{
   uchar i;

   Start_I2c();               /*启动总线*/
   SendByte(sla);            /*发送器件地址*/
     if(ack==0)return(0);
   SendByte(suba);            /*发送器件子地址*/
     if(ack==0)return(0);

   Start_I2c();
   SendByte(sla+1);
      if(ack==0)return(0);

   for(i=0;i<no-1;i++)
    {   
     *s=RcvByte();               /*发送数据*/
      Ack_I2c(0);                /*发送就答位*/  
     s++;
    } 
   *s=RcvByte();
    Ack_I2c(1);                 /*发送非应位*/
 Stop_I2c();                    /*结束总线*/ 
  return(1);
}

void InitDISP(){
	 mybuffer[0]=0;
	 mybuffer[1]=0;
	 mybuffer[2]=0;
	 mybuffer[3]=0;
	 mybuffer[4]=2;
	 mybuffer[5]=0;
	 mybuffer[6]=4;
	 mybuffer[7]=1;
}


void InitDISP0(){
	 mybuffer[0]=0;
	 mybuffer[1]=0;
	 mybuffer[2]=0;
	 mybuffer[3]=0;
	 mybuffer[4]=0;
	 mybuffer[5]=0;
	 mybuffer[6]=0;
	 mybuffer[7]=0;
}

void KeyManage(){
	InitDISP0();
    DISP(); 
    i=0;
   while(1)
    {
		if(KEYINT == 1){
          SLA=ZLG7290;
          SUBA=0x01;
          NUMBYTE=0x01;
          //IRcvStr(SLA,SUBA,MRD,NUMBYTE); //从sla中的suba地址读取no个字节到s中
          delay(10);
          k=0;
		  *MRD = 1;
          if(*MRD!=TABKEY[k])
          {
             while(*MRD!=TABKEY[k]) //获取读取的字符位于TABKEY中的位置k
              {
                k++;
               }
          } 
          mybuffer[i]=k; //8个数码管显示，与DISP通过该数组传递数据  
          if(i<8){//修改前8位
			  i++;
			}
          else
             {i=0;}          
          DISP();
		if(i == 8){
			break;
		}
	  }
     }

}

void main(void)
{
  Pdd = 0;
  IE=0xFF;
  InitDISP();
  DISP();
  delay(10);
 while(1)	    
  {
   unsigned char k;
   AD0809=0;
   //delay(10);
   k=AD0809;
   if(k>=0x90)
   DA0832=k;
   else
   DA0832=0x90;
   mybuffer[0]=k&0x0f;
   k=k>>4;
   mybuffer[1]=k&0x0f;
   DISP();
   //if(KeyManageFlag == 1){
   	//KeyManage();
	//KeyManageFlag = 0;
   //}
 }
}

void KeyFlag()interrupt 2 using 1
{
    Pdd = 1;
	KeyManage();
	//KeyManageFlag = 1;
}

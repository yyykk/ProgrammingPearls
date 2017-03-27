/*NET 51ʵ��5: ad0809��ģת�� Ӧ��ʵ��*/
#include <ABSACC.H>
#include<8279.h>
#include <intrins.h>
#define AD0809 XBYTE[0X8000]
#define DA0832 XBYTE[0x9000]
#define  uchar unsigned char /*�궨��*/
#define  uint  unsigned int
#define  ZLG7290  0x70    /*�˿�λ����*/
#define  _Nop()  _nop_()        /*�����ָ��*/

//void delay(unsigned char i);
void DISP (void);
void Start_I2c(void);
void Stop_I2c(void);
void  SendByte(uchar c);
unsigned char   RcvByte(void);
unsigned char buffer[8];
void Ack_I2c(bit a);
bit ISendStr(uchar sla,uchar suba,uchar *s,uchar no);
bit IRcvStr(uchar sla,uchar suba,uchar *s,uchar no);//��sla�е�suba��ַ��ȡno���ֽڵ�s��

bit ack;	         /*Ӧ���־λ*/   
sbit SDA=P3^1;            /*ģ��I2C���ݴ���λ*/
sbit SCL=P3^0;            /*ģ��I2Cʱ�ӿ���λ*/  
sbit Pdd=P1^2; 
sbit KEYINT=P1^0;             /*״̬��־*/
sbit FLAG = P1^3;
unsigned char SLA,SUBA,NUMBYTE,MTD[1],MRD[1],i,k,    //SLA�����ӵ�ַ��SUBA�����ӵ�ַ
              mybuffer[8];
unsigned char code TABKEY[16]={0x1d,0x15,0x0d,0x05,0x1e,0x16,0x0e,0x06,
                               0x1f,0x17,0x0f,0x07,0x20,0x18,0x10,0x08};

unsigned char KeyManageFlag = 0;							 
       
  //******��ʾ�ӳ���*************************
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
       Myj++;//0110_0000 -> 0110_1000 ��λ��������������ָ��
      SLA=ZLG7290;
      SUBA=0x07;//CmdBuf0
      NUMBYTE=0x02;//2���ֽ�
      ISendStr(SLA,SUBA,MyData,NUMBYTE); 
	  //��������ַsla���ӵ�ַsuba����sָ�������no���ֽ�  
    }
}





/*******************************************************************
                     �����ߺ���               
����ԭ��: void  Start_I2c();  
����:       ����I2C����,������I2C��ʼ����.
  
********************************************************************/
void Start_I2c(void)
{
  SDA=1;   /*������ʼ�����������ź�*/
  _Nop();
  SCL=1;
  _Nop();    /*��ʼ��������ʱ�����4.7us,��ʱ*/
  _Nop();
  _Nop();
  _Nop();
  _Nop();    
  SDA=0;   /*������ʼ�ź�*/
  _Nop();    /* ��ʼ��������ʱ�����4��s*/
  _Nop();
  _Nop();
  _Nop();
  _Nop();       
  SCL=0;   /*ǯסI2C���ߣ�׼�����ͻ�������� */
  _Nop();
  _Nop();
}




/*******************************************************************
                      �������ߺ���               
����ԭ��: void  Stop_I2c();  
����:       ����I2C����,������I2C��������.
  
********************************************************************/
void Stop_I2c(void)
{
  SDA=0;  /*���ͽ��������������ź�*/
  _Nop();   /*���ͽ���������ʱ���ź�*/
  SCL=1;  /*������������ʱ�����4��s*/
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  SDA=1;  /*����I2C���߽����ź�*/
  _Nop();
  _Nop();
  _Nop();
  _Nop();
}




/*******************************************************************
                 �ֽ����ݴ��ͺ���               
����ԭ��: void  SendByte(uchar c);
����:  ������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������,�����ȴ�Ӧ��,����
     ��״̬λ���в���.(��Ӧ����Ӧ��ʹack=0 ��)     
     ��������������ack=1; ack=0��ʾ��������Ӧ����𻵡�
********************************************************************/
void  SendByte(uchar c)
{
 uchar BitCnt;
 
 for(BitCnt=0;BitCnt<8;BitCnt++)  /*Ҫ���͵����ݳ���Ϊ8λ*/
    {
     if((c<<BitCnt)&0x80)SDA=1;   /*�жϷ���λ*/
       else  SDA=0;                
     _Nop();
     SCL=1;               /*��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ*/
      _Nop(); 
      _Nop();               /*��֤ʱ�Ӹߵ�ƽ���ڴ���4��s*/
      _Nop();
      _Nop();
      _Nop();         
     SCL=0; 
    }
    
    _Nop();
    _Nop();
    SDA=1;               /*8λ��������ͷ������ߣ�׼������Ӧ��λ*/
    _Nop();
    _Nop();   
    SCL=1;
    _Nop();
    _Nop();
    _Nop();
    if(SDA==1)ack=0;     
       else ack=1;        /*�ж��Ƿ���յ�Ӧ���ź�*/
    SCL=0;
    _Nop();
    _Nop();
}






/*******************************************************************
                 �ֽ����ݴ��ͺ���               
����ԭ��: uchar  RcvByte();
����:  �������մ���������������,���ж����ߴ���(����Ӧ���ź�)��
     ���������Ӧ������  
********************************************************************/	
uchar  RcvByte()
{
  uchar retc;
  uchar BitCnt;
  
  retc=0; 
  SDA=1;             /*��������Ϊ���뷽ʽ*/
  for(BitCnt=0;BitCnt<8;BitCnt++)
      {
        _Nop();           
        SCL=0;       /*��ʱ����Ϊ�ͣ�׼����������λ*/
        _Nop();
        _Nop();         /*ʱ�ӵ͵�ƽ���ڴ���4.7��s*/
        _Nop();
        _Nop();
        _Nop();
        SCL=1;       /*��ʱ����Ϊ��ʹ��������������Ч*/
        _Nop();
        _Nop();
        retc=retc<<1;
        if(SDA==1)retc=retc+1; /*������λ,���յ�����λ����retc�� */
        _Nop();
        _Nop(); 
      }
  SCL=0;    
  _Nop();
  _Nop();
  return(retc);
}




/********************************************************************
                     Ӧ���Ӻ���
ԭ��:  void Ack_I2c(bit a);
 
����:����������Ӧ���ź�,(������Ӧ����Ӧ���ź�)
********************************************************************/
void Ack_I2c(bit a)
{
  
  if(a==0)SDA=0;     /*�ڴ˷���Ӧ����Ӧ���ź� */
        else SDA=1;
  _Nop();
  _Nop();
  _Nop();      
  SCL=1;
    _Nop();
    _Nop();              /*ʱ�ӵ͵�ƽ���ڴ���4��s*/
    _Nop();
    _Nop();
    _Nop();  
 SCL=0;                /*��ʱ���ߣ�ǯסI2C�����Ա��������*/
    _Nop();
    _Nop();    
}









/*******************************************************************
                    �����ӵ�ַ�������Ͷ��ֽ����ݺ���               
����ԭ��: bit  ISendStr(uchar sla,uchar suba,ucahr *s,uchar no);  
����:     ���������ߵ����͵�ַ���ӵ�ַ,���ݣ��������ߵ�ȫ����,������
          ��ַsla���ӵ�ַsuba������������sָ������ݣ�����no���ֽڡ�
           �������1��ʾ�����ɹ��������������
ע�⣺    ʹ��ǰ�����ѽ������ߡ�
********************************************************************/
bit ISendStr(uchar sla,uchar suba,uchar *s,uchar no)
{
   uchar i;

   Start_I2c();               /*��������*/
   SendByte(sla);            /*����������ַ*/
     if(ack==0)return(0);
   SendByte(suba);            /*���������ӵ�ַ*/
     if(ack==0)return(0);

   for(i=0;i<no;i++)
    {   
     SendByte(*s);               /*��������*/
       if(ack==0)return(0);
     s++;
    } 
 Stop_I2c();                 /*��������*/ 
  return(1);
}


/*******************************************************************
                    �����ӵ�ַ������ȡ���ֽ����ݺ���               
����ԭ��: bit  ISendStr(uchar sla,uchar suba,ucahr *s,uchar no);  
����:     ���������ߵ����͵�ַ���ӵ�ַ,�����ݣ��������ߵ�ȫ����,������
          ��ַsla���ӵ�ַsuba�����������ݷ���sָ��Ĵ洢������no���ֽڡ�
           �������1��ʾ�����ɹ��������������
ע�⣺    ʹ��ǰ�����ѽ������ߡ�
********************************************************************/
bit IRcvStr(uchar sla,uchar suba,uchar *s,uchar no)
{
   uchar i;

   Start_I2c();               /*��������*/
   SendByte(sla);            /*����������ַ*/
     if(ack==0)return(0);
   SendByte(suba);            /*���������ӵ�ַ*/
     if(ack==0)return(0);

   Start_I2c();
   SendByte(sla+1);
      if(ack==0)return(0);

   for(i=0;i<no-1;i++)
    {   
     *s=RcvByte();               /*��������*/
      Ack_I2c(0);                /*���;ʹ�λ*/  
     s++;
    } 
   *s=RcvByte();
    Ack_I2c(1);                 /*���ͷ�Ӧλ*/
 Stop_I2c();                    /*��������*/ 
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
          //IRcvStr(SLA,SUBA,MRD,NUMBYTE); //��sla�е�suba��ַ��ȡno���ֽڵ�s��
          delay(10);
          k=0;
		  *MRD = 1;
          if(*MRD!=TABKEY[k])
          {
             while(*MRD!=TABKEY[k]) //��ȡ��ȡ���ַ�λ��TABKEY�е�λ��k
              {
                k++;
               }
          } 
          mybuffer[i]=k; //8���������ʾ����DISPͨ�������鴫������  
          if(i<8){//�޸�ǰ8λ
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

#include "DHT11.h"

void GPIO_OUT_DHT11(void){
	GPIO_InitTypeDef GPIO_OUT;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_OUT.GPIO_Pin	=	GPIO_Pin_8;
	GPIO_OUT.GPIO_Mode 	= 	GPIO_Mode_Out_PP;
	GPIO_OUT.GPIO_Speed = 	GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_OUT);
}

void GPIO_IN_DHT11(void){
	GPIO_InitTypeDef GPIO_IN;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_IN.GPIO_Pin	=	GPIO_Pin_8;
	GPIO_IN.GPIO_Mode 	= 	GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_IN);
}

uint8_t DHT_GetTempHumi(uint8_t *temp, uint8_t *humi){
		uint8_t buffer[5]={0x00,0x00,0x00,0x00,0x00};    // mang de doc du lieu tren chan DATA 
    uint8_t parity;
    
		GPIO_OUT_DHT11();
		DelayUs(60);
	
    __DHT11_OUT = 0;
    DelayMs(20); // it nhat 18ms
    __DHT11_OUT = 1;
	

    __DHT11_OUT = 0;
    DelayUs(60);      // Cho 60us kiem tra muc tren chan DATA
	
		GPIO_IN_DHT11();
		DelayUs(50);
    
		if(__DHT11_IN)   // Neu chan DATA ko duoc keo xuong muc 0    
    return 0 ;      // Tra ve gia tri 0    ==> ko giao tiep duoc voi DHT11
    else            // Chan DATA o muc thap 
			
		
    while(!__DHT11_IN);    //Doi chan DaTa len 1
    DelayUs(80);        // Chan Data o muc cao 80us
		
    if(!__DHT11_IN)        // Kiem tra muc tren chan DATA
    return 0;
    else 
    while(__DHT11_IN);     //Doi chan Data ve 0
    //Bat dau doc du lieu
		uint8_t i,j;		//Index in loop
    for(i=0;i<5;i++)  // nhan 5 byte du lieu
    {
        for(j=0;j<8;j++)     // nhan tung bit
        {    
        while(!__DHT11_IN); //Doi Data len 1
        DelayUs(50);
        if(__DHT11_IN)
            {
            buffer[i]|=(0x01<<(7-j));
            while(__DHT11_IN) ;   //Doi Data xuong 0
            }
        }
    }
    //Tinh toan check sum
    parity=buffer[0]+buffer[1]+buffer[2]+buffer[3];
    //Kiem tra check sum
    if((parity)!=buffer[4])return 0;
    //Lay du lieu
    *temp  =  buffer[2];
    *humi =   buffer[0];
    return 1;
}

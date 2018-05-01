#include "IC_74595.h"

void IC_74595_GPIOInit(void){
   GPIO_InitTypeDef GPIO_Structure;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
   GPIO_Structure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
   GPIO_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOA, &GPIO_Structure);	
}

void GPIO_Pulse(long pin){
  pin = 0;
  pin = 1;
  pin = 0;	
}

void IC_74595_WriteBit(uint8_t bit){
	bit = bit & 0xfe;
	__SER = bit;
}

void IC_74595_WriteByte(uint8_t byte){
   uint8_t i=8;
   //for(i;i>0;i--){
   //   IC_74595_WriteBit(byte<<(i));
   //}
}

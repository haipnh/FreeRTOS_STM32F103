#include "DS18B20.h"

void DS18B20_RCC(void){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
}

void DS18B20_In(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
}
void DS18B20_Out(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
}


uint8_t DS18B20_Check(void){
		DS18B20_Out();
		__DS18B20_OUT = 0;
		DelayUs(500);
		DS18B20_In();
		DelayUs(10);
		uint8_t t=240;
		while(__DS18B20_IN == 1 && t-- > 0){
				DelayUs(2);
		}
		if(t==0){
				
		}
		

}
uint16_t DS18B20_GetTemp(void);

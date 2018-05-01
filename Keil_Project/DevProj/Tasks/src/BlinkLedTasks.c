#include "BlinkLedTasks.h"

void blinkLedC13Init()
{
		 GPIO_InitTypeDef  blinkLed;
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		 blinkLed.GPIO_Pin = GPIO_Pin_13;   
		 blinkLed.GPIO_Mode = GPIO_Mode_Out_PP;
		 blinkLed.GPIO_Speed = GPIO_Speed_50MHz;
		 GPIO_Init(GPIOC, &blinkLed);
}

void blinkLedC15Init()
{
		 GPIO_InitTypeDef  blinkLed;
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		 blinkLed.GPIO_Pin = GPIO_Pin_15;   
		 blinkLed.GPIO_Mode = GPIO_Mode_Out_PP;
		 blinkLed.GPIO_Speed = GPIO_Speed_50MHz;
		 GPIO_Init(GPIOC, &blinkLed);
}

void blinkLedC13_task(){
		while(1){
				GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET);
			  DelayMs(1000);
				GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET);
			  DelayMs(1000);
		}
		vTaskDelete(NULL);
}

void blinkLedC15_task(){
		while(1){
				GPIO_WriteBit(GPIOC,GPIO_Pin_15,Bit_RESET);
			  DelayMs(200);
				GPIO_WriteBit(GPIOC,GPIO_Pin_15,Bit_SET);
			  DelayMs(200);
		}
		vTaskDelete(NULL);
}

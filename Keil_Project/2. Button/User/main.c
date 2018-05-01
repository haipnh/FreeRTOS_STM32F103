#include "stm32f10x.h"	

#include "FreeRTOS.h"
#include "task.h"

uint8_t button=0;		// 0 is unpressed, 1 is pressed

void C13Init(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void C13_task(void *ptr){
		C13Init();
		while(1){
				GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
				vTaskDelay(1000);
				GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
				vTaskDelay(1000);
		}
		vTaskDelete(NULL);
}

void C15Init(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void C15_task(void *ptr){
		C15Init();
		while(1){
				if(button==1){
					GPIO_WriteBit(GPIOC, GPIO_Pin_15, Bit_RESET);
					vTaskDelay(200);
					GPIO_WriteBit(GPIOC, GPIO_Pin_15, Bit_SET);
					vTaskDelay(200);
				}
		}
		vTaskDelete(NULL);
}

void C14Init(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void C14_task(void *ptr){
		C14Init();
		while(1){
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)==0)		//button is pressed
				{
						button = 1;
				}
				else {
						button = 0;
				}
		}
}

int main(){
		SystemInit();
		xTaskCreate(C13_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		xTaskCreate(C15_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		xTaskCreate(C14_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		vTaskStartScheduler();
		return 0;

}

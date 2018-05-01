#include "stm32f10x.h"	

#include "FreeRTOS.h"
#include "task.h"

#include "TIMER_DELAY.h"

void C13Init(void);
void C13_task(void *ptr);

void C15Init(void);
void C15_task(void *ptr);

int main(){
		SystemInit();
		initUsTimer();
		xTaskCreate(C13_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		xTaskCreate(C15_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		vTaskStartScheduler();
		return 0;
}

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
				//vTaskDelay(1000);
				DelayMs(1000);
				GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
				//vTaskDelay(1000);
				DelayMs(1000);
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
				GPIO_WriteBit(GPIOC, GPIO_Pin_15, Bit_RESET);
				//vTaskDelay(200);
				DelayMs(200);
				GPIO_WriteBit(GPIOC, GPIO_Pin_15, Bit_SET);
				//vTaskDelay(200);
				DelayMs(200);
		}
		vTaskDelete(NULL);
}

#include "stm32f10x.h"	

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

xSemaphoreHandle	xSemaphore=NULL;

/* PROTOTYPES */
//LED TASKS
void C13Init(void);
void C13_task(void *ptr);

//BUTTON TASKS
void C14Init(void);
void C14_task(void *ptr);

/* MAIN */
int main(){
		SystemInit();
		xSemaphore = xSemaphoreCreateCounting(1,0);
		if(xSemaphore == NULL)
		{
			//error handler
		}
		xTaskCreate(C13_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		xTaskCreate(C14_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		vTaskStartScheduler();
		return 0;

}

/* DEFINITIONS */
 
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
		xSemaphoreTake( xSemaphore, ( portTickType ) portMAX_DELAY );//Lay quyen vao mien gang.
		while(1){
				GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
				vTaskDelay(500);
				GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
				vTaskDelay(500);
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
				if( GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14) == 0){
					xSemaphoreGive(xSemaphore);			
					vTaskDelay(1);
				}
		}
}

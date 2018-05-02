#include "stm32f10x.h"	

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

xSemaphoreHandle	xSemaphoreC13=NULL;

/* PROTOTYPES */

void C13Init(void);
void C13_taskA(void *ptr);
void C13_taskB(void *ptr);

/* MAIN */

int main(){
		SystemInit();
		vSemaphoreCreateBinary(xSemaphoreC13);
		if(xSemaphoreC13 == NULL)
		{
			//error handler
		}
		xTaskCreate(C13_taskA,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		xTaskCreate(C13_taskB,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
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

void C13_taskA(void *ptr){
		C13Init();
		while(1){
				// DOWN
				xSemaphoreTake( xSemaphoreC13, ( portTickType ) portMAX_DELAY );
				// CRITICAL-SECTION
				GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
				vTaskDelay(2000);
				// UP
				xSemaphoreGive(xSemaphoreC13);
				// NON CRITICAL-SECTION
				vTaskDelay(1);
		}
		vTaskDelete(NULL);
}

void C13_taskB(void *ptr){
		C13Init();
		while(1){
				// DOWN
				xSemaphoreTake( xSemaphoreC13, ( portTickType ) portMAX_DELAY );
				// CRITICAL-SECTION
				GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
				vTaskDelay(500);
				// UP
				xSemaphoreGive(xSemaphoreC13);
				// NON CRITICAL-SECTION
				vTaskDelay(1);
		}
		vTaskDelete(NULL);
}

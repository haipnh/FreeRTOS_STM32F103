#include "stm32f10x.h"	

#include "FreeRTOS.h"
#include "task.h"

#include "LCD_20x4.h"

void C13Init(void);
void C13_task(void *ptr);

void C15Init(void);
void C15_task(void *ptr);

void A0Init(void);
void ADC1Init(void);
void A0_task(void *ptr);

void LCD_task(void *ptr);

int main(){
		SystemInit();
		initUsTimer();
		DelayMs(5);					//Wait for LCD warming up			
		LCD_Init4BitMode();
		DelayMs(5);					//Wait for LCD initializing
		xTaskCreate(C13_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		xTaskCreate(C15_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		xTaskCreate(A0_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		xTaskCreate(LCD_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
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

void A0Init(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1|RCC_APB2Periph_AFIO,ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void ADC1Init(void){
		ADC_InitTypeDef ADC_InitStructure;
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;						// ENABLE : If you use more than 2 ADC channels 
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;			// DISABLE : ADC converts just only one time then shutdown.
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		ADC_Init(ADC1,&ADC_InitStructure);		
		ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_239Cycles5);		
		ADC_Cmd(ADC1,ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetResetCalibrationStatus(ADC1));
		ADC_StartCalibration(ADC1);
		while(ADC_GetCalibrationStatus(ADC1));
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

uint16_t adcVal;
void A0_task(void *ptr){
		A0Init();
		ADC1Init();
		while(1){
				if(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==1){
						ADC_ClearFlag(ADC1,ADC_FLAG_EOC);
						adcVal=ADC_GetConversionValue(ADC1);
						vTaskDelay(5);
				}
		}
		vTaskDelete(NULL);
}

void LCD_task(void *ptr){
		
		LCD_GotoXY(0,1);
		LCD_PutS((uint8_t*)"ADC val : ");
		while(1){
				LCD_GotoXY(0,2);
				LCD_PutC(adcVal/1000+0x30);
				LCD_PutC(adcVal/100%10+0x30);
				LCD_PutC(adcVal/10%10+0x30);
				LCD_PutC(adcVal%10+0x30);
				vTaskDelay(500);
		}
		vTaskDelete(NULL);
}

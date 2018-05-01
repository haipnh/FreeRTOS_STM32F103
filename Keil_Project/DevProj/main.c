#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"

#include "stm32f10x_adc.h"

#include "LCD_20x4.h"

#include "BlinkLedTasks.h"
#include "DHT11.h"

#include <stdio.h>

void LM35_Configure_AFIO(void){
		GPIO_InitTypeDef ADC_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_ADC1|RCC_APB2Periph_AFIO,ENABLE);
		ADC_InitStructure.GPIO_Pin = GPIO_Pin_0;
		ADC_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOB,&ADC_InitStructure);
}

void LM35_Configure_ADC(void){
		/*INIT ADC*/
		ADC_InitTypeDef ADC_InitStructure;
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
		// SINGLE CONVERSION
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		ADC_Init(ADC1,&ADC_InitStructure);
		
		ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_239Cycles5);
		
		ADC_Cmd(ADC1,ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetResetCalibrationStatus(ADC1));
		ADC_StartCalibration(ADC1);
		while(ADC_GetCalibrationStatus(ADC1));
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);		
}

uint8_t lm35;

void LM35_task(void){
		while(1){
				if(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==1){
						ADC_ClearFlag(ADC1,ADC_FLAG_EOC);
						lm35=ADC_GetConversionValue(ADC1)*0.0806;		// 3.3/4095/10mA = 0.0806
				}
				vTaskDelay(100);
		}
		vTaskDelete(NULL);
}


uint8_t h=0,m=0,s=0;
void Clock_task(void){
		while(1){				
				s++;
				if(s==60){
						s=0;
						m++;
						if(m==60){
								m=0;
								h++;
								if(h==24){
										h=0;
								}
						}
				}
				vTaskDelay(1000);
		}		
		vTaskDelete(NULL);
}

uint8_t temp, humi, status;
void DHT11_task(void){
		DelayMs(2000);
		while(1){
				status=DHT_GetTempHumi(&temp,&humi);
				vTaskDelay(1000);
		}		
		vTaskDelete(NULL);
}


void LCD_task(void){
			LCD_GotoXY(10,0);
			LCD_PutS("Status : ");
			while(1){
				LCD_GotoXY(0,0);
				LCD_PutC(h/10+0x30);
				LCD_PutC(h%10+0x30);
				LCD_PutC(':');
				LCD_PutC(m/10+0x30);
				LCD_PutC(m%10+0x30);
				LCD_PutC(':');
				LCD_PutC(s/10+0x30);
				LCD_PutC(s%10+0x30);				
				LCD_GotoXY(19,0);
				LCD_PutC(status+0x30);
				LCD_GotoXY(0,1);
				LCD_PutS("DHT11: ");
				LCD_PutC(temp/10+0x30);
				LCD_PutC(temp%10+0x30);
				LCD_GotoXY(0,2);
				LCD_PutS("LM35 : ");
				LCD_PutC(lm35/10+0x30);
				LCD_PutC(lm35%10+0x30);
				//sprintf(LCD_PutS, "%2d",temp);
				vTaskDelay(1000);
			}
			vTaskDelete(NULL);
}

int main(void){
		SystemInit();
	  initUsTimer();
		blinkLedC13Init();
		blinkLedC15Init();
		LM35_Configure_AFIO();
		LM35_Configure_ADC();
		DelayMs(15); //Wait for LCD warm-up
		LCD_Init4BitMode();
		DelayMs(5);
		LCD_GotoXY(0,0);
		//xTaskCreate(blinkLedC13_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		//xTaskCreate(blinkLedC15_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		xTaskCreate(Clock_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		xTaskCreate(DHT11_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		xTaskCreate(LM35_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		xTaskCreate(LCD_task,NULL,configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
		vTaskStartScheduler();
		return 0;
}
 

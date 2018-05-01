#include "stm32f10x.h"	

#include "TIMER_DELAY.h"

void A0Init(void);
void ADC1Init(void);

void A0Init(void);
void ADC1Init(void);



uint16_t adcVal;
int main(){
		SystemInit();
		initUsTimer();
		A0Init();
		ADC1Init();
		
		while(1){
				if(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==1){
						ADC_ClearFlag(ADC1,ADC_FLAG_EOC);
						adcVal=ADC_GetConversionValue(ADC1);
				}
				DelayMs(5);
		}
		return 0;
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
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
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


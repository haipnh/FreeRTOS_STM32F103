#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f10x.h"
#include "TIMER_DELAY.h"
#include "DEF_STM32.h"

#define __DHT11_IN	PORTA_12	
#define __DHT11_OUT	PINA_12

void GPIO_OUT_DHT11(void);
void GPIO_IN_DHT11(void);
uint8_t DHT_GetTempHumi (uint8_t *temp,uint8_t *humi);

#endif

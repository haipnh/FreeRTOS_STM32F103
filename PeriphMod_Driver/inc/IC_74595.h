#ifndef IC_74595_H
#define IC_74595_H
#endif

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "DEF_STM32.h"
#include "TIMER_DELAY.h"

#ifdef __cplusplus
extern "C" {
#endif
	
#define __SER 		PORTA_9
#define __RCLK		PORTA_10
#define __SRCLK  	PORTA_11
#define __STIME	1000				// in milisecond
	
	
void IC_74595_GPIOInit(void);
void GPIO_Pulse(long pin);
void IC_74595_WriteBit(uint8_t bit);
void IC_74595_WriteByte(uint8_t byte);
	
#ifdef __cplusplus
}
#endif

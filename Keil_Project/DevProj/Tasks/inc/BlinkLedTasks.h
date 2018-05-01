#ifndef BLINKLEDTASKS_H
#define BLINKLEDTASKS_H

#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"
#include "TIMER_DELAY.h"

void blinkLedC13Init(void);
void blinkLedC15Init(void);

void blinkLedC13_task(void);
void blinkLedC15_task(void);

#endif

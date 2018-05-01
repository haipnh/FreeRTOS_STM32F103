#ifndef GLCD_5110_H
#define GLCD_5110_H

#ifdef __cplusplus
extern "C"{
#endif

// Pins connect
#define __GLCD_5110_RST        // RESET
#define __GLCD_5110_CE         // CHIP ENABLE
#define __GLCD_5110_DC         // DATA CONTROL
#define __GLCD_5110_DIN        // SPI DATA
#define __GLCD_5110_CLK        // SPI CLOCK
   
// Variables
   
// Prototype function
void GLCD_5110_Init(void);
void GLCD_5110_ReadMode(void);   
void GLCD_5110_FunctionSet();
   
   
#ifdef FREERTOS_H 
// FreeRTOS task
#endif

   
#ifdef __cplusplus
}
#endif
#endif

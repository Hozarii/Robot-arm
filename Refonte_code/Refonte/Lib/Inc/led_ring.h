/*
 * Led_ring.h
 *
 *  Created on: Feb 14, 2024
 *      Author: smore
 */

#include "main.h"
#ifndef INC_LED_RING_H_
#define INC_LED_RING_H_


#define MAX_LED 16
#define PI 3.14159265

void Set_LED (int LEDnum, int Red, int Green, int Blue);
void Set_Brightness (int brightness);
void WS2812_Send (void);


#endif /* INC_LED_RING_H_ */

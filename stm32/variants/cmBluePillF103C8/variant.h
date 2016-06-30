/****************************************************************************
 * Copyright (c) 2016 by Vassilis Serasidis <info@serasidis.gr>
 * 
 * Variant definition library for Arduino STM32 + HAL + CubeMX (HALMX).
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 ****************************************************************************/

#ifndef _VARIANT_BLUE_PILL_
#define _VARIANT_BLUE_PILL_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "Arduino.h"
#ifdef __cplusplus
//#include "UARTClass.h"
//#include "USARTClass.h"
#endif

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus
  
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
  
#define GPIO_PINS      35


/* This mapping is for from Blue pill Schematic */
enum {
  PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13,	PA14, PA15,
	PB0, PB1, PB2, PB3, PB4, PB5,	PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13, PB14, PB15,
  PC13, PC14, PC15
};

typedef struct _Pin2PortMapArray
{
  	uint32_t  GPIOx_Port;
  	uint32_t 	Pin_abstraction;
    rcc_periph_clken  periph_clock;
} Pin2PortMapArray ;

//extern const Pin2PortMapArray g_Pin2PortMapArray[] ;
#ifdef __cplusplus
}
#endif


#endif

/****************************************************************************
 * Copyright (c) 2016 by Vassilis Serasidis <info@serasidis.gr>
 *
 * Home: http://www.serasidis.gr
 *
 * Variant definition library for Arduino IDE + libopencm3.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 3
 * or the GNU Lesser General Public License version 3, both as
 * published by the Free Software Foundation.
 * ( https://www.gnu.org/licenses/gpl-3.0.html )
 *
 * Last edit: 07 Jul 2016
 *
 ****************************************************************************/

 /**
  * Edited by Evangelos Arkalis.
  */

#ifndef _VARIANT_BLUEPILL_F103_
#define _VARIANT_BLUEPILL_F103_

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC   8000000

/** Master clock frequency */
#define VARIANT_MCK       72000000

#define SYSTICK_RELOAD_VAL ((VARIANT_MCK / 8)/1000) //In this case the value is ((72000000 MHz / 8) / 1000) = 9000 ticks
/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "WVariant.h"
#ifdef __cplusplus
#include "Uart.h"
#endif

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>



#define GPIO_PINS      35

#define digitalPinToPort(P)        ( g_PinDescription[P].Port )
#define digitalPinToBitMask(P)     ( g_PinDescription[P].Pin )
//#define portOutputRegister(port)   ( &(GPIO_ODR(port)) )
//#define portInputRegister(port)    ( &(GPIO_IDR(port) )


enum {
  PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13,	PA14, PA15,
  PB0, PB1, PB2, PB3, PB4, PB5,	PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13, PB14, PB15,
  PC13, PC14, PC15
};

typedef struct spi_port{
  uint16_t  cs_pin;
  uint16_t  mosi_pin;
  uint16_t  miso_pin;
  uint16_t  sck_pin;
}spi_port;

extern const spi_port SPI_PinDescription[];

    // Generic signals namings
#define    LED1                 PC13
#define    LED2                 PC13

/*----------------------------------------------------------------------------
 *        Define Uarts Enables and Pins
 *----------------------------------------------------------------------------*/
#define USE_UART1
#define UART1_GPIO_AF           0
#define UART1_GPIO_PORT_RX      GPIOA
#define UART1_GPIO_RX           GPIO10
#define UART1_GPIO_PORT_TX      GPIOA
#define UART1_GPIO_TX           GPIO9

#define USE_UART2
#define UART2_GPIO_AF           0
#define UART2_GPIO_PORT_RX      GPIOA
#define UART2_GPIO_RX           GPIO3
#define UART2_GPIO_PORT_TX      GPIOA
#define UART2_GPIO_TX           GPIO2

#define SPI_INTERFACES_COUNT  2   //The STM32F103C8T6 has 2 SPI ports.
#define SPI_MIN_CLOCK_DIVIDER 4   //Maximum SPI clock speed (72MHz / 4 = 18 MHz)

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus

#ifdef USE_UART1
extern Uart Serial1;
#endif // USE_UART1

#ifdef USE_UART2
extern Uart Serial2;
#endif // USE_UART2

#define Serial Serial1

#endif

#endif

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
#include "Arduino.h"
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
//#define portOutputRegister(port)   ( &(port->PIO_ODSR) )
//#define portInputRegister(port)    ( &(port->PIO_PDSR) )

/* This mapping is for from Blue pill Schematic */
enum {
    PA0  = 0x00,
    PA1  = 0x01,
    PA2  = 0x02,
    PA3  = 0x03,
    PA4  = 0x04,
    PA5  = 0x05,
    PA6  = 0x06,
    PA7  = 0x07,
    PA8  = 0x08,
    PA9  = 0x09,
    PA10 = 0x0A,
    PA11 = 0x0B,
    PA12 = 0x0C,
    PA13 = 0x0D,
    PA14 = 0x0E,
    PA15 = 0x0F,

    PB0  = 0x10,
    PB1  = 0x11,
    PB2  = 0x12,
    PB3  = 0x13,
    PB4  = 0x14,
    PB5  = 0x15,
    PB6  = 0x16,
    PB7  = 0x17,
    PB8  = 0x18,
    PB9  = 0x19,
    PB10 = 0x1A,
    PB12 = 0x1C,
    PB13 = 0x1D,
    PB14 = 0x1E,
    PB15 = 0x1F,

    PC0  = 0x20,
    PC1  = 0x21,
    PC2  = 0x22,
    PC3  = 0x23,
    PC4  = 0x24,
    PC5  = 0x25,
    PC6  = 0x26,
    PC7  = 0x27,
    PC8  = 0x28,
    PC9  = 0x29,
    PC10 = 0x2A,
    PC11 = 0x2B,
    PC12 = 0x2C,
    PC13 = 0x2D,
    PC14 = 0x2E,
    PC15 = 0x2F,

    PD2  = 0x32,

    PH0  = 0x70,
    PH1  = 0x71
};

typedef struct _PinDescription
{
   uint32_t  Port;
   uint16_t  Pin;
} PinDescription ;

typedef struct spi_port{
  uint16_t  cs_pin;
  uint16_t  mosi_pin;
  uint16_t  miso_pin;
  uint16_t  sck_pin;
}spi_port;

extern const PinDescription g_PinDescription[];
extern const spi_port SPI_PinDescription[];

#define PIN_SERIAL1_RX        PA10
#define PIN_SERIAL1_TX        PA9

#define PIN_SERIAL2_RX        PA3
#define PIN_SERIAL2_TX        PA2

#define PIN_SERIAL3_RX        PB11
#define PIN_SERIAL3_TX        PB10

#define SPI_INTERFACES_COUNT  2   //The STM32F103C8T6 has 2 SPI ports.
#define SPI_MIN_CLOCK_DIVIDER 4   //Maximum SPI clock speed (72MHz / 4 = 18 MHz)

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern Uart Serial1;
#define Serial Serial1
extern Uart Serial2;
extern Uart Serial3;
#endif

#endif

/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Last edit: 07 Jul 2016

*/

 /**
  * Modified for using this library with libopencm3 and STM32 MCUs.
  * 06 Jul 2016 - Modified by Vassilis Serasidis <avrsite@yahoo.gr>
  * Home: http://www.serasidis.gr
  */

 /**
  * Edited by Evangelos Arkalis.
  */

#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const PinDescription g_PinDescription[]=
{

    {GPIOA, GPIO0},     /*  */
    {GPIOA, GPIO1},     /*  */
    {GPIOA, GPIO2},     /*  */
    {GPIOA, GPIO3},     /*  */
    {GPIOA, GPIO4},     /*  */
    {GPIOA, GPIO5},     /*  */
    {GPIOA, GPIO6},     /*  */
    {GPIOA, GPIO7},     /*  */
    {GPIOA, GPIO8},     /*  */
    {GPIOA, GPIO9},     /*  */
    {GPIOA, GPIO10},    /*  */
    {GPIOA, GPIO11},    /*  */
    {GPIOA, GPIO12},    /*  */
    {GPIOA, GPIO13},    /*  */
    {GPIOA, GPIO14},    /*  */
    {GPIOA, GPIO15},    /*  */

    {GPIOB, GPIO0},     /*  */
    {GPIOB, GPIO1},     /*  */
    {GPIOB, GPIO2},     /*  */
    {GPIOB, GPIO3},     /*  */
    {GPIOB, GPIO4},     /*  */
    {GPIOB, GPIO5},     /*  */
    {GPIOB, GPIO6},     /*  */
    {GPIOB, GPIO7},     /*  */
    {GPIOB, GPIO8},     /*  */
    {GPIOB, GPIO9},     /*  */
    {GPIOB, GPIO10},    /*  */
//    {GPIOB, GPIO11},    /*  */
    {GPIOB, GPIO12},    /*  */
    {GPIOB, GPIO13},    /*  */
    {GPIOB, GPIO14},    /*  */
    {GPIOB, GPIO15},    /*  */

    {GPIOC, GPIO0},     /*  */
    {GPIOC, GPIO1},     /*  */
    {GPIOC, GPIO2},     /*  */
    {GPIOC, GPIO3},     /*  */
    {GPIOC, GPIO4},     /*  */
    {GPIOC, GPIO5},     /*  */
    {GPIOC, GPIO6},     /*  */
    {GPIOC, GPIO7},     /*  */
    {GPIOC, GPIO8},     /*  */
    {GPIOC, GPIO9},     /*  */
    {GPIOC, GPIO10},    /*  */
    {GPIOC, GPIO11},    /*  */
    {GPIOC, GPIO12},    /*  */
    {GPIOC, GPIO13},    /*  */
    {GPIOC, GPIO14},    /*  */
    {GPIOC, GPIO15},    /*  */

    {GPIOD, GPIO2},     /*  */

    {GPIOH, GPIO0},     /*  */
    {GPIOH, GPIO1},     /*  */
};

//extern const spi_port SPI_PinDescription[]{
//   { PA4 , PA5 , PA6 , PA7  } // SPI1 - NSS pin, SCK pin, MISO pin, MOSI pin
//  ,{ PB12, PB13, PB14, PB15 } // SPI2 - NSS pin, SCK pin, MISO pin, MOSI pin
//  ,{ PA15, PB3 , PB4 , PB5  } // SPI3 - NSS pin, SCK pin, MISO pin, MOSI pin */
//};

#ifdef __cplusplus
}
#endif

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void serialEvent() __attribute__((weak));
void serialEvent() { }

Uart Serial1(USART1);
Uart Serial2(USART2);
//Uart Serial3(USART3);

// ----------------------------------------------------------------------------

// Custom board init

void init( void )
{
  // Nucleo has 8MHz HSE, pll to 84MHz
  rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_84MHZ]);
  // Connect All ports to CLK
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB);
  rcc_periph_clock_enable(RCC_GPIOC);
  rcc_periph_clock_enable(RCC_GPIOD);

  systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
  systick_set_reload(SYSTICK_RELOAD_VAL - 1);             /// SysTick Reload for 1ms tick
  systick_counter_enable();
  systick_interrupt_enable();


}




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
/// PORT   PIN    AD TM  TC
    {GPIOA, GPIO0,  0,  NA, NA},     /*  */
    {GPIOA, GPIO1,  1,  NA, NA},     /*  */
    {GPIOA, GPIO2,  2,  NA, NA},     /*  */
    {GPIOA, GPIO3,  3,  NA, NA},     /*  */
    {GPIOA, GPIO4,  4,  NA, NA},     /*  */
    {GPIOA, GPIO5,  5,  NA, NA},     /*  */
    {GPIOA, GPIO6,  6,  NA, NA},     /*  */
    {GPIOA, GPIO7,  7,  NA, NA},     /*  */
    {GPIOA, GPIO8,  NA, NA, NA},     /*  */
    {GPIOA, GPIO9,  NA, NA, NA},     /*  */
    {GPIOA, GPIO10, NA, NA, NA},    /*  */
    {GPIOA, GPIO11, NA, NA, NA},    /*  */
    {GPIOA, GPIO12, NA, NA, NA},    /*  */
    {GPIOA, GPIO13, NA, NA, NA},    /*  */
    {GPIOA, GPIO14, NA, NA, NA},    /*  */
    {GPIOA, GPIO15, NA, NA, NA},    /*  */

    {GPIOB, GPIO0,  8,  NA, NA},     /*  */
    {GPIOB, GPIO1,  9,  NA, NA},     /*  */
    {GPIOB, GPIO2,  NA, NA, NA},     /*  */
    {GPIOB, GPIO3,  NA, NA, NA},     /*  */
    {GPIOB, GPIO4,  NA, NA, NA},     /*  */
    {GPIOB, GPIO5,  NA, NA, NA},     /*  */
    {GPIOB, GPIO6,  NA, NA, NA},     /*  */
    {GPIOB, GPIO7,  NA, NA, NA},     /*  */
    {GPIOB, GPIO8,  NA, NA, NA},     /*  */
    {GPIOB, GPIO9,  NA, NA, NA},     /*  */
    {GPIOB, GPIO10, NA, NA, NA},    /*  */
//  {GPIOB, GPIO11, NA, NA, NA},    /*  */
    {GPIOB, GPIO12, NA, NA, NA},    /*  */
    {GPIOB, GPIO13, NA, NA, NA},    /*  */
    {GPIOB, GPIO14, NA, NA, NA},    /*  */
    {GPIOB, GPIO15, NA, NA, NA},    /*  */

    {GPIOC, GPIO0,  10, NA, NA},     /*  */
    {GPIOC, GPIO1,  11, NA, NA},     /*  */
    {GPIOC, GPIO2,  12, NA, NA},     /*  */
    {GPIOC, GPIO3,  NA, NA, NA},     /*  */
    {GPIOC, GPIO4,  NA, NA, NA},     /*  */
    {GPIOC, GPIO5,  NA, NA, NA},     /*  */
    {GPIOC, GPIO6,  NA, NA, NA},     /*  */
    {GPIOC, GPIO7,  NA, NA, NA},     /*  */
    {GPIOC, GPIO8,  NA, NA, NA},     /*  */
    {GPIOC, GPIO9,  NA, NA, NA},     /*  */
    {GPIOC, GPIO10, NA, NA, NA},    /*  */
    {GPIOC, GPIO11, NA, NA, NA},    /*  */
    {GPIOC, GPIO12, NA, NA, NA},    /*  */
    {GPIOC, GPIO13, NA, NA, NA},    /*  */
    {GPIOC, GPIO14, NA, NA, NA},    /*  */
    {GPIOC, GPIO15, NA, NA, NA},    /*  */

    {GPIOD, GPIO2,  NA, NA, NA},     /*  */

    {GPIOH, GPIO0,  NA, NA, NA},     /*  */
    {GPIOH, GPIO1,  NA, NA, NA},     /*  */
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

#ifdef USE_UART1
Uart Serial1(USART1);
#endif // USE_UART1

#ifdef USE_UART2
Uart Serial2(USART2);
#endif // USE_UART2

//Uart Serial3(USART3);

/*----------------------------------------------------------------------------
 *        Custom Board Init ( C API )
 *----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
void init( void )
{
    // Nucleo has 8MHz HSE, pll to 84MHz
    rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_84MHZ]);

    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    systick_set_reload(SYSTICK_RELOAD_VAL - 1);             /// SysTick Reload for 1ms tick
    systick_interrupt_enable();
    systick_counter_enable();
}
#ifdef __cplusplus
}
#endif


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

    {GPIOA, GPIO0,  PIN_ATTR_NONE},     /*  */
    {GPIOA, GPIO1,  PIN_ATTR_NONE},     /*  */
    {GPIOA, GPIO2,  PIN_ATTR_NONE},     /*  */
    {GPIOA, GPIO3,  PIN_ATTR_NONE},     /*  */
    {GPIOA, GPIO4,  PIN_ATTR_NONE},     /*  */
    {GPIOA, GPIO5,  PIN_ATTR_NONE},     /*  */
    {GPIOA, GPIO6,  PIN_ATTR_NONE},     /*  */
    {GPIOA, GPIO7,  PIN_ATTR_NONE},     /*  */
    {GPIOA, GPIO8,  PIN_ATTR_NONE},     /*  */
    {GPIOA, GPIO9,  PIN_ATTR_NONE},     /*  */
    {GPIOA, GPIO10, PIN_ATTR_NONE},    /*  */
    {GPIOA, GPIO11, PIN_ATTR_NONE},    /*  */
    {GPIOA, GPIO12, PIN_ATTR_NONE},    /*  */
    {GPIOA, GPIO13, PIN_ATTR_NONE},    /*  */
    {GPIOA, GPIO14, PIN_ATTR_NONE},    /*  */
    {GPIOA, GPIO15, PIN_ATTR_NONE},    /*  */

    {GPIOB, GPIO0,  PIN_ATTR_NONE},     /*  */
    {GPIOB, GPIO1,  PIN_ATTR_NONE},     /*  */
    {GPIOB, GPIO2,  PIN_ATTR_NONE},     /*  */
    {GPIOB, GPIO3,  PIN_ATTR_NONE},     /*  */
    {GPIOB, GPIO4,  PIN_ATTR_NONE},     /*  */
    {GPIOB, GPIO5,  PIN_ATTR_NONE},     /*  */
    {GPIOB, GPIO6,  PIN_ATTR_NONE},     /*  */
    {GPIOB, GPIO7,  PIN_ATTR_NONE},     /*  */
    {GPIOB, GPIO8,  PIN_ATTR_NONE},     /*  */
    {GPIOB, GPIO9,  PIN_ATTR_NONE},     /*  */
    {GPIOB, GPIO10, PIN_ATTR_NONE},    /*  */
//  {GPIOB, GPIO11, PIN_ATTR_NONE},    /*  */
    {GPIOB, GPIO12, PIN_ATTR_NONE},    /*  */
    {GPIOB, GPIO13, PIN_ATTR_NONE},    /*  */
    {GPIOB, GPIO14, PIN_ATTR_NONE},    /*  */
    {GPIOB, GPIO15, PIN_ATTR_NONE},    /*  */

    {GPIOC, GPIO0,  PIN_ATTR_NONE},     /*  */
    {GPIOC, GPIO1,  PIN_ATTR_NONE},     /*  */
    {GPIOC, GPIO2,  PIN_ATTR_NONE},     /*  */
    {GPIOC, GPIO3,  PIN_ATTR_NONE},     /*  */
    {GPIOC, GPIO4,  PIN_ATTR_NONE},     /*  */
    {GPIOC, GPIO5,  PIN_ATTR_NONE},     /*  */
    {GPIOC, GPIO6,  PIN_ATTR_NONE},     /*  */
    {GPIOC, GPIO7,  PIN_ATTR_NONE},     /*  */
    {GPIOC, GPIO8,  PIN_ATTR_NONE},     /*  */
    {GPIOC, GPIO9,  PIN_ATTR_NONE},     /*  */
    {GPIOC, GPIO10, PIN_ATTR_NONE},    /*  */
    {GPIOC, GPIO11, PIN_ATTR_NONE},    /*  */
    {GPIOC, GPIO12, PIN_ATTR_NONE},    /*  */
    {GPIOC, GPIO13, PIN_ATTR_NONE},    /*  */
    {GPIOC, GPIO14, PIN_ATTR_NONE},    /*  */
    {GPIOC, GPIO15, PIN_ATTR_NONE},    /*  */

    {GPIOD, GPIO2,  PIN_ATTR_NONE},     /*  */

    {GPIOH, GPIO0,  PIN_ATTR_NONE},     /*  */
    {GPIOH, GPIO1,  PIN_ATTR_NONE},     /*  */
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


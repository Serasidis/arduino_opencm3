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
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  NOADC2110-1301  USA

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
    {GPIOA, GPIO0,  0,  2,  1},   /*-WKUP  */
    {GPIOA, GPIO1,  1,  2,  2},   /*  */
    {GPIOA, GPIO2,  2,  2,  3},   /*  */
    {GPIOA, GPIO3,  3,  2,  4},   /*  */
    {GPIOA, GPIO4,  4,  NA, NA},  /*SPI1_NSS  SPI1_NSS (opt)*/
    {GPIOA, GPIO5,  5,  NA, NA},  /*SPI1_SCK  */
    {GPIOA, GPIO6,  6,  NA, NA},  /*SPI1_MISO  */
    {GPIOA, GPIO7,  7,  NA, NA},  /*SPI1_MOSI  */
    {GPIOA, GPIO8,  NA, 1,  1},   /*  */
    {GPIOA, GPIO9,  NA, 1,  2},   /*USART1_TX  */
    {GPIOA, GPIO10, NA, 1,  3},   /*USART1_RX  */
    {GPIOA, GPIO11, NA, 1,  4},   /* USBDM (-)  */
    {GPIOA, GPIO12, NA, NA, NA},  /* USBDP (+)  */
    {GPIOA, GPIO13, NA, NA, NA},  /*SYS_JTMS-SWDIO  */
    {GPIOA, GPIO14, NA, NA, NA},  /*SYS_JTCK-SWCLK  */
    {GPIOA, GPIO15, NA, NA, NA},  /*  */

    {GPIOB, GPIO0,  8,  3,  3},   /*  */
    {GPIOB, GPIO1,  9,  3,  4},   /*  */
    {GPIOB, GPIO2,  NA, NA, NA},  /* BOOT1 */
    {GPIOB, GPIO3,  NA, NA, NA},  /*  */
    {GPIOB, GPIO4,  NA, NA, NA},  /*  */
    {GPIOB, GPIO5,  NA, NA, NA},  /*  */
    {GPIOB, GPIO6,  NA, 4,  1},   /*I2C1_SCL  */
    {GPIOB, GPIO7,  NA, 4,  2},   /*I2C1_SDA  */
    {GPIOB, GPIO8,  NA, 4,  3},   /*CAN_RX  */
    {GPIOB, GPIO9,  NA, 4,  4},   /*CAN_TX  */
    {GPIOB, GPIO10, NA, NA, NA},  /* USART3_TX  */
    {GPIOB, GPIO11, NA, NA, NA},  /* USART3_RX  */
    {GPIOB, GPIO12, NA, NA, NA},  /* SPI2_NSS  */
    {GPIOB, GPIO13, NA, NA, NA},  /* SPI2_SCK */
    {GPIOB, GPIO14, NA, NA, NA},  /* SPI2_MISO */
    {GPIOB, GPIO15, NA, NA, NA},  /* SPI2_MOSI */

    {GPIOC, GPIO13, NA, NA, NA},  /*-TAMPER-RTC  Output  GPIO_Output  */
    {GPIOC, GPIO14, NA, NA, NA},  /*-OSC32_IN   */
    {GPIOC, GPIO15, NA, NA, NA}   /*-OSC32_OUT  */
};

extern const spi_port SPI_PinDescription[]
{
    { PA4,  PA5,  PA6,  PA7  },    // SPI1 - NSS pin, SCK pin, MISO pin, MOSI pin
    { PB12, PB13, PB14, PB15 } // SPI2 - NSS pin, SCK pin, MISO pin, MOSI pin
    /* The SPI3 is not  used in this variant
      ,{ PA15, PB3 , PB4 , PB5  } // SPI3 - NSS pin, SCK pin, MISO pin, MOSI pin */
};

extern const i2c_port I2C_PinDescription[]
{
    { PB6,  PB7  }, // I2C_1 - SCL pin, SDA pin
    { PB10, PB11 }  // I2C_2 - SCL pin, SDA pin
};

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
    // BluePill has 8MHz HSE
    rcc_clock_setup_in_hse_8mhz_out_72mhz();    /// Clock 72Hz from HSE 8MHz

    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);    /// SysTick at 72Mhz/8
    systick_set_reload(SYSTICK_RELOAD_VAL - 1);             /// SysTick Reload for 1ms tick
    systick_interrupt_enable();
    systick_counter_enable();
}
#ifdef __cplusplus
}
#endif



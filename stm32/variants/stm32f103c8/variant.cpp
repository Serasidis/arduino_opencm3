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

    {GPIOA, GPIO0},  /*-WKUP  */
    {GPIOA, GPIO1},  /*  */
    {GPIOA, GPIO2},  /*  */
    {GPIOA, GPIO3},  /*  */
    {GPIOA, GPIO4},  /*SPI1_NSS  SPI1_NSS (opt)*/
    {GPIOA, GPIO5},  /*SPI1_SCK  */
    {GPIOA, GPIO6},  /*SPI1_MISO  */
    {GPIOA, GPIO7},  /*SPI1_MOSI  */
    {GPIOA, GPIO8},  /*  */
    {GPIOA, GPIO9},  /*USART1_TX  */
    {GPIOA, GPIO10},  /*USART1_RX  */
    {GPIOA, GPIO11},  /* USBDM (-)  */
    {GPIOA, GPIO12},  /* USBDP (+)  */
    {GPIOA, GPIO13},  /*SYS_JTMS-SWDIO  */
    {GPIOA, GPIO14},  /*SYS_JTCK-SWCLK  */
    {GPIOA, GPIO15},  /*  */

    {GPIOB, GPIO0},  /*  */
    {GPIOB, GPIO1},  /*Output  GPIO_Output  Blue_LED*/
    {GPIOB, GPIO2},  /* BOOT1 */
    {GPIOB, GPIO3},  /*  */
    {GPIOB, GPIO4},  /*  */
    {GPIOB, GPIO5},  /*  */
    {GPIOB, GPIO6},  /*I2C1_SCL  */
    {GPIOB, GPIO7},  /*I2C1_SDA  */
    {GPIOB, GPIO8},  /*CAN_RX  */
    {GPIOB, GPIO9},  /*CAN_TX  */
    {GPIOB, GPIO10},  /* USART3_TX  */
    {GPIOB, GPIO11},  /* USART3_RX  */
    {GPIOB, GPIO12},  /* SPI2_NSS  */
    {GPIOB, GPIO13},  /* SPI2_SCK */
    {GPIOB, GPIO14},  /* SPI2_MISO */
    {GPIOB, GPIO15},  /* SPI2_MOSI */

    {GPIOC, GPIO13},  /*-TAMPER-RTC  Output  GPIO_Output  */
    {GPIOC, GPIO14},  /*-OSC32_IN   */
    {GPIOC, GPIO15}   /*-OSC32_OUT  */
};

extern const spi_port SPI_PinDescription[]
{
    { PA4, PA5, PA6, PA7  }    // SPI1 - NSS pin, SCK pin, MISO pin, MOSI pin
    ,{ PB12, PB13, PB14, PB15 } // SPI2 - NSS pin, SCK pin, MISO pin, MOSI pin
    /* The SPI3 is not  used in this variant
      ,{ PA15, PB3 , PB4 , PB5  } // SPI3 - NSS pin, SCK pin, MISO pin, MOSI pin */
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
    // Connect All ports to CLK
    //rcc_periph_clock_enable(RCC_GPIOA);
    //rcc_periph_clock_enable(RCC_GPIOB);
    //rcc_periph_clock_enable(RCC_GPIOC);

    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);    /// SysTick at 72Mhz/8
    systick_set_reload(SYSTICK_RELOAD_VAL - 1);             /// SysTick Reload for 1ms tick
    systick_interrupt_enable();
    systick_counter_enable();
}
#ifdef __cplusplus
}
#endif



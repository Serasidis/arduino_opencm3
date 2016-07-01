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
  
  - 08 April 2016 Modified by Vassilis Serasidis
    This file is converted for using it with ST HAL + CubeMX + Arduino SAM core files.
*/

#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif
  
extern const Pin2PortMapArray g_Pin2PortMapArray[]=
{    

    {GPIOA, GPIO0,  RCC_GPIOA},  /*-WKUP  */
    {GPIOA, GPIO1,  RCC_GPIOA},  /*  */
    {GPIOA, GPIO2,  RCC_GPIOA},  /*  */
    {GPIOA, GPIO3,  RCC_GPIOA},  /*  */
    {GPIOA, GPIO4,  RCC_GPIOA},  /*SPI1_NSS  SPI1_NSS (opt)*/
    {GPIOA, GPIO5,  RCC_GPIOA},  /*SPI1_SCK  */
    {GPIOA, GPIO6,  RCC_GPIOA},  /*SPI1_MISO  */
    {GPIOA, GPIO7,  RCC_GPIOA},  /*SPI1_MOSI  */
    {GPIOA, GPIO8,  RCC_GPIOA},  /*  */
    {GPIOA, GPIO9,  RCC_GPIOA},  /*USART1_TX  */
    {GPIOA, GPIO10, RCC_GPIOA},  /*USART1_RX  */
    {GPIOA, GPIO11, RCC_GPIOA},  /* USBDM (-)  */
    {GPIOA, GPIO12, RCC_GPIOA},  /* USBDP (+)  */
    {GPIOA, GPIO13, RCC_GPIOA},  /*SYS_JTMS-SWDIO  */
    {GPIOA, GPIO14, RCC_GPIOA},  /*SYS_JTCK-SWCLK  */
    {GPIOA, GPIO15, RCC_GPIOA},  /*  */
    
    {GPIOB, GPIO0,  RCC_GPIOB},  /*  */
    {GPIOB, GPIO1,  RCC_GPIOB},  /*Output  GPIO_Output  Blue_LED*/
    {GPIOB, GPIO2,  RCC_GPIOB},  /* BOOT1 */
    {GPIOB, GPIO3,  RCC_GPIOB},  /*  */
    {GPIOB, GPIO4,  RCC_GPIOB},  /*  */
    {GPIOB, GPIO5,  RCC_GPIOB},  /*  */
    {GPIOB, GPIO6,  RCC_GPIOB},  /*I2C1_SCL  */
    {GPIOB, GPIO7,  RCC_GPIOB},  /*I2C1_SDA  */
    {GPIOB, GPIO8,  RCC_GPIOB},  /*CAN_RX  */
    {GPIOB, GPIO9,  RCC_GPIOB},  /*CAN_TX  */
    {GPIOB, GPIO10, RCC_GPIOB},  /* USART3_TX  */
    {GPIOB, GPIO11, RCC_GPIOB},  /* USART3_RX  */
    {GPIOB, GPIO12, RCC_GPIOB},  /* SPI2_NSS  */
    {GPIOB, GPIO13, RCC_GPIOB},  /* SPI2_SCK */
    {GPIOB, GPIO14, RCC_GPIOB},  /* SPI2_MISO */
    {GPIOB, GPIO15, RCC_GPIOB},  /* SPI2_MOSI */
    
    {GPIOC, GPIO13, RCC_GPIOC},  /*-TAMPER-RTC  Output  GPIO_Output  */
    {GPIOC, GPIO14, RCC_GPIOC},  /*-OSC32_IN   */
    {GPIOC, GPIO15, RCC_GPIOC}   /*-OSC32_OUT  */
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

// ----------------------------------------------------------------------------

// Custom board init  
  
void initVariant( void )
{
  // BluePill has 8MHz HSE
  rcc_clock_setup_in_hse_8mhz_out_72mhz();    /// Clock 72Hz from HSE 8MHz
  // Connect All ports to CLK
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB);
  rcc_periph_clock_enable(RCC_GPIOC);
  
  systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);    /// SysTick at 72Mhz/8
  systick_set_reload(8999);                               /// SysTick Reload for 1ms tick
  systick_interrupt_enable();
  systick_counter_enable();
    
}

  


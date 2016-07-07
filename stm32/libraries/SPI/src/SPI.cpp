/*
 * SPI Master library for Arduino Zero.
 * Copyright (c) 2015 Arduino LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

 /**
  * Modified for using this library with libopencm3 and STM32 MCUs.
  * 06 Jul 2016 - Modified by Vassilis Serasidis <avrsite@yahoo.gr>
  * Home: http://www.serasidis.gr
  */
   
#include "SPI.h"
#include <Arduino.h>
#include <wiring_private.h>
#include <assert.h>

#define SPI_IMODE_NONE   0
#define SPI_IMODE_EXTINT 1
#define SPI_IMODE_GLOBAL 2

const SPISettings DEFAULT_SPI_SETTINGS = SPISettings();

SPIClass::SPIClass(uint32_t spi)
{
  _spi = spi;
}

void SPIClass::begin()
{
  init();

  config(DEFAULT_SPI_SETTINGS);
}

void SPIClass::init()
{
  if (initialized)
    return;
  
  _cpol     = SPI_CR1_CPOL_CLK_TO_1_WHEN_IDLE;
  _cpha     = SPI_CR1_CPHA_CLK_TRANSITION_2;
 
  uint16_t cs_pin;
  uint16_t mosi_pin;
  uint16_t miso_pin;
  uint16_t sck_pin;
  uint8_t spiDev;

#if SPI_INTERFACES_COUNT > 0
  if(_spi == SPI_1){
    rcc_periph_clock_enable(RCC_SPI1);
    spiDev = 0;
  }
#endif  
#if SPI_INTERFACES_COUNT > 1
  if(_spi == SPI_2){
    rcc_periph_clock_enable(RCC_SPI2);
    spiDev = 1;
  }
#endif  
#if SPI_INTERFACES_COUNT > 2
  if(_spi == SPI_3){
    rcc_periph_clock_enable(RCC_SPI3);
    spiDev = 2;
  }
#endif
#if SPI_INTERFACES_COUNT > 3
  if(_spi == SPI_4){
    rcc_periph_clock_enable(RCC_SPI3);
    spiDev = 3;
  }
#endif
#if SPI_INTERFACES_COUNT > 4
  if(_spi == SPI_5){
    rcc_periph_clock_enable(RCC_SPI3);
    spiDev = 4;
  }
#endif
#if SPI_INTERFACES_COUNT > 5
  if(_spi == SPI_6){
    rcc_periph_clock_enable(RCC_SPI3);
    spiDev = 5;
  }
#endif

#if SPI_INTERFACES_COUNT > 0
  gpio_set_mode(g_PinDescription[SPI_PinDescription[spiDev].sck_pin].Port,      // SPI port
                GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
                g_PinDescription[SPI_PinDescription[spiDev].cs_pin].Pin         // SPI Chip Select pin
                | g_PinDescription[SPI_PinDescription[spiDev].sck_pin].Pin      // SPI CLOCK port
                | g_PinDescription[SPI_PinDescription[spiDev].mosi_pin].Pin );  // SPI MOSI pin
                  
  gpio_set_mode(g_PinDescription[SPI_PinDescription[spiDev].miso_pin].Port,     // MISO pin, port
                GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, 
                g_PinDescription[SPI_PinDescription[spiDev].miso_pin].Pin);     // MISO pin
  
  initialized = true;
#else
  initialized = false;
#endif
}

void SPIClass::config(SPISettings settings)
{
  /* Reset SPI, SPI_CR1 register cleared, SPI is disabled */
  spi_reset(_spi);
  
  switch (settings.dataMode){
    case 0: _cpol = _cpha = 0; break;
    case 1: _cpol = 0; _cpha = 1; break;
    case 2: _cpol = 1; _cpha = 0; break;
    case 3: _cpol = 1; _cpha = 1; break;    
  }
  
  spi_init_master(_spi, settings.prescaler, _cpol, _cpha, _dff, settings.bitOrder);
  
  spi_enable_software_slave_management(_spi);
  
  spi_set_nss_high(_spi);
  
  /* Enable SPI periph. */
  spi_enable(_spi);
}

void SPIClass::end()
{
  spi_reset(_spi);
  initialized = false;
}

#ifndef interruptsStatus
#define interruptsStatus() __interruptsStatus()
static inline unsigned char __interruptsStatus(void) __attribute__((always_inline, unused));
static inline unsigned char __interruptsStatus(void)
{
  // TODO:
}
#endif

void SPIClass::usingInterrupt(int interruptNumber)
{
  // TODO:
}

void SPIClass::beginTransaction(SPISettings settings)
{
  config(settings);
}

void SPIClass::endTransaction(void)
{
  // TODO:
}

void SPIClass::setBitOrder(BitOrder order)
{
  if (order == LSBFIRST) {
    spi_send_lsb_first(_spi);
    _xsbfirst = LSBFIRST;
  } else {
    spi_send_msb_first(_spi);
    _xsbfirst = LSBFIRST;
  }
}

void SPIClass::setDataMode(uint8_t mode)
{
    spi_set_standard_mode(_spi, mode);
}

void SPIClass::setClockDivider(uint8_t div)
{
  if (div < SPI_MIN_CLOCK_DIVIDER) {
    /**
     * That limits the SPI Max speed to 72 MHz / 4 = 18 MHz
     * Unofficially, the SPI_1 port can be clocked upto 36 MHz by setting the clock divider to 2. 
     */
    spi_set_baudrate_prescaler(_spi, SPI_MIN_CLOCK_DIVIDER);
  } else {
    spi_set_baudrate_prescaler(_spi, div);
  }
}

byte SPIClass::transfer(uint8_t data)
{
  if(_dff == SPI_CR1_DFF_8BIT)   // Checks if the SPI data frame is set to 8-bit data mode.
    return spi_xfer(_spi, data); // Writing data to the SPI bus and after that, read data.
  else{
    spi_set_dff_8bit(_spi);      // If the SPI is set to 16-bit data mode,
    _dff = SPI_CR1_DFF_8BIT;     // change the data frame mode to 8-bit.
    return spi_xfer(_spi, data);
  }
}

uint16_t SPIClass::transfer16(uint16_t data) {
  if(_dff == SPI_CR1_DFF_16BIT)
    spi_write(_spi, data);
  else{
    spi_set_dff_16bit(_spi);
    _dff = SPI_CR1_DFF_16BIT;
    spi_write(_spi, data);
  }
  return data;
}

void SPIClass::attachInterrupt() {
  // TODO:
  // Should be enableInterrupt()
}

void SPIClass::detachInterrupt() {
  // TODO:
  // Should be disableInterrupt()
}

#if SPI_INTERFACES_COUNT > 0
  SPIClass SPI(SPI_1);
#endif
#if SPI_INTERFACES_COUNT > 1
  SPIClass SPI2(SPI_2);
#endif
#if SPI_INTERFACES_COUNT > 2
  SPIClass SPI3(SPI_3);
#endif
#if SPI_INTERFACES_COUNT > 3
  SPIClass SPI4(SPI_4);
#endif
#if SPI_INTERFACES_COUNT > 4
  SPIClass SPI5(SPI_5);
#endif
#if SPI_INTERFACES_COUNT > 5
  SPIClass SPI6(SPI_6);
#endif


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
  
#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <Arduino.h>

// SPI_HAS_TRANSACTION means SPI has
//   - beginTransaction()
//   - endTransaction()
//   - usingInterrupt()
//   - SPISetting(clock, bitOrder, dataMode)
#define SPI_HAS_TRANSACTION 1

#define SPI_MODE0 0x00
#define SPI_MODE1 0x01
#define SPI_MODE2 0x02
#define SPI_MODE3 0x03

class SPISettings {
  public:
  SPISettings(uint32_t clock, BitOrder bitOrder, uint8_t dataMode) {
    if (__builtin_constant_p(clock)) {
      init_AlwaysInline(clock, bitOrder, dataMode);
    } else {
      init_MightInline(clock, bitOrder, dataMode);
    }
  }

  // Default speed set to 4.5 MHz, SPI mode set to MODE 0 and Bit order set to MSB first.
  SPISettings() { init_AlwaysInline(4500000, MSBFIRST, SPI_MODE0); }

  private:
  void init_MightInline(uint32_t clock, BitOrder bitOrder, uint8_t dataMode) {
    init_AlwaysInline(clock, bitOrder, dataMode);
  }

  void init_AlwaysInline(uint32_t clock, BitOrder bitOrder, uint8_t dataMode) __attribute__((__always_inline__)) {
    uint32_t  cpu_clock = (F_CPU / 2);
    uint32_t  clockFreq;
    clockFreq = (clock >= (F_CPU / SPI_MIN_CLOCK_DIVIDER) ? F_CPU / SPI_MIN_CLOCK_DIVIDER : clock);
    
    while(cpu_clock > clockFreq){
      cpu_clock /= 2;        
      prescaler++;
    }
    prescaler <<= 3;
    
    this->bitOrder = (bitOrder == MSBFIRST ? SPI_CR1_MSBFIRST : SPI_CR1_LSBFIRST);
    this->dataMode = dataMode;
  }

  uint8_t   prescaler = 0;
  uint32_t  bitOrder;
  uint8_t   dataMode;

  friend class SPIClass;
};

class SPIClass {
  public:
  SPIClass(uint32_t spi);

  byte transfer(uint8_t data);
  uint16_t transfer16(uint16_t data);
  inline void transfer(void *buf, size_t count);

  // Transaction Functions
  void usingInterrupt(int interruptNumber);
  void beginTransaction(SPISettings settings);
  void endTransaction(void);

  // SPI Configuration methods
  void attachInterrupt();
  void detachInterrupt();

  void begin();
  void end();

  void setBitOrder(BitOrder order);
  void setDataMode(uint8_t uc_mode);
  void setClockDivider(uint8_t uc_div);

  private:
  void init();
  void config(SPISettings settings);

  uint8_t _uc_pinMiso;
  uint8_t _uc_pinMosi;
  uint8_t _uc_pinSCK;
  uint32_t _spi;
  uint32_t _br;
  uint32_t _cpol;
  uint32_t _cpha;
  uint32_t _dff;
  uint32_t _xsbfirst;

  bool initialized;
  uint8_t interruptMode;
  char interruptSave;
  uint32_t interruptMask;
};

void SPIClass::transfer(void *buf, size_t count)
{
  // TODO: Optimize for faster block-transfer
  uint8_t *buffer = reinterpret_cast<uint8_t *>(buf);
  for (size_t i=0; i<count; i++)
    buffer[i] = transfer(buffer[i]);
}

#if SPI_INTERFACES_COUNT > 0
  extern SPIClass SPI;
#define SPI1 SPI  
#endif
#if SPI_INTERFACES_COUNT > 1
  extern SPIClass SPI2;
#endif
#if SPI_INTERFACES_COUNT > 2
  extern SPIClass SPI3;
#endif
#if SPI_INTERFACES_COUNT > 3
  extern SPIClass SPI4;
#endif
#if SPI_INTERFACES_COUNT > 4
  extern SPIClass SPI5;
#endif
#if SPI_INTERFACES_COUNT > 5
  extern SPIClass SPI6;
#endif

// Define the SPI Clock Divisions according to the libopencm3 definitions.
  #define SPI_CLOCK_DIV2   SPI_CR1_BAUDRATE_FPCLK_DIV_2
  #define SPI_CLOCK_DIV4   SPI_CR1_BAUDRATE_FPCLK_DIV_4
  #define SPI_CLOCK_DIV8   SPI_CR1_BAUDRATE_FPCLK_DIV_8
  #define SPI_CLOCK_DIV16  SPI_CR1_BAUDRATE_FPCLK_DIV_16
  #define SPI_CLOCK_DIV32  SPI_CR1_BAUDRATE_FPCLK_DIV_32
  #define SPI_CLOCK_DIV64  SPI_CR1_BAUDRATE_FPCLK_DIV_64
  #define SPI_CLOCK_DIV128 SPI_CR1_BAUDRATE_FPCLK_DIV_128
  #define SPI_CLOCK_DIV256 SPI_CR1_BAUDRATE_FPCLK_DIV_256

#endif
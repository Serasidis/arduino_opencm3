/*
 * TWI/I2C library for Arduino Zero
 * Copyright (c) 2015 Arduino LLC. All rights reserved.
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
 * 21 Jul 2016 - Modified by Vassilis Serasidis <avrsite@yahoo.gr>
 * Home: http://www.serasidis.gr
 */
 
extern "C" {
#include <string.h>
}

#include <Arduino.h>
#include <wiring_private.h>

#include "Wire.h"

TwoWire::TwoWire(uint32_t twi) {
  i2c = twi;
}

void TwoWire::begin(void) {
  //Master Mode
  init();
}

void TwoWire::begin(uint8_t address) {
  //Slave mode 
  //TODO

}

void TwoWire::setClock(uint32_t baudrate) {
  //TODO
}

void TwoWire::end() {

}

uint8_t TwoWire::requestFrom(uint8_t address, size_t quantity, bool stopBit) {
  if(quantity == 0){
    return 0;
  }
  
  size_t byteRead = 0;  

  rxBuffer.clear();
    
  i2c_send_start(i2c);
  while ((I2C_SR1(i2c) & I2C_SR1_SB) == 0);
  
  i2c_send_7bit_address(i2c, address, I2C_READ);
  while (!(I2C_SR1(i2c) & I2C_SR1_ADDR));
  
  uint32_t reg32 = I2C_SR2(i2c); //Read status register.
  
  for (byteRead = 0; byteRead < quantity; ++byteRead){
    while ((I2C_SR1(i2c) & I2C_SR1_BTF) == 0);
    rxBuffer.store_char(I2C_DR(i2c));
  }
  i2c_send_stop(i2c);
  
  return byteRead;
}

uint8_t TwoWire::requestFrom(uint8_t address, size_t quantity) {
  return requestFrom(address, quantity, true);
}

void TwoWire::beginTransmission(uint8_t address) {
  uint32_t reg32 __attribute__((unused));
  
  i2c_send_start(i2c);
  while ((I2C_SR1(i2c) & I2C_SR1_SB) == 0);
    
  i2c_send_7bit_address(i2c, address, I2C_WRITE);
  while (!(I2C_SR1(i2c) & I2C_SR1_ADDR));
    
  reg32 = I2C_SR2(i2c); //Read status register.
}

uint8_t TwoWire::endTransmission(bool stopBit) {
  // Start I2C transmission
  //TODO
}

uint8_t TwoWire::endTransmission() {
  i2c_send_stop(i2c);
  return 1;  //TODO
}

size_t TwoWire::write(uint8_t ucData) {
  i2c_send_data(i2c, ucData);
  while (!(I2C_SR1(i2c) & (I2C_SR1_BTF | I2C_SR1_TxE)));
  return 1;
}

size_t TwoWire::write(const uint8_t *data, size_t quantity) {
  //Try to store all data
  for(size_t i = 0; i < quantity; ++i)
  {
    //Return the number of data stored, when the buffer is full (if write return 0)
    if(!write(data[i]))
      return i;
  }

  //All data stored
  return quantity;
}

int TwoWire::available(void) {
  return rxBuffer.available();
}

int TwoWire::read(void) {
  
  return rxBuffer.read_char();
}

int TwoWire::peek(void) {
//  return rxBuffer.peek();
}

void TwoWire::flush(void) {
  //TODO
  // Do nothing, use endTransmission(..) to force
  // data transfer.
}

void TwoWire::onReceive(void(*function)(int)) {
  //TODO
  //  onReceiveCallback = function;
}

void TwoWire::onRequest(void(*function)(void)) {
  //TODO
  //  onRequestCallback = function;
}

void TwoWire::onService(void) {

}

void TwoWire::init(){
  
  if (initialized)
    return;
  
  uint8_t i2cDev;
  volatile int divider;
  volatile int risetime;
  
#if WIRE_INTERFACES_COUNT > 0
  if(i2c == I2C1){
    rcc_periph_clock_enable(RCC_I2C1);
    rcc_periph_clock_enable(RCC_GPIOB); // Temporary RCC_GPIOX initiallization
    i2cDev = 0;
  }
#endif

#if WIRE_INTERFACES_COUNT > 1
  if(i2c == I2C2){
    rcc_periph_clock_enable(RCC_I2C2);
    rcc_periph_clock_enable(RCC_GPIOB); // Temporary RCC_GPIOX initiallization
    i2cDev = 1;
  }
#endif

#if WIRE_INTERFACES_COUNT > 2
  if(i2c == I2C3){
    rcc_periph_clock_enable(RCC_I2C3);
    i2cDev = 2;
  }
#endif

#if WIRE_INTERFACES_COUNT > 3
  if(i2c == I2C4){
    rcc_periph_clock_enable(RCC_I2C4);
    i2cDev = 3;
  }
#endif

#if WIRE_INTERFACES_COUNT > 4
  if(i2c == I2C5){
    rcc_periph_clock_enable(RCC_I2C5);
    i2cDev = 4;
  }
#endif

#if WIRE_INTERFACES_COUNT > 5
  if(i2c == I2C6){
    rcc_periph_clock_enable(RCC_I2C6);
    i2cDev = 5;
  }
#endif

#if SPI_INTERFACES_COUNT > 0
  gpio_set_mode(g_PinDescription[I2C_PinDescription[i2cDev].scl_pin].Port,    // I2C port
                GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN,
                  g_PinDescription[I2C_PinDescription[i2cDev].sda_pin].Pin    // I2C DATA pin
                | g_PinDescription[I2C_PinDescription[i2cDev].scl_pin].Pin ); // I2C CLOCK pin

  divider = (rcc_apb1_frequency / 2000) / (I2C_CLOCK_SPEED / 1000);
  risetime = 1000000 / (I2C_CLOCK_SPEED / 1000) / 6 / 28;
  
  i2c_peripheral_disable(i2c);
  i2c_set_clock_frequency(i2c, I2C_CR2_FREQ_36MHZ);
  i2c_set_ccr(i2c, divider);
  i2c_set_trise(i2c, risetime);
  i2c_peripheral_enable(i2c);
  
  initialized = true;
#else
  initialized = false;
#endif
}

#if WIRE_INTERFACES_COUNT > 0
  TwoWire Wire(I2C1);
#endif
#if WIRE_INTERFACES_COUNT > 1
  TwoWire Wire1(I2C2);
#endif
#if WIRE_INTERFACES_COUNT > 2
  TwoWire Wire2(I2C3);
#endif
#if WIRE_INTERFACES_COUNT > 3
  TwoWire Wire3(I2C4);
#endif
#if WIRE_INTERFACES_COUNT > 4
  TwoWire Wire4(I2C5);
#endif
#if WIRE_INTERFACES_COUNT > 5
  TwoWire Wire5(I2C6);
#endif

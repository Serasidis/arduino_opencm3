/*
  Copyright (c) 2014 Arduino LLC.  All right reserved.

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
*/

 /**
  * Edited by Evangelos Arkalis.
  */

#include "Arduino.h"
#include "wiring_private.h"
#include <stm32/gpio_arch.h>
#include <stm32/adc_arch.h>

#ifdef __cplusplus
extern "C" {
#endif

static int _readResolution = 10;
static int _writeResolution = 8;

void analogReference(eAnalogReference reference)
{
}

void analogReadResolution(int resolution)
{
    _readResolution = resolution;
}

static inline uint32_t mapResolution( uint32_t value, uint32_t from, uint32_t to )
{
  if ( from == to )
  {
    return value ;
  }

  if ( from > to )
  {
    return value >> (from-to) ;
  }
  else
  {
    return value << (to-from) ;
  }
}


uint32_t analogRead( uint32_t ulPin ) {
// USE ADC1
    gpio_setup_pin_analog( digitalPinToPort(ulPin), digitalPinToBitMask(ulPin));
    adc_init();
    uint8_t channel = g_PinDescription[ulPin].AdcChan;
	adc_set_regular_sequence(ADC1, 1, &channel);
    uint32_t valueRead = adc_read();
	adc_power_off(ADC1);
    return mapResolution(valueRead, 12, _readResolution);
}

void analogWriteResolution( int resolution )
{
    _writeResolution = resolution;
}

#ifdef __cplusplus
}
#endif

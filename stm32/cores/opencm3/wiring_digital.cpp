/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/*
 * Arduino-compatible digital I/O implementation.
 */

 /*
  * Arduino srl - www.arduino.org
  * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
  */
  
  /*
  * http://www.serasidis.gr
  * 2016 Jun 30: Modified by Vassilis Serasidis - avrsite@yahoo.gr
  */

//#include "wiring.h"
#include "io.h"
#include "Arduino.h"
//#include "variant.h"
//#include "dac.h"

extern const Pin2PortMapArray g_Pin2PortMapArray[] ;

void pinMode(uint8 pin, WiringPinMode mode)
{
  if (pin >= GPIO_PINS){
        return;
  }
    
  rcc_periph_clock_enable(g_Pin2PortMapArray[pin].periph_clock);
  
  switch ( mode )
  {
    case INPUT:
        gpio_set_mode(g_Pin2PortMapArray[pin].GPIOx_Port,       //Port
                      GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT,    //
                      g_Pin2PortMapArray[pin].Pin_abstraction); //Pin
		break ;

    case INPUT_PULLUP:
        gpio_set_mode(g_Pin2PortMapArray[pin].GPIOx_Port,
                      GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN,
                      g_Pin2PortMapArray[pin].Pin_abstraction);
		break ;

    case OUTPUT:
        gpio_set_mode(g_Pin2PortMapArray[pin].GPIOx_Port,
                      GPIO_MODE_OUTPUT_50_MHZ,
                      GPIO_CNF_OUTPUT_PUSHPULL,
                      g_Pin2PortMapArray[pin].Pin_abstraction);
		break ;

    default:
        break ;
    }
}


uint32 digitalRead(uint8 pin)
{
  if (pin >= GPIO_PINS){
        return 0;
  }
  
  gpio_get(g_Pin2PortMapArray[pin].GPIOx_Port, g_Pin2PortMapArray[pin].Pin_abstraction);
}

void digitalWrite(uint8 pin, uint8 val)
{
  if (pin >= GPIO_PINS){
        return;
  }
    
  if(val == HIGH)
    gpio_set(g_Pin2PortMapArray[pin].GPIOx_Port, g_Pin2PortMapArray[pin].Pin_abstraction);
  else
    gpio_clear(g_Pin2PortMapArray[pin].GPIOx_Port, g_Pin2PortMapArray[pin].Pin_abstraction);
}

void togglePin(uint8 pin)
{
  if (pin >= GPIO_PINS){
        return;
  }
  
  gpio_toggle(g_Pin2PortMapArray[pin].GPIOx_Port, g_Pin2PortMapArray[pin].Pin_abstraction);
}

uint32_t pulseIn( uint8 pin, uint32_t state, uint32_t timeout )
{
#if 0
    while(digitalRead(pin) == state);
    while(digitalRead(pin) == !state);
    uint32_t start_time = micros();
    while(digitalRead(pin) == state);
    return (micros()-start_time);
#endif
}

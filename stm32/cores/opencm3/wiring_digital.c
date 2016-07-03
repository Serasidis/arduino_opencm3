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


#include "Arduino.h"

#ifdef __cplusplus
 extern "C" {
#endif

void pinMode( uint32_t ulPin, uint32_t ulMode )
{

  if (ulPin >= GPIO_PINS){
        return;
  }

  switch ( ulMode )
  {
    case INPUT:
        gpio_set_mode(g_PinDescription[ulPin].Port,       //Port
                      GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT,    //
                      g_PinDescription[ulPin].Pin); //Pin
		break ;

    case INPUT_PULLUP:
        gpio_set_mode(g_PinDescription[ulPin].Port,
                      GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN,
                      g_PinDescription[ulPin].Pin);
		break ;

    case OUTPUT:
        gpio_set_mode(g_PinDescription[ulPin].Port,
                      GPIO_MODE_OUTPUT_50_MHZ,
                      GPIO_CNF_OUTPUT_PUSHPULL,
                      g_PinDescription[ulPin].Pin);
		break ;

    default:
        break ;
    }
}

int digitalRead( uint32_t ulPin )
{
  if (ulPin >= GPIO_PINS){
        return 0;
  }
  return gpio_get(g_PinDescription[ulPin].Port, g_PinDescription[ulPin].Pin);
}

void digitalWrite( uint32_t ulPin, uint32_t ulVal )
{

  if (ulPin >= GPIO_PINS){
        return;
  }

  if(ulVal == HIGH)
    gpio_set(g_PinDescription[ulPin].Port, g_PinDescription[ulPin].Pin);
  else
    gpio_clear(g_PinDescription[ulPin].Port, g_PinDescription[ulPin].Pin);

}

void togglePin(uint32_t ulPin)
{
  if (ulPin >= GPIO_PINS){
        return;
  }

  gpio_toggle(g_PinDescription[ulPin].Port, g_PinDescription[ulPin].Pin);
}
/*
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
*/

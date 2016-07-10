/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

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

 /*
  * 2016 Jul 4: Modified by Evangelos Arkalis
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
#if defined(STM32F1)
        gpio_set_mode(g_PinDescription[ulPin].Port,       //Port
                      GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT,    //
                      g_PinDescription[ulPin].Pin); //Pin
#endif // defined
		break ;

    case INPUT_PULLUP:
#if defined(STM32F1)
        gpio_set_mode(g_PinDescription[ulPin].Port,
                      GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN,
                      g_PinDescription[ulPin].Pin);
#endif
		break ;

    case OUTPUT:
#if defined(STM32F1)
        gpio_set_mode(g_PinDescription[ulPin].Port,
                      GPIO_MODE_OUTPUT_50_MHZ,
                      GPIO_CNF_OUTPUT_PUSHPULL,
                      g_PinDescription[ulPin].Pin);
#endif
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

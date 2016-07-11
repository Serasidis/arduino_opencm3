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
  * 2016 Jul 12: Modified by Evangelos Arkalis
  */

 /*
  * http://www.serasidis.gr
  * 2016 Jun 30: Modified by Vassilis Serasidis - avrsite@yahoo.gr
  */


#include "Arduino.h"
#include "stm32/gpio_arch.h"

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
        gpio_setup_input(g_PinDescription[ulPin].Port, g_PinDescription[ulPin].Pin );
		break ;


    case INPUT_PULLUP:
        gpio_setup_input_pullup(g_PinDescription[ulPin].Port, g_PinDescription[ulPin].Pin  );
		break ;

    case OUTPUT:
        gpio_setup_output(g_PinDescription[ulPin].Port, g_PinDescription[ulPin].Pin );
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

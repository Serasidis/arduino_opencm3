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

/**
 *  @brief Delay implementation.
 */

 /*
	* Arduino srl - www.arduino.org
	* 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
	*/
  
 /*
  * http://www.serasidis.gr
  * 2016 Jul 1: Modified by Vassilis Serasidis - avrsite@yahoo.gr
  */

//#include "memory.h"
//#include "systick.h"
#include "wiring_time.h"
//#include "delay.h"

unsigned long temp32;
volatile uint32 systick_uptime_millis;

void delay(unsigned long ms) {
  
  while(ms > 0){
    delayMicroseconds(1000);
    ms--;
  }
}

void delayMicroseconds(unsigned long us) {              
      asm volatile ("MOV R0,%[loops]\n\t"\
			"1: \n\t"\
			"SUB R0, #1\n\t"\
			"CMP R0, #0\n\t"\
			"BNE 1b \n\t" : : [loops] "r" (8*us) : "memory"\
		);
}

void sys_tick_handler(void) {
    systick_uptime_millis++;
}
/*
  Copyright (C)2016 Evangelos Arkalis

  This file is part of arduino_opencm3.

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
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/dwt.h>

#include "sys_arch.h"

inline uint32_t sysclk()
{
    return rcc_ahb_frequency;
}

inline uint32_t pb1clk()
{
    return rcc_apb1_frequency;
}

inline uint32_t pb2clk()
{
    return rcc_apb2_frequency;
}

void delay_nano(uint32_t ns)
{
    uint32_t               _clock;
    uint32_t               _delay;     /* ticks per ms */
    uint32_t               _scale;

    uint32_t ticks, delay, ms;

    _clock = sysclk();
	_delay = (uint32_t)(_clock / 1000);
	_scale = (uint32_t)(((uint64_t)1000000000 * (uint64_t)4096) / (uint64_t)_clock);

	dwt_enable_cycle_counter();
    if (ns > 1000000) {
	        ms = ns / 1000000;
	        ns -= ms * 1000000;
	        delay = ms * _delay;
	        ticks = dwt_read_cycle_counter();
	        while ((uint32_t)(dwt_read_cycle_counter() - ticks) < delay);
	        {}
    }
    delay = (ns * 4096) / _scale;
    ticks = dwt_read_cycle_counter();
    while ((uint32_t)(dwt_read_cycle_counter() - ticks) < delay);
    {}
}

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

void nanodelay(uint32_t ns)
{
    uint32_t               clock;
    uint32_t               delay;     /* ticks per ms */
    uint32_t               scale;

    clock = rcc_ahb_frequency;
	delay = (uint32_t)(clock / 1000);
	scale = (uint32_t)(((uint64_t)1000000000 * (uint64_t)4096) / (uint64_t)clock);
}

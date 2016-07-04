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

#include "Uart.h"
#include "Arduino.h"
#include "wiring_private.h"
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/nvic.h>

Uart::Uart(uint32_t usartn)
{
    usart = usartn;
}

void Uart::begin(unsigned long baudrate)
{
  begin(baudrate, (uint8_t)SERIAL_8N1);
}

void Uart::begin(unsigned long baudrate, uint16_t config)
{
    /* Setup GPIO pins */
    switch(usart)
    {
        case USART1:
            rcc_periph_clock_enable(RCC_USART1);
            nvic_enable_irq(NVIC_USART1_IRQ);
            gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);   // TODO - Use g_PinDescription
            gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO_USART1_RX);                    // TODO - Use g_PinDescription
            break;

        case USART2:
            rcc_periph_clock_enable(RCC_USART2);
            nvic_enable_irq(NVIC_USART2_IRQ);
            gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART2_TX);
            gpio_set_mode(GPIOA, GPIO_MODE_INPUT,GPIO_CNF_INPUT_FLOAT, GPIO_USART2_RX);
            break;

        case USART3:
            rcc_periph_clock_enable(RCC_USART3);
            nvic_enable_irq(NVIC_USART3_IRQ);
            gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART3_TX);
            gpio_set_mode(GPIOB, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO_USART3_RX);
            break;
    }
    usart_set_baudrate(usart, baudrate);
    //usart_set_databits(usart, bits);
    //usart_set_stopbits(usart, stopbits);
    //usart_set_parity(usart, parity);
    usart_set_flow_control(usart, USART_FLOWCONTROL_NONE);
    usart_set_mode(usart, USART_MODE_TX_RX);
    USART_CR1(usart) |= USART_CR1_RXNEIE;
    usart_enable(usart);
}

void Uart::end()
{
  usart_disable(usart);
  rxBuffer.clear();
}

void Uart::flush()
{
  // TODO
}

int Uart::available()
{
  return rxBuffer.available();
}

int Uart::availableForWrite()
{
  // TODO
  return 1;
}

int Uart::peek()
{
  return rxBuffer.peek();
}

int Uart::read()
{
  return rxBuffer.read_char();
}

size_t Uart::write(const uint8_t data)
{
  usart_send_blocking(usart,data);
  return 1;
}

void Uart::push(uint8_t b) {
    rxBuffer.store_char(b);
}

extern Uart Serial1;
extern Uart Serial2;
extern Uart Serial3;


void usart1_isr(void)
{
    /* Check if we were called because of RXNE. */
    if (((USART_CR1(USART1) & USART_CR1_RXNEIE) != 0) &&
            ((USART_SR(USART1) & USART_SR_RXNE) != 0))
    {
        char c = usart_recv(USART1);
        Serial1.push(c);
    }
}

void usart2_isr(void)
{
    /* Check if we were called because of RXNE. */
    if (((USART_CR1(USART2) & USART_CR1_RXNEIE) != 0) &&
            ((USART_SR(USART2) & USART_SR_RXNE) != 0))
    {
        char c = usart_recv(USART2);
        Serial2.push(c);
    }
}

void usart3_isr(void)
{
    /* Check if we were called because of RXNE. */
    if (((USART_CR1(USART3) & USART_CR1_RXNEIE) != 0) &&
            ((USART_SR(USART3) & USART_SR_RXNE) != 0))
    {
        char c = usart_recv(USART3);
        Serial3.push(c);
    }
}


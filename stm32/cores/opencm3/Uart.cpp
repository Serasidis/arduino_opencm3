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
#include "stm32/gpio_arch.h"

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
#ifdef USE_UART1
        case USART1:
            rcc_periph_clock_enable(RCC_USART1);
            nvic_enable_irq(NVIC_USART1_IRQ);
            gpio_setup_pin_af(UART1_GPIO_PORT_TX, UART1_GPIO_TX, UART1_GPIO_AF, TRUE);
            gpio_setup_pin_af(UART1_GPIO_PORT_RX, UART1_GPIO_RX, UART1_GPIO_AF, FALSE);
            break;
#endif
#ifdef USE_UART2
        case USART2:
            rcc_periph_clock_enable(RCC_USART2);
            nvic_enable_irq(NVIC_USART2_IRQ);
            gpio_setup_pin_af(UART2_GPIO_PORT_TX, UART2_GPIO_TX, UART2_GPIO_AF, TRUE);
            gpio_setup_pin_af(UART2_GPIO_PORT_RX, UART2_GPIO_RX, UART2_GPIO_AF, FALSE);
            break;
#endif
#ifdef USE_UART3
        case USART3:
            rcc_periph_clock_enable(RCC_USART3);
            nvic_enable_irq(NVIC_USART3_IRQ);
            gpio_setup_pin_af(UART3_GPIO_PORT_TX, UART3_GPIO_TX, UART3_GPIO_AF, TRUE);
            gpio_setup_pin_af(UART3_GPIO_PORT_RX, UART3_GPIO_RX, UART3_GPIO_AF, FALSE);
            break;
#endif
#ifdef USE_UART4
        case USART4:
            rcc_periph_clock_enable(RCC_USART4);
            nvic_enable_irq(NVIC_USART4_IRQ);
            gpio_setup_pin_af(UART4_GPIO_PORT_TX, UART4_GPIO_TX, UART4_GPIO_AF, TRUE);
            gpio_setup_pin_af(UART4_GPIO_PORT_RX, UART4_GPIO_RX, UART4_GPIO_AF, FALSE);
            break;
#endif
#ifdef USE_UART5
        case USART5:
            rcc_periph_clock_enable(RCC_USART5);
            nvic_enable_irq(NVIC_USART5_IRQ);
            gpio_setup_pin_af(UART5_GPIO_PORT_TX, UART5_GPIO_TX, UART5_GPIO_AF, TRUE);
            gpio_setup_pin_af(UART5_GPIO_PORT_RX, UART5_GPIO_RX, UART5_GPIO_AF, FALSE);
            break;
#endif
        default:
            ;
    }
    usart_set_baudrate(usart, baudrate);
    usart_set_databits(usart, HARDSER_DATA_8);
    usart_set_stopbits(usart, USART_STOPBITS_1);
    usart_set_parity(usart, USART_PARITY_NONE);
    usart_set_flow_control(usart, USART_FLOWCONTROL_NONE);
    usart_set_mode(usart, USART_MODE_TX_RX);
    rxBuffer.clear();
    txBuffer.clear();
    txRunning=false;
    usart_enable_rx_interrupt(usart);
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
  return !txBuffer.isFull();
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
  while (txBuffer.isFull()) ;
  usart_disable_tx_interrupt(usart);
  if (txRunning) {
    txBuffer.store_char(data);
  } else {
    txRunning=true;
    usart_send(usart,data);
  }
  usart_enable_tx_interrupt(usart);
  return 1;
}

void Uart::push(uint8_t b) {
    rxBuffer.store_char(b);
}


void Uart::IrqHandler()
{
    if (((USART_CR1(usart) & USART_CR1_RXNEIE) != 0) && usart_get_flag(usart, USART_SR_RXNE)) {
        push(usart_recv(usart));
    }
    if (((USART_CR1(usart) & USART_CR1_TXEIE) != 0) && usart_get_flag(usart, USART_SR_TXE)) {
        if ( txBuffer.available()>0 ) {
            usart_send(usart,txBuffer.read_char());
        } else {
            txRunning=false;
            usart_disable_tx_interrupt(usart);
        }
    }
}

#ifdef USE_UART1
extern Uart Serial1;
void usart1_isr(void) { Serial1.IrqHandler();}
#endif

#ifdef USE_UART2
extern Uart Serial2;
void usart2_isr(void) { Serial2.IrqHandler();}
#endif

#ifdef USE_UART3
extern Uart Serial3;
void usart3_isr(void) { Serial3.IrqHandler();}
#endif

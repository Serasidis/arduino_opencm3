#ifndef SYS_ARCH_H
#define SYS_ARCH_H

#include <libopencm3/cm3/common.h>

BEGIN_DECLS

uint32_t sysclk(void);
uint32_t pb1clk(void);
uint32_t pb2clk(void);
void delay_nano(uint32_t ns);

static inline void enable_irq()   { __asm volatile ("cpsie i"); }
static inline void disable_irq()  { __asm volatile ("cpsid i"); }

END_DECLS

#endif // SYS_ARCH_H

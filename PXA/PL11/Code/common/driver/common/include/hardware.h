/*
 *  common/hardware.h
 *
 */

#ifndef __COMMON_HARDWARE_H
#define __COMMON_HARDWARE_H


#define CLOCK_TICK_RATE     3250000
#define PXA_IRQ_SKIP        0
#define u32                 (unsigned long)


#define io_p2v(x) (x)
#define io_v2p(x) (x)

#ifndef __ASSEMBLY__

# define __REG(x)	(*((volatile unsigned long *)io_p2v(x)))

/* With indexed regs we don't want to feed the index through io_p2v()
   especially if it is a variable, otherwise horrible code will result. */
# define __REG2(x,y)	(*(volatile unsigned long *)((unsigned long)&__REG(x) + (y)))

# define __PREG(x)	(io_v2p((u32)&(x)))

#else

# define __REG(x)	io_p2v(x)
# define __PREG(x)	io_v2p(x)

#endif


#include "common/include/bitfield.h"


#endif  /* __COMMON_HARDWARE_H */

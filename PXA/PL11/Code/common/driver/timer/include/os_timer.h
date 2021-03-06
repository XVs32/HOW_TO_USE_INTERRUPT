// --------------------------------------------------------------------
//
//   Title     :  ost_timer.h
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  ost_timer routines
//             :
//   Limitation:
//             :
//   Note      :
//             :
// --------------------------------------------------------------------
//   modification history :
// --------------------------------------------------------------------
//   Version| mod. date: |
//   V1.0   | 12/12/2006 | Programming start
// --------------------------------------------------------------------
//
// Note:
//
//       MICROTIME COMPUTER INC.
//
// --------------------------------------------------------------------

#ifndef _OS_TIMER_H_
#define _OS_TIMER_H_

#ifndef __ADDR_PXA27X_H__
#include        "common/include/addr.h"
#endif

#include        "irq/include/irq.h"


//=================================================================
// Global Variables
//=================================================================

typedef struct timer_realtime_st
{
    U16  hour;  // 1 hour
    U16  min;   // 1 min
    U16  sec;   // 1 sec
    U16  msec;  // 1 msec
} timer_realtime_t;
extern timer_realtime_t g_timer_realtime;


//=================================================================
// Default Values
//=================================================================

#define OST_TICKS_MS    3250          // 1ms in ticks 
#define NR_TIMERS       12

//
// Enumeration for compatible OST match registers
//
typedef enum 
{
    TIMER0 = 0,
    TIMER1,
    TIMER2,
    TIMER3,
    TIMER4,
    TIMER5,
    TIMER6,
    TIMER7,
    TIMER8,
    TIMER9,
    TIMER10,
    TIMER11
}OST_MATCHREG;

typedef enum 
{
    RES_DISABLE=0,
    RES_REG=1,               /* 程虫 1/32768 second             */
    RES_1MSEC=2,             /* 程虫 1 millisecond. 1 睝(ms)  */
    RES_1SEC=3,              /* 程虫 1 second. 1 (s)          */ 
    RES_1USEC=4              /* 程虫 1 microsecond. 1 稬(us)  */
} OST_4_11_RES_TYPE ;   

#define OST_ONE_SHOT     0
#define OST_PERIODIC      ~(OST_ONE_SHOT)

#define OST_FREE_TIMER    (~0)


void Delay(U16 ms);
void delay_ms (U16 ms);
void delay_s(U16 sec);
void ostimer_init(void);

int  register_ostimer(U32 *device, U16 ms, U8 periodic, isrfun isr, char*pDesc,
                      void* pVoid);
int  register_ostimer_ext(U32 *device, U16 timeval, int res_type, U8 periodic, 
                          isrfun isr, char*pDesc, void* pVoid);
int  unregister_ostimer(U32 device);
int  ostimer_disable (U32 device);
int  ostimer_restart (U32 device);

#endif // _OS_TIMER_H_

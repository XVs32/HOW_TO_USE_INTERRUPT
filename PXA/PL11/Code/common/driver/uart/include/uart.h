// --------------------------------------------------------------------
//
//   Title     :  uart.h
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  UART routines
//             :
//   Limitation:
//             :
//   Note      :
//             :
// --------------------------------------------------------------------
//   modification history :
// --------------------------------------------------------------------
//   Version| mod. date: |
//   V1.0   | 12/28/2006 | Programming start
// --------------------------------------------------------------------
//
// Note:
//
//       MICROTIME COMPUTER INC.
//
// --------------------------------------------------------------------

#ifndef _DRIVER_UART_H_
#define _DRIVER_UART_H_

#ifndef __ADDR_PXA27X_H__
#include        "common/include/addr.h"
#endif


//=================================================================
// Global Variables
//=================================================================
#define UART0        0  // FFUART 
#define UART1        1  // BTUART 
#define UART2        2  // STUART 

#define CS5          1  //  word length per frame
#define CS6          2
#define CS7          3
#define CS8          4
#define CSTOPB       1      /* two Stop bits per frame */
#define PARENB       1      /* enable parity mode */
#define PARODD       2      /* odd parity mode */

typedef unsigned int    tcflag_t;

typedef struct termios {
    unsigned long baud_rate ;   // UART baudrate
    unsigned long word_len ;    
    unsigned long parity ;      // UART Data format
    unsigned long stop_bit ;
    unsigned long rts ;
    unsigned long afe ;         // auto flow control
}termios_t;


//=================================================================
// High-Level functions
//=================================================================


//=================================================================
// low-level functions
//=================================================================
int  uart_put_char (int channel, char ch);
int  uart_put_string(int channel, char* pstring);
int  uart_get_char (int channel, char *ch);

int  uart_on(int channel, termios_t *options);
int  uart_start(int channel);
int  uart_stop(int channel);
int  uart_off(int channel);
int  uart_set_speed(int channel, unsigned int baud);
int  uart_set_flow(int channel, int enable_rts, int enable_afe);
int  uart_set_config(int channel, termios_t *options);
int  uart_get_config(int channel, termios_t *options);
int  uart_flush_buffer(int channel);
int  uart_init(void);
int  uart_exit(void);


#endif // _DRIVER_UART_H_

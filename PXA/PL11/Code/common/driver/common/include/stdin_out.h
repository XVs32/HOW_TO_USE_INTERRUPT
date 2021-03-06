// --------------------------------------------------------------------
//
//   Title     :  stdio_out.h
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  standard io/out routines
//             :
//   Limitation:
//             :
//   Note      :
//             :
// --------------------------------------------------------------------
//   modification history :
// --------------------------------------------------------------------
//   Version| mod. date: |
//   V1.0   | 12/22/2006 | Programming start
// --------------------------------------------------------------------
//
// Note:
//
//       MICROTIME COMPUTER INC.
//
// --------------------------------------------------------------------

#ifndef _DRIVER_STDIO_H_
#define _DRIVER_STDIO_H_


#include <stdarg.h>
#include <string.h>
#include <stdio.h>


#ifndef __ADDR_PXA27X_H__
#include "common/include/addr.h"
#endif


//=================================================================
// Global Variables
//=================================================================


//=================================================================
// 標準輸入/輸出類函數
//=================================================================
void  mt_putch(char ch);
void  mt_puts(char *msg);
void  mt_printf(__const char *fmt, ...);
int   mt_getch(void); 
char* mt_gets(char *p_out_buffer);	


//=================================================================
// 指標類函數
//=================================================================
void  mt_getcursor(int *x, int *y);
void  mt_setcursor(int x, int y);
void  mt_enable_cursor(void);
void  mt_disable_cursor(void);

void  mt_clrscr(void);


void  stdio_reset (void);
void  stdio_init(void);
void  stdio_exit(void);






#endif // _DRIVER_STDIO_H_

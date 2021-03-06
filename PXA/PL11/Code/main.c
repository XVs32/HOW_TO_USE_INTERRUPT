// --------------------------------------------------------------------
//
//   Title     :  main.c
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  DEMO Program for Creator Board
//             :
//   Limitation:
//             :
//   Note      :
//             :
// --------------------------------------------------------------------
//   modification history :
// --------------------------------------------------------------------
//   Version| mod. date: |
//   Vx.x   | mm/dd/yyyy |
//   V1.0   | 12/22/2006 | First release
// --------------------------------------------------------------------
//
// Note:
//
//       MICROTIME COMPUTER INC.
//
// --------------------------------------------------------------------


/*************************************************************************
Include files
*************************************************************************/
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "common/include/addr.h"
#include "common/include/creator_io.h"
#include "common/include/stdin_out.h"
#include "common/include/scan.h"
#include "lcd/include/lcd.h"
#include "irq/include/irq.h"
#include "timer/include/os_timer.h"
#include "uart.h"
#include "serial_reg.h"

/*************************************************************************
Constant define
*************************************************************************/
#define MODE_POLLING     	0
#define MODE_INTERRUPT		1

#define EXE 	0

/*************************************************************************
Function prototypes
*************************************************************************/
static int  process(void);
static void uart_poll_process();
static void uart_int_process();
static int  creator_system_init(void);
void rand_transmit(U32 channel);
void recieve(U32 channel, U32 f_packet);

/*************************************************************************
Variable define
*************************************************************************/
static int mode;

static int process(void){
	
	if (!LCD_init())
		return (UM);
	
	if (!uart_init())       
        return (UM);
		
	if (!scan_init(0))
		return (UM);
	
	stdio_init();                      
    mt_enable_cursor();  
    mt_clrscr();

	while (1){

		if (mode == MODE_POLLING)
			uart_poll_process();
		else
			uart_int_process();	
	}
    uart_exit(); 
    stdio_exit(); 
    LCD_exit();
}

static void uart_poll_process(){

	U8	ch;

	/* 設定rate */
	FFIER |= 0x40;		// Enable UART
	FFLCR = 0x03;	    //只將WLS欄位  enable ，對照投影片 P.18
	FFLCR |= 0x80;      //enable DLAB欄位 準備 接收 DLH DLL 的設定 
	FFDLH = 0x00;		//rate 高位元
	FFDLL = 0x60;		//rate 低
	FFLCR = 0x03;	    //end ，將DLAB 再 disable
	
	FFTHR = '\n';
	Delay(2);
	FFTHR = '\r';
	Delay(2);
	FFTHR = 'P';
	Delay(2);
	
	while(1){
		    
		if(FFLSR & UART_LSR_DR){
			ch = FFRBR;
			FFTHR = ch;
			Delay(2);	
			if (ch == '\r'){
				FFTHR = '\n';
				Delay(2);
			}
			else if (ch == '\x1'){
				mode = MODE_INTERRUPT;
				break;
			}
			
		}
	}
}

static void uart_int_process(){
	
	termios_t option ;
    U8	ch, channel ; 

	srand(g_timer_realtime.msec + g_timer_realtime.sec * 1000);
		
	option.baud_rate = 9600;
    option.word_len = CS8; 
    option.parity = 0;      // no parity
    option.stop_bit = 0;    // 1 stop bit     
    option.rts = 0;         // deassert nRTS                   
    option.afe = 0;         // auto flow control        
    channel = UART0;
	
	if (uart_on(channel, &option)){

		uart_put_string(channel, "\r\nI");
        while (1){
            if (uart_get_char (channel, &ch)) { 
                if (ch == '\r')
                    uart_put_char(channel, '\n');
				else if (ch == '\x1'){
					mode = MODE_POLLING;
					break;
				}				
				uart_put_char(channel, ch);
            }
        }


    }
	
	uart_off(channel);
}

/*************************************************************************
MAIN Program 
*************************************************************************/
int 
main (void)
{       
        if (!creator_system_init())
            return (0);
        
        while (1)
            process();      

        return (1);
}

static
int creator_system_init(void)
{
        if (!creator_io_init())
            return (0);                          
            	
        irq_init();
        ostimer_init();
        enable_irq();                                      

        return (1);         
}
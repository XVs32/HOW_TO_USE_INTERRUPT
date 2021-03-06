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
#include <stdlib.h>

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
void rand_recv(U32 channel, U32 type);
void process_command(char *cmd);

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
#if EXE == 4
	mode = MODE_INTERRUPT;
#endif

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
			
			if (ch == '\r'){
				FFTHR = '\n';
				Delay(2);
			}
			else if (ch == '\x1'){
				mode = MODE_INTERRUPT;
				break;
			}
#if EXE == 2
			else if (ch == '\x8'){
				FFTHR = ch;
				Delay(2);
				FFTHR = ' ';
				Delay(2);
			}
#endif
			ch = FFRBR;
			FFTHR = ch;
			Delay(2);
		} 
	}
}

static void uart_int_process(){
	
	termios_t option ;
    U8	ch, channel, cmd[33], cmd_index; 

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
#if EXE != 3
        while (1){
            if (uart_get_char (channel, &ch)) { 
                if (ch == '\r')
                    uart_put_char(channel, '\n');
				else if (ch == '\x1'){
					mode = MODE_POLLING;
					break;
				}
#if EXE == 2 || EXE == 4
				else if (ch == '\x8'){
					uart_put_string(channel, "\x8 ");
				}
#endif
				uart_put_char(channel, ch);
#if EXE == 4
				if (ch == '\x8'){
					if (cmd_index > 0)
						cmd_index--;
				} else if (ch == '\r' || ch == '\n'){
					cmd[cmd_index] = '\0';
					process_command(cmd);
					cmd_index = 0;
				}else if (cmd_index < sizeof(cmd))
					cmd[cmd_index++] = ch;
				else
					uart_put_string(channel, "\x8 \x8");
#endif
				
            }
        }
#else
		while (1){
			if (get_key(&ch)){
				if (ch == 1){
					rand_transmit(channel);
				}
			}
			
			if (uart_get_char(channel, &ch)){
				rand_recv(channel, ch);
			}
		}
#endif
    }
	
	uart_off(channel);
}

#if EXE == 3
void rand_transmit(U32 channel){

	const U32 hex = 0xff4670;
	const U16 dec = 12345;
	const char* str = "Hi, man!";
	U32 type = rand() % 3, i;
	U32 len = (type == 0) ? 4 : (type == 1) ? 2 : 8;
	void* p = (void*)((type == 0) ? &hex : (type == 1) ? &dec : str);
	char* byte_ptr = (char*)p;
	
	uart_put_char(channel, (char)type);
	uart_put_char(channel, (char)len);
	for (i = 0; i < len; i++, byte_ptr++){
		uart_put_char(channel, *byte_ptr);
	}
	
	if (type == 0)
		mt_printf("S: HEX4 %x", hex);
	else if (type == 1)
		mt_printf("S: DEC2 %d", dec);
	else
		mt_printf("S: STR %s", str);
}

void rand_recv(U32 channel, U32 type){

	U32 len, hex = 0, i;
	char str[8], ch;
	
	if (type > 2)
		return;
	
	while (!uart_get_char(channel, &ch));
	len = ch;
	
	for (i = 0; i < len; i++){
		while (!uart_get_char(channel, &ch));
		if (type < 2)
			hex |= ch << (i << 3);
		else
			str[i] = ch;
	}
	
	if (type == 0)
		mt_printf("R: HEX4 %x", hex);
	else if (type == 1)
		mt_printf("R: DEC2 %d", hex);
	else
		mt_printf("R: STR %s", str);
}
#endif

#if EXE == 4
void process_command(char *cmd){
	char *tok, *content;
	U8 result;
	
	mt_printf("%s\n", cmd);
	tok = strtok(cmd, " ");
	content = strtok(NULL, " ");
	
	if (!strcmp(tok, "led")){
		mt_main_led_set(~strtol(content, NULL, 16));
	} else if (!strcmp(tok, "lcd"))
		mt_printf("%s\n", content);
}
#endif

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
        ostimer_init();   // for delay 等等刪掉看看
        enable_irq();                                      

        return (1);         
}
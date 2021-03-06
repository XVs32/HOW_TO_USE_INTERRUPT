// --------------------------------------------------------------------
//
//   Title     :  menu.h
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  menu routines
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

#ifndef _DRIVER_CREATOR_IO_H_
#define _DRIVER_CREATOR_IO_H_

#ifndef __ADDR_PXA27X_H__
#include        "common/include/addr.h"
#endif



//=================================================================
// Global Variables
//=================================================================
extern creator_regs_t       gcreator_io;
extern p_base_regs_t       pg_base_regs;
extern p_main_regs_t       pg_main_regs;


//=================================================================
// High-Level functions
//=================================================================



//=================================================================
// low-level functions
//=================================================================
#define BASE_LED_D1      4  
#define BASE_LED_D2      5     
#define BASE_LED_D3      6
#define BASE_LED_D4      7

#define MAIN_LED_D9      0
#define MAIN_LED_D10     1 
#define MAIN_LED_D11     2 
#define MAIN_LED_D12     3
#define MAIN_LED_D13     4 
#define MAIN_LED_D14     5
#define MAIN_LED_D15     6
#define MAIN_LED_D16     7


void mt_main_led_set(U16 led);
int  mt_main_led_on(int led_bit);
int  mt_main_led_off(int bit);

U8   mt_main_get_sw(void);

U16  mt_base_led_get(void);
void mt_base_led_set(U16 led);
int  mt_base_led_on(int led_bit);
int  mt_base_led_off(int bit);
int  mt_main_keypad_set_scanline(U32 code);
U32  mt_main_keypad_get_scancode(void);
int  mt_main_7segment_set(U16 segment, U16 common);
U16  mt_main_io_reg0_get(void);
void mt_main_io_reg0_set(U16 value);

/*
 * PXA270子版上的SW 函數
 */
#define KEY_PRESS     OK
#define KEY_NO_PRESS  UM

#define BASE_SW_1     0
#define BASE_SW_2     1

int  mt_base_get_sw(int sw_idx);


U16  mt_base_cpld_ctrl3_get(void);
void mt_base_cpld_ctrl3_set(U16 value);
void mt_base_cpld_ctrl3_set_bit(U16 bit);
void mt_base_cpld_ctrl3_clear_bit(U16 bit);

void mt_base_d1_d4_connect_pwm0_pwm3(void);
void mt_base_d1_d4_disconnect_pwm0_pwm3(void);


U8   mt_main_cpld_get_version(void);
int  creator_io_init(void);

#endif // _DRIVER_CREATOR_IO_H_

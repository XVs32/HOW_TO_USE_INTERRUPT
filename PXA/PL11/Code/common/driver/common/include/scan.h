// --------------------------------------------------------------------
//
//   Title     :  scan.h
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  scan routines
//             :
//   Limitation:
//             :
//   Note      :
//             :
// --------------------------------------------------------------------
//   modification history :
// --------------------------------------------------------------------
//   Version| mod. date: |
//   V1.0   | 12/15/2006 | Programming start
// --------------------------------------------------------------------
//
// Note:
//
//       MICROTIME COMPUTER INC.
//
// --------------------------------------------------------------------

#ifndef _SCAN_H_
#define _SCAN_H_

#ifndef __ADDR_PXA27X_H__
#include        "common/include/addr.h"
#endif


//=================================================================
// Global Variables
//=================================================================



//=================================================================
// High-Level input functions
//=================================================================
U8   get_key (U8 *ch);
int  chk_key (U8 *ch);


//=================================================================
// low-level KEYPAD functions
//=================================================================
typedef enum {
    KEY_CODE_0 = 0,
    KEY_CODE_1 = 1,
    KEY_CODE_2 = 2,
    KEY_CODE_3 = 3,
    KEY_CODE_4 = 4,
    KEY_CODE_5 = 5,
    KEY_CODE_6 = 6,
    KEY_CODE_7 = 7,
    KEY_CODE_8 = 8,
    KEY_CODE_9 = 9,                                 
    KEY_CODE_A = 0xa,   
    KEY_CODE_B = 0xb,   
    KEY_CODE_C = 0xc,   
    KEY_CODE_D = 0xd,   
    KEY_CODE_STAR = 0xe,    // *
    KEY_CODE_POND = 0xf     // #

} KEYPAD_CODE ; 

U8   mt_main_keypad_get_key(U8 *ch);
int  mt_main_keypad_chk_key(U8 *ch);
int  mt_main_keypad_flush(void);
U8   mt_main_keypad_vkey2num (U16 ch);
void mt_main_keypad_wait_char(void);
int  mt_main_keypad_init(U16 scan_time_ms);
int  mt_main_keypad_exit (void);


//=================================================================
// low-level 7_segment functions
//=================================================================
typedef enum {
   SEGMENT_SHIFT_LEFT = 0, 
   SEGMENT_SHIFT_RIGHT= 1   
} SEGMENT_SHIFT_TYPE ;

typedef enum {
   _7SEG_D5 = 0,
   _7SEG_D6 = 1,
   _7SEG_D7 = 2,
   _7SEG_D8 = 3,
} _7SEG_DIGIT;


//=================================================================
// High-Level input functions
//=================================================================
void mt_main_7seg_blank (void);


//=================================================================
// low-level 7segment functions
//=================================================================
int  mt_main_7seg_shift(SEGMENT_SHIFT_TYPE  shift_type, U8 data);
int  mt_main_7seg_put_pattern(U8 digit, U8 pattern);
void mt_main_7seg_put_all_pattern(U8 pattern);
int  mt_main_7seg_put_number(U8 digit, U8 number);
void mt_main_7seg_enable_system_time(int enable);



int  scan_init(int show_system_time);
void scan_exit (void);

#endif // _SCAN_H_

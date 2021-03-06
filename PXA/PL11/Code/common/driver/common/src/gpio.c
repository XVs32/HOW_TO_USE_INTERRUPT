// --------------------------------------------------------------------
//
//   Title     :  gpio.c
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  XScale-PXA270 GPIO routines for Creataor Board
//             :  GpioSetOutputState1()  : 設定GPIO輸出準位為High
//             :  GpioSetOutputState0()  : 設定GPIO輸出準位為Low 
//             :  GpioSetAlternateFunction() : 設定此GPIO pin功能為一般的GPIO
//             :                               或特殊功能的I/O
//             :  GpioSetDirection()     : 設定GPIO pin當做輸出或輸入
//             :  GpioGetLevelState      : 讀取GPIO pin的準位狀態
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
//   V1.0   | 01/08/2007 | First release
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
#include <stdio.h>
#include "common/include/addr.h"


/*************************************************************************
Constant define
*************************************************************************/



/*************************************************************************
Function prototypes
*************************************************************************/


/*************************************************************************
Variable define
*************************************************************************/



/**
 * General-purpose I/O access routines 
 * Registers:
 *  GPLR_0,1,2,3:   line-level registers
 *  GPDR_0,1,2,3:   data-direction registers
 *  GPSR_0,1,2,3:   set registers
 *  GPCR_0,1,2,3:   clear registers
 *  GRER_0,1,2,3:   rising-edge detect registers
 *  GFER_0,1,2,3:   falling-edge detect registers
 *  GEDR_0,1,2,3:   edge-detect status register
 *  GAFR0_L: alternate function select registers
 *  GAFR0_U: alternate function select registers
 *  GAFR1_L: alternate function select registers
 *  GAFR1_U: alternate function select registers
 *  GAFR2_L: alternate function select registers
 *  GAFR2_U: alternate function select registers
 *  GAFR3_L: alternate function select registers
 *  GAFR3_U: alternate function select registers
 */


/****************************************************************************
 * 功能 : 設定GPIO pin輸出準位為High                                        *
 * 輸入 : bit_no ...: GPIO pin的編號. range 0..120                          *
 * 輸出 : 無                                                                * 
 ****************************************************************************/
void 
GpioSetOutputState1 (U8 bit_no)
{
        U32 gpsr_addr[]={0x40e00018, 0x40e0001c, 0x40e00020, 0x40e00118};
        volatile U32 *reg_ptr;
        U32          reg_data;
        U8           reg_idx, bit_idx;
        
        reg_idx = bit_no / 32;
        bit_idx = bit_no % 32;
        reg_data = (1 << bit_idx);

        reg_ptr = (U32 *)gpsr_addr[reg_idx];
        *reg_ptr = reg_data;
}



/****************************************************************************
 * 功能 : 設定GPIO pin輸出準位為Low                                         *
 * 輸入 : bit_no ...: GPIO pin的編號. range 0..120                          *
 * 輸出 : 無                                                                * 
 ****************************************************************************/
void 
GpioSetOutputState0  (U8 bit_no)
{
        U32 gpcr_addr[]={0x40e00024, 0x40e00028, 0x40e0002c, 0x40e00124};
        volatile U32 *reg_ptr;
        U32          reg_data;
        U8           reg_idx, bit_idx;

        reg_idx = bit_no / 32;
        bit_idx = bit_no % 32;
        reg_data = (1 << bit_idx);

        reg_ptr = (U32*)gpcr_addr[reg_idx];
        *reg_ptr = reg_data;
}



/****************************************************************************
 * 功能 : 設定此GPIO pin功能為一般的GPIO或特殊功能的I/O                     *
 * 輸入 : bit_no ...: GPIO pin的編號. range 0..120                          *
 *      : function .: GPIO的功能.                                           *
 *                    功能有 0(GPIO_ALT_FN_0): 一般GPIO                     * 
 *                           1(GPIO_ALT_FN_1): 特殊功能1, 依pin決定那個功能 *      
 *                           2(GPIO_ALT_FN_1): 特殊功能2, 依pin決定那個功能 *   
 *                           3(GPIO_ALT_FN_2): 特殊功能3, 依pin決定那個功能 *      
 * 輸出 : 無                                                                * 
 ****************************************************************************/
void 
GpioSetAlternateFunction (U8 bit_no, U8 Function)
{
        U32 gafr_addr[]={ 0x40e00054, 0x40e00058, 0x40e0005c, 0x40e00060,
                          0x40e00064, 0x40e00068, 0x40e0006c, 0x40e00070};
        volatile U32  *reg_ptr;
        U32           reg_data, bit_mask;
        U8            reg_idx, bit_idx;

        reg_idx = bit_no / 16;
        bit_idx = (bit_no % 16) * 2;
        bit_mask = 3 << bit_idx;
        reg_data = (Function << bit_idx);

        reg_ptr = (U32 *)gafr_addr[reg_idx];
        *reg_ptr = ((*reg_ptr) & (~bit_mask)) | reg_data;
}



/****************************************************************************
 * 功能 : 設定GPIO pin當做輸出或輸入                                        *
 * 輸入 : bit_no ...: GPIO pin的編號. range 0..120                          *
 *      : dir ......: GPIO的輸出入方向.                                     *
 *                    功能有 0(GPIO_DIR_IN) : 當做輸入                      * 
 *                    功能有 0(GPIO_DIR_OUT): 當做輸出                      *  
 * 輸出 : 無                                                                * 
 ****************************************************************************/
void 
GpioSetDirection (U8 bit_no, U8 dir)
{
        U32 gpdr_addr[]={0x40e0000c, 0x40e00010, 0x40e00014, 0x40e0010c};
        volatile U32 *reg_ptr;
        U32          reg_data, bit_mask;
        U8           reg_idx, bit_idx;

        reg_idx = bit_no / 32;
        bit_idx = bit_no % 32;
        bit_mask = 1 << bit_idx;
        reg_data = (dir << bit_idx);

        reg_ptr = (U32 *)gpdr_addr[reg_idx];
        *reg_ptr = ((*reg_ptr) & (~bit_mask)) | reg_data;
}



/****************************************************************************
 * 功能 : 讀取GPIO pin的準位狀態                                            *
 * 輸入 : 無                                                                *
 * 輸出 : 1 : pin 狀態為High                                                *
 *        0 : pin 狀態為Low                                                 *
 ****************************************************************************/
int 
GpioGetLevelState (U8 bit_no)
{
/*
 * Read level status (GPLR): 
 * return 0 = Pin state is low., 1 = Pin state is high.
*/  
        U32 gplr_addr[]={0x40e00000, 0x40e00004, 0x40e00008, 0x40e00100};
        volatile U32 *reg_ptr;
        U32          reg_mask, reg_level;
        U8           reg_idx, bit_idx;

        reg_idx = bit_no / 32;
        bit_idx = bit_no % 32;
        reg_mask = (1 << bit_idx);

        reg_ptr = (U32 *)gplr_addr[reg_idx];
        if(((*reg_ptr) & reg_mask) != 0) return(1);
        
        return(0);      
}

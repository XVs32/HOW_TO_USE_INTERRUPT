// --------------------------------------------------------------------
//
//   Title     :  gpio.c
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  XScale-PXA270 GPIO routines for Creataor Board
//             :  GpioSetOutputState1()  : �]�wGPIO��X�Ǧ쬰High
//             :  GpioSetOutputState0()  : �]�wGPIO��X�Ǧ쬰Low 
//             :  GpioSetAlternateFunction() : �]�w��GPIO pin�\�ର�@�몺GPIO
//             :                               �ίS��\�઺I/O
//             :  GpioSetDirection()     : �]�wGPIO pin����X�ο�J
//             :  GpioGetLevelState      : Ū��GPIO pin���Ǧ쪬�A
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
 * �\�� : �]�wGPIO pin��X�Ǧ쬰High                                        *
 * ��J : bit_no ...: GPIO pin���s��. range 0..120                          *
 * ��X : �L                                                                * 
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
 * �\�� : �]�wGPIO pin��X�Ǧ쬰Low                                         *
 * ��J : bit_no ...: GPIO pin���s��. range 0..120                          *
 * ��X : �L                                                                * 
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
 * �\�� : �]�w��GPIO pin�\�ର�@�몺GPIO�ίS��\�઺I/O                     *
 * ��J : bit_no ...: GPIO pin���s��. range 0..120                          *
 *      : function .: GPIO���\��.                                           *
 *                    �\�঳ 0(GPIO_ALT_FN_0): �@��GPIO                     * 
 *                           1(GPIO_ALT_FN_1): �S��\��1, ��pin�M�w���ӥ\�� *      
 *                           2(GPIO_ALT_FN_1): �S��\��2, ��pin�M�w���ӥ\�� *   
 *                           3(GPIO_ALT_FN_2): �S��\��3, ��pin�M�w���ӥ\�� *      
 * ��X : �L                                                                * 
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
 * �\�� : �]�wGPIO pin����X�ο�J                                        *
 * ��J : bit_no ...: GPIO pin���s��. range 0..120                          *
 *      : dir ......: GPIO����X�J��V.                                     *
 *                    �\�঳ 0(GPIO_DIR_IN) : ����J                      * 
 *                    �\�঳ 0(GPIO_DIR_OUT): ����X                      *  
 * ��X : �L                                                                * 
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
 * �\�� : Ū��GPIO pin���Ǧ쪬�A                                            *
 * ��J : �L                                                                *
 * ��X : 1 : pin ���A��High                                                *
 *        0 : pin ���A��Low                                                 *
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

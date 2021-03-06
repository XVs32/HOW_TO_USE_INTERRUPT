/*--------------------------------------------------------------------
;
;   Title     :  low-level-init.S
;             :
;   Library   :
;             :
;   Developers:  MICROTIME MDS group
;             :
;   Purpose   :  Creator XScale-PXA270 Initialization routines
;             :
;   Limitation:
;             :
;   Note      :
;             :
;---------------------------------------------------------------------
;   modification history :
;---------------------------------------------------------------------
;   Version| mod. date: |
;   Vx.x   | mm/dd/yyyy |  
;   V1.0   | 11/16/2006 | First release
;---------------------------------------------------------------------
;
; Note:
;
;       MICROTIME COMPUTER INC.
;
;------------------------------------------------------------------- */
#include "common/include/option.h"
#include "memcfg_s.h"

.section ".stext"


         .globl low_level_init

low_level_init:	
    
clk_init:    
  	/*===========================================================
     * Initial CLK 
     *==========================================================*/   
	ldr		r0, =CC_BASE
	
	ldr		r1, =CCCR_VALUE
	str		r1, [r0, #CCCR_OFFSET]
	
	mov		r0, #CLKCFG_VALUE
	mcr		p14, 0, r0, c6, c0, 0
  	


GPIO_init:
  	/*===========================================================
     * ########## Initial GPIO
     *==========================================================*/  
	ldr     r1,  =GPIO_BASE

	/*===========================================================
	 *	1=set
     *==========================================================*/ 
     	
	ldr     r2,   =0x00008000	/* CFG_GPSR0_VAL */
	str     r2,   [r1, #GPSR0_OFFSET]
	
	ldr     r2,   =0x00CF0002	/* CFG_GPSR1_VAL */
	str     r2,   [r1, #GPSR1_OFFSET]

	ldr     r2,   =0x0201c000	/* CFG_GPSR2_VAL */
	str     r2,   [r1, #GPSR2_OFFSET]

	ldr     r2,   =0	       /* CFG_GPSR3_VAL  */
	str     r2,   [r1, #GPSR3_OFFSET]
	
	/*===========================================================	
	 *	1=clear
     *==========================================================*/ 	
	
	ldr     r2,   =0	/* CFG_GPCR0_VAL */
	str     r2,   [r1, #GPCR0_OFFSET]
	
	ldr     r2,   =0	/* CFG_GPCR1_VAL */
	str     r2,   [r1, #GPCR1_OFFSET]

	ldr     r2,   =0	/* CFG_GPCR2_VAL */
	str     r2,   [r1, #GPCR2_OFFSET]

	ldr     r2,   =0	/* CFG_GPCR3_VAL */
	str     r2,   [r1, #GPCR3_OFFSET]

	/*===========================================================
	 *	1=out/0=in
     *==========================================================*/ 		

	ldr     r2,   =CFG_GPDR0_VAL
	str     r2,   [r1, #GPDR0_OFFSET]
	
	ldr     r2,   =CFG_GPDR1_VAL
	str     r2,   [r1, #GPDR1_OFFSET]

	ldr     r2,   =CFG_GPDR2_VAL
	str     r2,   [r1, #GPDR2_OFFSET]

	ldr     r2,   =CFG_GPDR3_VAL
	str     r2,   [r1, #GPDR3_OFFSET]

	/*===========================================================
	 *	0=gpio
     *==========================================================*/ 		

	ldr     r2,   =CFG_GAFR0_L_VAL
	str     r2,   [r1, #GAFR0_L_OFFSET]
	ldr     r2,   =CFG_GAFR0_U_VAL
	str     r2,   [r1, #GAFR0_U_OFFSET]

	ldr     r2,   =CFG_GAFR1_L_VAL
	str     r2,   [r1, #GAFR1_L_OFFSET]
	ldr     r2,   =CFG_GAFR1_U_VAL
	str     r2,   [r1, #GAFR1_U_OFFSET]

	ldr     r2,   =CFG_GAFR2_L_VAL
	str     r2,   [r1, #GAFR2_L_OFFSET]
	ldr     r2,   =CFG_GAFR2_U_VAL
	str     r2,   [r1, #GAFR2_U_OFFSET]

	ldr     r2,   =CFG_GAFR3_L_VAL
	str     r2,   [r1, #GAFR3_L_OFFSET]
	ldr     r2,   =CFG_GAFR3_U_VAL
	str     r2,   [r1, #GAFR3_U_OFFSET]

	ldr		r0,	=PSSR
	ldr		r1,	=0x30    /*	CFG_PSSR_VAL  */
	str		r1,   [r0]



	/*===========================================================
     * ########## Initial Mmory Controller
     *==========================================================*/ 
mem_init:

	ldr     r1,  =MEMC_BASE

 	/* ---------------------------------------------------------------- */
 	/* Step 1: Initialize Asynchronous static memory controller         */
 	/* ---------------------------------------------------------------- */

 	/* MSC registers: timing, bus width, mem type                       */

 	/* MSC0: nCS(1,0)                                                   */
	ldr     r2,  =MCS0_VALUE
	str     r2,  [r1, #MSC0_OFFSET]
	ldr     r2,  [r1, #MSC0_OFFSET]

 	/* MSC1: nCS(3,2)                                                   */
	ldr     r2,  =MCS1_VALUE
	str     r2,  [r1, #MSC1_OFFSET]
	ldr     r2,  [r1, #MSC1_OFFSET]

 	/* MSC2: nCS(5,4)                                                   */
	ldr     r2,  =MCS2_VALUE
	str     r2,  [r1, #MSC2_OFFSET]
	ldr     r2,  [r1, #MSC2_OFFSET]

 	/* ---------------------------------------------------------------- */
    /* Step 2: Initialize Card Interface                                */
 	/* ---------------------------------------------------------------- */

 	/* MECR: Memory Expansion Card Register                             */
	ldr     r2, =CFG_MECR_VAL
	str     r2, [r1, #MECR_OFFSET]
	ldr		r2,	[r1, #MECR_OFFSET]

 	/* MCMEM0: Card Interface slot 0 timing                             */
	ldr     r2, =CFG_MCMEM0_VAL
	str     r2, [r1, #MCMEM0_OFFSET]
	ldr		r2,	[r1, #MCMEM0_OFFSET]

 	/* MCMEM1: Card Interface slot 1 timing                             */
	ldr     r2, =CFG_MCMEM1_VAL
	str     r2, [r1, #MCMEM1_OFFSET]
	ldr		r2,	[r1, #MCMEM1_OFFSET]

 	/* MCATT0: Card Interface Attribute Space Timing, slot 0            */
	ldr     r2, =CFG_MCATT0_VAL
	str     r2, [r1, #MCATT0_OFFSET]
	ldr		r2,	[r1, #MCATT0_OFFSET]

 	/* MCATT1: Card Interface Attribute Space Timing, slot 1            */
	ldr     r2, =CFG_MCATT1_VAL
	str     r2, [r1, #MCATT1_OFFSET]
	ldr		r2,	[r1, #MCATT1_OFFSET]

    /* MCIO0: Card Interface I/O Space Timing, slot 0                   */
	ldr     r2, =CFG_MCIO0_VAL
	str     r2, [r1, #MCIO0_OFFSET]
	ldr		r2,	[r1, #MCIO0_OFFSET]

 	/* MCIO1: Card Interface I/O Space Timing, slot 1                   */
	ldr     r2, =CFG_MCIO1_VAL
	str     r2, [r1, #MCIO1_OFFSET]
	ldr		r2,	[r1, #MCIO1_OFFSET]


    /* ---------------------------------------------------------------- */
 	/* Step 3: Initialize timing for Sync memory                        */
 	/* ---------------------------------------------------------------- */
	
	/*	MDREFR = (MDREFR & 0xfffff000) | 0x01e							*/
	ldr		r4,	[r1, #MDREFR_OFFSET]
	ldr     r2,     =0xFFF
	bic		r4,     r4, r2
	ldr     r3,     =0x01e   /*	CFG_MDREFR_VAL */
	and     r3,     r3,  r2
	orr		r4,     r4, r3
	str		r4,	[r1, #MDREFR_OFFSET]

	/*	MDREFR = (MDREFR & 0xfffff000) | 0x01e							*/
	/*	Do not clear MDREFR_K1RUN in case of download operation         */
	bic     r4, r4, #(MDREFR_K2RUN  | MDREFR_K0RUN)
	bic     r4, r4, #(MDREFR_K2FREE |MDREFR_K1FREE | MDREFR_K0FREE)
    bic     r4, r4, #MDREFR_K1DB2	/* SDCLK1 = CLK_MEM */
	str		r4,	 [r1, #MDREFR_OFFSET]
	ldr     r4,  [r1, #MDREFR_OFFSET]

 	/* Note: preserve the mdrefr value in r4                            */


 	/* ---------------------------------------------------------------- */
 	/* Step 4: Initialize Synchronous Static Memory (Flash/Peripherals) */
 	/* ---------------------------------------------------------------- */

 	/* No SX memory, disable all SX partition */
    ldr     r2,  =0x40044004
    str     r2,  [r1, #SXCNFG_OFFSET]


    /* ---------------------------------------------------------------- */
 	/* Step 5: Initialize SDRAM                                         */
 	/* ---------------------------------------------------------------- */
	
	/* Enable SDCLK1 */
    orr     r4, r4, #MDREFR_K1RUN		
    str     r4, [r1, #MDREFR_OFFSET]
    ldr     r4, [r1, #MDREFR_OFFSET]

    /* Disable self-refresh */
    bic     r4, r4, #MDREFR_SLFRSH
    str     r4, [r1, #MDREFR_OFFSET]
    ldr     r4, [r1, #MDREFR_OFFSET]

	/* Enable SDCKE */
    orr     r4, r4, #MDREFR_E1PIN
    str     r4, [r1, #MDREFR_OFFSET]
    ldr     r4, [r1, #MDREFR_OFFSET]

    nop
    nop

 	/* Setup address configuration and timing for Samsung-K4S561632E    */
	ldr		r4,	=0x08000ac9
	str     r4, [r1, #MDCNFG_OFFSET]
	ldr     r4, [r1, #MDCNFG_OFFSET]


 	/* Wait for the clock to the SDRAMs to stabilize (~200uS)           */
	ldr 	r3, =OSCR
	mov 	r2, #0
	str 	r2, [r3]
	ldr 	r4, =0x300
loop1:
	ldr 	r2, [r3]
	cmp 	r4, r2
	bgt 	loop1


	/* Set MDCNFG_DE0                                                   */
	
	ldr     r3,	[r1, #MDCNFG_OFFSET]
	mov		r4, r3
	orr		r3,	r3,	#1	 
	str     r3,	[r1, #MDCNFG_OFFSET]
	mov		r0, r3
	

 	/* Set MDMRS                                                        */
	ldr     r2,  =0
	str     r2,  [r1, #MDMRS_OFFSET]

	/* We are finished with PXA270's memory controller initialisation   */
	
	mov	    pc, lr  
	
.section ".bss" 	


/*--------------------------------------------------------------------
;
;   Title     :  startup.S
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

    .global _reset_entry
    .global main
    .global CUdefHandler, CIrqHandler, CPabtHandler, CDabtHandler, CFiqHandler
    .global MMU_Init, MMU_EnableICache, MMU_EnableDCache,MMU_EnableMMU
    .global enable_irq, disable_irq
    .globl  low_level_init
     

/* wait for coprocessor write complete */
    .macro CPWAIT
    mrc     p15,0,r0,c2,c0,0
    mov     r0,r0
    sub     pc,pc,#4
    .endm
    

.section ".vector"
_reset_entry:
    b       ResetHandler      /* Relative branch allows remap, 
                                 limited to 32 MByte          */
    b       UdefHnd
    b       SwiHnd
    b       PabtHnd
    b       DabtHnd
    b       Unexpected
    b       IrqHnd
    b       FiqHnd


/*****************************************************************************/
/*                                                                           */
/* exception handlers                                                        */
/*                                                                           */
/*****************************************************************************/
Unexpected:     
    b       Unexpected
    
UdefHnd:
    stmdb   sp!,{r0-r12,lr}
    bl      CUdefHandler
    ldmia   sp!,{r0-r12,lr}
    subs    pc,lr,#4

SwiHnd: 
    stmdb   sp!,{r0-r12,lr}
    subs    r0, lr, #4
    ldr     r0,[r0]
    mov     r1, #0xffffff
    and     r0,r0,r1
    cmp     r0, #1
    beq     Enable_IRQ_SWI
    b       EndOfSwi
    
Enable_IRQ_SWI:
    mrs     r1,spsr
    mvn     r0,#0xc0
    and     r1,r1,r0
    msr     spsr_c,r1
    b       EndOfSwi
    
EndOfSwi:
    ldmia   sp!,{r0-r12,lr}
    movs    pc, lr

IrqHnd:	
    stmdb   sp!,{r0-r12,lr}
    ldr     r1,=CIrqHandler
    mov     lr,pc
    mov     pc,r1     
    ldmia   sp!,{r0-r12,lr}
    subs    pc,lr,#4

PabtHnd:
    stmdb   sp!,{r0-r12,lr}
    sub     r0,lr,#8
    ldr     r1,=CPabtHandler
    mov     lr,pc
    mov     pc,r1  
    ldmia   sp!,{r0-r12,lr}
    subs    pc,lr,#4

DabtHnd:
    stmdb   sp!,{r0-r12,lr}
    sub     r0,lr,#8
    ldr     r1,=CDabtHandler
    mov     lr,pc
    mov     pc,r1  
    ldmia   sp!,{r0-r12,lr}
    subs    pc,lr,#4

FiqHnd:
    stmdb   sp!,{r0-r7,lr}
    ldr     r1,=CFiqHandler
    mov     lr,pc
    mov     pc,r1       
    ldmia   sp!,{r0-r7,lr}
    subs    pc,lr,#4
    
     

.section ".stext"


/*============================================================================
 * Execution starts here.
 * After a reset, the mode is ARM, Supervisor, interrupts disabled.
 *==========================================================================*/   
ResetHandler:

    /*========================================================================
     * Perform pre-initialization (enter supervisor mode,
     *  disable MMU and caches 
     *=======================================================================*/         
    bl      PreInit
    
    bl      low_level_init

    /*========================================================================
     * Copy the bootloader image from flash to RAM.  The image is configured
     * to run in RAM, but is stored in flash.  Absolute address references
     * should be avoided until the image has been relocated and the MMU enabled
     *
     *  check to see if the PC is already in RAM.  
    /*========================================================================
    
relocate:                         /* relocate Imag to RAM              */
    ands    r9, pc, #0xFF000000   /* see if we are in flash or in ram  */
    bne     setup_mmu_table       /* go ahead if we are already in ram */ 
    
    mov     r0,#0                 /* r0 <- source start address code   */
    ldr     r1,=_reset_entry  
                   
	mov	    r2, r1
	ldr   	r3,=_edata
	sub	    r2, r3, r2		      /* r2 <- size of code & data        */
	add	    r2, r0, r2	          /* r2 <- source end address         */    
	
copy_loop:
    ldmia   r0!, {r3-r10}         /* copy from source address [r0]    */
    stmia   r1!, {r3-r10}         /* copy to   target address [r1]    */
 	cmp	    r0, r2			      /* until source end addreee [r2]    */
	ble	    copy_loop    

         
    
    /*========================================================================
    ; Create MMU tables
    ; ======================================================================*/   
setup_mmu_table:    
    ldr     r1,=_USR_STACK      /* Set up a stack [for calling C code] */  
    ldr     r2,=_RAM_STARTADDRESS
    orr     sp,r1,r2    
    
    bl      MMU_Init 


    /*========================================================================
    ; Enable MMU
    ; ======================================================================*/
    ldr     r2,=REMAP
    mrc     p15,0,r0,c1,c0,0
    orr     r0,r0,#1
    mcr     p15,0,r0,c1,c0,0
    mov     pc,r2               /* Change address spaces */
    nop
    nop
    nop 
    
    
REMAP:
    /*========================================================================
    ; Enable I & D Cache
    ; DCache should be turned on after MMU is turned on.
    ; =======================================================================*/
    bl      MMU_EnableICache
    bl      MMU_EnableDCache    
      
cstartup:

    
/*
 * SysInitVars: Initialise the DATA and BSS sections.
 *
 * The DATA section is initialised by copying data from the end of the
 * ROM image (given by _etext) to the start of the RAM image
 * (given by _sdata), stopping when we reach _edata.
 * All data from _sbss to _ebss is then cleared to 0
 */

/*
 * Load up the linker defined values for the static data copy
 */
    ldr     r0, =_etext
    ldr     r1, =_sdata
    ldr     r3, =_sbss

/*
 * But first check whether we are trying to copy to the same address.
 * If so, this means that the image was linked as an application image
 * with the DATA section immediately following the CODE section.
 * Therefore there is nothing to copy since the data is already in place
 */
    cmp     r0, r1
    beq     1f

/*
 * Stop on Carry Set (ie R1 becomes >= R3).
 */
0:  cmp     r1, r3
    ldrcc   r2, [r0], #4
    strcc   r2, [r1], #4
    bcc     0b

/*
 * Clear remainder of data to _end to 0
 */
1:  ldr     r1, =_ebss
    mov     r2, #0
2:  cmp     r3, r1
    strcc   r2, [r3], #4
    bcc     2b


/*
 * Set up the stack 
 */
stack_setup:
    mrs     r0,cpsr
    bic     r0,r0,#MODE_MASK
    orr     r1,r0,#IRQ_MODE|NOINT
    msr     cpsr,r1            @IRQMode
    ldr     sp,=_IRQ_STACK

    orr     r1,r0,#FIQ_MODE|NOINT
    msr     cpsr,r1            @FIQMode
    ldr     sp,=_FIQ_STACK

    mrs     r0, cpsr
    bic     r0, r0, #MODE_MASK
    orr     r0, r0, #SVC_MODE
    bic     r0,r0,#0xc0     @enable IRQ and FIQ
    msr     cpsr, r0
    ldr     sp, =_USR_STACK
    
    /* USER mode has not be initialized.    */
    

/*
 * Embedded System should never return, if return then run again
 */
3: 
    bl  main
    b   3b     


       

/*=============================================================================
 * PreInit: perform CPU pre-initialization tasks (enter supervisor mode, 
 *          disable MMUs and caches, determine reset reason, etc.
 *===========================================================================*/  
PreInit:

    /*=========================================================================
     * Put the CPU in Supervisor mode (SVC) and disable IRQ and FIQ interrupts.
     *=======================================================================*/          
    mrs     r0,cpsr         /* set the cpu to SVC32 mode        */
    bic     r0,r0,#0x1f     /* (superviser mode, M=10011)       */
    orr     r0,r0,#0x13
    msr     cpsr,r0     
    
   
    /*=========================================================================
     * mask all interrupts & set all IRQ Mode
     *=======================================================================*/
    ldr     r0, =IC_BASE
    mov     r1, #0x00
    str     r1, [r0, #ICMR_OFFSET]
    str     r1, [r0, #ICLR_OFFSET]    
    
    
    /*========================================================================
     * Disable and clear caches
     *======================================================================*/  
    mrc     p15,0,r0,c1,c0,0
    bic     r0,r0,#0x1000           /* disable ICache   */
    bic     r0,r0,#0x000f           /* disable DCache, write buffer */  
                                    /* MMU and alignment faults     */
    mcr     p15,0,r0,c1,c0,0
    CPWAIT
    
    mov     r0,#0
    mcr     p15,0,r0,c7,c6,0        /* clear data cache     */
    CPWAIT  
    
    mov     pc, lr          



/*****************************************************************************/
/*                                                                           */
/* Interrupt routines                                                        */
/*                                                                           */
/*****************************************************************************/
enable_irq:
    mrs     r0,cpsr
    bic     r0,r0,#0x80
    msr     cpsr_c,r0
    
    mov     pc,lr 
    
    
disable_irq:        
    mrs     r0,cpsr
    orr     r0,r0,#0x80
    msr     cpsr_c,r0
    
    mov     pc,lr
    

.section ".bss" 

/*--------------------------------------------------------------------
;
;   Title     :  2410slib.s
;             :
;   Library   :
;             :
;   Developers:  MICROTIME MDS group
;             :
;   Purpose   :  MMU functions
; 	          :  
;             :
;   Limitation:
;             :
;   Note      :
;             :
;--------------------------------------------------------------------
;  modification history :
;--------------------------------------------------------------------
;   Version| mod. date: |
;   V1.0   | 09/07/2004 | First release
;   V2.0   | 03/25/2005 | Add MMU_SetExceptionAddrToFFFF0000() and MMU_SetExceptionAddrTo0()
;--------------------------------------------------------------------
;
; Note:
;
;       MICROTIME COMPUTER INC.
;
;-------------------------------------------------------------------*/


	.equ	NOINT,		0xc0    /* 1100 0000  */

/*
	.global SET_IF, WR_IF, CLR_IF	
*/	
	.global	MMU_EnableICache, MMU_DisableICache,MMU_EnableDCache,MMU_DisableDCache
	.global MMU_EnableAlignFault,MMU_DisableAlignFault,MMU_EnableMMU,MMU_DisableMMU
	.global MMU_SetExceptionAddrToFFFF0000,MMU_SetExceptionAddrTo0
	.global MMU_SetTTBase,MMU_SetDomain,
	.global MMU_SetFastBusMode,MMU_SetAsyncBusMode
	.global MMU_InvalidateIDCache,MMU_InvalidateICache,MMU_InvalidateICacheMVA,MMU_PrefetchICacheMVA
	.global MMU_InvalidateDCache,MMU_InvalidateDCacheMVA,MMU_CleanDCacheMVA,MMU_CleanInvalidateDCacheMVA
	.global MMU_CleanDCacheIndex,MMU_CleanInvalidateDCacheIndex,MMU_WaitForInterrupt
	.global MMU_InvalidateTLB,MMU_InvalidateITLB,MMU_InvalidateITLBMVA,MMU_InvalidateDTLB,MMU_InvalidateDTLBMVA
	.global MMU_SetDCacheLockdownBase,MMU_SetICacheLockdownBase,MMU_SetDTLBLockdown,MMU_SetITLBLockdown
	.global MMU_SetProcessId

.section ".mmulib"

 

/*====================================
; MMU Cache/TLB/etc on/off functions
;====================================*/
		.equ	R1_I,		(1<<12)
		.equ	R1_C,	    (1<<2)
		.equ	R1_A,    	(1<<1)
		.equ	R1_M,    	(1)
		.equ	R1_iA,   	(1<<31)
		.equ	R1_nF,   	(1<<30)
		.equ	R1_V,   	(1<<13)		

MMU_EnableICache:        
	mrc  	p15,0,r0,c1,c0,0
	orr  	r0,r0,#R1_I
	mcr  	p15,0,r0,c1,c0,0
	mov		pc,lr

MMU_DisableICache:       
	mrc  	p15,0,r0,c1,c0,0
	bic  	r0,r0,#R1_I
	mcr  	p15,0,r0,c1,c0,0
	mov		pc,lr


MMU_EnableDCache:        
	mrc  	p15,0,r0,c1,c0,0
	orr  	r0,r0,#R1_C
	mcr  	p15,0,r0,c1,c0,0
	mov		pc,lr


MMU_DisableDCache:       
	mrc  	p15,0,r0,c1,c0,0
	bic  	r0,r0,#R1_C
	mcr  	p15,0,r0,c1,c0,0
	mov		pc,lr

MMU_EnableAlignFault:
	mrc  	p15,0,r0,c1,c0,0
	orr  	r0,r0,#R1_A
	mcr  	p15,0,r0,c1,c0,0
	mov		pc,lr

MMU_DisableAlignFault:
	mrc  	p15,0,r0,c1,c0,0
	bic  	r0,r0,#R1_A
	mcr  	p15,0,r0,c1,c0,0
	mov		pc,lr

MMU_EnableMMU:
	mrc  	p15,0,r0,c1,c0,0
	orr  	r0,r0,#R1_M
	mcr  	p15,0,r0,c1,c0,0
	mov		pc,lr

MMU_DisableMMU:
	mrc  	p15,0,r0,c1,c0,0
	bic  	r0,r0,#R1_M
	mcr  	p15,0,r0,c1,c0,0
	mov		pc,lr
	
MMU_SetExceptionAddrToFFFF0000:
	mrc  	p15,0,r0,c1,c0,0
	orr  	r0,r0,#R1_V
	mcr  	p15,0,r0,c1,c0,0
	mov		pc,lr

MMU_SetExceptionAddrTo0:
	mrc  	p15,0,r0,c1,c0,0
	bic  	r0,r0,#R1_V
	mcr  	p15,0,r0,c1,c0,0
	mov		pc,lr	
	

/*
 * FCLK:HCLK= 1:1
 */
MMU_SetFastBusMode:
	mrc  	p15,0,r0,c1,c0,0
	bic  	r0,r0,#(R1_iA|R1_nF)
	mcr  	p15,0,r0,c1,c0,0
	mov		pc,lr

/*
 * FCLK:HCLK= 1:2
 */
MMU_SetAsyncBusMode:
	mrc  	p15,0,r0,c1,c0,0
	orr  	r0,r0,#(R1_nF|R1_iA)
	mcr  	p15,0,r0,c1,c0,0
	mov		pc,lr

/*=========================
 * Set TTBase
 *  ro=TTBase
 *========================*/
MMU_SetTTBase:
	mcr  	p15,0,r0,c2,c0,0
	mov		pc,lr

/*=========================
 * Set Domain
 *ro=domain 
 *========================*/
MMU_SetDomain:
	mcr  	p15,0,r0,c3,c0,0
	mov		pc,lr

/*=========================
 * ICache/DCache functions
 *========================*/
MMU_InvalidateIDCache:
	mcr  	p15,0,r0,c7,c7,0
	mov		pc,lr

MMU_InvalidateICache:
	mcr  	p15,0,r0,c7,c5,0
	mov		pc,lr

MMU_InvalidateICacheMVA: 
   /* r0=mva */
	mcr  	p15,0,r0,c7,c5,1
	mov		pc,lr
        
MMU_PrefetchICacheMVA:
   /* r0=mva */
	mcr  	p15,0,r0,c7,c13,1
	mov		pc,lr

MMU_InvalidateDCache:
	mcr  	p15,0,r0,c7,c6,0
	mov		pc,lr

MMU_InvalidateDCacheMVA:
   	/* r0=mva	*/
	mcr  	p15,0,r0,c7,c6,1
	mov		pc,lr

MMU_CleanDCacheMVA:
	/* r0=mva	*/
	mcr  	p15,0,r0,c7,c10,1
	mov		pc,lr

MMU_CleanInvalidateDCacheMVA:
	/* r0=mva	*/
	mcr  	p15,0,r0,c7,c14,1
	mov		pc,lr

MMU_CleanDCacheIndex:
	/* r0=index */	
	mcr  	p15,0,r0,c7,c10,2
	mov		pc,lr

MMU_CleanInvalidateDCacheIndex: 
	/* r0=index	*/
	mcr  	p15,0,r0,c7,c14,2
	mov		pc,lr

MMU_WaitForInterrupt:    
	mcr  	p15,0,r0,c7,c0,4
	mov		pc,lr

/*===============
 * TLB functions
 *==============*/
MMU_InvalidateTLB:       
	mcr  	p15,0,r0,c8,c7,0
	mov		pc,lr

MMU_InvalidateITLB:      
	mcr  	p15,0,r0,c8,c5,0
	mov		pc,lr
   
MMU_InvalidateITLBMVA:
   	/* ro=mva	*/
   	mcr  	p15,0,r0,c8,c5,1
	mov		pc,lr

MMU_InvalidateDTLB:
	mcr 	p15,0,r0,c8,c6,0
	mov		pc,lr

MMU_InvalidateDTLBMVA:
    /* r0=mva	*/
	mcr 	p15,0,r0,c8,c6,1
	mov		pc,lr

/*=================
 * Cache lock down
 *================*/
MMU_SetDCacheLockdownBase:
   	/* r0= victim & lockdown base	*/
	mcr  	p15,0,r0,c9,c0,0
	mov		pc,lr
        
MMU_SetICacheLockdownBase:
   	/* r0= victim & lockdown base	*/
	mcr  	p15,0,r0,c9,c0,1
	mov		pc,lr

/*=================
 * TLB lock down
 *================*/
MMU_SetDTLBLockdown:
   	/* r0= baseVictim	*/
	mcr  	p15,0,r0,c10,c0,0
	mov		pc,lr
        
MMU_SetITLBLockdown:
   	/* r0= baseVictim	*/
	mcr  	p15,0,r0,c10,c0,1
	mov		pc,lr

/*============
 * Process ID
 *============*/
MMU_SetProcessId:        
   	/* r0= pid */
	mcr  	p15,0,r0,c13,c0,0
	mov		pc,lr
        

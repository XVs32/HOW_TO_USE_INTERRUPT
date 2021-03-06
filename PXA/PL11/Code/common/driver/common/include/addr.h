//=============================================================================
// File Name : addr.h
// Function  : PXA270 Register MAP
// Program   :
// Date      : 01-20-2006
// Version   : 1.0
// History
// 
//=============================================================================

#ifndef __ADDR_PXA27X_H__
#define __ADDR_PXA27X_H__

#ifndef __OPTION_H__
#include    "common/include/option.h"
#endif

#ifndef __DEF_H__
#include    "common/include/def.h"
#endif


#define  CONFIG_PXA27x

#ifndef __COMMON_PXA_REGS_H
#include    "common/include/pxa-regs.h"
#endif 

#ifndef __COMMON_PXA_IRQS_H
#include    "common/include/pxa-irqs.h"
#endif

#define CS0_BASE 		0x00000000
#define CS1_BASE 		0x04000000
#define CS2_BASE 		0x08000000
#define CS3_BASE 		0x0c000000
#define CS4_BASE 		0x10000000
#define CS5_BASE 		0x14000000
#define PCC_BASE 		0x20000000


/*============================================================================================
;Create XScale-PXA270 Registers (Base Board)
;============================================================================================*/
//CPLD Registers
#define CPLD_INTPEND1 	(*(volatile unsigned short *)(CS4_BASE+0x2))
						//Write '1' to clear the corresponding pending bit
						//00 : CF_IDE		: R/W-(0)1 = CF IRQ Pending (IDE Mode)
						//01 : TOUCH		: R/W-(0)1 = Touch Screen Pending
						//02 : CF_IRQ		: R/W-(0)1 = CF IRQ Pending (IO Mode)
						//03 : CF_STS		: R/W-(0)1 = CF STSCHG Pending
						//04 : MIRQ0		: R/W-(0)1 = Master Bus IRQ(0) Pending
						//05 : MIRQ1		: R/W-(0)1 = Master Bus IRQ(1) Pending
						//06 : MIRQ2		: R/W-(0)1 = Master Bus IRQ(2) Pending
						//07 : MIRQ3		: R/W-(0)1 = Master Bus IRQ(3) Pending
#define CPLD_INTPEND2 	(*(volatile unsigned short *)(CS4_BASE+0x4))
						//Write '1' to clear the corresponding pending bit
						//00 : CF_I			: R/W-(0)1 = CF Inserted Pending
						//01 : CF_O			: R/W-(0)1 = CF Removed Pending
						//02 : MMC_I		: R/W-(0)1 = MMC Inserted Pending
						//03 : MMC_O		: R/W-(0)1 = MMC Removed Pending
						//04 : USB_I		: R/W-(0)1 = USB Device Cable Attached Pending
						//05 : USB_O		: R/W-(0)1 = USB Device Cable Detached Pending
						//06 : RSV			: R/W-(0)X   Should Be 0
						//07 : RSV			: R/W-(0)X   Should Be 0
#define CPLD_INTMASK1 	(*(volatile unsigned short *)(CS4_BASE+0x6))
						//Write '1' to disable the corresponding IRQ
						//00 : CF_IDE		: R/W-(1)1 = Mask CF IRQ (IDE Mode)
						//01 : TOUCH		: R/W-(1)1 = Mask Touch Screen IRQ
						//02 : CF_IRQ		: R/W-(1)1 = Mask CF IRQ (IO Mode)
						//03 : CF_STS		: R/W-(1)1 = Mask CF STSCHG IRQ
						//04 : MIRQ0		: R/W-(1)1 = Mask Master Bus IRQ(0) 
						//05 : MIRQ1		: R/W-(1)1 = Mask Master Bus IRQ(1) 
						//06 : MIRQ2		: R/W-(1)1 = Mask Master Bus IRQ(2) 
						//07 : MIRQ3		: R/W-(1)1 = Mask Master Bus IRQ(3) 
#define CPLD_INTMASK2 	(*(volatile unsigned short *)(CS4_BASE+0x8))
						//Write '1' to disable the corresponding IRQ
						//00 : CF_I			: R/W-(1)1 = Mask CF Inserted IRQ
						//01 : CF_O			: R/W-(1)1 = Mask CF Removed IRQ
						//02 : MMC_I		: R/W-(1)1 = Mask MMC Inserted IRQ
						//03 : MMC_O		: R/W-(1)1 = Mask MMC Removed IRQ
						//04 : USB_I		: R/W-(1)1 = Mask USB Device Cable Attached IRQ
						//05 : USB_O		: R/W-(1)1 = Mask USB Device Cable Detached IRQ
						//06 : RSV			: R/W-(1)X   Should Be 1
						//07 : RSV			: R/W-(1)X   Should Be 1
#define CPLD_CTRL1		(*(volatile unsigned short *)(CS4_BASE+0xA))
						//00 : USB_FS		: R/W-(0)1 = D+ Pull Hi 1.5K (Attached)
						//01 : FF_UART		: R/W-(1)1 = COM2 (FF-UART) Enable
						//02 : CF_PWR		: R/W-(0)1 = CF Power ON
						//03 : CF_RST		: R/W-(0)1 = CF Reset
						//04 : ROM_WP		: R/W-(1)0 = SOM-PXA270 Flash Write Protect
						//05 : LCD_PWR		: R/W-(0)1 = TFT-LCD Power ON
						//06 : ETH_RST		: R/W-(0)1 = Reset LAN91C111
						//07 : SB0			: R/W-(0)X   Should Be 0
#define CPLD_CTRL2		(*(volatile unsigned short *)(CS4_BASE+0xC))
						//00 : EMU_FA		: R/W-(1)0 = Use KEY(0) to emulation nBATT_FAULT
						//							 	 Use KEY(1) to emulation nVDD_FAULT
						//01 : SB1			: R/W-(1)X   Should Be 1
						//02 : N_MIRQ3		: R/W-(1)0 = Polarity change on MIRQ 
						//03 : ADACK		: R/W-(1)1 = Auto DACK
						//04 : LED0			: R/W-(1)0 = D1 On
						//05 : LED1			: R/W-(1)0 = D2 On
						//06 : LED2			: R/W-(1)0 = D3 On
						//07 : LED3			: R/W-(1)0 = D4 On
#define CPLD_CTRL3		(*(volatile unsigned short *)(CS4_BASE+0x1000000))
						//00 : SB0			: W-(0)X   Should Be 0
						//...				: W-(0)X   Should Be 0
						//07 : SB0			: W-(0)X   Should Be 0
#define CPLD_STATUS1 	(*(volatile unsigned short *)(CS4_BASE+0x0))
						//00 : KEY0			: State of S1
						//01 : KEY1			: State of S2
						//02 : MMC_WP		: State of MMC/SD WP Pin
						//03 : MMC_CD		: State of MMC/SD nCD Pin
						//04 : Version		: Version Number
						//05 : Version		: 0001 = Ver 1.0
						//06 : Version		: 0010 = Ver 2.0
						//07 : Version		: ...
#define CPLD_STATUS2 	(*(volatile unsigned short *)(CS4_BASE+0xE))
						//00 : USBC_IRQ		: USB Device Cable Status, (1)=Cable Inserted
						//01 : CF_nINPACK	: State of CF nINPACK Pin
						//02 : CF_nCD1		: State of CF CF_nCD1 Pin
						//03 : CF_RDY		: State of CF CF_RDY Pin
						//04 : CF_BVD1		: State of CF CF_BVD1 Pin
						//05 : CF_BVD2		: State of CF CF_BVD2 Pin
						//06 : RSV			: Reserved
						//07 : RSV			: Reserved


//LAN91C111 Registers
#define ETH_R_TCR			(*(volatile unsigned short *)(CS1_BASE+0x300+0x0))
#define ETH_R_EPH_STATUS	(*(volatile unsigned short *)(CS1_BASE+0x300+0x2))
#define ETH_R_RCR			(*(volatile unsigned short *)(CS1_BASE+0x300+0x4))
#define ETH_R_COUNTER		(*(volatile unsigned short *)(CS1_BASE+0x300+0x6))
#define ETH_R_MIR			(*(volatile unsigned short *)(CS1_BASE+0x300+0x8))
#define ETH_R_RPCR			(*(volatile unsigned short *)(CS1_BASE+0x300+0xA))
#define ETH_R_RESERVED		(*(volatile unsigned short *)(CS1_BASE+0x300+0xC))
#define ETH_R_BANK			(*(volatile unsigned short *)(CS1_BASE+0x300+0xe))
#define ETH_R_BASE			(*(volatile unsigned short *)(CS1_BASE+0x300+0x2))

//PXA270 PCMCIA Registers
#define PCC_S0CMS_BASE 	(0x0C000000)
#define PCC_TASK_BASE 	(PCC_BASE+PCC_S0CMS_BASE+0x0000)
#define PCC_STATUS_BASE	(PCC_BASE+PCC_S0CMS_BASE+0x0200)
#define PCC_BYTDATREG   (*(volatile unsigned short *)(PCC_TASK_BASE+0x0000)) /* DATA read/write */
#define PCC_ERRFEAREG   (*(volatile unsigned char *)(PCC_TASK_BASE+0x0001)) /* read error/write feature */
#define PCC_SECTCOUNT   (*(volatile unsigned char *)(PCC_TASK_BASE+0x0002)) /* sector count */
#define PCC_SECTORNO    (*(volatile unsigned char *)(PCC_TASK_BASE+0x0003)) /* sector number */
#define PCC_CYLINDLOW   (*(volatile unsigned char *)(PCC_TASK_BASE+0x0004)) /* cylinder low */
#define PCC_CYLINDHI    (*(volatile unsigned char *)(PCC_TASK_BASE+0x0005)) /* cylinder high */
#define PCC_SCARDHEAD   (*(volatile unsigned char *)(PCC_TASK_BASE+0x0006)) /* select card/head */
#define PCC_STATCOMMD   (*(volatile unsigned char *)(PCC_TASK_BASE+0x0007)) /* read status/write command */
#define PCC_CONTROL		(*(volatile unsigned char *)(PCC_TASK_BASE+ATA_CONTROL_OFFSET))	/* control */



/*============================================================================================
;Master Bus Peripheral control registers (Main Board)
;============================================================================================*/
#define ECS0_BASE 		(CS2_BASE+0x00000000)	//Creator main I/O
#define ECS1_BASE 		ECS0_BASE				//Unuse
#define ECS2_BASE 		ECS0_BASE				//Unuse
#define RCS0_BASE 		(CS2_BASE+0x01000000)	//Creator 2M FLASH
#define ECS3_BASE 		(CS2_BASE+0x02000000) 	//FPGA board I/O
#define RCS3_BASE 		(CS2_BASE+0x03000000)	//FPGA board SRAM

#define CF_TASK_BASE 	(ECS0_BASE+0x0000)	/* CF_nCS0 */
#define CF_STATUS_BASE	(ECS0_BASE+0x0200)	/* CF_nCS1 : not used */

#define ATA_BYTDAT_OFFSET 		(0) 		/* DATA read/write */
#define ATA_ERRFEA_OFFSET   	(2) 		/* read error/write feature */
#define ATA_SECTCOUNT_OFFSET    (4) 		/* sector count */
#define ATA_SECTORNO_OFFSET     (6)			/* sector number */
#define ATA_CYLINDLOW_OFFSET    (8)			/* cylinder low */
#define ATA_CYLINDHI_OFFSET     (0xa)		/* cylinder high */
#define ATA_SCARDHEAD_OFFSET    (0xc)		/* select card/head */
#define ATA_STATCOMMD_OFFSET    (0xe)
#define ATA_CONTROL_OFFSET		(0X200+0xc)	/* control */

#define ATA_BYTDATREG   (*(volatile unsigned short *)(CF_TASK_BASE+0x0000)) /* DATA read/write */
#define ATA_ERRFEAREG   (*(volatile unsigned short *)(CF_TASK_BASE+0x0002)) /* read error/write feature */
#define ATA_SECTCOUNT   (*(volatile unsigned short *)(CF_TASK_BASE+0x0004)) /* sector count */
#define ATA_SECTORNO    (*(volatile unsigned short *)(CF_TASK_BASE+0x0006)) /* sector number */
#define ATA_CYLINDLOW   (*(volatile unsigned short *)(CF_TASK_BASE+0x0008)) /* cylinder low */
#define ATA_CYLINDHI    (*(volatile unsigned short *)(CF_TASK_BASE+0x000A)) /* cylinder high */
#define ATA_SCARDHEAD   (*(volatile unsigned short *)(CF_TASK_BASE+0x000C)) /* select card/head */
#define ATA_STATCOMMD   (*(volatile unsigned short *)(CF_TASK_BASE+0x000E)) /* read status/write command */
#define ATA_CONTROL		(*(volatile unsigned short *)(CF_TASK_BASE+ATA_CONTROL_OFFSET))	/* control */

#define USB_DATA 		(*(volatile unsigned short *)(ECS0_BASE+0x0400))
#define USB_CMD 		(*(volatile unsigned short *)(ECS0_BASE+0x0402))
#define CCM_DATA 		(*(volatile unsigned short *)(ECS0_BASE+0x0600))
#define LCD_CMD 		(*(volatile unsigned short *)(ECS0_BASE+0x0800))
#define LCD_DATA 		(*(volatile unsigned short *)(ECS0_BASE+0x0802))
#define CODEC_DATA 		(*(volatile unsigned short *)(ECS0_BASE+0x0A00))
#define IO_REG0			(*(volatile unsigned short *)(ECS0_BASE+0x0C00))
#define IO_REG1 		(*(volatile unsigned short *)(ECS0_BASE+0x0C02))	
#define IO_REG2 		(*(volatile unsigned short *)(ECS0_BASE+0x0C04))	
#define CPLD_CTRL 		(*(volatile unsigned short *)(ECS0_BASE+0x0E00))	/* Write */
						//00	: IO_nRST
						//01	: AIC_ON
						//02	: EXPTM1
						//03	: EXPTM2
						//04	: FPGA_nPGM
						//05	: FPGA_CCLK
						//06	: IRQ3_SEL	0 : IRQ3=CCM(CMOS sensor)
						//					1 : IRQ3=X_nINT(FPGA Slave Bus)
						//07	: DMA_SEL	0 : DMA0=CODEC_nDRQ, 	DMA1=X_nDRQ
						//					1 : DMA0=USB_DRQ, 		DMA1=X_nDRQ 
						
#define CPLD_STATUS		(*(volatile unsigned short *)(ECS0_BASE+0x0E00))	/* Read */
						//00 	: EE_DO
						//01 	: USB_nEOT
						//02 	: USB_ON
						//03 	: NA
						//04 	: CCD_nRDY
						//07-05 : 0
						//15-08	: Version (0x10=V1.0, 0x11=V1.1, ...)

#define IRQ_SELECT 		(*(volatile unsigned short *)(ECS0_BASE+0x0E02))	/* For CPLD(U16) V1.1 or later */
						//02-00	: IRQ0_MUX (see IRQ mapping)
						//05-03	: IRQ1_MUX (see IRQ mapping)
						//08-06	: IRQ2_MUX (see IRQ mapping)
						//11-09	: IRQ3_MUX (see IRQ mapping)
						//12	: INV_CF_IRQ 	: (0)1 => CF_IRQ Inversed	/* For CPLD(U16) V1.2 or later */
						//13	: IRQ3_MODE		: (0)1 => IRQ3 = Function of IRQ3_PEND and IRQ3_MASK
						//14	: IRQ0_MODE		: (0)0 => IRQ0 = Main Board PHY_nINT(U19:PHY)
						//							 1 => IRQ0 = Main Board CF_IRQ
						//15	: IRQ_DEFAULT (0=use default)
						//		: 0 : 	IRQ0=PHY_nINT(U19),		IRQ1=USB_nINT(U25)
						//				IRQ2=CODEC_IRQ(U21),	IRQ3=CCM or X_nINT (CPLD_CTRL bit6)
						//		: 1 :	Controlled by IRQ?_MUX
						
						//IRQ mapping :	000 -> PHY_nINT(U19:PHY)	001 -> USB_nINT(U25:USB)
						//				010 -> CODEC_IRQ(U21:AIC)	011 -> X_nINT(FPGA Slave Bus)
						//				100 -> CCM (CMOS sensor)	101 -> RTC_nINT(U32:RTC)
						//				110 -> Reserved (J4:CF card)

#define DMA_SELECT 		(*(volatile unsigned short *)(ECS0_BASE+0x0E04))	/* For CPLD(U16) V1.1 or later */
						//01-00	: DMA0_MUX (see IRQ mapping)
						//02-01	: DMA1_MUX (see IRQ mapping)
						//07	: DMA_DEFAULT (0=use default)
						//		: 0 : 	DMA0=CODEC_nDRQ, 	DMA1=X_nDRQ (when DMA_SEL(CPLD_CTRL bit7)=0)
						//				DMA0=USB_nDRQ, 		DMA1=X_nDRQ (when DMA_SEL(CPLD_CTRL bit7)=1)
						//		: 1 : 	Controlled by DMA?_MUX
						
						//DMA mapping :	00 -> CODEC_nDRQ(U21:AIC)	01 -> USB_nDRQ(U25:USB)
						//				10 -> X_nDRQ(FPGA Slave Bus
#define IRQ3_PEND 		(*(volatile unsigned short *)(ECS0_BASE+0x0A02))
						//Write '1' to clear the corresponding pending bit
						//00 	: CF_IRQ		: R/W-(0)1 = CF IRQ Pending
						//01 	: X_nINT		: R/W-(0)1 = Slave Bus IRQ Pending
						//02-15 : Reserved		: R/W-(0)X   Should Be 0
#define IRQ3_MASK 		(*(volatile unsigned short *)(ECS0_BASE+0x0A04))
						//Write '1' to disable the corresponding IRQ
						//00 	: CF_IRQ		: R/W-(1)1 = Mask CF_IRQ IRQ
						//01 	: X_nINT		: R/W-(1)1 = Mask Slave Bus IRQ
						//02-15 : Reserved		: R/W-(1)X   Should Be 1

/*============================================================================================
;Slave Bus FPGA Board Control Registers
;============================================================================================*/
#define FPGA_CTRL 		(*(volatile unsigned short *)(ECS3_BASE+0x0000))	//CD_PORT & ADDRL=0 & WR
#define FPGA_STATUS 	(*(volatile unsigned short *)(ECS3_BASE+0x0000))	//CD_PORT & ADDRL=0 & RD
#define SCAN_OUT 		(*(volatile unsigned short *)(ECS3_BASE+0x0002))	//CS_PORT & ADDRL=1 & WR
#define FPGA_LED_HUHU	(*(volatile unsigned short *)(ECS3_BASE+0x0004))	//CS_PORT & ADDRL=2 & WR
#define CODEC_DATA_FPGA	(*(volatile unsigned short *)(ECS3_BASE+0x0200))	//CS_AIC  & ADDRL=X & RD/WR


/*============================================================================================
;Slave Bus DSP5502 Board Control Registers
;============================================================================================*/ 
#define REG_HPIC	    (*(volatile unsigned short *)(ECS3_BASE+0x0000))
#define REG_HPID_AINC	(*(volatile unsigned short *)(ECS3_BASE+0x0002))
#define REG_HPIA	    (*(volatile unsigned short *)(ECS3_BASE+0x0004))
#define REG_HPID	    (*(volatile unsigned short *)(ECS3_BASE+0x0006))
#define REG_SLAVE_S     (*(volatile unsigned short *)(ECS3_BASE+0x0010))
#define REG_SLAVE_C     (*(volatile unsigned short *)(ECS3_BASE+0x0018))


/*============================================================================================
;Slave Bus GPRS Board Control Registers
;============================================================================================*/ 
#define GPRS_CTRL1	    (*(volatile unsigned short *)(RCS3_BASE+(0x7000<<1)))
#define GPRS_CTRL2    	(*(volatile unsigned short *)(RCS3_BASE+(0x7001<<1)))
#define GPRS_CTRL3	    (*(volatile unsigned short *)(RCS3_BASE+(0x7002<<1)))
#define GPRS_STATUS1    (*(volatile unsigned short *)(RCS3_BASE+(0x7000<<1)))
#define GPRS_STATUS2    (*(volatile unsigned short *)(RCS3_BASE+(0x7001<<1)))
#define GPRS_STATUS3    (*(volatile unsigned short *)(RCS3_BASE+(0x7002<<1)))



//
//  Creator XScale-PXA270: Creator Main Board Level Registers
//
typedef struct 
{
	volatile U16  master_status1;	// 00000000 -> 00000001
	volatile U16  master_intpend1;	// 00000002 -> 00000003
    volatile U16  master_intpend2;	// 00000004 -> 00000005
    volatile U16  master_intmask1;	// 00000006 -> 00000007
    volatile U16  master_intmask2;  // 00000008 -> 00000009
    volatile U16  master_ctrl1;     // 0000000A -> 0000000B
    volatile U16  master_ctrl2;		// 0000000C -> 0000000D
    volatile U16  master_status2;   // 0000000E -> 0000000F
    volatile U16  rsvd0[(0X01000000-0X10)>>1];     // 00000010 -> 00FFFFFF    
    volatile U16  master_ctrl3;       // 01000000 -> 01000001 write only
} base_regs_t, *p_base_regs_t;



//
//  Creator XScale-PXA270: Create XScale-PXA270 board Registers
//
typedef struct 
{
    volatile U16     ata_bytdatreg;     // 00000000 -> 00000001 
    volatile U16     ata_errfeareg;     // 00000002 -> 00000003
    volatile U16     ata_sectcount;     // 00000004 -> 00000005
    volatile U16     ata_sectorno;      // 00000006 -> 00000007
    volatile U16     ata_cylindlow;     // 00000008 -> 00000009
    volatile U16     ata_cylindhi;      // 0000000A -> 0000000B
    volatile U16     ata_scardhead;     // 0000000C -> 0000000D     
    volatile U16     ata_statcommd;     // 0000000E -> 0000000F
    volatile U16     rsvd0[0XFE];       // 00000010 -> 0000020B
    volatile U16     ata_control;	    // 0000020C -> 0000020D        
    volatile U16     rsvd1[0XF9];       // 0000020E -> 000003FF    
    volatile U16     usb_data;          // 00000400 -> 00000401
    volatile U16     usb_cmd;           // 00000402 -> 00000403 write only
    volatile U16     rsvd2[0XFE];       // 00000404 -> 000005FF 
    volatile U16     ccm_data; 		    // 00000600 -> 00000601 read  only
    volatile U16     rsvd3[0XFF];       // 00000602 -> 000007FF
    volatile U16     lcd_cmd;           // 00000800 -> 00000801 write only
//  volatile U16 lcd_status;            // 00000800 -> 00000801 read  only        
    volatile U16     lcd_data; 	        // 00000802 -> 00000803
    volatile U16     rsvd4[0XFE];       // 00000804 -> 000009FF    
    volatile U16     codec_data;        // 00000A00 -> 00000A01
    volatile U16     irq3_pend;         // 00000A02 -> 00000A03
    volatile U16     irq3_mask;         // 00000A04 -> 00000A05    
    volatile U16     rsvd5[0XFD];       // 00000A06 -> 00000BFF        
    volatile U16     io_reg0;           // 00000C00 -> 00000C01 write only & share
    volatile U16     io_reg1;           // 00000C02 -> 00000C03 read  only	
    volatile U16     io_reg2;           // 00000C04 -> 00000C05 write only & share	
    volatile U16     rsvd6[0XFD];       // 00000C06 -> 00000DFF     
    volatile U16     cpld_ctrl;         // 00000E00 -> 00000E01 write register
//  volatile U16     cpld_status;       // 00000E00 -> 00000E01 Read  register            
    volatile U16     irq_select;        // 00000E02 -> 00000E03 write only
    volatile U16     dma_select;        // 00000E04 -> 00000E05 write only
} main_regs_t, *p_main_regs_t;


typedef struct {
    p_base_regs_t       p_base_regs;
    p_main_regs_t       p_main_regs;     	
    
    /*
     * creator board write only register
     */ 
    union {
        struct  {
            U8     hi_byte;   // bit0..bit7         	
            U8     _7segment;  // 7 segment on creator board           	
        } fields; 
        U16        value ;
    } io_reg0 ;      
    
    union {
        struct  {
            U8     scan;    // scan keypad creator board           	
            U8     led;     // D16..D9 on creator board
        } fields; 
        U16        value ;
    } io_reg2 ;        
    
    U16               cpld_ctrl ;

    
    /*
     * pxa base board write only register
     */     
    U16               master_ctrl3 ;
    
    /*
     * cpld verstion information
     */ 
    U16               main_cpld_version ;    
    U16               base_cpld_version ;  
} creator_regs_t, *p_creator_regs_t ;	
// VA


#define CPLD_1_VIRT			    (CS4_BASE)						
#define CPLD_REG(x)             (*((volatile unsigned short *)(CPLD_1_VIRT + (x))))


#define CPLD_STATUS1_VIRT 		CPLD_REG(0x0)
#define CPLD_INTPEND1_VIRT 		CPLD_REG(0x2)
#define CPLD_INTPEND2_VIRT 		CPLD_REG(0x4)
#define CPLD_INTMASK1_VIRT 		CPLD_REG(0x6)
#define CPLD_INTMASK2_VIRT 		CPLD_REG(0x8)
#define CPLD_CTRL1_VIRT			CPLD_REG(0xA)
#define CPLD_CTRL2_VIRT			CPLD_REG(0xC)
#define CPLD_STATUS2_VIRT 		CPLD_REG(0xE)
#define CPLD_IO1_VIRT	 		CPLD_REG(0x0)	/* TODO */
#define CPLD_IO2_VIRT	 		CPLD_REG(0x2)	/* TODO */	

#define MASTER_STATUS1          CPLD_STATUS1_VIRT
#define MASTER_INTPEND1     	CPLD_INTPEND1_VIRT
#define MASTER_INTPEND2     	CPLD_INTPEND2_VIRT
#define MASTER_INTMASK1    		CPLD_INTMASK1_VIRT
#define MASTER_INTMASK2    		CPLD_INTMASK2_VIRT
#define MASTER_CTRL1      		CPLD_CTRL1_VIRT
#define MASTER_CTRL2   			CPLD_CTRL2_VIRT
#define MASTER_STATUS2     		CPLD_STATUS2_VIRT
#define MASTER_IO1     	 		CPLD_IO1_VIRT	/* TODO */
#define MASTER_IO2     	 		CPLD_IO2_VIRT	/* TODO */
#define MASTER_IRQ3_PEND     	(IRQ3_PEND)
#define MASTER_IRQ3_MASK     	(IRQ3_MASK)


#define VA_CS0_BASE             0x18000000   
#define VA_CREATOR_FLASH        (RCS0_BASE) 


#define MaskInterrupt(irq)      (ICMR &= ~(1 << (irq)));
#define UnMaskInterrupt(irq)    (ICMR |= (1<<irq));



#endif // __ADDR_PXA27X_H__

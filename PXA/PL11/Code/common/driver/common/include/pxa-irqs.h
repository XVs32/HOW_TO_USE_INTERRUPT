/*
 *  common/irqs.h
 *
 */
 
#ifndef __COMMON_PXA_IRQS_H 
#define __COMMON_PXA_IRQS_H


#define PXA_IRQ_SKIP    0


#define PXA_IRQ(x)  ((x) - PXA_IRQ_SKIP)

#define IRQ_SSP3    PXA_IRQ(0)  /* SSP3 service request */
#define IRQ_MSL     PXA_IRQ(1)  /* MSL Interface interrupt */
#define IRQ_USBH2   PXA_IRQ(2)  /* USB Host interrupt 1 (OHCI) */
#define IRQ_USBH1   PXA_IRQ(3)  /* USB Host interrupt 2 (non-OHCI) */
#define IRQ_KEYPAD  PXA_IRQ(4)  /* Key pad controller */
#define IRQ_MEMSTK  PXA_IRQ(5)  /* Memory Stick interrupt */
#define IRQ_PWRI2C  PXA_IRQ(6)  /* Power I2C interrupt */
#define IRQ_HWUART  PXA_IRQ(7)  /* HWUART Transmit/Receive/Error (PXA26x) */
#define IRQ_OST_4_11    PXA_IRQ(7)  /* OS timer 4-11 matches (PXA27x) */
#define IRQ_GPIO0   PXA_IRQ(8)  /* GPIO0 Edge Detect */
#define IRQ_GPIO1   PXA_IRQ(9)  /* GPIO1 Edge Detect */
#define IRQ_GPIO_2_x    PXA_IRQ(10) /* GPIO[2-x] Edge Detect */
#define IRQ_USB     PXA_IRQ(11) /* USB Service */
#define IRQ_PMU     PXA_IRQ(12) /* Performance Monitoring Unit */
#define IRQ_I2S     PXA_IRQ(13) /* I2S Interrupt */
#define IRQ_AC97    PXA_IRQ(14) /* AC97 Interrupt */
#define IRQ_ASSP    PXA_IRQ(15) /* Audio SSP Service Request (PXA25x) */
#define IRQ_USIM    PXA_IRQ(15)     /* Smart Card interface interrupt (PXA27x) */
#define IRQ_NSSP    PXA_IRQ(16) /* Network SSP Service Request (PXA25x) */
#define IRQ_SSP2    PXA_IRQ(16) /* SSP2 interrupt (PXA27x) */
#define IRQ_LCD     PXA_IRQ(17) /* LCD Controller Service Request */
#define IRQ_I2C     PXA_IRQ(18) /* I2C Service Request */
#define IRQ_ICP     PXA_IRQ(19) /* ICP Transmit/Receive/Error */
#define IRQ_STUART  PXA_IRQ(20) /* STUART Transmit/Receive/Error */
#define IRQ_BTUART  PXA_IRQ(21) /* BTUART Transmit/Receive/Error */
#define IRQ_FFUART  PXA_IRQ(22) /* FFUART Transmit/Receive/Error*/
#define IRQ_MMC     PXA_IRQ(23) /* MMC Status/Error Detection */
#define IRQ_SSP     PXA_IRQ(24) /* SSP Service Request */
#define IRQ_DMA     PXA_IRQ(25) /* DMA Channel Service Request */
#define IRQ_OST0    PXA_IRQ(26) /* OS Timer match 0 */
#define IRQ_OST1    PXA_IRQ(27) /* OS Timer match 1 */
#define IRQ_OST2    PXA_IRQ(28) /* OS Timer match 2 */
#define IRQ_OST3    PXA_IRQ(29) /* OS Timer match 3 */
#define IRQ_RTC1Hz  PXA_IRQ(30) /* RTC HZ Clock Tick */
#define IRQ_RTCAlrm PXA_IRQ(31) /* RTC Alarm */

#ifdef CONFIG_PXA27x
#define IRQ_TPM     PXA_IRQ(32) /* TPM interrupt */
#define IRQ_CAMERA  PXA_IRQ(33) /* Camera Interface */

#define PXA_INTERNAL_IRQS 34
#else
#define PXA_INTERNAL_IRQS 32
#endif

#define GPIO_2_x_TO_IRQ(x)              PXA_IRQ((x) - 2 + PXA_INTERNAL_IRQS)
#define IRQ_GPIO(x) (((x) < 2) ? (IRQ_GPIO0 + (x)) : GPIO_2_x_TO_IRQ(x))

#define IRQ_TO_GPIO_2_x(i)              ((i) - IRQ_GPIO(2) + 2)
#define IRQ_TO_GPIO(i)  (((i) < IRQ_GPIO(2)) ? ((i) - IRQ_GPIO0) : IRQ_TO_GPIO_2_x(i))

#if defined(CONFIG_PXA25x)
#define PXA_LAST_GPIO   80
#elif defined(CONFIG_PXA27x)
#define PXA_LAST_GPIO   127
#endif

/*
 * The next 16 interrupts are for board specific purposes.  Since
 * the kernel can only run on one machine at a time, we can re-use
 * these.  If you need more, increase IRQ_BOARD_END, but keep it
 * within sensible limits.
 */
#define IRQ_BOARD_START     (IRQ_GPIO(PXA_LAST_GPIO) + 1)
#define IRQ_BOARD_END       (IRQ_BOARD_START + 16)


/*
 * Figure out the MAX IRQ number.
 *
 */

#define NR_IRQS         (CREATOR_LAST_IRQ + 1)


#define CREATOR_IRQ(x)      (IRQ_BOARD_START + (x))
#define CREATOR_ETHERNET_IRQ    CREATOR_IRQ(0)
#define CREATOR_TOUCH_IRQ    CREATOR_IRQ(1) 
#define CREATOR_CF_IRQ       CREATOR_IRQ(2) 
#define CREATOR_STSCHG_IRQ   CREATOR_IRQ(3)
#define CREATOR_IO_XIRQ0_IRQ CREATOR_IRQ(4)
#define CREATOR_IO_XIRQ1_IRQ CREATOR_IRQ(5)
#define CREATOR_IO_XIRQ2_IRQ CREATOR_IRQ(6)
#define CREATOR_IO_XIRQ3_IRQ CREATOR_IRQ(7)
#define CREATOR_CFI_IRQ      CREATOR_IRQ(8)
#define CREATOR_CFO_IRQ      CREATOR_IRQ(9)
#define CREATOR_MMCI_IRQ     CREATOR_IRQ(10)
#define CREATOR_MMCO_IRQ     CREATOR_IRQ(11)
#define CREATOR_USBI_IRQ     CREATOR_IRQ(12)
#define CREATOR_USBO_IRQ     CREATOR_IRQ(13)
#define CREATOR_MMCWP_IRQ    CREATOR_IRQ(14)
#define CREATOR_MISC_IRQ     CREATOR_IRQ(15)
#define CREATOR_OST_4_IRQ    CREATOR_IRQ(16)
#define CREATOR_OST_5_IRQ    CREATOR_IRQ(17)
#define CREATOR_OST_6_IRQ    CREATOR_IRQ(18)
#define CREATOR_OST_7_IRQ    CREATOR_IRQ(19)
#define CREATOR_OST_8_IRQ    CREATOR_IRQ(20)
#define CREATOR_OST_9_IRQ    CREATOR_IRQ(21)
#define CREATOR_OST_10_IRQ   CREATOR_IRQ(22)
#define CREATOR_OST_11_IRQ   CREATOR_IRQ(23)
#define CREATOR_IO_XIRQ3_EXT_CF_IRQ     CREATOR_IRQ(24)
#define CREATOR_IO_XIRQ3_EXT_SLAVE_IRQ  CREATOR_IRQ(25)
#define CREATOR_IO_XIRQ3_EXT_RTC_IRQ    CREATOR_IRQ(26)
#define CREATOR_IO_XIRQ3_EXT_CCD_IRQ    CREATOR_IRQ(27)
#define CREATOR_LAST_IRQ     CREATOR_IO_XIRQ3_EXT_CCD_IRQ

#define CREATOR_IRQ_BIT(x)   (((x) <= (CREATOR_IO_XIRQ3_IRQ)) ? (x-CREATOR_ETHERNET_IRQ) : (x-CREATOR_CFI_IRQ))

#define CREATOR_FPGA_IRQ     CREATOR_IO_XIRQ3_IRQ 

#endif /* __COMMON_PXA_IRQS_H */
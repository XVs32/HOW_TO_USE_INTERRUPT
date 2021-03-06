// --------------------------------------------------------------------
//
//   Title     :  irq.c
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  irq routines for Creator XScale-PXA270 Board
//             :
//   Limitation:
//             :
//   Note      :
//             :
// --------------------------------------------------------------------
//   modification history :
// --------------------------------------------------------------------
//   Version| mod. date: |
//   V1.0   | 12/11/2006 | First Release
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
#include <string.h>

#include "irq/include/irq.h"
#include "common/include/pxa-irqs.h"
#include "common/include/pxa-regs.h"
#include "common/include/creator_io.h"




/*************************************************************************
Constant define
*************************************************************************/
//#define DEBUG                      1

#ifdef IRQ_INT_NO
#undef IRQ_INT_NO
#endif
#define IRQ_INT_NO                 NR_IRQS

/*
* This table holds the list of irq handlers and is indexed by interrupt
* priority - 1. Therefore each interrupt must be assigned a unique priority
* in the range 1-17 in the irq_priority_table below.
*/



/*************************************************************************
Function prototypes
*************************************************************************/
void mt_printf (__const char *fmt,...);

static void __set_bit (int nr, volatile U32 *p);
static void __clear_bit (int nr, volatile U32 *p);
static void pxa_init_irq (void);



/*************************************************************************
Variable define
*************************************************************************/
static struct irq_desc irq_table[IRQ_INT_NO];
struct irq_desc *p_irq_desc=irq_table;



int 
register_irq (U16 irqno, isrfun handler, char *name, void *pVoid)
{ 
        if (irqno < IRQ_INT_NO){
            if (!irq_table[irqno].handler){
                irq_table[irqno].handler = handler;     
                strncpy(irq_table[irqno].name, name, IRQ_NAME_SIZE);
                irq_table[irqno].pVoid = pVoid;
                irq_table[irqno].irqno = irqno;
                return (1);
            }else{
            }
        }   
        
        return (0);
}




void 
unregister_irq (U16 irqno, char* name)
{
        /* check for owneship of the irq and then unregister it */
        if (!strncmp(irq_table[irqno].name, name, 
             sizeof(irq_table[irqno].name))){
                
            irq_table[irqno].handler=NULL;
            irq_table[irqno].name[0]='\0';
            irq_table[irqno].pVoid = NULL;
        }
        else{
        }
}



void 
CIrqHandler (void)
{ 
        U32  value ;
        int  irq_no, i;
        
#if DEBUG
        mt_printf("\n\nEntry IRQ\n"); 
#endif            
   
        irq_no = 0;   
        value = (ICIP & ICMR) ;           
        while (value) {                         
            if (value & 1){                  
                if (irq_table[irq_no].handler){
                    irq_table[irq_no].handler(irq_no, 
                                              &irq_table[irq_no], 
                                              irq_table[irq_no].pVoid);
                } 
            }
            value >>= 1;
            irq_no++;           
        }   
        
        irq_no = 32;                
        value = (ICIP2 & ICMR2);           
        for (i=0; i < 2; i++){
            if (!value)
                break ;
                                            
            if (value & 1){                  
                if (irq_table[irq_no].handler){
                    irq_table[irq_no].handler(irq_no, 
                                              &irq_table[irq_no], 
                                              irq_table[irq_no].pVoid);
                } 
            }
            value >>= 1;
            irq_no++;                   
        }           
#if DEBUG
        mt_printf("Exit IRQ\n"); 
#endif     
}



void 
CFiqHandler (void)
{
        /* This shouldn't happen, but let's trap it just in case */
        //printf("Unexpected FIQ\r\n");
        return;
}



/*************************************************************************
EXCEPTIONS
*************************************************************************/
void 
CAbtHandler (void)
{
        //printf("Data abort\n\r");
}



void 
CPabtHandler (unsigned int address)
{
        //printf("Error prefetch abort at address %#x\n\r",address);
}



void 
CDabtHandler (unsigned int address)
{
        //printf("Error data abort at address %#x\n\r", address);
}



void 
CSwiHandler (void)
{
        //printf("Error swi\n\r");
}



void 
CUdefHandler (void)
{
        //printf("Error undefined instruction\n\r");
}



void 
register_irq_mirq3 (U16 mirq3_subid, isrfun handler, char *name, 
                    int unmask, void *pVoid)
{
        if (mt_main_cpld_get_version() < 0x13){                 
            register_irq(CREATOR_IO_XIRQ3_IRQ, handler, name, pVoid);    
            if (unmask)
                creator_unmask_irq_gpio1(CREATOR_IO_XIRQ3_IRQ);
        }
        else{
            register_irq(mirq3_subid, handler, name, pVoid);    
            if (unmask)         
                creator_unmask_mirq3(mirq3_subid);        
        }            
}
    
    

void 
unregister_irq_mirq3 (U16 mirq3_subid, char* name)
{
        if (mt_main_cpld_get_version() < 0x13){ 
            unregister_irq(CREATOR_IO_XIRQ3_IRQ, name);                      
        }
        else{
            unregister_irq(mirq3_subid, name);            
        }
                
}



/*
 * PXA GPIO edge detection for IRQs:
 * IRQs are generated on Falling-Edge, Rising-Edge, or both.
 * Use this instead of directly setting GRER/GFER.
 */


static U32 GPIO_IRQ_rising_edge[4];
static U32 GPIO_IRQ_falling_edge[4];
static U32 GPIO_IRQ_mask[4];



static void 
__set_bit (int nr, volatile U32 *p)
{
        p[nr >> 5] |= (1UL << (nr & 31));
}



static void 
__clear_bit (int nr, volatile U32 *p)
{
        p[nr >> 5] &= ~(1UL << (nr & 31));
}



void 
pxa_gpio_mode (int gpio_mode)
{
        U32 flags;
        int gpio = gpio_mode & GPIO_MD_MASK_NR;
        int fn = (gpio_mode & GPIO_MD_MASK_FN) >> 8;
        int gafr;

        if (gpio_mode & GPIO_DFLT_LOW)
            GPCR(gpio) = GPIO_bit(gpio);
        else if (gpio_mode & GPIO_DFLT_HIGH)
            GPSR(gpio) = GPIO_bit(gpio);
        if (gpio_mode & GPIO_MD_MASK_DIR)
            GPDR(gpio) |= GPIO_bit(gpio);
        else
            GPDR(gpio) &= ~GPIO_bit(gpio);
        gafr = GAFR(gpio) & ~(0x3 << (((gpio) & 0xf)*2));
        GAFR(gpio) = gafr |  (fn  << (((gpio) & 0xf)*2));
}



/*
 * This is for peripheral IRQs internal to the PXA chip.
 */

void 
pxa_mask_low_irq (U16  irq)
{        
        ICMR &= ~(1 << (irq + PXA_IRQ_SKIP));
}



void 
pxa_unmask_low_irq (U16 irq)
{       
        ICMR |= (1 << (irq + PXA_IRQ_SKIP));
}



/*
 * GPIO IRQs must be acknowledged.  This is for GPIO 0 and 1.
 */
void 
pxa_ack_low_gpio (U16  irq)
{   
        GEDR0 = (1 << (irq - IRQ_GPIO0));   
}



void 
pxa_mask_muxed_gpio (U16 irq)
{
        int gpio = irq - IRQ_GPIO(2) + 2;
        
        __clear_bit(gpio, GPIO_IRQ_mask);
        GRER(gpio) &= ~GPIO_bit(gpio);
        GFER(gpio) &= ~GPIO_bit(gpio);
}



void 
pxa_unmask_muxed_gpio (U16 irq)
{
        int gpio = irq - IRQ_GPIO(2) + 2;
        int idx = gpio >> 5;
        
        __set_bit(gpio, GPIO_IRQ_mask);
        GRER(gpio) = GPIO_IRQ_rising_edge[idx] & GPIO_IRQ_mask[idx];
        GFER(gpio) = GPIO_IRQ_falling_edge[idx] & GPIO_IRQ_mask[idx];
}



/*
 * This is for the second set of internal IRQs as found on the PXA27x.
 */
void 
pxa_mask_high_irq (U16 irq)
{
        ICMR2 &= ~(1 << (irq - 32 + PXA_IRQ_SKIP));
}



void 
pxa_unmask_high_irq (U16 irq)
{
        ICMR2 |= (1 << (irq - 32 + PXA_IRQ_SKIP));
}



void 
creator_ack_irq_gpio1 (U16 irqno)
{
/*
Enable IRQ
mask : 1 : disable, 
       0 : Enable.
       
pend : 1 : has IRQ : 
           Once a PENDING bit is set by an edge event, the bit remains set 
           until it is cleared by writing a one to the status bit. Writing
           a zero to a GEDR status bit has no effect.
       0 : no IRQ           
*/    
       U16   bitval ;  
       
       if (irqno < CREATOR_CFI_IRQ){
           /* 
            * the irq can be acknowledged only if deasserted, 
            * so it's done here 
            */
           bitval = (1 <<(irqno - CREATOR_IRQ(0)));                                 
           MASTER_INTPEND1 = (bitval);            
       }
       else{
           bitval = (1 <<(irqno - CREATOR_IRQ(8)));                                 
           MASTER_INTPEND2 = (bitval);                                   
       }                 
}



void 
creator_mask_irq_gpio1 (U16 irqno)
{
/*
mask : 1 : disable, 
       0 : Enable.
       
pend : 1 : has IRQ : 
           Once a PENDING bit is set by an edge event, the bit remains set 
           until it is cleared by writing a one to the status bit. Writing
           a zero to a GEDR status bit has no effect.
       0 : no IRQ           
*/    
       U16 bitval, mask ;      

       if (irqno < CREATOR_CFI_IRQ){
           bitval = 1 << (irqno - CREATOR_IRQ(0)); 
           mask = MASTER_INTMASK1;
           mask |= bitval;
           MASTER_INTMASK1 = mask;            
       } 
       else{
           bitval = 1 << (irqno - CREATOR_IRQ(8)); 
           mask = MASTER_INTMASK2;
           mask |= bitval;
           MASTER_INTMASK2 = mask;                           
       }                  
}



void 
creator_unmask_irq_gpio1 (U16 irqno)
{
/*
unmask IRQ :
mask : 1 : disable, 
       0 : Enable.
       
pend : 1 : has IRQ : 
           Once a PENDING bit is set by an edge event, the bit remains set 
           until it is cleared by writing a one to the status bit. Writing
           a zero to a GEDR status bit has no effect.
       0 : no IRQ   
*/    
       U16 bitval, mask;   
      
       if (irqno < CREATOR_CFI_IRQ){
           /* 
            * the irq can be acknowledged only if deasserted, 
            * so it's done here 
            */
           bitval = (1 <<(irqno - CREATOR_IRQ(0)));                                           
           mask = MASTER_INTMASK1;           
           mask &= (~bitval);
           MASTER_INTMASK1 = mask;
       }
       else{
           bitval = (1 <<(irqno - CREATOR_IRQ(8)));                                            
           mask = MASTER_INTMASK2;           
           mask &= (~bitval);
           MASTER_INTMASK2 = mask;                          
       }                                                 
}



int 
pxa_gpio_irq_type (U16 irq, unsigned int type)
{
        int gpio, idx;

        gpio = IRQ_TO_GPIO(irq);
        idx = gpio >> 5;

        if (type == IRQT_PROBE) {    
            /* 
             * Don't mess with enabled GPIOs using preconfigured edges or
             *  GPIOs set to alternate function during probe 
             */
            if ((GPIO_IRQ_rising_edge[idx] | GPIO_IRQ_falling_edge[idx]) &
                 GPIO_bit(gpio))
                return 0;
                
            if (GAFR(gpio) & (0x3 << (((gpio) & 0xf)*2)))
                return 0;
                
            type = __IRQT_RISEDGE | __IRQT_FALEDGE;
        }


        pxa_gpio_mode(gpio | GPIO_IN);

        if (type & __IRQT_RISEDGE) {
            __set_bit(gpio, GPIO_IRQ_rising_edge);
        } else
            __clear_bit(gpio, GPIO_IRQ_rising_edge);

        if (type & __IRQT_FALEDGE) {
            __set_bit(gpio, GPIO_IRQ_falling_edge);
        } else
            __clear_bit(gpio, GPIO_IRQ_falling_edge);

        GRER(gpio) = GPIO_IRQ_rising_edge[idx] & GPIO_IRQ_mask[idx];
        GFER(gpio) = GPIO_IRQ_falling_edge[idx] & GPIO_IRQ_mask[idx];
       
        return (0);
}



void 
creator_ack_mirq3 (U16 irqno)
{
/*
clear pending & unmask mirq3 :
mask : 1 : disable, 
       0 : Enable.
       
pend : 1 : has IRQ : 
           Once a PENDING bit is set by an edge event, the bit remains set 
           until it is cleared by writing a one to the status bit. Writing
           a zero to a GEDR status bit has no effect.
       0 : no IRQ        
*/    
       U16 irq_bit   ;      
        
       irq_bit = 1 << (irqno - CREATOR_IO_XIRQ3_EXT_CF_IRQ);                
       MASTER_IRQ3_PEND = (irq_bit);                          

}



void 
creator_mask_mirq3 (U16 irqno)
{
/*
mask mirq3 :
mask : 1 : disable, 
       0 : Enable.
       
pend : 1 : has IRQ : 
           Once a PENDING bit is set by an edge event, the bit remains set 
           until it is cleared by writing a one to the status bit. Writing
           a zero to a GEDR status bit has no effect.
       0 : no IRQ       
*/    
       U16  bitval, mask ;       
        
       bitval = (1 <<(irqno - CREATOR_IO_XIRQ3_EXT_CF_IRQ));        

       mask = MASTER_IRQ3_MASK;
       mask |= bitval;
       MASTER_IRQ3_MASK = mask;                                
}



void 
creator_unmask_mirq3 (U16  irqno)
{
/*
unmask mirq3 :
mask : 1 : disable, 
       0 : Enable.
       
pend : 1 : has IRQ
       0 : no IRQ        
*/    
       U16 bitval, mask;
   
       bitval = (1 << (irqno - CREATOR_IO_XIRQ3_EXT_CF_IRQ));  
                                     
       mask = MASTER_IRQ3_MASK;           
       mask &= (~bitval);
       MASTER_IRQ3_MASK = mask;                                  
       creator_unmask_irq_gpio1(CREATOR_IO_XIRQ3_IRQ);  
}



void 
creator_ack_mirq3_subid (U16 mirq3_subid)
{
        if (mt_main_cpld_get_version() < 0x13){ 
            creator_ack_irq_gpio1(CREATOR_IO_XIRQ3_IRQ);    
        }    
        else{
            creator_ack_mirq3(mirq3_subid);     
        }       
}



void 
creator_mask_mirq3_subid (U16 mirq3_subid)
{
        if (mt_main_cpld_get_version() < 0x13){ 
            creator_mask_irq_gpio1(CREATOR_IO_XIRQ3_IRQ);    
        }    
        else{
            creator_mask_mirq3(mirq3_subid);        
        }                                
}
    


void
creator_mirq3_irq_demux (U16 irq, struct irq_desc *desc, void *pVoid)
{
        U16 bitval;
        U16 pending;                
        U8  irqno;        
                     
        // do you code.                     
        pending = (MASTER_IRQ3_PEND & (~MASTER_IRQ3_MASK)) ;              
        if (pending){
            irqno = CREATOR_IO_XIRQ3_EXT_CF_IRQ;                
            bitval = (1 << (CREATOR_IO_XIRQ3_IRQ - CREATOR_IRQ(0)));             
            MASTER_INTPEND1 = (bitval);               
            do {
                if (pending & 1){              
                    if (irq_table[irqno].handler){
                        creator_mask_mirq3(irqno);
                        irq_table[irqno].handler(irqno, desc, desc->pVoid);
                        creator_unmask_mirq3(irqno);                        
                    }       
                }    
                irqno++;
                desc++;
                pending >>=1;            
            } while (pending);                    
        }           
}
    
    
/*
 * Demux handler for GPIO>=2 edge detect interrupts
 */

static void 
pxa_gpio_demux_handler (U16 irqno, struct irq_desc *desc, void *pVoid)    
{
        U32 pending, irq;
        int loop;

#if DEBUG
        mt_printf("Entry gpio>=2 isr\n"); 
#endif
        do {
            loop = 0;

            pending = GEDR0 & ~3;
            if (pending) {
                GEDR0 = pending;
                irq = IRQ_GPIO(2);
                desc = &irq_table[irq];
                pending >>= 2;
                do {
                    if (pending & 1)
                        irq_table[irq].handler(irq, desc, desc->pVoid);
                    irq++;
                    desc++;
                    pending >>= 1;
                } while (pending);
                loop = 1;
            }

            pending = GEDR1;
            if (pending) {
                GEDR1 = pending;
                irq = IRQ_GPIO(32);
                desc = &irq_table[irq];                
                 do {
                    if (pending & 1)
                        irq_table[irq].handler(irq, desc, desc->pVoid);
                    irq++;
                    desc++;
                    pending >>= 1;
                } while (pending);
                loop = 1;
            }

            pending = GEDR2;
            if (pending) {
                GEDR2 = pending;
                irq = IRQ_GPIO(64);
                desc = &irq_table[irq];                
                do {
                    if (pending & 1)
                        irq_table[irq].handler(irq, desc, desc->pVoid);
                    irq++;
                    desc++;
                    pending >>= 1;
                } while (pending);
                loop = 1;
            }

#if PXA_LAST_GPIO >= 96
            pending = GEDR3;
            if (pending) {
                GEDR3 = pending;
                irq = IRQ_GPIO(96);
                desc = &irq_table[irq];                
                do {
                    if (pending & 1)
                        irq_table[irq].handler(irq, desc, desc->pVoid);
                    irq++;
                    desc++;
                    pending >>= 1;
                } while (pending);
                loop = 1;
            }
#endif
        } while (loop); 
        
#if DEBUG
        mt_printf("Exit gpio>=2 isr\n"); 
#endif        
}   



static void  
pxa_gpio1_irq_demux (U16 irq, struct irq_desc *desc, void *pVoid)
{
        static U8   irqno, PriorityIndex  = 0;
        U16  mask, irq_idx;
        U16  pending;   
           
#if DEBUG
        mt_printf("Entry gpio1 irq\n"); 
#endif           
           
        // mask GPIO1
        ICMR &= ~(1 << (IRQ_GPIO1));   
                   
        // ack GPIO1   
        GEDR0 = (1 << (1));            
        
        // do you code.        
        pending =  (((MASTER_INTPEND2 & (~MASTER_INTMASK2)) & 0xff)<<8)+ 
                    ((MASTER_INTPEND1 & (~MASTER_INTMASK1)) & 0xff);              
        if (pending){      
            irqno = CREATOR_IRQ(0);     
            desc = &irq_table[irqno];   
            do {
                if (pending & (1 << PriorityIndex)){
                    irq_idx = irqno + PriorityIndex;            
                    if (irq_table[irq_idx].handler){
                        //creator_mask_irq_gpio1(irq_idx);                      
                        irq_table[irq_idx].handler(irq_idx, 
                                                   desc, 
                                                   desc->pVoid);
                        //creator_unmask_irq_gpio1(irq_idx);                         
                    }    
                    PriorityIndex++;
                    PriorityIndex &= 0x0f;
                    ICMR |= (1<<IRQ_GPIO1);   
                    
#if DEBUG
                    mt_printf("Exit gpio1 irq\n"); 
#endif                          
                    return ;
                }    
                PriorityIndex++;
                PriorityIndex &= 0x0f;    
                desc++;           
            } while (pending);                    
        }             
        
        // unmask GPIO1
        ICMR |= (1 << (IRQ_GPIO1 + PXA_IRQ_SKIP));    
        
#if DEBUG
        mt_printf("Exit gpio1 irq\n"); 
#endif                       
}    


   

static void  
pxa_init_irq (void)
{
        /* disable all IRQs */
        ICMR = 0;

        /* all IRQs are IRQ, not FIQ */
        ICLR = 0;

        /* clear all GPIO edge detects */
        GFER0 = 0;
        GFER1 = 0;
        GFER2 = 0;
        GRER0 = 0;
        GRER1 = 0;
        GRER2 = 0;
        GEDR0 = GEDR0;
        GEDR1 = GEDR1;
        GEDR2 = GEDR2;

        /* And similarly for the extra regs on the PXA27x */
        ICMR2 = 0;
        ICLR2 = 0;
        GFER3 = 0;
        GRER3 = 0;
        GEDR3 = GEDR3;

        /* only unmasked interrupts kick us out of idle */
        ICCR = 1;

        /* GPIO 0 and 1 must have their mask bit always set */
        GPIO_IRQ_mask[0] = 3;
       
        // GPIO1 extend IRQ 
        MASTER_IRQ3_MASK = ~(0);              
        MASTER_INTMASK1 = ~(0);
        MASTER_INTMASK2 = ~(0);  
        MASTER_IRQ3_PEND = ~0;          
        MASTER_INTPEND1 = ~0;
        MASTER_INTPEND2 = ~0;                
    
        if (mt_main_cpld_get_version() >= 0x13){
            // Creator Board XINTREQ map.
            // IRQ SELECT:
            //  bit  2-0 : IRQ0_MUX : PHY_nINT(U19)
            //  bit  5-3 : IRQ1_MUX : USB_nINT(U25)
            //  bit  8-6 : IRQ2_MUX : CODEC_INT(U21)
            //  bit 11-9 : IRQ3_MUX : SubXINT3
            //  bit 12   : INKCF_1  : 0 : Normal Mode, 1 : invert CF_IRQ signal
            //  bit 13   : IRQ3_MODE: 0 : Old Mode. 1 : User 1.2 Mode.
            //  bit 14   : IRQ0_MODE: 0 : XINTREQ(0) map to ethernet of 
            //                            creator board.
            //                        1 : XINTREQ(0) map to CF of creator board.
            //  bit 15   : IRQ_DEFAULT : 0 : Use V1.0 INT 
            //                            1 : Use V1.2 INT  
            IRQ_SELECT = (1<<15) + (1<<13) + (1<<12) + (2 << 6) + (1<<3) + (0) ;  
                        
            register_irq(CREATOR_IO_XIRQ3_IRQ, 
                         creator_mirq3_irq_demux, 
                         "mirq3 ISR", 
                         NULL);
            creator_unmask_irq_gpio1(CREATOR_IO_XIRQ3_IRQ);                                       
        }             
        else{
        }
        
        pxa_gpio_irq_type(IRQ_GPIO1, IRQT_FALLING); 
        register_irq(IRQ_GPIO1, pxa_gpio1_irq_demux, "GPIO1 ISR", NULL);         
        pxa_unmask_low_irq(IRQ_GPIO1);                
        
        register_irq(IRQ_GPIO_2_x, pxa_gpio_demux_handler, "GPIO_x ISR", NULL);              
        pxa_unmask_low_irq(IRQ_GPIO_2_x);             
}



void 
irq_init (void)
{  
        int     i;
    
        for (i=0; i < IRQ_INT_NO; i++){
            irq_table[i].handler = NULL;        
        }   
        pxa_init_irq(); 
}
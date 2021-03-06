// --------------------------------------------------------------------
//
//   Title     :  irq.h
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  IRQ handler
//             :
//   Limitation:
//             :
//   Note      :
//             :
// --------------------------------------------------------------------
//   modification history :
// --------------------------------------------------------------------
//   Version| mod. date: |
//   V1.0   | 09/07/2004 | Programming start
// --------------------------------------------------------------------
//
// Note:
//
//       MICROTIME COMPUTER INC.
//
// --------------------------------------------------------------------

#ifndef _IRQ_INCLUDE_IRQ_H_
#define _IRQ_INCLUDE_IRQ_H_

#ifndef __ADDR_PXA27X_H__
#include        "common/include/addr.h"
#endif

#define IRQ_NAME_SIZE              24

struct irq_desc;
typedef void (*isrfun)(U16 irqno, struct irq_desc *desc, void *pVoid);

struct irq_desc{
    isrfun       handler;                 //pointer to an interrupt handler
    U16          irqno;                   // 
    char         name[IRQ_NAME_SIZE];     
    void         *pVoid ;
};

struct irq_desc *p_irq_desc;

/*****************************
 * max of interrupt table size
 *****************************/


#define __IRQT_FALEDGE  (1 << 0)
#define __IRQT_RISEDGE  (1 << 1)
#define __IRQT_LOWLVL   (1 << 2)
#define __IRQT_HIGHLVL  (1 << 3)

#define IRQT_NOEDGE (0)
#define IRQT_RISING (__IRQT_RISEDGE)
#define IRQT_FALLING    (__IRQT_FALEDGE)
#define IRQT_BOTHEDGE   (__IRQT_RISEDGE|__IRQT_FALEDGE)
#define IRQT_LOW    (__IRQT_LOWLVL)
#define IRQT_HIGH   (__IRQT_HIGHLVL)
#define IRQT_PROBE  (1 << 4)


void irq_init(void);
void do_irq(void);
int  register_irq (U16 irqno, isrfun isr, char *name, void *pVoid);
int  unrequest_irq(int i, char* name);
void register_irq_mirq3 (U16 irqno, isrfun isr, char *name, 
                         int Unmask, void *pVoid);
void unregister_irq_mirq3 (U16  mirq3_subid, char* name);

void pxa_ack_low_gpio (U16  irq);
void pxa_unmask_low_irq (U16  irq);
void pxa_mask_low_irq (U16  irq);
void pxa_mask_muxed_gpio (U16  irq);
void pxa_unmask_muxed_gpio (U16  irq);
int  pxa_gpio_irq_type (U16  irq, unsigned int type);
void creator_ack_irq_gpio1 (U16  irqno);
void creator_mask_irq_gpio1 (U16  irqno);
void creator_unmask_irq_gpio1 (U16  irqno);
void creator_ack_mirq3 (U16  irqno);
void creator_mask_mirq3 (U16  irqno);
void creator_unmask_mirq3 (U16 irqno);
void creator_ack_mirq3_subid (U16  mirq3_subid);
void creator_mask_mirq3_subid (U16  mirq3_subid);

#endif // _IRQ_INCLUDE_IRQ_H_

// --------------------------------------------------------------------
//
//   Title     :  os_timer.c
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  OS timer functions for Creator PXA270
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
//   V1.0   | 12/13/2006 | First release
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

#include "timer/include/os_timer.h"



/*************************************************************************
Constant define
*************************************************************************/
typedef struct OST_REG {
    U32                 ossrbit ;
    U32                 oierbit ;
    U32                 icmrbit ;
    volatile U32        *pOMCR  ;       
    volatile U32        *pOSMR  ; 
    volatile U32        *pOSCR  ; 
} ost_reg_t ;


typedef struct {
        struct irq_desc irq_desc;
        
        U16    timeval ;
        U32    countsPerSysTick;        
        int    res_type;        
        U8     periodic;
        U8     valid ;              
        S16    irqno;
         
        ost_reg_t Reg;
} ost_desc_t, *post_desc_t;  



/*************************************************************************
Function prototypes
*************************************************************************/
static int  ost_set_interval(post_desc_t  post_desc, 
                             OST_MATCHREG matchreg, U16 ms);
static void system_time_isr(U16 irqno, struct irq_desc *desc, void *pVoid);
static void ost_1_3_irq_isr(U16 irqno, struct irq_desc *irq_desc, 
                            void *pVoid);
static void ost_4_11_irq_isr(U16 irqno, struct irq_desc *irq_desc, 
                             void *pVoid);
static void ost_timer0_isr(U16 irqno, struct irq_desc *desc, void *pVoid);
static int  ost_set_match_tickcount(post_desc_t  post_desc, 
                                    OST_MATCHREG matchreg, U32 matchvalue);
static int  ost_ext_set_interval(post_desc_t post_desc, 
                                 OST_MATCHREG matchreg, U32 matchvalue, 
                                 int res_type, U8 periodic);
static int  ost_get_free_timer(U32 minId, U32 maxId, U32 *Id);
static void ost_delay_ticks (U32 ticks);
static void ost_setup(void);



/*************************************************************************
Variable define
*************************************************************************/
timer_realtime_t g_timer_realtime =
{
    0,  // 1 hour
    0,  // 1 min
    0,  // 1 sec
    0   // 1 msec
};

static ost_desc_t  g_ost_desc[NR_TIMERS];



void
delay_ms (U16 ms)
{
        U32  ticks;
        
        ticks = ms * OST_TICKS_MS;
        ost_delay_ticks(ticks);
}



void
delay_s (U16 sec)
{   
        while (--sec)
            delay_ms(1000);                     
}



void
Delay (U16 ms)
{
        delay_ms(ms);   
}   



int  
register_ostimer (U32 *device, U16 ms, U8 periodic, isrfun isr, 
                  char*pDesc, void* pVoid)
{
        post_desc_t       post_desc;        
        OST_MATCHREG      matchreg;     
        U32               min, max ;                        
        int               nRet ;           
        U32               index ;
            
        if (*device == OST_FREE_TIMER){
            min = 1; max = 3;
        }
        else{
            min = *device; max = *device;        
        }    
        nRet = ost_get_free_timer(min, max, &index);
        if (!nRet)
            return (0);           
            
        matchreg = index ;                      
        post_desc= &g_ost_desc[matchreg];                                         
        post_desc->irqno = index + IRQ_OST0;            
        post_desc->periodic = periodic == OST_ONE_SHOT ? 
                                          OST_ONE_SHOT : OST_PERIODIC;
        post_desc->irq_desc.handler = isr;
        post_desc->irq_desc.pVoid = pVoid;        
        
        if (!ost_set_interval(post_desc, matchreg, ms))
            return (0);               
                    
        if (matchreg == TIMER0){            
            if (!register_irq(post_desc->irqno, ost_timer0_isr, pDesc, 
                              post_desc))
                return (0); 
        }    
        else{
            if (!register_irq(post_desc->irqno, ost_1_3_irq_isr, 
                              pDesc, post_desc))            
                return (0);
        }    
        pxa_unmask_low_irq(IRQ_OST0 + index);           
        *device = index;
        post_desc->valid = 1;  
                
        return (1);
}   



int  
register_ostimer_ext (U32 *device, U16 timeval, int res_type, U8 periodic, 
                      isrfun isr, char*pDesc, void* pVoid)
{
        post_desc_t       post_desc;    
        OST_MATCHREG      matchreg;         
        int               nRet;
        U32               index ;

        nRet = ost_get_free_timer(4, 11, &index);
        if (!nRet)
            return (0);   
                     
        matchreg = index ;    
        post_desc= &g_ost_desc[matchreg];       
        post_desc->timeval = timeval;
        post_desc->res_type = res_type;        
        post_desc->periodic = (UC)((periodic == OST_ONE_SHOT) ? 
                               OST_ONE_SHOT : OST_PERIODIC);       
        post_desc->irqno = (index - 4)+ CREATOR_OST_4_IRQ;                               
                                       

        if (!register_irq(post_desc->irqno, isr, pDesc, pVoid))
            return (0);
        
        if (!ost_ext_set_interval(&g_ost_desc[index], matchreg, 
                                  timeval, res_type, periodic))
            return (0);
            
        *device = index ;
        post_desc->valid = 1; 
                   
        return (1);                         
}
    


int 
unregister_ostimer (U32 device)
{
        post_desc_t   post_desc;                             
    
        if (!ostimer_disable(device))
            return (0);

        post_desc  = &g_ost_desc[device];               
        unregister_irq(post_desc->irqno, p_irq_desc[post_desc->irqno].name);  
          
        post_desc->irq_desc.handler = NULL;  
        post_desc->valid = 0;             
                
        return (1);                     
}



int
ostimer_disable (U32 device)
{
        post_desc_t   post_desc;                             
    
        if (device > NR_TIMERS)
            return (0);
            
        post_desc  = &g_ost_desc[device];  
        if (!post_desc->valid)
            return (0);       

        //
        // Disable interrupts on the specified Match register
        //
        OIER &= ~(post_desc->Reg.oierbit | OIER_RESERVED_BITS);               
         
        //
        // Disable count
        //         
        if (post_desc->Reg.pOMCR)
            *post_desc->Reg.pOMCR =  0;                       
      
        //
        // Clear any interrupt on the specified Match register
        //
        OSSR = post_desc->Reg.ossrbit;                   
        
        //
        // Disable the Match interrupt at the interrupt controller
        //
        ICMR &= (~post_desc->Reg.icmrbit);                 
        
        return (1);             
}   



int 
ostimer_restart (U32 device)
{
        post_desc_t   post_desc;                             
        int           nRet ;
    
        if (!ostimer_disable(device))
            return (0);
            
        post_desc  = &g_ost_desc[device];  
            
        if (device <= 3){     
            nRet = ost_set_match_tickcount(post_desc, device, 
                                            post_desc->timeval);                                  
        }
        else{
            nRet = ost_ext_set_interval(post_desc, device, 
                                        post_desc->timeval, 
                                        post_desc->res_type, 
                                        post_desc->periodic);        
        }    
        
        return (nRet);
}

    

static int 
ost_set_interval (post_desc_t post_desc, 
                  OST_MATCHREG matchreg, 
                  U16 ms)
{       
        U32          matchvalue,  matchincrement;

        if (matchreg > TIMER4)
            return (0);   

        matchincrement = ms * OST_TICKS_MS;         
        post_desc->countsPerSysTick = matchincrement;        
        post_desc->timeval = ms;
        matchvalue = OSCR0 + matchincrement;        
        //
        // Compute the new match value to load
        //      
        ost_set_match_tickcount(post_desc, matchreg, matchvalue);               
}   



static void  
system_time_isr (U16 irqno, struct irq_desc *desc, void *pVoid)
{         
        g_timer_realtime.msec++;
        
        if (g_timer_realtime.msec == 1000) { 
            g_timer_realtime.msec = 0; 
            g_timer_realtime.sec++; 
        }
        if (g_timer_realtime.sec == 60){ 
            g_timer_realtime.sec = 0;  
            g_timer_realtime.min++; 
        }
        if (g_timer_realtime.min == 60){ 
            g_timer_realtime.min = 0;  
            g_timer_realtime.hour++; 
        }        
}

    

static void  
ost_timer0_isr (U16 irqno, struct irq_desc *irq_desc, void *pVoid)
{   
        post_desc_t    post_desc  = (post_desc_t)pVoid; 
        U32 TimerCount;
        U32 TimerMatch;
    
        if (post_desc->valid && post_desc->irq_desc.handler){
            post_desc->irq_desc.handler(irqno, 
                                        irq_desc, 
                                        post_desc->irq_desc.pVoid);             
        }                     
        
        //
        // Configure and arm the timer interrupt to interrupt every specified
        // system tick interval.
        //
        TimerCount = OSCR0;
        TimerMatch = OSMR0;

        if ((long)(TimerCount - TimerMatch - 500) < 0){
            ost_set_match_tickcount(post_desc, TIMER0, 
                                (TimerMatch + post_desc->countsPerSysTick));
        }
        else{    
            ost_set_interval(post_desc, 
                             TIMER0, 
                             post_desc->timeval);   
        }                   
}



static void  
ost_1_3_irq_isr (U16 irqno, struct irq_desc *irq_desc, void *pVoid)
{
        post_desc_t    post_desc  = (post_desc_t)pVoid; 
        
        if (post_desc->valid && post_desc->irq_desc.handler){
            post_desc->irq_desc.handler(irqno, 
                                        irq_desc, 
                                        post_desc->irq_desc.pVoid);             
        }           
        
        if (post_desc->periodic == (UC)OST_PERIODIC){       
            ost_set_interval(post_desc, 
                             post_desc->irqno - IRQ_OST0, 
                             post_desc->timeval);
        }            
        else {
            OIER &= ~(post_desc->Reg.oierbit | OIER_RESERVED_BITS);                                         
      
            //
            // Clear any interrupt on the specified Match register
            //
            OSSR = post_desc->Reg.ossrbit;       
            
            //
            // Disable the Match interrupt at the interrupt controller
            //
            ICMR &= (~post_desc->Reg.icmrbit);                      
        }               
}



static void 
ost_4_11_irq_isr (U16 irqno, struct irq_desc *irq_desc, void *pVoid)
{       
        post_desc_t    post_desc  = (post_desc_t)pVoid;         
        U32            pending;    

        irqno = CREATOR_OST_4_IRQ;
        irq_desc = p_irq_desc + irqno;     
        pending =  ((OSSR & (~OSSR_RESERVED_BITS))>> 4);                 
        do {           
            if (pending & 1) { 
                irq_desc->handler(irqno, irq_desc, irq_desc->pVoid);
                
                //
                // Clear any interrupt on the specified Match register
                //                
                OSSR = post_desc->Reg.ossrbit;  
                
                return ;                               
            }    
            irqno++;
            irq_desc++;
            post_desc++;
            pending >>= 1;
        } while (pending);                         
}



static int 
ost_set_match_tickcount (post_desc_t  post_desc, OST_MATCHREG matchreg, 
                     U32 matchvalue)
{                           
        if (matchreg > TIMER4)
            return (0);                                                                              

        //
        // Disable interrupts on the specified Match register
        //
        OIER &= ~(post_desc->Reg.oierbit | OIER_RESERVED_BITS);

        //
        // Clear any interrupt on the specified Match register
        //
        OSSR = post_desc->Reg.ossrbit; 

        // 
        // Set up the match register to expire when the oscr0 reaches
        // the next match interval.
        //
        *post_desc->Reg.pOSMR = matchvalue ; 
        
        //
        // Enable the Match register interrupt on 
        //
        OIER |= post_desc->Reg.oierbit;

        //
        // Enable the Match interrupt at the interrupt controller
        //
        ICMR |= post_desc->Reg.icmrbit;             
    
        return (1);
}   



static int 
ost_ext_set_interval (post_desc_t  post_desc, OST_MATCHREG matchreg, 
                      U32 matchvalue, int res_type, U8 periodic)
{
        U8              periodic_enable ;
        U8              counter_resolution ;
                            
        if (matchreg < TIMER4 || matchreg > TIMER11)
            return (0);
                            
        switch (res_type){
        case RES_REG :
            counter_resolution = RES_REG;                       
            break;              
        case RES_1MSEC :
            counter_resolution = RES_1MSEC;                     
            break;     
        case RES_1SEC :
            counter_resolution = RES_1SEC;                      
            break;     
        case RES_1USEC :
            counter_resolution = RES_1USEC;                     
            break;     
        default :
            counter_resolution = RES_DISABLE;                       
            break;                                                     
        }                                                
  
        periodic_enable = periodic ? 1 : 0;        
        *post_desc->Reg.pOMCR = (1<<7) + (periodic_enable<<6) + 
                                (0<<4) + (1<<3) + (counter_resolution); 
        

        //
        // Disable interrupts on the specified Match register
        //
        OIER &= ~(post_desc->Reg.oierbit | OIER_RESERVED_BITS);

        //
        // Clear any interrupt on the specified Match register
        //
        OSSR = post_desc->Reg.ossrbit; 

        // 
        // Set up the match register to expire when the oscr0 reaches
        // the next match interval.
        //
        *post_desc->Reg.pOSMR = matchvalue; 
        
        *post_desc->Reg.pOSCR = 0;

        //
        // Enable the Match register interrupt on 
        //
        OIER |= post_desc->Reg.oierbit;

        //
        // Enable the Match interrupt at the interrupt controller
        //
        ICMR |= post_desc->Reg.icmrbit;             
    
        return (1);
}   



static int
ost_get_free_timer (U32 mindevice, U32 maxdevice, U32 *device)
{
        U32  i;        

        for (i=mindevice; i < NR_TIMERS && i <= maxdevice; i++)
            if (!g_ost_desc[i].valid){
                *device = i;
                return (1);
            }                 
        
        return (0);     
}   



static void 
ost_delay_ticks (U32 ticks)
{    
        U32    expireTime, time;

        time = OSCR0;
        expireTime = time + ticks;

        //
        // Check if we wrapped on the expireTime
        // and delay first part until wrap
        //
        if (expireTime < time) {
            while (time < OSCR0);
        }
        while (OSCR0 <= expireTime);
        return ;
}



static void
ost_setup (void)
{
        ost_reg_t ost_reg[] = {
          { OSSR_M0,  OIER_E0,  IRQ_OST0,     NULL,            (U32*)&(OSMR0),
           (U32*)&(OSCR0)  } ,           
          { OSSR_M1,  OIER_E1,  IRQ_OST1,     NULL,            (U32*)&(OSMR1),
           (U32*)&(OSCR0)  } ,           
          { OSSR_M2,  OIER_E2,  IRQ_OST2,     NULL,            (U32*)&(OSMR2),
           (U32*)&(OSCR0)  } ,           
          { OSSR_M3,  OIER_E3,  IRQ_OST3,     NULL,            (U32*)&(OSMR3),
           (U32*)&(OSCR0)  } ,                                          
          { OSSR_M4,  OIER_E4,  IRQ_OST_4_11, (U32*)&(OMCR4),  (U32*)&(OSMR4),
            (U32*)&(OSCR4)  } ,
          { OSSR_M5,  OIER_E5,  IRQ_OST_4_11, (U32*)&(OMCR5),  (U32*)&(OSMR5),
            (U32*)&(OSCR5)  } ,            
          { OSSR_M6,  OIER_E6,  IRQ_OST_4_11, (U32*)&(OMCR6),  (U32*)&(OSMR6),
            (U32*)&(OSCR6)  } ,            
          { OSSR_M7,  OIER_E7,  IRQ_OST_4_11, (U32*)&(OMCR7),  (U32*)&(OSMR7),
            (U32*)&(OSCR7)  } ,            
          { OSSR_M8,  OIER_E8,  IRQ_OST_4_11, (U32*)&(OMCR8),  (U32*)&(OSMR8),
            (U32*)&(OSCR8)  } ,            
          { OSSR_M9,  OIER_E9,  IRQ_OST_4_11, (U32*)&(OMCR9),  (U32*)&(OSMR9),
            (U32*)&(OSCR9)  } ,            
          { OSSR_M10, OIER_E10, IRQ_OST_4_11, (U32*)&(OMCR10), (U32*)&(OSMR10),
           (U32*)&(OSCR10) } ,
          { OSSR_M11, OIER_E11, IRQ_OST_4_11, (U32*)&(OMCR11), (U32*)&(OSMR11),
           (U32*)&(OSCR11) }                                       
        } ;         
        post_desc_t   desc ;
        int           device;
  
        desc = g_ost_desc;     
        for (device=0; device < NR_TIMERS; device++, desc++){
            desc->timeval = 0;
            desc->res_type = 0;        
            desc->periodic = 0;;
            desc->valid = 0;                        
            desc->irqno = -1;          
            desc->irq_desc.handler = NULL;               
     
            
            desc->Reg.ossrbit = ost_reg[device].ossrbit;
            desc->Reg.oierbit = ost_reg[device].oierbit;            
            desc->Reg.icmrbit = ost_reg[device].icmrbit;
            
            desc->Reg.pOMCR = ost_reg[device].pOMCR;
            desc->Reg.pOSMR = ost_reg[device].pOSMR;
            desc->Reg.pOSCR = ost_reg[device].pOSCR; 
            
            if (desc->Reg.pOMCR)                       
                *desc->Reg.pOMCR =  0;  
            else     
            OSSR = desc->Reg.ossrbit;              
        }   
}   



void
ostimer_init (void)
{   
        U32  device = TIMER0;   
    
        OIER = 0;                      /* disable any timer interrupts */
        OSSR = ~(OSSR_RESERVED_BITS);  /* clear status on all timers */
            
        ost_setup();

        g_timer_realtime.msec = 0; 
        g_timer_realtime.sec = 0;     
        g_timer_realtime.min = 0;    
        g_timer_realtime.hour = 0;                     
        
        // 
        // init system tick timer 0
        //         
        register_ostimer(&device, 1, OST_PERIODIC, system_time_isr, 
                         "timer0", g_ost_desc);    


                                                                       
        
        //
        // handle OST 4..11 ISR.
        //
        register_irq(IRQ_OST_4_11, ost_4_11_irq_isr, 
                     "OST4_11 ISR", &g_ost_desc[4]);        
        pxa_unmask_low_irq(IRQ_OST_4_11);       
}       
// --------------------------------------------------------------------
//
//   Title     :  uart.c
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  uart Program for Creator Board
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
//   V1.0   | 12/22/2006 | First release
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
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "common/include/addr.h"
#include "irq/include/irq.h"
#include "uart/include/uart.h"
#include "serial_reg.h"


/*************************************************************************
Constant define
*************************************************************************/
#define NR_UARTS      3
//#define EXE3
/* modem lines */
#define TIOCM_LE    0x001
#define TIOCM_DTR   0x002
#define TIOCM_RTS   0x004
#define TIOCM_ST    0x008
#define TIOCM_SR    0x010
#define TIOCM_CTS   0x020
#define TIOCM_CAR   0x040
#define TIOCM_RNG   0x080
#define TIOCM_DSR   0x100
#define TIOCM_CD    TIOCM_CAR
#define TIOCM_RI    TIOCM_RNG
#define TIOCM_OUT1  0x2000
#define TIOCM_OUT2  0x4000
#define TIOCM_LOOP  0x8000
#define TIOCM_AFE   0x1000  /* flow control */


#define QUEUE_SIZE  2048

typedef struct 
{
    unsigned char buf[QUEUE_SIZE];   /* data buffer */
    int           wptr;               /* write pointer */
    int           rptr;               /* read pointer */
} queue_t;


typedef struct uart_port 
{
    U8                  *membase;       /*            */
    U32                 irq;            /* irq number */
    U32                 uartclk;        /* base uart clock */
    U8                  fifosize;       /* tx fifo size */
    U32                 line;           /* port index */
    U32                 mctrl ;         /* current modem ctrl settings */
    U8                  name[32];
    termios_t           termios ;
    
    queue_t             txqueue ;       /* tx buffer */
    queue_t             rxqueue ;       /* rx buffer */
    
} uart_port_t, *p_uart_port_t;  


typedef struct uart_pxa_port 
{
    uart_port_t        port;    
    U32                cken;    
            
    U8                 ier;
    U8                 lcr;
    U8                 mcr;
    U8                 inused;  
}uart_pxa_port_t, *p_uart_pxa_port_t;


#define uart_circ_empty(circ)       ((circ)->wptr == (circ)->rptr)
#define uart_circ_clear(circ)       ((circ)->wptr = (circ)->rptr = 0)

/*************************************************************************
Function prototypes
*************************************************************************/
static void serial_isr(U16 irq, struct irq_desc *desc, void *pVoid);
static inline void uart_receive_chars (uart_pxa_port_t *up, int *status);
static void uart_transmit_chars (uart_pxa_port_t  *up);
static inline U32  serial_in(uart_pxa_port_t *up, int offset);
static inline void serial_out(uart_pxa_port_t *up, int offset, int value);
static void uart_start_tx(uart_pxa_port_t *up);
static void uart_stop_tx(uart_pxa_port_t *up);
static void uart_start_rx(uart_pxa_port_t *up);
static void uart_stop_rx(uart_pxa_port_t *up);
static unsigned int uart_baud2quot(uart_pxa_port_t *up, unsigned int baudrate);
static void uart_set_termios_mctrl(uart_pxa_port_t *up,  termios_t *termios);
static void uart_set_termios (uart_pxa_port_t *up, termios_t *termios);
static void uart_set_mctrl(uart_pxa_port_t *up, unsigned int mctrl);
static int  uart_port_startup(uart_pxa_port_t *up);
static int  uart_port_shutdown(uart_pxa_port_t *up);
static void uart_tx_queue_init(uart_pxa_port_t *up);
static void uart_rx_queue_init(uart_pxa_port_t *up);
static int  uart_tx_queue_write(uart_pxa_port_t *up, char data);
static int  uart_tx_queue_read(uart_pxa_port_t *up, char *ch);
static int  uart_rx_queue_write(uart_pxa_port_t *up, char data);
static int  uart_rx_queue_read(uart_pxa_port_t *up, char *ch);


/*************************************************************************
Variable define
*************************************************************************/
static struct uart_pxa_port serial_pxa_ports[NR_UARTS]   ;

int
uart_on (int channel, termios_t *termios)
{
         uart_pxa_port_t  *up = &serial_pxa_ports[channel];     
         
         if (channel < UART0 || channel > UART2 || up->inused)
             return (UM);
                
         uart_port_startup(up);  
         uart_set_config(channel, termios);         
         up->inused = 1;

         return (OK);        
}   



int
uart_start (int channel)
{
         uart_pxa_port_t  *up = &serial_pxa_ports[channel];     
         
         if (channel < UART0 || channel > UART2)
             return (UM);   
             
         //uart_start_tx(up);             
         uart_start_rx(up);             
}   



int
uart_stop (int channel)
{
        uart_pxa_port_t  *up = &serial_pxa_ports[channel];      
         
        if (channel < UART0 || channel > UART2)
            return (UM);    
             
        uart_stop_tx(up);             
        uart_stop_rx(up);               
}   
    
    

int
uart_off (int channel)
{
        uart_pxa_port_t  *up = &serial_pxa_ports[channel];      

        if (channel < UART0 || channel > UART2)
            return (UM);    
            
        up->inused = 0;
        return (uart_port_shutdown(up));
}   



int
uart_set_speed (int channel, unsigned int baud)
{
        termios_t        termios;   
        uart_pxa_port_t  *up = &serial_pxa_ports[channel];      

        if (channel < UART0 || channel > UART2)
            return (UM);                    
                            
        uart_get_config(channel, &termios);
        termios.baud_rate = baud ;
                                        
        uart_stop(channel);                 
        uart_set_termios(up, &termios);             
        uart_start(channel);    
}



int
uart_set_flow (int channel, int enable_rts, int auto_flow)
{
        uart_pxa_port_t  *up = &serial_pxa_ports[channel];  
        termios_t        termios;       
        if (channel < UART0 || channel > UART2)
            return (UM);                    
                            
        uart_get_config(channel, &termios);
        
        termios.rts = enable_rts;
        termios.afe = auto_flow;                                                    
        uart_set_termios_mctrl(up, &termios);                               
        
        uart_stop(channel);                 
        uart_set_termios(up, &termios);             
        uart_start(channel);    
}
    
    

int 
uart_set_config (int channel, termios_t *termios)
{
        uart_pxa_port_t  *up = &serial_pxa_ports[channel];      

        if (channel < UART0 || channel > UART2)
            return (UM);    
                
        uart_set_termios_mctrl(up, termios);                                    
        uart_stop(channel);                 
        uart_set_termios(up, termios);              
		uart_flush_buffer(channel);
        uart_start(channel);
        
        return (OK); 
}



int 
uart_get_config (int channel, termios_t *termios)
{
        uart_pxa_port_t  *up = &serial_pxa_ports[channel];      

        if (channel < UART0 || channel > UART2)
            return (UM);
            
        memcpy(termios, &up->port.termios, sizeof(termios_t));
        return (OK);                                
}



int
uart_get_char (int channel, char *ch)
{
        uart_pxa_port_t  *up = &serial_pxa_ports[channel];      
        int  nRet ;         

        if (channel < UART0 || channel > UART2)
            return (UM);    
         
        nRet = uart_rx_queue_read(up, ch);                    
        return (nRet);          
}   



int
uart_put_char (int channel, char ch)
{
        uart_pxa_port_t  *up = &serial_pxa_ports[channel];      
        int              nRet ;         

        if (channel < UART0 || channel > UART2)
            return (UM);    
         
        nRet = uart_tx_queue_write(up, ch); 
        if (nRet)        
            uart_start_tx(up);
            
        return (nRet);                      
}   



int
uart_put_string (int channel, char* pstring)
{
        uart_pxa_port_t  *up = &serial_pxa_ports[channel];      
        char             *ptr, ch;
        int              nRet = OK;         

        if (channel < UART0 || channel > UART2)
            return (UM);    
         
        ptr = pstring ;
        while (*ptr && nRet) {
            nRet = uart_tx_queue_write(up, *ptr); 
            if (nRet == UM)
                break;
            if (*ptr++ == '\n')
                nRet = uart_tx_queue_write(up, '\r');                     
        }             
        
        if (nRet)        
            uart_start_tx(up);
            
        return (nRet);                      
}   



int  
uart_flush_buffer (int channel)
{
        uart_pxa_port_t  *up = &serial_pxa_ports[channel];           

        if (channel < UART0 || channel > UART2)
            return (UM);    

        uart_circ_clear(&up->port.txqueue);        
        return (OK);            
}   



static void
serial_isr (U16 irq, struct irq_desc *desc, void *pVoid)
{
        uart_pxa_port_t  *up = (uart_pxa_port_t  *)pVoid;
        unsigned int iir, lsr;
        /*
         * 檢查是否中斷等待處理
         */          
        iir = serial_in(up, UART_IIR);
        if (iir & UART_IIR_NO_INT)
            return ;
			
		mt_printf("ISR of UART\n");
            
        //MaskInterrupt(up->port.irq);            
        lsr = serial_in(up, UART_LSR);
        
        /*
         * 檢查接收端是否有資料
         */
        if (lsr & UART_LSR_DR){
            uart_receive_chars(up, &lsr);
        }            
        
        
        /*
         * 檢查傳送端是否送完資料
         */        
        if (lsr & UART_LSR_THRE){
            uart_transmit_chars(up);
        }            
        //UnMaskInterrupt(up->port.irq);         
}



static void
uart_receive_chars (uart_pxa_port_t  *up, int *status)
{
        queue_t       *queue = &up->port.rxqueue;   
        unsigned int  ch ;
        int           max_count = 256;

        do {        
            ch = serial_in(up, UART_RX);
            queue->buf[queue->wptr++] = ch ;
            if (queue->wptr == QUEUE_SIZE)
                queue->wptr = 0;
                
            if (uart_circ_empty(queue))
                break ;    
                
            *status = serial_in(up, UART_LSR);
        } while ((*status & UART_LSR_DR) && (max_count-- > 0));
}



static void 
uart_transmit_chars (uart_pxa_port_t  *up)
{
        queue_t  *xmit = &up->port.txqueue;
        int      count;

        if (uart_circ_empty(xmit)) {
            uart_stop_tx(up);           
            return;
        }

        count = up->port.fifosize / 2;
        do {
            serial_out(up, UART_TX, xmit->buf[xmit->rptr]);
            xmit->rptr++;
            if (xmit->rptr == QUEUE_SIZE)
                xmit->rptr = 0;
                        
            if (uart_circ_empty(xmit)) 
                break;
                
        } while (--count > 0);

        if (uart_circ_empty(xmit)) 
            uart_stop_tx(up);
}



static  U32 
serial_in (uart_pxa_port_t *up, int offset)
{
        volatile U32 *ptr = (U32 *)up->port.membase;        
       
        return (*(ptr+offset));
}



static  void 
serial_out (uart_pxa_port_t *up, int offset, int value)
{
        volatile U32 *ptr = (U32 *)up->port.membase;        
         
        *(ptr+offset) =(U32) value;
}



static void 
uart_start_tx (uart_pxa_port_t *up)
{
        if (!(up->ier & UART_IER_THRI)) {
            up->ier |= UART_IER_THRI;
            serial_out(up, UART_IER, up->ier);
        }
}



static void 
uart_stop_tx (uart_pxa_port_t *up)
{
        if (up->ier & UART_IER_THRI) {
            up->ier &= ~UART_IER_THRI;
            serial_out(up, UART_IER, up->ier);
        }
}



static void 
uart_start_rx (uart_pxa_port_t *up)
{
        if (!(up->ier & UART_IER_RLSI)){
            up->ier |= UART_IER_RLSI;
			serial_out(up, UART_IER, up->ier);
		}
}



static void 
uart_stop_rx (uart_pxa_port_t *up)
{
		if (up->ier & UART_IER_RLSI){
			up->ier &= ~UART_IER_RLSI;
			serial_out(up, UART_IER, up->ier);
		}
}


    
static  unsigned int 
uart_baud2quot (uart_pxa_port_t *up, unsigned int baudrate)
{
        int baud[] = {
                      150, 200, 300, 600, 1200, 1800, 2400, 4800,
                      9600, 19200, 38400, 57600, 115200 
                     }; 
        int i, cbaud = 9600;

                 
        for (i=0; i < ARRAY_LENGTH(baud); i++){
            if (baudrate == baud[i]){
                cbaud = baudrate ;                  
            }                                     
        }

        return (up->port.uartclk / cbaud);
}   



static void
uart_set_termios (uart_pxa_port_t *up, termios_t *termios)
{
        unsigned long flags;
        unsigned int  baud, quot;
        unsigned char cval, fcr = 0;        

        switch (termios->word_len) {
        case CS5:
            cval = UART_LCR_WLEN5;
            break;
        case CS6:
            cval = UART_LCR_WLEN6;
            break;
        case CS7:
            cval = UART_LCR_WLEN7;
            break;
        default:
        case CS8:
            cval = UART_LCR_WLEN8;
            break;
        }

        if (termios->stop_bit & CSTOPB)
            cval |= UART_LCR_STOP;
            
        if (termios->parity & PARENB)
            cval |= UART_LCR_PARITY;
        if (!(termios->parity & PARODD))
            cval |= UART_LCR_EPAR;

        /*
         * Ask the core to calculate the divisor for us.
         */         
        quot = uart_baud2quot(up, termios->baud_rate);  

        /*
         * 設定FIFO 
         */    
        if (termios->baud_rate < 2400)
            fcr = UART_FCR_ENABLE_FIFO | UART_FCR_PXAR1;
        else if (termios->baud_rate < 230400)
            fcr = UART_FCR_ENABLE_FIFO | UART_FCR_PXAR8;
        else
            fcr = UART_FCR_ENABLE_FIFO | UART_FCR_PXAR32;         

        /*
         * Ok, we're now changing the port state.  Do it with
         * interrupts disabled.
         */
        MaskInterrupt(up->port.irq);

        /*
         * Ensure the port will be enabled.
         * This is required especially for serial console.
         */
        up->ier |= IER_UUE;


        /*
         * CTS flow control flag and modem status interrupts
         */
        up->ier &= ~UART_IER_MSI;

        serial_out(up, UART_IER, up->ier);

        serial_out(up, UART_LCR, cval | UART_LCR_DLAB);/* set DLAB */
        serial_out(up, UART_DLL, quot & 0xff);         /* LS of divisor */
        serial_out(up, UART_DLM, quot >> 8);           /* MS of divisor */
        serial_out(up, UART_LCR, cval);                /* reset DLAB */
        up->lcr = cval;                                /* Save LCR */
        uart_set_mctrl(up, up->port.mctrl);
        serial_out(up, UART_FCR, fcr);
                
        UnMaskInterrupt(up->port.irq);        
        memcpy(&up->port.termios, termios, sizeof(termios_t));        
}   



static void 
uart_set_termios_mctrl (uart_pxa_port_t *up,  termios_t *termios)
{
        U32              mctrl;
  
        mctrl = up->port.mctrl ;
        mctrl &= ~(TIOCM_RTS | TIOCM_AFE);
        
        if (termios->rts)
            mctrl |= TIOCM_RTS;            
       
        if (termios->afe)
            mctrl |= TIOCM_AFE ;           
        up->port.mctrl = mctrl ;        
}
    


static void 
uart_set_mctrl (uart_pxa_port_t *up, unsigned int mctrl)
{
        U8 mcr = 0;

        if (mctrl & TIOCM_DTR)
            mcr |= UART_MCR_DTR;
        if (mctrl & TIOCM_RTS)
            mcr |= UART_MCR_RTS;
        if (mctrl & TIOCM_OUT1)
            mcr |= UART_MCR_OUT1;
        if (mctrl & TIOCM_OUT2)
            mcr |= UART_MCR_OUT2;
        if (mctrl & TIOCM_LOOP)
            mcr |= UART_MCR_LOOP ;            
        if (mctrl & TIOCM_AFE)
            mcr |= UART_MCR_AFE ;            

        mcr |= up->mcr;

        serial_out(up, UART_MCR, mcr);
}


static int
uart_port_startup (uart_pxa_port_t *up)
{
       int retval;  

       uart_tx_queue_init(up);       
       uart_rx_queue_init(up);
              
       CKEN |= up->cken ;  // enable UART clock
              
       up->mcr = 0;          

       retval = register_irq(up->port.irq, serial_isr, up->port.name, up);
       if (!retval)
           return (0);
           
       pxa_unmask_low_irq(up->port.irq);               

       serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO);
       serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO |
                  UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
       serial_out(up, UART_FCR, 0);

       serial_in(up, UART_LSR);
       serial_in(up, UART_RX);
       serial_in(up, UART_IIR);
       serial_in(up, UART_MSR);

       serial_out(up, UART_LCR, UART_LCR_WLEN8);


       up->port.mctrl |= TIOCM_OUT2;
       uart_set_mctrl(up, up->port.mctrl);


       up->ier = UART_IER_RLSI | UART_IER_RDI | UART_IER_RTOIE | UART_IER_UUE;
       serial_out(up, UART_IER, up->ier);

       serial_in(up, UART_LSR);
       serial_in(up, UART_RX);
       serial_in(up, UART_IIR);
       serial_in(up, UART_MSR);     
       
       return (1);
}   



static int
uart_port_shutdown (uart_pxa_port_t *up)
{
        unregister_irq(up->port.irq, up->port.name);

        /*
         * Disable interrupts from this port
         */
        up->ier = 0;
        serial_out(up, UART_IER, up->ier);

        up->port.mctrl &= ~TIOCM_OUT2;
        uart_set_mctrl(up, up->port.mctrl);

        /*
         * Disable break condition and FIFOs
         */
        serial_out(up, UART_LCR, serial_in(up, UART_LCR) & ~UART_LCR_SBC);
        serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO |
                       UART_FCR_CLEAR_RCVR |
                       UART_FCR_CLEAR_XMIT);
        serial_out(up, UART_FCR, 0);
        
        return (OK);    
}




/*****************************************************/
/*  UART QUEUE function Initialize and Read, Write   */
/*****************************************************/
static void 
uart_tx_queue_init (uart_pxa_port_t *up)
{
        queue_t  *queue = &up->port.txqueue;
        int      i ;        
       
        for (i=0; i < QUEUE_SIZE; i++){    
            queue->buf[i] = '\0';
        }
        uart_circ_clear(queue);
}



static void 
uart_rx_queue_init (uart_pxa_port_t *up)
{
        queue_t  *queue = &up->port.txqueue;
        int      i;        
       
        for (i=0; i < QUEUE_SIZE; i++){    
            queue->buf[i] = '\0';
        }
        uart_circ_clear(queue);
}



static int  
uart_tx_queue_write (uart_pxa_port_t *up, char data)
{
        queue_t  *queue = &up->port.txqueue;;       
    
        if (queue->wptr + 1 == queue->rptr) {        
            /*
             * buffer overflow
             */ 
            return (UM); 
        }
        queue->buf[queue->wptr++] = data;
        if (queue->wptr == QUEUE_SIZE)
            queue->wptr = 0;

        return (OK);
}



static int 
uart_tx_queue_read (uart_pxa_port_t *up, char *ch)
{
        queue_t  *queue = &up->port.txqueue;                    
        
        if (queue->rptr == QUEUE_SIZE) 
            queue->rptr = 0; /*loop back*/
     
        if (uart_circ_empty(queue)) {
            return (UM); //ring buffer is empty state
        }
        queue->rptr++;
        *ch = queue->buf[queue->rptr-1];
        
        return (OK);
}


static int  
uart_rx_queue_write (uart_pxa_port_t *up, char data)
{
        queue_t  *queue = &up->port.rxqueue;
        
        if (queue->wptr + 1 == queue->rptr) {        
            /*
             * buffer overflow
             */ 
            return (UM); 
        }
        queue->buf[queue->wptr++] = data;
        if (queue->wptr == QUEUE_SIZE)
            queue->wptr = 0;

        return (OK);
}



static int 
uart_rx_queue_read (uart_pxa_port_t *up, char *ch)
{
        queue_t  *queue = &up->port.rxqueue;                    
        
        if (queue->rptr == QUEUE_SIZE) 
            queue->rptr = 0; /*loop back*/
     
        if (uart_circ_empty(queue)) {
            return (UM); //ring buffer is empty state
        }
        queue->rptr++;
        *ch = queue->buf[queue->rptr-1];
        
        return (OK);
}



int
uart_init (void)
{                              
        uart_pxa_port_t *up;        
        int             i;

        for (i=0; i < NR_UARTS; i++){
            up = &serial_pxa_ports[i];
			memset(up, 0, sizeof(uart_pxa_port_t));
            if (i == 0){                
                up->cken = CKEN6_FFUART ;               
                up->port.membase = (U8*)&FFUART ;
                up->port.irq = IRQ_FFUART ;
                up->port.uartclk = 921600 ;
                up->port.fifosize = 64 ;                                    
                up->port.line = 1 ;              
                up->port.mctrl = TIOCM_RTS;
                strcpy(up->port.name, "FFUART");
            }       
            else if (i == 1){                
                up->cken = CKEN7_BTUART ;               
                up->port.membase = (U8*)&BTUART ;
                up->port.irq = IRQ_BTUART ;
                up->port.uartclk = 921600 ;
                up->port.fifosize = 64 ;                                    
                up->port.line = 1 ;      
                up->port.mctrl = TIOCM_RTS;                        
                strcpy(up->port.name, "BTUART");                     
            }   
            else {
                up->cken = CKEN5_STUART ;               
                up->port.membase = (U8*)&STUART ;
                up->port.irq = IRQ_STUART ;
                up->port.uartclk = 921600 ;
                up->port.fifosize = 64 ;                                    
                up->port.line = 1 ;                              
                strcpy(up->port.name, "STUART");            
            }               
                            
            up->port.termios.baud_rate = 9600;                        
            up->port.termios.word_len = CS8;  
            up->port.termios.parity = 0;  
            up->port.termios.stop_bit = 0;  
            up->port.termios.rts = 1;       
            up->inused = 0;                                             
        }                                   
        
        for (i=0; i < NR_UARTS; i++){
            up = &serial_pxa_ports[i];
            uart_stop_rx(up);                   
            uart_stop_tx(up);  
            uart_tx_queue_init(up);                         
            uart_rx_queue_init(up);               
        }           
         
        return (1); 
}


int
uart_exit (void)
{
        return (1);
}   




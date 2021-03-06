// --------------------------------------------------------------------
//
//   Title     :  creator_io.c
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  Creator XScale-PXA270 CPLD routines for Creataor Board
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
//   V1.0   | 01/11/2007 | First release
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

#include "common/include/creator_io.h"

creator_regs_t      gcreator_io;
p_base_regs_t       pg_base_regs;
p_main_regs_t       pg_main_regs;



/*************************************************************************
Constant define
*************************************************************************/



/*************************************************************************
Function prototypes
*************************************************************************/



/*************************************************************************
Variable define
*************************************************************************/



/*************************************************************************
creator board LED
*************************************************************************/
void 
mt_main_led_set (U16 led)
{
        p_creator_regs_t  p_reg = &gcreator_io;  
        
        p_reg->io_reg2.fields.led = (led & 0xff);
        
        pg_main_regs->io_reg2 = p_reg->io_reg2.value ;
}



int  
mt_main_led_on (int bit)
{
        p_creator_regs_t p_reg = &gcreator_io;
        U8               *p_addr = &p_reg->io_reg2.fields.led;
        U8               bitval ;                   
        
        if (bit < MAIN_LED_D9 || bit > MAIN_LED_D16)
            return (UM);
                        
        bitval = (1 << bit);
        *p_addr &= ~(bitval);
        pg_main_regs->io_reg2 = p_reg->io_reg2.value ;        
                                  
        return (OK);
}



int 
mt_main_led_off (int bit)
{
        p_creator_regs_t p_reg = &gcreator_io;
        U8               *p_addr = &p_reg->io_reg2.fields.led;
        U8               bitval ;                   
        
        if (bit < MAIN_LED_D9 || bit > MAIN_LED_D16)
            return (UM);
                        
        bitval = (1 << bit);
        *p_addr |= (bitval);
        
        pg_main_regs->io_reg2 = p_reg->io_reg2.value ; 
               
        return (OK);
}



int  
mt_main_keypad_set_scanline (U32 code)
{
        p_creator_regs_t  p_reg = &gcreator_io;                

        p_reg->io_reg2.fields.scan = (U8)code;                                  
        pg_main_regs->io_reg2 = p_reg->io_reg2.value ;  
                                        
        return (OK);
}



U32  
mt_main_keypad_get_scancode (void){
                                
        return ((pg_main_regs->io_reg1 & 0x0f00) >> 8);                                  
}



int  
mt_main_7segment_set (U16 segment, U16 common)
{
        p_creator_regs_t p_reg = &gcreator_io; 
        U16              io_reg0 = p_reg->io_reg0.value;                

        io_reg0 &= 0xF000;
        io_reg0 |= (segment) | ((common & 0x0f) << 8);   
        p_reg->io_reg0.value = io_reg0;                                                              
        pg_main_regs->io_reg0 = p_reg->io_reg0.value;  
               
        return (OK);
}



/*************************************************************************
creator board DIP switch
*************************************************************************/
U8 
mt_main_sw_get (void)
{        
        return((UC)(pg_main_regs->io_reg1));
}



U16
mt_main_io_reg0_get (void)
{      
        return (gcreator_io.io_reg0.value);        
}



void
mt_main_io_reg0_set (U16 value)
{
        p_creator_regs_t   p_reg = &gcreator_io;          
       
        p_reg->io_reg0.value = (U16)value;
        pg_main_regs->io_reg0 = p_reg->io_reg0.value;        
}



/*************************************************************************
PX270 S1 & S2 switch
*************************************************************************/
int
mt_base_sw_get (int sw_idx)
{           
        	
        switch (sw_idx){                	
        case BASE_SW_1 :
            return ((pg_base_regs->master_status1 & 0x01) ? KEY_NO_PRESS :
                     KEY_PRESS);                                 
        case BASE_SW_2 :
            return ((pg_base_regs->master_status1 & 0x02) ? KEY_NO_PRESS :
                    KEY_PRESS);                                                  
        }       
        
        return (KEY_NO_PRESS);
}



/*************************************************************************
PX270 D1..D4 LED
*************************************************************************/
void 
mt_base_led_set (U16 led)
{
        volatile U16         *p_addr = &pg_base_regs->master_ctrl2; 
        UC                   value ;                                              
                       
        value = ((led & 0xf) << 4);                      
        *p_addr &= ~(0xf0);
        *p_addr |= value;                                  
}



U16 
mt_base_led_get (void)
{
        volatile U16         *p_addr = &pg_base_regs->master_ctrl2; 
        U16                   value ;                                                                     
                
        value = (*p_addr & 0xf0) >> 4;
        
        return (value);                                  
}



int  
mt_base_led_on (int bit)
{
        volatile U16         *p_addr = &pg_base_regs->master_ctrl2;
        U16                  bitval ;                   
        
        if (bit < BASE_LED_D1 || bit > BASE_LED_D4)
            return (UM);
                        
        bitval = (1 << bit);
        *p_addr &= ~(bitval);
                                  
        return (OK);
}



int
mt_base_led_off (int bit)
{
        volatile U16         *p_addr = &pg_base_regs->master_ctrl2;
        U16                  bitval ;                   
        
        if (bit < BASE_LED_D1 || bit > BASE_LED_D4)
            return (UM);
                        
        bitval = (1 << bit);
        *p_addr |= (bitval);
        
        return (OK);
}



void
mt_base_d1_d4_connect_pwm0_pwm3 (void)
{
        //connect D1 to PWM0, D4 to PWM3 
        pg_base_regs->master_ctrl1 |= 0x80;    
}
    


void
mt_base_d1_d4_disconnect_pwm0_pwm3 (void)
{
        //disconnect D1 to PWM0, D4 to PWM3      
        pg_base_regs->master_ctrl1 &= (~0x80);     
}



U16
mt_base_cpld_ctrl3_get (void)
{      
        return (gcreator_io.master_ctrl3);        
}



void
mt_base_cpld_ctrl3_set (U16 value)
{
        p_creator_regs_t   p_reg = &gcreator_io;          
       
        p_reg->master_ctrl3 = (U16)value;
        pg_base_regs->master_ctrl3 = p_reg->master_ctrl3;        
}



void
mt_base_cpld_ctrl3_set_bit (U16 bit)
{              
        U16      value = gcreator_io.master_ctrl3;   
       
        value |= (1 << bit);
       
        pg_base_regs->master_ctrl3 = value ;
}



void
mt_base_cpld_ctrl3_clear_bit (U16 bit)
{              
        U16    value = gcreator_io.master_ctrl3;     
       
        value &= ~(1 << bit);
       
        pg_base_regs->master_ctrl3 = value ;   
}



U8
mt_main_cpld_get_version(void)
{
        return (gcreator_io.main_cpld_version);           
}      



static void
mt_base_board_init (p_creator_regs_t p_reg)
{   
        p_base_regs_t   p_base_regs = p_reg->p_base_regs;
          
        p_base_regs->master_ctrl1 = 0x12;        
        p_base_regs->master_ctrl2 = 0xFF;      
        
        p_reg->master_ctrl3 = 0;      
        p_base_regs->master_ctrl3 = 0x00;        
        
        p_base_regs->master_intmask1 = 0xFF;  
        p_base_regs->master_intmask2 = 0xFF;                    
}   



/*************************************************************************
System Initialize
*************************************************************************/
static void
mt_main_board_init (p_creator_regs_t p_reg)
{
        p_main_regs_t p_main_regs = p_reg->p_main_regs;
            
        // get Creator Board Version for IRQ ;
        //
        p_reg->main_cpld_version = p_main_regs->cpld_ctrl >> 8 ; 
        
        p_reg->io_reg0.value = 0xc000;
        p_main_regs->io_reg0 = p_reg->io_reg0.value;
            
        p_reg->io_reg2.value = 0xff;    
        p_main_regs->io_reg2 = p_reg->io_reg2.value;      
        
        p_reg->cpld_ctrl = 0x3D ;             
        p_main_regs->cpld_ctrl = p_reg->cpld_ctrl;        
        
        switch(p_reg->main_cpld_version) {
        	case 0x00 :	//CPLD_VERSION = V1.0
        	case 0x10 :	//CPLD_VERSION = V1.0
        		p_reg->cpld_ctrl |= 0xc0;    //IRQ3=XnINT, DMA1=XnDRQ
        		break;
        	case 0x11 :	//CPLD_VERSION = V1.1
        		p_reg->cpld_ctrl |= 0xc0;    //IRQ3=XnINT, DMA1=XnDRQ
        		break;
        	case 0x13 :	//CPLD_VERSION = V1.2
        		p_reg->cpld_ctrl |= 0xc0;    //IRQ3=XnINT, DMA1=XnDRQ
        		break;        		
        	case 0x14 :	//CPLD_VERSION = V1.4
        		p_reg->cpld_ctrl |= 0xc0;    //IRQ3=XnINT, DMA1=XnDRQ
        		break;        		
        	default :
        		break;
        }
        p_main_regs->cpld_ctrl = p_reg->cpld_ctrl;        
}



int
creator_io_init (void)
{
        p_creator_regs_t  p_reg = &gcreator_io;    

        pg_base_regs = (p_base_regs_t)CS4_BASE ;;
        p_reg->p_base_regs = pg_base_regs ;
        
        pg_main_regs = (p_main_regs_t)ECS0_BASE ;
        p_reg->p_main_regs = pg_main_regs;
        
        mt_base_board_init(p_reg);  
        mt_main_board_init(p_reg);
        mt_main_led_set(0x55);
                
        return (OK);       
}   
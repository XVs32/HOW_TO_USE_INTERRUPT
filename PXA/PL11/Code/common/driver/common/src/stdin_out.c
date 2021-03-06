// --------------------------------------------------------------------
//
//   Title     :  stdin_out.c
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  standard in/out process for Creator Board
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

#include "common/include/addr.h"
#include "lcd/include/lcd.h"



/*************************************************************************
Constant define
*************************************************************************/
typedef void (*putch_func)(char);
typedef void (*puts_func)(char *);
typedef int  (*getch_func)(void);
typedef char*(*gets_func)(char*);
typedef void (*setcursor_func)(int x, int y);
typedef void (*getcursor_func)(int *x, int *y);
typedef void (*clrscr_func)(void);

typedef struct stdio_st 
{
        /*
         *  ��J/��X�����
         */  
        putch_func  putch_funptr ;     
        puts_func   puts_funptr  ; 
        getch_func  getch_funptr ;
        gets_func   gets_funptr ;

        /*
         *  �B�~��X�����. 
         */
        putch_func  option_putch_funptr ;     
        puts_func   option_puts_funptr  ; 
    
        /*
         * ���������
         */
        setcursor_func setcursor_funptr;    
        getcursor_func getcursor_funptr;
   
   
        /*
         * ���������
         */
        clrscr_func clrscr_funptr;    
                
} stdio_t, *p_stdio_t ;



/*************************************************************************
Function prototypes
*************************************************************************/



/*************************************************************************
Variable define
*************************************************************************/
stdio_t stdio_info ;

    

void
mt_putch (char ch)
{
        p_stdio_t  info = &stdio_info ; 
        
        if (info->putch_funptr){
            (*info->putch_funptr)(ch);   
            if (info->option_putch_funptr){
                (*info->option_putch_funptr)(ch);               
            }                       
        }               
}   



void
mt_puts (char *msg)
{
        p_stdio_t  info = &stdio_info ; 
        
        if (info->puts_funptr){
            (*info->puts_funptr)(msg);   
            if (info->option_puts_funptr){
                (*info->option_puts_funptr)(msg);               
            }                       
        }       
}



void
mt_printf (__const char *fmt, ...)
{
        va_list     ap;
        char        string[512], *p=string;

        va_start(ap, fmt);
        vsprintf(string, fmt, ap); 
        mt_puts(string);
        va_end(ap);             
}
        


int
mt_getch (void) 
{
        p_stdio_t  info = &stdio_info ;     
        
        if (info->getch_funptr)
            return ((*info->getch_funptr)());
            
        return (-1);
}



char *
mt_gets (char *p_out_buffer)    
{
        p_stdio_t  info = &stdio_info ;     
        
        if (info->getch_funptr)
            return ((*info->gets_funptr)(p_out_buffer));    
            
        return (NULL);              
}   



void
mt_clrscr (void)
{
        p_stdio_t  info = &stdio_info ;     
        
        if (info->clrscr_funptr)
            (*info->clrscr_funptr)();                       
}   



void
mt_getcursor (int *x, int *y)
{
        p_stdio_t  info = &stdio_info ;     
        
        if (info->getcursor_funptr)
            (*info->getcursor_funptr)(x, y);                    
}


void
mt_setcursor (int x, int y)
{
        p_stdio_t  info = &stdio_info ;     
        
        if (info->setcursor_funptr)
            (*info->setcursor_funptr)(x, y);                    
}



void
mt_enable_cursor (void)
{
        LCD_EnableCursor(&screen_info, SCREEN_CURSOR_ON);   
}
    

    
void
mt_disable_cursor (void)
{
        LCD_EnableCursor(&screen_info, SCREEN_CURSOR_OFF);  
}



void
stdio_setup (p_stdio_t *info)
{
}   




void
stdio_reset (void)
{
        p_stdio_t info = &stdio_info;        
        
        info->putch_funptr = LCD_putch ;          //��X�r�������V��LCD
        info->puts_funptr  = LCD_puts ;           //��X�r������V��LCD 
        info->getch_funptr = NULL;
        info->gets_funptr  = NULL ;

        info->option_putch_funptr = NULL ;        //�B�~��X�r�������V
        info->option_puts_funptr = NULL ;         //�B�~��X�r������V
        
        info->clrscr_funptr = LCD_clear_screen;   //��X�ù����ťը��
        info->setcursor_funptr = LCD_set_cursor ; //�]�w��гB�z���
        info->getcursor_funptr = LCD_get_cursor;  //���o��гB�z���       
}   



void
stdio_init (void)
{
        stdio_reset();       
}



void
stdio_exit (void)
{
}   
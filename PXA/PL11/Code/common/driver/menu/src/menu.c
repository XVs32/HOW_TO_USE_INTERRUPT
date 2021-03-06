// --------------------------------------------------------------------
//
//   Title     :  menu.c
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  menu process for Creator Board
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
//   V1.0   | 12/25/2006 | First release
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
#include "common/include/stdin_out.h"
#include "lcd/include/lcd.h"
#include "menu/include/menu.h"




/*************************************************************************
Constant define
*************************************************************************/
//#define LAB_MODIFY           1



/*************************************************************************
Function prototypes
*************************************************************************/
int  menu_change(void) { return (1); }
int  menu_space(void)  { return (1); }
int  menu_quit(void)   { return (1); }  

static int   menu_open(menu_t *mn, int src_heigth);



/*************************************************************************
Variable define
*************************************************************************/


void
process_menu (menu_t *top_mn, int scr_height,              
              mu_func_ptr funptr, void *pVoid)
{
        menu_t    *active_mn ;  
        U32       func_addr ;
        int       terminate = 1, second_loop;
        int       sel, i, menu_item_count; 
        int       sx, sy;       
        U8        ch ;        
    
        active_mn = top_mn ;         
                
        while (terminate){                                      
            mt_disable_cursor();            
            
            mt_clrscr();
            menu_item_count = menu_open(active_mn, scr_height);             
            second_loop = 1;
            while (second_loop){                
                
                /*
                 * 呼叫使用者待處理的事項
                 */
                if (funptr)
                    (*funptr)(pVoid);    
                                    
                /*
                 * 等待使用者選擇選項
                 */            
                if (chk_key(&ch) == UM)
                    continue ;                    
                
                if (get_key(&ch) == UM)
                    continue ;
                    
                if (ch < 0 || ch >= menu_item_count)
                    continue ;
                      
                /*
                 * 跳過空白行之選單, 選擇真正的選項
                 */
                for (i=sel=0; (active_mn+sel)->funptr; i++){
                    if ((U32)((active_mn+i)->funptr) != (U32)menu_space){ 
                        if (sel == ch){
                            sel = i;
                            break ;
                        }
                        sel++;                        
                    }                            
                }                 
                       
                if ((active_mn+sel)->funptr){
                    func_addr = (U32)((active_mn+sel)->funptr);
                    if (func_addr == (U32)menu_quit){                   
                        
                        return ;
                        
                    }   
                    else if (func_addr == (U32)menu_change){
                        active_mn = (active_mn+sel)->next;                          
                    }                    
                    else {
                        mt_enable_cursor();                         
                        (active_mn+sel)->funptr();   
                        mt_printf("\nAny Key To Ret:");    
                        while(get_key(&ch) == UM);                                                                               
                    }             
                    second_loop = 0;                         
                }                                    
            }                   
        }            
        mt_enable_cursor();        
}   



static int
menu_open (menu_t *mn, int scr_height)
{
        int  i, limit_height, num  ;
            
        /*
         * 將選單印到標準輸出
         * 空白行不增加選擇號碼 
         */    
        limit_height = scr_height - 1;                     
           
        for (i=num=0; 1 < limit_height && (mn+i)->pmsg != 0; i++){  
            if ((U32)((mn+i)->funptr) != (U32)menu_space)                          
                mt_printf(" %1X:%s", num++,  (mn+i)->pmsg);
            else     
                mt_printf("");            
        }  
       
        return (i);                 
}   
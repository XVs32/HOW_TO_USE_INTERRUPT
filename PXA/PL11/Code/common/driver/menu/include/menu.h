// --------------------------------------------------------------------
//
//   Title     :  menu.h
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  menu routines
//             :
//   Limitation:
//             :
//   Note      :
//             :
// --------------------------------------------------------------------
//   modification history :
// --------------------------------------------------------------------
//   Version| mod. date: |
//   V1.0   | 12/22/2006 | Programming start
// --------------------------------------------------------------------
//
// Note:
//
//       MICROTIME COMPUTER INC.
//
// --------------------------------------------------------------------

#ifndef _DRIVER_MENU_H_
#define _DRIVER_MENU_H_

#ifndef __ADDR_PXA27X_H__
#include        "common/include/addr.h"
#include        "common/include/def.h"
#endif

typedef void (*mu_func_ptr)(void*);


//=================================================================
// Global Variables
//=================================================================


//=================================================================
// High-Level functions
//=================================================================


//=================================================================
// low-level functions
//=================================================================
struct menu_st ;
typedef struct menu_st{
        char             *pmsg;          // 選單項目
        int              (*funptr)(void);// 選單功能
        struct menu_st    *next ;        // 下一個選單, 如此可串起多層的選單
} menu_t, *p_menu_t;


#define MENU_ITEM_SPACE { "",      menu_space, NULL }
#define MENU_QUIT       { "Quit",  menu_quit,  NULL }


void process_menu (menu_t *mn, int scr_height, mu_func_ptr funptr, void* pVoid);
int  menu_change(void); 
int  menu_space(void); 
int  menu_quit(void) ;  

#endif // _DRIVER_MENU_H_

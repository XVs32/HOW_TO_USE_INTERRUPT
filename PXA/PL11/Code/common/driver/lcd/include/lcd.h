// ---------------------------------------------------------------------------
//
//   Title     :  lcd.h
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  lcd Define constant 
//             :
//   Limitation:
//             :
//   Note      :
//             :
// ---------------------------------------------------------------------------
//   modification history :
// ---------------------------------------------------------------------------
//   Version| mod. date: |
//   V1.0   | 12/28/2006 | Programming 128 x 128-dot Graphics LCD Controller
//                         /Driver with Four-grayscale Functions
// ---------------------------------------------------------------------------
//
// Note:
//
//       MICROTIME COMPUTER INC.
//
// ---------------------------------------------------------------------------

#ifndef __DRV_LCD_H__
#define __DRV_LCD_H__

#include    <stdarg.h>
#include    <string.h>
#include    <stdio.h>

#include "common/include/def.h"


struct tag_lcd_controller {
        U16 driver_ouput ;
        U16 lcd_driving_waveform;
        U16 power;
        U16 contrast;
        U16 endtry_mode;
        U16 rotation ;
        U16 display;
        U16 cursor;
        U16 double_height_display_position;
        U16 vertical_scroll;
        U16 horisontal_cursor_position ;
        U16 vertical_cursor_position;
                
        U16 line_address_delta;
} ; 


typedef struct screen_info
{
        struct tag_lcd_controller controller;   
    
        U16 xres;
        U16 yres;
        U8  bpp;                     /* bits per pixel */

    
        /* Cursor Values */
        struct {
            S16 x;  
            S16 y;              
            U16 enable;
            U16 mode;
        } cursor;   

        /* Font Values */       
        struct {
            S16 width ;
            S16 height;
        } font; 
        
        
        U32 mem_len ;       
        U16 max_col ;
        U16 max_raw ;
        U16 next_raw_address;
        U16 YScrollOffset ;     
} screen_info_t, *p_screen_info_t;  
extern screen_info_t screen_info;

#define SCREEN_CURSOR_ON    1
#define SCREEN_CURSOR_OFF   0


//=================================================================
// High-Level functions
//=================================================================
void  LCD_putch(char ch) ;
void  LCD_puts(char* msg);
void  LCD_clear_screen (void);
void  LCD_set_cursor(int x, int y);
void  LCD_get_cursor(int *x, int *y);


//=================================================================
// LCD low-level functions
//=================================================================
void   LCD_ClearScreen (screen_info_t *screen_info);
void   LCD_ClearOneLine (screen_info_t *screen_info, int y);
void   LCD_scroll (screen_info_t *screen_info);
void   LCD_displ (screen_info_t *screen_info, int x, int y, int ch);
void   LCD_putchar (screen_info_t *screen_info, char c);
void   LCD_put_string (screen_info_t *screen_info, char *msg);
void   LCD_printf (screen_info_t *screen_info, char *fmt,...);
U32    LCD_Write(screen_info_t*screen_info, const void *pInpBuffer, U32 size);
void   LCD_get_height_width(screen_info_t* screen_info, int *height, int *width);


/*************************************************************************
Cursor functions
*************************************************************************/
void   LCD_CursorMode (screen_info_t *screen_info, unsigned char Mode);
void   LCD_EnableCursor (screen_info_t *screen_info, int bCursorOn);
void   LCD_MoveCursor (screen_info_t *screen_info, int x, int y);
void   LCD_GetCursor (screen_info_t *screen_info, int *x, int *y);

/*************************************************************************
LCD Initial functions
*************************************************************************/
struct screen_info *LCD_init (void);
void   LCD_exit (void);


#endif /*__DRV_LCD_H__*/


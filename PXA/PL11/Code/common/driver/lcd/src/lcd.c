// ---------------------------------------------------------------------------
//
//   Title     :  lcd.c
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  Driver for AF-128128CFI-H LCD
//             :
//   Limitation:
//             :

//   Note      :
//             :
// ---------------------------------------------------------------------------
//   modification history :
// ---------------------------------------------------------------------------
//   Version| mod. date: |
//   V1.0   | 12/07/2006 | First release
// ---------------------------------------------------------------------------
//
// Note:
//
//       MICROTIME COMPUTER INC.
//
// ---------------------------------------------------------------------------

/*************************************************************************
Include files
*************************************************************************/
#include    "common/include/addr.h"
#include    "lcd/include/lcd.h"
#include    "lcd/include/genfont8_8.h"


/*************************************************************************
Constant define
*************************************************************************/

enum LCDCommand{
    LCD_START_OSC=0,        // Start oscillation    
    LCD_DEVICE_CODE=0,      // Device code read 
    LCD_DRV_OUT=1,          // Driver output control
    LCD_WAVEFORM=2,         // LCD-driving-waveform control
    LCD_PWR_CONTROL=3,      // Power control
    LCD_CONTRAST=4,         // Contrast control
    LCD_ENTRY_MODE=5,       // Entry mode
    LCD_ROTATION=6,         // Rotation
    LCD_DISPLAY=7,          // Display control      
    LCD_CURSOR=8,           // Cursor control
    LCD_DB_HEIGHT=9,        // Double-height display position
    LCD_VET_SCROLL=0xa,     // Vertical scroll
    LCD_HOR_CURSOR_POS=0xb,     // Horizontal cursor position
    LCD_VER_CURSOR_POS=0xc,     // Vertical cursor position
    LCD_RAM_MASK=0x10,      // RAM write data mask
    LCD_RAM_ADDR=0x11,      // RAM address set
    LCD_RAM_DATA=0x12,      // RAM Data
    LCD_RAM_WR=0x12,        // RAM data write
    LCD_RAM_RD=0x12         // RAM data read
};


#define TABS                    4
#define WHITE_BLINK_CURSOR      0
#define BLACK_BLINK_CURSOR      1
#define REVERSE_CURSOR          2
#define REVERSE_BLINK_CURSOR    3

#define SET_ADDRESS_LCD(x)      WriteLCD(LCD_RAM_ADDR, x);
#define SET_RAM_DATA_LCD(x)     WriteLCD(LCD_RAM_DATA, x);



/*************************************************************************
Function prototypes
*************************************************************************/
static U16  ReadLCD(U16 reg_no);
static void WriteLCD(U16 reg_no, U16 data);
static void LCD_PutRAMData(U16 address, U16 data);
static U16  LCD_GetRAMData(U16 address);
static void LCD_FillScreenPattern(screen_info_t *screen_info, U16 pattern);
static void LCD_setup(struct screen_info *screen_info);



/*************************************************************************
Variable define
*************************************************************************/
screen_info_t screen_info;



//=================================================================
// High-Level functions
//=================================================================
void  LCD_putch(char ch)  { LCD_putchar(&screen_info, ch); }
void  LCD_puts(char* msg) { LCD_put_string(&screen_info, msg); }
void  LCD_clear_screen (void) { LCD_ClearScreen(&screen_info); }
void  LCD_set_cursor(int x, int y)   {LCD_MoveCursor(&screen_info, x, y); }
void  LCD_get_cursor(int *x, int *y) {LCD_GetCursor(&screen_info, x, y); }



/* 
 * lcd controller low-level functions 
 */
static U16 
ReadLCD (U16 reg_no)
{
        U16 data;

        LCD_CMD = 0xff; //MSB
        LCD_CMD = reg_no; //LSB
        data = LCD_DATA << 8;
        data |= LCD_DATA;

        /*
         * 當讀取RAM data時第一個Word是dummy
         * 讀第二個Word才是正確地
         */
        if (reg_no == LCD_RAM_DATA) {
            LCD_CMD = 0xff; //MSB  
            LCD_CMD = reg_no; //LSB
            data = LCD_DATA << 8;
            data |= LCD_DATA;
        }
}



static void 
WriteLCD (U16 reg_no, U16 data)
{
        LCD_CMD = 0xff; //MSB
        LCD_CMD = reg_no; //LSB
        
        LCD_DATA = (data >> 8) ;
        LCD_DATA = data;
}



static void 
LCD_PutRAMData (U16 address, U16 data)
{
        SET_ADDRESS_LCD(address);
        SET_RAM_DATA_LCD(data);
}



static U16 
LCD_GetRAMData (U16 address)
{
        SET_ADDRESS_LCD(address);
        
        return (ReadLCD(LCD_RAM_DATA));
}



static void 
LCD_FillScreenPattern (screen_info_t *screen_info, U16 pattern)
{
        int i;
    
        SET_ADDRESS_LCD(0);
    
        for (i=0; i < screen_info->mem_len; i++)
            SET_RAM_DATA_LCD(pattern);

        screen_info->YScrollOffset = 0;         
        WriteLCD(LCD_VET_SCROLL, 0);        
}



static void 
LCD_setup (screen_info_t *screen_info)
{
        int     i;
    
        // The eight upper and lower bits can be corrected by 
        // a reset triggered by consecutively writing 
        // a 00H instruction four times.
        //      
        for (i=0; i < 4; i++){
            LCD_CMD = 0;
        }
        
        // The start oscillation instruction restarts the oscillator 
        // from the halt state in the standby mode. After issuing
        // this instruction, wait at least 10 ms for oscillation to
        //  stabilize before issuing the next instruction   
        //
        WriteLCD(LCD_START_OSC, 1);
        Delay(15);
    
        WriteLCD(LCD_DRV_OUT, screen_info->controller.driver_ouput);        
        WriteLCD(LCD_WAVEFORM, screen_info->controller.lcd_driving_waveform);
        WriteLCD(LCD_PWR_CONTROL, screen_info->controller.power);   
        WriteLCD(LCD_CONTRAST,  screen_info->controller.contrast);
        WriteLCD(LCD_ENTRY_MODE, screen_info->controller.endtry_mode);
        WriteLCD(LCD_ROTATION, screen_info->controller.rotation);
    
        WriteLCD(LCD_CURSOR, screen_info->controller.cursor);
        WriteLCD(LCD_DB_HEIGHT, 
                 screen_info->controller.double_height_display_position);
                 
        WriteLCD(LCD_VET_SCROLL, screen_info->controller.vertical_scroll);
        WriteLCD(LCD_HOR_CURSOR_POS, 
                 screen_info->controller.horisontal_cursor_position);
        WriteLCD(LCD_RAM_MASK, 0);
        WriteLCD(LCD_RAM_ADDR, 0);  
        WriteLCD(LCD_DISPLAY, screen_info->controller.display); 
    
        LCD_ClearScreen(screen_info);   
}




/* ------------------ display a character to screen ------------------- */
void
LCD_displ (screen_info_t*screen_info, int x, int y, int ch)
{
        unsigned short  addr, data, line_address_delta ;
        int             i, YRelation; 

        line_address_delta = screen_info->controller.line_address_delta;

        YRelation = y - screen_info->YScrollOffset;
        addr = x + (YRelation * screen_info->next_raw_address);
        data = (ch >= 0x20) ? ch : ' ';        

        for (i=0; i < screen_info->font.height; i++){
            LCD_PutRAMData(addr, charset[data][i]);
            addr += line_address_delta;
        }
}



void
LCD_ClearScreen (screen_info_t *screen_info)
{
        LCD_FillScreenPattern(screen_info, 0);
        LCD_MoveCursor(screen_info, 0, 0);      
}



/* ------------------ clear one line ---------------------------------- */
void
LCD_ClearOneLine (screen_info_t *screen_info, int y)
{
        int             x;

        for (x=0; x < screen_info->max_col; x++)
            LCD_displ(screen_info, x, y, ' ');
        screen_info->cursor.x = 0;
}



/* ------------------ scroll contents up or down ---------------------- */
void
LCD_scroll (screen_info_t *screen_info)
{
        U16 scroll, count ;
         
        if (screen_info->YScrollOffset == 0)
            screen_info->YScrollOffset = screen_info->max_raw - 1;
        else
            screen_info->YScrollOffset--;

        count = screen_info->cursor.y - screen_info->YScrollOffset + 1;
        scroll = screen_info->font.height * count ;
                         
        WriteLCD(LCD_VET_SCROLL, scroll);
        LCD_ClearOneLine(screen_info, screen_info->cursor.y);
}



/* ------------------ write a character to screen --------------------- */
void
LCD_putchar (screen_info_t *screen_info, char c)
{
        U16  *pX, *pY;  
        
        pX = &screen_info->cursor.x ;
        pY = &screen_info->cursor.y ;        
        switch (c){
        case '\n' :
            if (*pY == (screen_info->max_raw-1))
                LCD_scroll(screen_info);
            else
                (*pY)++;
            *pX = 0;
            break ;
        case '\t' :
            do LCD_putchar(screen_info, ' ');
            while (*pX % TABS);
            break ;
        default :
			/*if ((*pX+1) >= screen_info->max_col){
                LCD_putchar(screen_info, '\n');
            }
            LCD_displ(screen_info, (*pX)++, *pY, c);
			*/
            LCD_displ(screen_info, (*pX)++, *pY, c);
			if ((*pX) >= screen_info->max_col){
                LCD_putchar(screen_info, '\n');
            }
            break ;
        }
        if (screen_info->cursor.enable)
            LCD_MoveCursor(screen_info, *pX, *pY);
}



void
LCD_put_string (screen_info_t *screen_info, char *msg)
{
        char        *ptr = msg; 
        
        while (*ptr){
            LCD_putchar(screen_info, *ptr++);           
        }           
        //LCD_putchar(screen_info, '\n');        
}

    

/* ------------------ printf  ----------------------------------------- */
void
LCD_printf (screen_info_t *screen_info, char *fmt,...)
{
        va_list     ap;
        char        string[512];

        va_start(ap, fmt);
        vsprintf(string, fmt, ap);
        LCD_put_string(screen_info, string);
        va_end(ap);            
}



U32
LCD_Write (screen_info_t*screen_info, const void *pInpBuffer, U32 size)
{
         U32 len = size;          
         const U8 *p = pInpBuffer;
         
         for (; len > 0; len--)             
             LCD_putchar(screen_info,  *p++);   
             
         return (size);    
}   



void   
LCD_get_height_width (screen_info_t* screen_info, int *height, int *width)
{
        if (screen_info){
            *height = screen_info->max_raw;  
            *width  = screen_info->max_col;             
        }
        else{
            *height = 0;     
            *width  = 0;                  
        }           
}

    

/* ------------------ Set  Cursor mode ------------------------------- */
void
LCD_CursorMode (screen_info_t *screen_info, unsigned char Mode)
{
        unsigned short  data;

        screen_info->cursor.mode = Mode;
        if (screen_info->cursor.enable)
            data = screen_info->cursor.mode | 0x04;
        else
            data = screen_info->cursor.mode;
        WriteLCD(LCD_CURSOR, data);
}



/* ------------------ Enable Cursor on/off----------------------------- */
void LCD_EnableCursor (screen_info_t *screen_info, int bCursorOn)
{
        unsigned short  data;

        screen_info->cursor.enable = bCursorOn;
        if (screen_info->cursor.enable)
            data = screen_info->cursor.mode | 0x04;
        else
            data = 0;
        WriteLCD(LCD_CURSOR, data);
}




/* ------------------ set cursor -------------------------------------- */
void 
LCD_MoveCursor (screen_info_t *screen_info, int x, int y)
{
        U16  HS, HE, VS;

        HS = x * screen_info->font.width;
        HE = HS + (screen_info->font.width - 1);
        WriteLCD(LCD_HOR_CURSOR_POS, (HE << 8) + HS);

        VS = (y + 1) * screen_info->font.height - 2;
        WriteLCD(LCD_VER_CURSOR_POS, ((VS+1)<<8) + VS);
        
        screen_info->cursor.x = x; 
        screen_info->cursor.y = y;             
}



void 
LCD_GetCursor (screen_info_t *screen_info, int *x, int *y)
{    
        *x = screen_info->cursor.x; 
        *y = screen_info->cursor.y;    
}



screen_info_t *
LCD_init (void)
{
        p_screen_info_t info = &screen_info;
        U16           addr_per_line;                
        
        memset(info, 0, sizeof(struct screen_info));    

        /*
         * setup LCD controller parameter 
         */        
        info->controller.driver_ouput = 0x030f;
        info->controller.lcd_driving_waveform = 0;
        info->controller.power = 0x23c;
        info->controller.contrast = 0x18;
        info->controller.endtry_mode = 0x10; 
        info->controller.rotation = 0;
        info->controller.display = 1;
        info->controller.cursor = 4;
        info->controller.double_height_display_position = 0;
        info->controller.vertical_scroll = 0;
        info->controller.horisontal_cursor_position = 0;
        info->controller.vertical_cursor_position = 0;   
        info->controller.line_address_delta = 0x10;
            
            
        info->xres = 128;       
        info->yres = 128;      
        info->bpp = 2;        
        info->mem_len = (info->yres * info->xres * info->bpp) >> 3;          
                                
        info->cursor.x = 0; 
        info->cursor.y = 0;                                      

        info->font.width = 8;
        info->font.height = 8;          
        info->max_col = info->xres / info->font.width;
        info->max_raw = info->yres / info->font.height;                
        
        addr_per_line = info->font.height *  
                        info->controller.line_address_delta;  
                                              
        info->next_raw_address = addr_per_line ;    
        info->YScrollOffset = 0;        
 
        LCD_setup(info);
        LCD_CursorMode(info, BLACK_BLINK_CURSOR);
        LCD_EnableCursor(info, SCREEN_CURSOR_ON);          
    
        return (info);
}   



void
LCD_exit (void)
{ 
}    

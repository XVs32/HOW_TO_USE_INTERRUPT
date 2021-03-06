// --------------------------------------------------------------------
//
//   Title     :  scan.c
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  scan keypad& 7 segment routines for Creator Board
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
//   V1.0   | 12/18/2006 | First release
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
#include    <stdarg.h>
#include    <string.h>
#include    <stdio.h>

#include "common/include/addr.h"
#include "scan.h"
#include "common/include/creator_io.h"
#include "timer/include/os_timer.h"


/*************************************************************************
Constant define
*************************************************************************/
#define SCAN_TIME_KEYPAD             100         // 100 ms
#define INP_BUFFER_LEN               16
#define SCAN_NULL                    0xffff

#define NUMS_7SEGMENT                4
#define SCAN_TIME_7SEGMENT           4          // 4 ms
#define BLANK_PATTERN_7SEGMENT       0xff
#define SYSTEM_TIME_BUF_IDX          0
#define USER_BUF_IDX                 1


typedef struct 
{           
        U16    buffer[INP_BUFFER_LEN]; /* data buffer */ 
        U16    inp_buff_len;
        U16    last_scan_key;        
        U8     key_assigned;         
                    
        U8     wptr;            
        U8     rptr;        
        U16    scan_time_ms ;
        
        U32    timer_device ;
} keypad_info_t , *p_keypad_info_t; 

typedef struct
{            
        U16    scan_time_ms ;   
        U8     scan_idx;    
        U8     buffer[2][NUMS_7SEGMENT];        
        U8     buf_len; 
        U8     act_idx, *p_act_buf;
        
  const U16    *tbl_7seg_com ;       
  const U8     *tbl_pattern;       
        U8     tbl_pattern_len;  
        U8     blank_pattern ;        
        
        U32    timer_device ;        
} _7seg_info_t, *p_7seg_info_t ;


#define keypad_empty(circ)      ((circ)->wptr == (circ)->rptr)
#define keypad_clear(circ)      ((circ)->wptr = (circ)->rptr = 0)



/*************************************************************************
Function prototypes
*************************************************************************/
static void keypad_scan_isr (U16 irqno, struct irq_desc *desc, void *pVoid);
static void _7segment_scan_isr (U16 irqno, struct irq_desc *desc, void *pVoid); 



/*************************************************************************
Variable define
*************************************************************************/
static keypad_info_t key_info; 
static _7seg_info_t   _7seg_info;




U8 
get_key (U8 *ch)
{
        return (mt_main_keypad_get_key(ch));    
}



int 
chk_key (U8 *ch)
{
        return (mt_main_keypad_chk_key(ch));    
}

        

/***********************************************************************/
/*        keypad_scan_isr:  鍵盤掃瞄程式                                   */
/*                                                                     */
/*      INPUTS:  =                                                     */
/***********************************************************************/
static void  
keypad_scan_isr (U16 irqno, struct irq_desc *desc, void *pVoid) 
{
        p_keypad_info_t info = (p_keypad_info_t)pVoid;   
        UN_CVT          cvt;            

        if ((info->wptr+1) == info->rptr) { //Key_Pad Overfllow
                //TODO
        }
        else {            
        	/*
        	 * 一次一列掃瞄鍵盤, 完整的掃瞄碼放到cvt.w[0]
        	 */ 
            mt_main_keypad_set_scanline(0xfe);          
            cvt.b[0] = (UC)(mt_main_keypad_get_scancode());
            mt_main_keypad_set_scanline(0xfd);             
            cvt.b[0] |= (UC)(mt_main_keypad_get_scancode() << 4);
            mt_main_keypad_set_scanline(0xfb); 
            cvt.b[1] = (UC)(mt_main_keypad_get_scancode());
            mt_main_keypad_set_scanline(0xf7);             
            cvt.b[1] |= (UC)(mt_main_keypad_get_scancode() << 4);
        
            if (info->last_scan_key == cvt.w[0]) { // 是否是彈跳
                if (info->key_assigned == UM) {    // 是否處裡過
                    if (cvt.w[0] != SCAN_NULL) {   // 有效按鍵
                        info->buffer[info->wptr++] = cvt.w[0];
                        if (info->wptr == info->inp_buff_len)
                           info->wptr = 0;
                    }
                    info->key_assigned = OK;
                }
            }
            else {
                info->key_assigned = UM;          // 設定尚未處理
            }
            info->last_scan_key = cvt.w[0];       // 儲存此次掃瞄碼   
        }   
}



U8 
mt_main_keypad_get_key (U8 *ch)
{
        p_keypad_info_t info = &key_info;   
        U16             temp;
        
        if (!keypad_empty(info)) {
            temp = info->buffer[info->rptr++];
            if (info->rptr == info->inp_buff_len)
                info->rptr = 0;
            *ch = mt_main_keypad_vkey2num(temp);
            
            return (OK);
        }
        return (UM);
}



int 
mt_main_keypad_chk_key (U8 *ch)
{
        p_keypad_info_t info = &key_info;       
        U16   temp;
        
        if (!keypad_empty(info)) {
            temp = info->buffer[info->rptr];
            *ch = mt_main_keypad_vkey2num(temp);
            return (OK);
        }
        return (UM);
}



int
mt_main_keypad_flush (void)
{
        p_keypad_info_t info = &key_info;            
        
        keypad_clear(info);
}   



/*************************************************************************
Wait key 
*************************************************************************/
void 
mt_main_keypad_wait_char (void)
{
        U8    key;
        
        while (mt_main_keypad_get_key(&key) != OK);
}



/*************************************************************************
4X4 KEY PAD
*************************************************************************/
#define KEY_0       0xdfff
#define KEY_1       0xfffe
#define KEY_2       0xfffd
#define KEY_3       0xfffb
#define KEY_4       0xffef
#define KEY_5       0xffdf
#define KEY_6       0xffbf
#define KEY_7       0xfeff
#define KEY_8       0xfdff
#define KEY_9       0xfbff
#define KEY_A       0xfff7
#define KEY_B       0xff7f
#define KEY_C       0xf7ff
#define KEY_D       0x7fff
#define KEY_STAR    0xefff
#define KEY_POND    0xbfff

static U16 scan_code_to_vkey_table[16] = {
        KEY_0, KEY_1, KEY_2, KEY_3,
        KEY_4, KEY_5, KEY_6, KEY_7,
        KEY_8, KEY_9, KEY_A, KEY_B,
        KEY_C, KEY_D, KEY_STAR, KEY_POND
        };
    

U8 
mt_main_keypad_vkey2num (U16 ch)
{
        U8     idx;
        
        for (idx=0; idx < 16; idx++) {
            if (ch == scan_code_to_vkey_table[idx]) 
                return (idx);
        }
        
        return (0xff);
}



int
mt_main_keypad_init (U16 scan_time_ms)
{
        p_keypad_info_t info;   
        int          nRet, inp_buff_len ;
        U16          i;
        
        info = &key_info;
        info->inp_buff_len = inp_buff_len = INP_BUFFER_LEN;
        info->scan_time_ms = scan_time_ms ;
        info->last_scan_key = SCAN_NULL;        
        keypad_clear(info);
        info->key_assigned = UM;
        
        for (i=0; i < inp_buff_len; i++)
            info->buffer[i] = SCAN_NULL;        
        
        
        nRet = register_ostimer_ext(&info->timer_device, info->scan_time_ms,
                                    RES_1MSEC, OST_PERIODIC, 
                                    keypad_scan_isr, 
                                    "scankey", &key_info);      
                                    
        return (nRet);                                    
}   



int
mt_main_keypad_exit (void)
{
        unregister_ostimer(key_info.timer_device);  
}   



/*************************************************************************
7 SEGMENT LED
*************************************************************************/
static const U16 tbl_7seg_com[] = {0x0e, 0x0d, 0x0b, 0x07};
static const U8 LED_tb2[] = {
        0xc0, 0xf9, 0xa4, 0xb0, 0x99,
        0x92, 0x82, 0xf8, 0x80, 0x90,
        0xa0, 0x83, 0xc6, 0xa1, 0x84,
        0x8e, 0x7f  //,0xff
        };  



/***********************************************************************/
/*        _7segment_scan_isr:  七段顯示器掃瞄程式                      */
/*                                                                     */
/*      INPUTS:  =                                                     */
/***********************************************************************/
static void  
_7segment_scan_isr (U16 irqno, struct irq_desc *desc, void *pVoid) 
{
        p_7seg_info_t info = (p_7seg_info_t)pVoid;  
        
        info->scan_idx++;
        if (info->scan_idx == info->buf_len)
            info->scan_idx = 0;
        
        /*
         * 啟動顯示系統時間
         */
        if (info->act_idx == SYSTEM_TIME_BUF_IDX){
            U8  *p_buf = info->p_act_buf;
            const U8  *tbl   = info->tbl_pattern;
            
            p_buf[3] = tbl[g_timer_realtime.sec % 10];
            p_buf[2] = tbl[g_timer_realtime.sec / 10];
            p_buf[1] = tbl[g_timer_realtime.min % 10];
            p_buf[0] = tbl[g_timer_realtime.min / 10];          
            
        }       
        
        /*
         * 一次點亮一個七節顯示
         */        
        mt_main_7segment_set(info->p_act_buf[info->scan_idx],
                             info->tbl_7seg_com[info->scan_idx]);                                    
}


    
void
mt_main_7seg_enable_system_time (int enable)
{
        p_7seg_info_t info = &_7seg_info;
            
        info->act_idx = (enable) ? SYSTEM_TIME_BUF_IDX : USER_BUF_IDX;
        info->p_act_buf = &info->buffer[info->act_idx][0];      
}


        
    
int 
mt_main_7seg_shift (SEGMENT_SHIFT_TYPE shift_type, U8 data)
{
        p_7seg_info_t info = &_7seg_info;
        U8            *pbuffer = &info->buffer[USER_BUF_IDX][0];  
        U8            pattern ;                
        U8            start, end;
  
       if (data >=  info->tbl_pattern_len)
           return (0);
           
        pattern =  info->tbl_pattern[data];         
        if (shift_type == SEGMENT_SHIFT_RIGHT){
            start = info->buf_len -1;
            end   = 1;
            for (;start >= end; start--)
                pbuffer[start] = pbuffer[start-1];          
            pbuffer[0] = pattern;                                                         
        }               
        else{
            start = 0;
            end   = info->buf_len - 2 ;
            for (;start <= end; start++)
                pbuffer[start] = pbuffer[start+1];          
            pbuffer[start] = pattern;           
        }          
        return (1);      
}

    

int
mt_main_7seg_put_pattern (U8 digit, U8 pattern)
{
        p_7seg_info_t info = &_7seg_info;
            

        if (digit >= info->buf_len )
            return (0);
            
        info->buffer[USER_BUF_IDX][digit] = pattern;
        return (1);
}



void 
mt_main_7seg_put_all_pattern  (U8 pattern)
{
        p_7seg_info_t info = &_7seg_info;
        U8            *pbuffer = &info->buffer[USER_BUF_IDX][0];
        int           i;
        
        for (i=0; i < info->buf_len; i++)
            pbuffer[i] = pattern;           
}


int
mt_main_7seg_put_number (U8 digit, U8 number)
{
        p_7seg_info_t info = &_7seg_info;
            

        if (digit >= info->buf_len || number >= info->tbl_pattern_len)
            return (0);
            
        info->buffer[USER_BUF_IDX][digit] = info->tbl_pattern[number];
        return (1);
}
    

void 
mt_main_7seg_blank (void)
{
        p_7seg_info_t info = &_7seg_info;   
        
        mt_main_7seg_put_all_pattern(info->blank_pattern);                                                  
}



int
mt_main_7segment_init (U16 scan_time_ms, int show_system_time)
{
        p_7seg_info_t info = &_7seg_info;
        U8            *p_buf;
        int           i, nRet ;
        
        
        info->scan_idx = 0; 
        info->buf_len = NUMS_7SEGMENT;
        info->tbl_7seg_com = tbl_7seg_com;
        info->tbl_pattern = LED_tb2;
        info->tbl_pattern_len = sizeof(LED_tb2);
        info->blank_pattern = BLANK_PATTERN_7SEGMENT;        
    
        for (i=0; i < 2; i++){
            p_buf = &info->buffer[i][0];
            p_buf[0] = 0x90;
            p_buf[1] = 0xA3;
            p_buf[2] = 0xA3;
            p_buf[3] = 0xA1;    
        }           
        mt_main_7seg_enable_system_time(show_system_time);         
        
        info->scan_time_ms = scan_time_ms;  
        
        nRet = register_ostimer_ext(&info->timer_device, 
                                    info->scan_time_ms,
                                    RES_1MSEC, OST_PERIODIC, 
                                    _7segment_scan_isr, 
                                    "scankey", &_7seg_info);                 
                                    
        return (nRet);                                    
}



int
mt_main_7segment_exit (void)
{
        return (unregister_ostimer(_7seg_info.timer_device));
}   



int
scan_init (int show_system_time)
{
       int  nRet = 1;
       
       if (!mt_main_keypad_init(SCAN_TIME_KEYPAD))
           return (0);  
           
       if (!mt_main_7segment_init(SCAN_TIME_7SEGMENT, show_system_time))
           return (0);             
      
       return (nRet);
}
    


void
scan_exit (void)
{
        mt_main_keypad_exit();
        mt_main_7segment_exit(); 
}   




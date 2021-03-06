// --------------------------------------------------------------------
//
//   Title     :  mmu.c
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  MMU memory mapping
//             :
//   Limitation:
//             :
//   Note      :
//             :
// --------------------------------------------------------------------
//   modification history :
// --------------------------------------------------------------------
//   Version| mod. date: |
//   V1.0   | 04/26/2006 |  1. First release
//                          
// --------------------------------------------------------------------
//
// Note:
//     1) Only the section table is used. 
//     2) The cachable/non-cachable area can be changed by MMT_DEFAULT value.
//        The section size is 1MB.
//
//       MICROTIME COMPUTER INC.
//
// 
 
/*************************************************************************
Include files
*************************************************************************/
#include "common/include/addr.h"
#include "common/include/mmu.h"
#include "common/include/mmulib.h"



/*************************************************************************
Constant define
*************************************************************************/


/*************************************************************************
Function prototypes
*************************************************************************/

/*************************************************************************
Variable define
*************************************************************************/

void 
MMU_Disable (void)
{
        int i,j;
    
        //========================== IMPORTANT NOTE =========================
        //The current stack and code area can't be re-mapped in this routine.
        //If you want memory map mapped freely, your own sophiscated MMU
        //initialization code is needed.
        //===================================================================

        MMU_DisableDCache();
        MMU_DisableICache();

        //If write-back is used,the DCache should be cleared.
        for(i=0;i<64;i++)
            for(j=0;j<8;j++)
                MMU_CleanInvalidateDCacheIndex((i<<26)|(j<<5));
        MMU_InvalidateICache();
    
        // V bit : Base location of exception register.
        // Set V bit = 0, Low  address = 0x00000000.
        //           = 1, High address = 0xFFFF0000
        MMU_SetExceptionAddrTo0();
    
    
        MMU_DisableMMU();
        MMU_InvalidateTLB();    
}



void 
MMU_Init (void)
{
        MMU_Disable();

        //MMU_SetMTT(int vaddrStart,int vaddrEnd,int paddrStart,int attr)
        MMU_SetMTT(0x00000000,0x03FFFFFF,0xA0000000,RW_CNB);   //nSDCS0(SDRAM) 
        MMU_SetMTT(0x04000000,0x17FFFFFF,0x04000000,RW_NCNB);  //nCS1~nCS5
        MMU_SetMTT(0x18000000,0x1BFFFFFF,0x00000000,RW_CNB);   //nCS0(ROM)   
        MMU_SetMTT(0x1C000000,0x1FFFFFFF,0x1C000000,RW_FAULT); //Unused
        MMU_SetMTT(0x20000000,0x2FFFFFFF,0x20000000,RW_NCNB);  //PCMCIA_0
        MMU_SetMTT(0x30000000,0x3FFFFFFF,0x30000000,RW_FAULT); //Unused
        MMU_SetMTT(0x40000000,0x5FFFFFFF,0x40000000,RW_NCNB);  //CPU internal
        MMU_SetMTT(0x60000000,0x9FFFFFFF,0x60000000,RW_FAULT); //Unused
        MMU_SetMTT(0xA0000000,0xA3FFFFFF,0xA0000000,RW_CNB);   //nSDCS0(SDRAM)                 
        MMU_SetMTT(0xA4000000,0xFFFFFFFF,0xA4000000,RW_FAULT); //Unused     

        MMU_SetTTBase(_MMUTT_STARTADDRESS);
        MMU_SetDomain(0x55555550|DOMAIN1_ATTR|DOMAIN0_ATTR); 
        //DOMAIN1: no_access, DOMAIN0,2~15=client(AP is checked)
        MMU_SetProcessId(0x0);
        MMU_EnableAlignFault();     
}    



void 
MMU_SetMTT (int vaddrStart,int vaddrEnd,int paddrStart,int attr)
{
        U32 *pTT;
        int i,nSec;
    
        pTT=(U32 *)(_MMUTT_STARTADDRESS | ((vaddrStart>>18)&(0x3ffc)));
        nSec=(vaddrEnd>>20)-(vaddrStart>>20);
        for(i=0;i<=nSec;i++)*pTT++=attr |(((paddrStart>>20)+i)<<20);
}







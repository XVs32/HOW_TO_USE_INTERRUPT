// --------------------------------------------------------------------
//
//   Title     :  option.h
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  define different parameter for compilters
//             :
//   Limitation:
//             :
//   Note      :
//             :
// --------------------------------------------------------------------
//   modification history :
// --------------------------------------------------------------------
//   Version| mod. date: |
//   V1.0   | 09/07/2004 | Programming start
// --------------------------------------------------------------------
//
// Note:
//
//       MICROTIME COMPUTER INC.
//
// --------------------------------------------------------------------

#ifndef __OPTION_H__
#define __OPTION_H__

//#include "compiler_option.h"


// BUSWIDTH : 16,32
#define BUSWIDTH    (32)

#define _RAM_STARTADDRESS       0xa0000000
#define _STACK_BASEADDRESS      0xa3ff8000
#define _MMUTT_STARTADDRESS     0xa3ff8000

#endif    //__OPTION_H__
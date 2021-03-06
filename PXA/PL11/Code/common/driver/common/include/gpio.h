// --------------------------------------------------------------------
//
//   Title     :  gpio.h
//             :
//   Library   :
//             :
//   Developers:  MICROTIME MDS group
//             :
//   Purpose   :  Define constant 
//             :
//   Limitation:
//             :
//   Note      :
//             :
// --------------------------------------------------------------------
//   modification history :
// --------------------------------------------------------------------
//   Version| mod. date: |
//   V1.0   | 11/21/2006 | Programming start
// --------------------------------------------------------------------
//
// Note:
//
//       MICROTIME COMPUTER INC.
//
// --------------------------------------------------------------------

#ifndef __GPIO_H__
#define __GPIO_H__


#define GPIO_DIR_IN         (0x0u)  //
#define GPIO_DIR_OUT        (0x1u)

#define GPIO_ALT_FN_0       (0x0u)  // �@��GPIO
#define GPIO_ALT_FN_1       (0x1u)  // �S��\��1, ��pin�M�w���ӥ\��
#define GPIO_ALT_FN_2       (0x2u)  // �S��\��2, ��pin�M�w���ӥ\��
#define GPIO_ALT_FN_3       (0x3u)  // �S��\��3, ��pin�M�w���ӥ\��


void GpioSetOutputState1 (U8 bit_no);
void GpioSetOutputState0  (U8 bit_no);
void GpioSetAlternateFunction (U8 bit_no, U8 Function);
void GpioSetDirection (U8 bit_no, U8 dir);
int  GpioGetLevelState (U8 bit_no);


#endif /*__GPIO_H__*/


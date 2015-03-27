/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                          (c) Copyright 2003-2006; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                        BOARD SUPPORT PACKAGE
*
*                                              NXP LPC2148
*                                                on the
*                                     Keil MCB2140 Evaluation Board
*
* Filename      : bsp.h
* Version       : V1.00
* Programmer(s) : JJL
*********************************************************************************************************
*/

#ifndef  __BSP_H__
#define  __BSP_H__

/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   BSP_GLOBALS
#define  BSP_EXT
#else
#define  BSP_EXT  extern
#endif

/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  CPU_OSC_FREQ                  12000000L

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void         BSP_Init           (void);
void         BSP_IntDisAll      (void);
CPU_INT32U   BSP_CPU_ClkFreq    (void);
CPU_INT32U   BSP_CPU_PclkFreq   (void);

/*
*********************************************************************************************************
*                                             LED SERVICES
*********************************************************************************************************
*/

void         LED_On             (CPU_INT08U led);
void         LED_Off            (CPU_INT08U led);
void         LED_Toggle         (CPU_INT08U led);

/*
*********************************************************************************************************
*                                         PUSH BUTTON SERVICES
*********************************************************************************************************
*/

CPU_BOOLEAN  PB_GetStatus       (CPU_INT08U pb);

/*
*********************************************************************************************************
*                                         ADC SERVICES
*********************************************************************************************************
*/

CPU_INT16U   ADC_GetStatus      (CPU_INT08U  adc);

/*
*********************************************************************************************************
*                                             TICK SERVICES
*********************************************************************************************************
*/

void         Tmr_TickISR_Handler(void);


extern void uart1_init (unsigned int);
extern void uart0_init (unsigned int);
extern void uart1_putc	(char);
extern void uart0_putc	(char);
extern void uart1_puts	(char *);
extern void uart0_puts	(char *);

#endif

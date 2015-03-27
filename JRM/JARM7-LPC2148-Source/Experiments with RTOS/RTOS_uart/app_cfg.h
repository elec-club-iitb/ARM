/*
*********************************************************************************************************
*                                              EXAMPLE CODE
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
*                                       APPLICATION CONFIGURATION
*
*                                              NXP LPC2148
*                                                on the
*                                     Keil MCB2140 Evaluation Board
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : JJL
*********************************************************************************************************
*/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/

#define  OS_VIEW_MODULE                  DEF_DISABLED            /* DEF_ENABLED = Present, DEF_DISABLED = Not Present        */

/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_TASK_START_PRIO                   5
#define  APP_TASK_2_PRIO                     6
#define  APP_TASK_3_PRIO                     7

#define  OS_VIEW_TASK_PRIO                     8
#define  OS_VIEW_TASK_ID                       8

#define  OS_TASK_TMR_PRIO              (OS_LOWEST_PRIO - 2)

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                            Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

#define  APP_TASK_START_STK_SIZE           256
#define  APP_TASK_2_STK_SIZE               256
#define  APP_TASK_3_STK_SIZE               256

#define  OS_VIEW_TASK_STK_SIZE               256

/*
*********************************************************************************************************
*                                         uC/OS-View CONFIGURATION
*********************************************************************************************************
*/

#define  OS_VIEW_UART_0                         0
#define  OS_VIEW_UART_1                         1
#define  OS_VIEW_UART_2                         2

#define  OS_VIEW_PARSE_TASK                     1                     /* Parsing of received packets will be done by a task   */
#define  OS_VIEW_TMR_32_BITS                    1                     /* uC/OS-View timer is 32 bits                          */
#define  OS_VIEW_TIMER_SEL                      2                     /* Choose an internal timer to use for OSView 0, 1, 2   */
#define  OS_VIEW_COMM_SEL                  OS_VIEW_UART_1             /* Select UART1 for uC/OS-View to use                   */

/*
*********************************************************************************************************
*                                      uC/OS-II DCC CONFIGURATION
*********************************************************************************************************
*/

#define  OS_CPU_ARM_DCC_EN                     0




#endif

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
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : JJL
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_GLOBALS
#include <includes.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/
                                                                /* ---------------------- GPIO0 Pins ---------------------- */
#define  GPIO0_TXD0             DEF_BIT_00
#define  GPIO0_RXD0             DEF_BIT_01
#define  GPIO0_TXD1             DEF_BIT_08
#define  GPIO0_RXD1             DEF_BIT_09
#define  GPIO0_INT1             DEF_BIT_14
#define  GPIO0_SCK1             DEF_BIT_17
#define  GPIO0_MISO1            DEF_BIT_18
#define  GPIO0_MOSI1            DEF_BIT_19
#define  GPIO0_SSEL1            DEF_BIT_20
#define  GPIO0_AVOUT            DEF_BIT_25
#define  GPIO0_DPP              DEF_BIT_26
#define  GPIO0_DPM              DEF_BIT_27
#define  GPIO0_AVIN             DEF_BIT_28

                                                                /* ---------------------- GPIO1 Pins ---------------------- */
#define  GPIO1_LED1             DEF_BIT_04
#define  GPIO1_LED2             DEF_BIT_05
#define  GPIO1_LED3             DEF_BIT_06
#define  GPIO1_LED4             DEF_BIT_07
#define  GPIO1_LED5             DEF_BIT_10
#define  GPIO1_LED6             DEF_BIT_11
#define  GPIO1_LED7             DEF_BIT_12
#define  GPIO1_LED8             DEF_BIT_13
#define  GPIO1_LEDS       (GPIO1_LED1 | GPIO1_LED2 | GPIO1_LED3 | GPIO1_LED4 | GPIO1_LED5 | GPIO1_LED6 | GPIO1_LED7 | GPIO1_LED8)

/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

        CPU_INT32U  VIC_SpuriousInt;


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  ADC_Init       (void);
static  void  LED_Init       (void);

static  void  BSP_PLL_Init   (void);
static  void  BSP_IO_Init    (void);
static  void  BSP_MAM_Init   (void);

static  void  Tmr_TickInit   (void);

static  void  VIC_Init       (void);
static  void  VIC_Dummy      (void);
static  void  VIC_DummyWDT   (void);
static  void  VIC_DummyTIMER0(void);
static  void  VIC_DummyTIMER1(void);
static  void  VIC_DummyUART0 (void);
static  void  VIC_DummyUART1 (void);
static  void  VIC_DummyPWM0  (void);
static  void  VIC_DummyI2C   (void);
static  void  VIC_DummySPI   (void);
static  void  VIC_DummyRTC   (void);
static  void  VIC_DummyEINT0 (void);
static  void  VIC_DummyEINT1 (void);
static  void  VIC_DummyEINT2 (void);

/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             BSP_Init()
*
* Description : Initialize the Board Support Package (BSP).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : (1) This function SHOULD be called before any other BSP function is called.
*********************************************************************************************************
*/

void  BSP_Init (void)
{
    MEMMAP = 2;                                                 /* Remap 64 bytes of int. RAM to 0x00                       */

    OS_CPU_InitExceptVect();

    BSP_PLL_Init();                                             /* Initialize PLL0 and the VPB Divider Register             */
    BSP_MAM_Init();                                             /* Initialize the Memory Acceleration Module                */
    BSP_IO_Init();                                              /* Initialize the board's I/Os                              */

    VIC_Init();                                                 /* Initialize the Vectored Interrupt Controller             */
    LED_Init();                                                 /* Initialize the LED controls                              */
    ADC_Init();
    uart1_init(9600);	                                                 /* Intiialize the ADC control                               */
	uart0_init(9600);

    Tmr_TickInit();                                             /* Initialize the uC/OS-II tick interrupt                   */
}


/*
*********************************************************************************************************
*                                            BSP_CPU_ClkFreq()
*
* Description : Get the CPU clock frequency.
*
* Argument(s) : none.
*
* Return(s)   : The CPU clock frequency, in Hz.
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
    CPU_INT32U  msel;
    CPU_INT32U  cpu_clk_freq;


    msel         = (CPU_INT32U)(PLLCFG & 0x1F);
    cpu_clk_freq = CPU_OSC_FREQ * (msel + 1);
    return (cpu_clk_freq);
}


/*
*********************************************************************************************************
*                                            BSP_CPU_PclkFreq()
*
* Description : Get the peripheral clock frequency.
*
* Argument(s) : none.
*
* Return(s)   : The peripheral clock frequency, in Hz.
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_PclkFreq (void)
{
    CPU_INT32U  msel;
    CPU_INT32U  vpbdiv;
    CPU_INT32U  clk_freq;
    CPU_INT32U  pclk_freq;


    msel         = (CPU_INT32U)(PLLCFG   & 0x1F);
    clk_freq     = CPU_OSC_FREQ * (msel + 1);

    vpbdiv       = (CPU_INT32U)(VPBDIV & 0x03);
    switch (vpbdiv) {
        case 0:
             pclk_freq = clk_freq / 4;
             break;

        case 1:
             pclk_freq = clk_freq;
             break;

        case 2:
             pclk_freq = clk_freq / 2;
             break;

        default:
             pclk_freq = clk_freq / 4;
             break;
    }
    return (pclk_freq);
}


/*
*********************************************************************************************************
*                                          OS_CPU_ExceptHndlr()
*
* Description : Handle any exceptions.
*
* Argument(s) : except_id     ARM exception type:
*
*                                  OS_CPU_ARM_EXCEPT_RESET             0x00
*                                  OS_CPU_ARM_EXCEPT_UNDEF_INSTR       0x01
*                                  OS_CPU_ARM_EXCEPT_SWI               0x02
*                                  OS_CPU_ARM_EXCEPT_PREFETCH_ABORT    0x03
*                                  OS_CPU_ARM_EXCEPT_DATA_ABORT        0x04
*                                  OS_CPU_ARM_EXCEPT_ADDR_ABORT        0x05
*                                  OS_CPU_ARM_EXCEPT_IRQ               0x06
*                                  OS_CPU_ARM_EXCEPT_FIQ               0x07
*
* Return(s)   : none.
*
* Caller(s)   : OS_CPU_ARM_EXCEPT_HANDLER(), which is declared in os_cpu_a.s.
*********************************************************************************************************
*/

void  OS_CPU_ExceptHndlr (CPU_INT32U  except_id)
{
    CPU_FNCT_VOID  pfnct;


    if (except_id == OS_CPU_ARM_EXCEPT_IRQ) {

        pfnct = (CPU_FNCT_VOID)VICVectAddr;                     /* Read the interrupt vector from the VIC                   */
        while (pfnct != (CPU_FNCT_VOID)0) {                     /* Make sure we don't have a NULL pointer                   */
          (*pfnct)();                                           /* Execute the ISR for the interrupting device              */
            VICVectAddr = 1;                                    /* Acknowlege the VIC interrupt                             */
            pfnct = (CPU_FNCT_VOID)VICVectAddr;                 /* Read the interrupt vector from the VIC                   */
        }

    } else {

                                                                /* Infinite loop on other exceptions.                       */
                                                                /* Should be replaced by other behavior (reboot, etc.)      */
        while (DEF_TRUE) {
            ;
        }
    }
}


/*
*********************************************************************************************************
*                                           BSP_IntDisAll()
*
* Description : Disable ALL interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

void  BSP_IntDisAll (void)
{
    VICIntEnClear = 0xFFFFFFFFL;                                /* Disable ALL interrupts                                   */
}


/*
*********************************************************************************************************
*********************************************************************************************************
**                                       PB, LED, AND ADC FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             LED_Init()
*
* Description : Setup the I/O for the LEDs.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

void  LED_Init (void)
{
	IO0DIR =  GPIO1_LEDS;
    LED_Off(0);                                                 /* Turn OFF all the LEDs                                    */
}


/*
*********************************************************************************************************
*                                             LED_On()
*
* Description : Turn ON any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    turn ON all LEDs on the board
*                       1    turn ON LED1
*                       .
*                       .
*                       .
*                       8    turn ON LED8
*
* Return(s)   : none.
*********************************************************************************************************
*/

void  LED_On (CPU_INT08U led)
{
    switch (led) {
        case 0:
             IO0SET = GPIO1_LEDS;
             break;

        case 1:
             IO0SET = GPIO1_LED1;
             break;

        case 2:
             IO0SET = GPIO1_LED2;
             break;

        case 3:
             IO0SET = GPIO1_LED3;
             break;

        case 4:
             IO0SET = GPIO1_LED4;
             break;

        case 5:
             IO0SET = GPIO1_LED5;
             break;

        case 6:
             IO0SET = GPIO1_LED6;
             break;

        case 7:
             IO0SET = GPIO1_LED7;
             break;

        case 8:
             IO0SET = GPIO1_LED8;
             break;

        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                             LED_Off()
*
* Description : Turn OFF any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    turn OFF all LEDs on the board
*                       1    turn OFF LED1
*                       .
*                       .
*                       .
*                       8    turn OFF LED8
*
* Return(s)   : none.
*********************************************************************************************************
*/

void  LED_Off (CPU_INT08U led)
{
    switch (led) {
        case 0:
             IO0CLR = GPIO1_LEDS;
             break;

        case 1:
             IO0CLR = GPIO1_LED1;
             break;

        case 2:
             IO0CLR = GPIO1_LED2;
             break;

        case 3:
             IO0CLR = GPIO1_LED3;
             break;

        case 4:
             IO0CLR = GPIO1_LED4;
             break;

        case 5:
             IO0CLR = GPIO1_LED5;
             break;

        case 6:
             IO0CLR = GPIO1_LED6;
             break;

        case 7:
             IO0CLR = GPIO1_LED7;
             break;

        case 8:
             IO0CLR = GPIO1_LED8;
             break;

        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                             LED_Toggle()
*
* Description : TOGGLE any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    TOGGLE all LEDs on the board
*                       1    TOGGLE LED1
*                       .
*                       .
*                       .
*                       8    TOGGLE LED8
*
* Return(s)   : none.
*********************************************************************************************************
*/

void  LED_Toggle (CPU_INT08U led)
{
    CPU_INT32U  are_off;
    CPU_INT32U  are_on;


    switch (led) {
        case 0:
             are_off = ( (IO1PIN ^ GPIO1_LEDS) & GPIO1_LEDS);
             are_on  = (~(IO1PIN ^ GPIO1_LEDS) & GPIO1_LEDS);
             IO1CLR =  are_on;
             IO1SET =  are_off;

        case 1:
             if ((IO1PIN & GPIO1_LED1) == 0) {
                 IO1CLR  = GPIO1_LED1;
             } else {
                 IO1SET  = GPIO1_LED1;
             }
             break;

        case 2:
             if ((IO1PIN & GPIO1_LED2) == 0) {
                 IO1CLR  = GPIO1_LED2;
             } else {
                 IO1SET  = GPIO1_LED2;
             }
             break;

        case 3:
             if ((IO1PIN & GPIO1_LED3) == 0) {
                 IO1CLR  = GPIO1_LED3;
             } else {
                 IO1SET  = GPIO1_LED3;
             }
             break;

        case 4:
             if ((IO1PIN & GPIO1_LED4) == 0) {
                 IO1CLR  = GPIO1_LED4;
             } else {
                 IO1SET  = GPIO1_LED4;
             }
             break;

        case 5:
             if ((IO1PIN & GPIO1_LED5) == 0) {
                 IO1CLR  = GPIO1_LED5;
             } else {
                 IO1SET  = GPIO1_LED5;
             }
             break;

        case 6:
             if ((IO1PIN & GPIO1_LED6) == 0) {
                 IO1CLR  = GPIO1_LED6;
             } else {
                 IO1SET  = GPIO1_LED6;
             }
             break;

        case 7:
             if ((IO1PIN & GPIO1_LED7) == 0) {
                 IO1CLR  = GPIO1_LED7;
             } else {
                 IO1SET  = GPIO1_LED7;
             }
             break;

        case 8:
             if ((IO1PIN & GPIO1_LED8) == 0) {
                 IO1CLR  = GPIO1_LED8;
             } else {
                 IO1SET  = GPIO1_LED8;
             }
             break;
    }
}


/*
*********************************************************************************************************
*                                         PB_GetStatus()
*
* Description : Get the status of a push button on the board.
*
* Argument(s) : pb      The ID of the push button to probe
*
*                       1    probe the push button INT1
*
* Return(s)   : DEF_FALSE   if the push button is pressed
*               DEF_TRUE    if the push button is not pressed
*********************************************************************************************************
*/

CPU_BOOLEAN  PB_GetStatus (CPU_INT08U pb)
{
    CPU_BOOLEAN  status;


    status = DEF_FALSE;

    switch (pb) {
        case 1:
             if ((IO0PIN & GPIO0_INT1) == 0) {
                 return (DEF_TRUE);
             }
             break;

        default:
             break;
    }

    return (status);
}

/*
*********************************************************************************************************
*                                         ADC_Init()
*
* Description : Initializes the board's ADC.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

static  void  ADC_Init (void)
{
    CPU_INT08U  div;
    CPU_INT32U  pinsel;


    div      = (BSP_CPU_PclkFreq() / 4500000) + 1;
                                                                /* Configure ADC ...                                        */
    AD0CR    = (0x02 <<  0)                                     /*  ... Sample/convert pin AD0.1 ...                        */
             | (div  <<  8)                                     /*  ... Set divider so sample freq. < 4.5 MHz ...           */
             | (   1 << 16)                                     /*  ... Use burst mode for continuous conversion ...        */
             | (0x00 << 17)                                     /*  ... Use 11 clocks per conversion for 10-bit accuracy ...*/
             | (   1 << 21);                                    /*  ... Power up the ADC.                                   */

                                                                /* Select AD0.1 function for PIN0.28                        */
    pinsel   = PINSEL1;
    pinsel  &= ~0x03000000;
    pinsel  |=  0x01000000;
    PINSEL1  =  pinsel;

    AD0CR   |=  (0x01 << 24);                                   /* Start conversion                                         */
}


/*
*********************************************************************************************************
*                                           ADC_GetStatus()
*
* Description : This function initializes the board's ADC
*
* Argument(s) : adc     The ID of the ADC to probe:
*                       1   Probe the potentiometer.
*
* Return(s)   : The numerator of the binary fraction representing the result of the latest ADC conversion.
*               This value will be a 10-bit value between 0x0000 and 0x03FF, inclusive.
*********************************************************************************************************
*/

CPU_INT16U  ADC_GetStatus (CPU_INT08U  adc)
{
    if (adc == 1) {
        return ((AD0DR1 >> 6) & 0x03FF);
    } else {
        return (0);
    }
}


/*
*********************************************************************************************************
*********************************************************************************************************
**                                          uC/OS-View FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                              OSView_TmrInit()
*
* Description : Select & initialize a timer for use with uC/OS-View.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

#if (OS_VIEW_MODULE > 0)
void  OSView_TmrInit (void)
{
    T1PR  = 0;
    T1TCR = 0x00000001;                                         /* Enable the timer                                         */

}
#endif


/*
*********************************************************************************************************
*                                         OSView_TmrRd()
*
* Description : Read the current counts of a 32-bit free running timer.
*
* Argument(s) : none.
*
* Return(s)   : The 32 bit counts of the timer.
*********************************************************************************************************
*/

#if (OS_VIEW_MODULE > 0)
CPU_INT32U  OSView_TmrRd (void)
{
    return ((CPU_INT32U)T1TC);
}
#endif


/*
*********************************************************************************************************
*********************************************************************************************************
*                             uC/Probe PLUG-IN FOR uC/OS-II FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       OSProbe_TmrInit()
*
* Description : Select & initialize a timer for use with the uC/Probe Plug-In for uC/OS-II.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

#if (uC_PROBE_OS_PLUGIN > 0) && (OS_PROBE_HOOKS_EN == 1)
void  OSProbe_TmrInit (void)
{
    T1PR  = 0;
    T1TCR = 0x00000001;                                         /* Enable the timer                                         */

}
#endif


/*
*********************************************************************************************************
*                                        OSProbe_TmrRd()
*
* Description : Read the current counts of a 32-bit free running timer.
*
* Argument(s) : none.
*
* Return(s)   : The 32bit counts of the timer.
*********************************************************************************************************
*/

#if (uC_PROBE_OS_PLUGIN > 0) && (OS_PROBE_HOOKS_EN == 1)
CPU_INT32U  OSProbe_TmrRd (void)
{
    return ((CPU_INT32U)T1TC);
}
#endif

/*
*********************************************************************************************************
*********************************************************************************************************
**                                     uC/OS-II TIMER FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            Tmr_TickInit()
*
* Description : Initialize uC/OS-II's tick source.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

static  void  Tmr_TickInit (void)
{
    CPU_INT32U  pclk_freq;
    CPU_INT32U  tmr_reload;

                                                                /* VIC TIMER #0 Initialization                              */
    VICIntSelect &= ~(1 << VIC_TIMER0);                         /* Enable interrupts                                        */
    VICVectAddr2  = (CPU_INT32U)Tmr_TickISR_Handler;            /* Set the vector address                                   */
    VICVectCntl2  = 0x20 | VIC_TIMER0;                          /* Enable vectored interrupts                               */
    VICIntEnable  = (1 << VIC_TIMER0);                          /* Enable Interrupts                                        */

    pclk_freq     = BSP_CPU_PclkFreq();
    tmr_reload    = pclk_freq / OS_TICKS_PER_SEC;
    T0TCR         = 0;                                          /* Disable timer 0.                                         */
    T0PC          = 0;                                          /* Prescaler is set to no division.                         */

    T0MR0         = tmr_reload;
    T0MCR         = 3;                                          /* Interrupt on MR0 (reset TC)                              */

    T0CCR         = 0;                                          /* Capture is disabled.                                     */
    T0EMR         = 0;                                          /* No external match output.                                */
    T0TCR         = 1;                                          /* Enable timer 0                                           */
}


/*
*********************************************************************************************************
*                                       Tmr_TickISR_Handler()
*
* Description : Handle the timer interrupt that is used to generate TICKs for uC/OS-II.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

void  Tmr_TickISR_Handler (void)
{
    T0IR = 0xFF;                                                /* Clear timer #0 interrupt                                 */

    OSTimeTick();                                               /* Call uC/OS-II's OSTimeTick()                             */
}


/*
*********************************************************************************************************
*********************************************************************************************************
**                                          LOCAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                        BSP_PLL_Init()
*
* Description : Set up and activate the PLL
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

static  void  BSP_PLL_Init (void)
{
#if OS_CRITICAL_METHOD == 3                                     /* Allocate storage for CPU status register                 */
    OS_CPU_SR   cpu_sr = 0;
#endif
    CPU_INT16U  loop_ctr;

                                                                /* Configure PLL0, which determines the CPU clock           */
    PLLCFG   = 0x00000023;                                      /* Use PLL values of M = 4 and P = 2                        */
    PLLCON  |= 0x00000001;                                      /* Set the PLL Enable bit                                   */

    OS_ENTER_CRITICAL();
    PLLFEED  = 0xAA;                                            /* Write to the PLL Feed register                           */
    PLLFEED  = 0x55;
    OS_EXIT_CRITICAL();

    loop_ctr = 10000;                                           /* Wait for the PLL to lock into the new frequency          */
    while (((PLLSTAT & DEF_BIT_10) == 0) && (loop_ctr > 0)) {
        loop_ctr--;
    }

    PLLCON  |= 0x00000002;                                      /* Connect the PLL                                          */

    OS_ENTER_CRITICAL();
    PLLFEED  = 0xAA;                                            /* Write to the PLL Feed register                           */
    PLLFEED  = 0x55;
    OS_EXIT_CRITICAL();

    VPBDIV   = 0x00000002;                                      /* Set the VPB frequency to one-half of the CPU clock       */
}


/*
*********************************************************************************************************
*                                          BSP_IO_Init()
*
* Description : Initilize the GPIO pins.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     :  (1) The pins P1.36-26 are setup as a Debug port and the pins P1.25-16 are setup as a
*                   trace port (by the last statements in this function).  If pins for one of these
*                   are to be used as GPIO, comment out the appropriate statement.
*
*               (2) Additional hardware may be necessary for using the Trace or Debug capability.
*                   According to section 23.5 of the LPC2148 user manual (UM10139, rev. 02):
*
*                       "To have these pins [P1.25-16] come as a Trace port, connect a
*                        weak bias resistor (4.7 kOhm) between the P1.20/TRACESYNC pin and Vss."
*
*                   Similarly, according to section 22.5 of the LPC2148 user manual,
*
*                       "To have them [pins P1.36-26] come up as a Debug port, connect a weak
*                        bias resistor (4.7-10kOhm depending on the external JTAG circuitry)
*                        between Vss and the P1.26/RTCK pin"
*********************************************************************************************************
*/

static  void  BSP_IO_Init (void)
{
//    SCS      = 0x00000001;                                      /* Fast GPIO registers will be used                         */

    PINSEL0  = 0x00000000;

    IO0DIR  &= ~GPIO0_INT1;                                     /* Push button INT1                                         */
    IO1DIR  |=  GPIO1_LEDS;                                     /* LEDs                                                     */

                                                                /* The following statements setup the Trace/Debug           */
                                                                /* capabilitiy. If the pins indicated are to be used as     */
                                                                /* GPIO, remove or comment out these statements.            */

    PINSEL2  |= 0x00000004;                                     /* The pins P1.36-26 will be used as a Debug port.          */
//  PINSEL2  |= 0x00000008;                                     /* The pins P1.25-16 will be used as a Trace port.          */
}

#define _PCLK 24000000  // Define PCLK for configuration baudrate
#define uart1_setbaud(x) uart1_init(x)  // Define function name uart1_setbaud equal uart1_init
#define uart0_setbaud(x) uart0_init(x)  // Define function name uart0_setbaud equal uart0_init

void uart1_init(unsigned int _baudrate)
{
    unsigned short u1dl;    
    u1dl = _PCLK/(16*_baudrate);    // Calculate for U1DL value
    PINSEL0 |= 0x00050000;	// Enable rx,tx
	U1LCR = 0x00000083;		// 8 bit data,1 stop bit,no parity bit
    U1DLL = u1dl & 0xFF;    // U1DL for low byte
    U1DLM = (u1dl>>8);      // U1DL for high byte
    U1LCR = 0x00000003;		// DLAB =0
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for send character 1 time via UART1-----------------------//
//------------------------------------------------------------------------------------------------//
void uart1_putc(char c)
{
	while(!(U1LSR & 0x20)); // Wait until UART1 ready to send character     
	U1THR = c;  // Send character
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for send string via UART1---------------------------------//
//------------------------------------------------------------------------------------------------//
void uart1_puts(char *p)
{
	while(*p) // Point to character
	{
		uart1_putc(*p++);   // Send character then point to next character
	}
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for Initial UART0 ----------------------------------------//
//------------------------------------------------------------------------------------------------//
void uart0_init(unsigned int _baudrate)
{
	unsigned short u0dl;
    u0dl = _PCLK/(16*_baudrate); // Calculate for U0DL value
    PINSEL0 |= 0x00000005;	// Enable rx,tx
	U0LCR = 0x00000083;		// 8 bit data,1 stop bit,no parity bit
    U0DLL = u0dl & 0xFF;    // U0DL for low byte
    U0DLM = (u0dl>>8);      // U0DL for high byte
    U0LCR = 0x00000003;		// DLAB =0
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for send character 1 time via UART0-----------------------//
//------------------------------------------------------------------------------------------------//
void uart0_putc(char c)
{
	while(!(U0LSR & 0x20)); // Wait until UART0 ready to send character  
	U0THR = c; // Send character
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for send string via UART1---------------------------------//
//------------------------------------------------------------------------------------------------//
void uart0_puts(char *p)
{
	while(*p) // Point to character
	{
		uart0_putc(*p++);  // Send character then point to next character
	}
}

/*
*********************************************************************************************************
*                                             BSP_MAM_Init()
*
* Description : Initialize the memory acceleration module.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

static  void  BSP_MAM_Init (void)
{
    MAMCR  = 0x00;                                              /* Disable the Memory Accelerator Module                    */
    MAMTIM = 0x03;                                              /* MAM fetch cycles are 3 CCLKs in duration                 */
    MAMCR  = 0x02;                                              /* Enable the Memory Accelerator Module                     */
}

/*
*********************************************************************************************************
*********************************************************************************************************
**                                            VIC FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                        Vectored Interrupt Controller
*********************************************************************************************************
*/

static  void  VIC_Init (void)
{
    VICIntEnClear = 0xFFFFFFFF;                                 /* Disable ALL interrupts                                   */
    VICProtection = 0;                                          /* Setup interrupt controller                               */

    VICVectAddr1  = (CPU_INT32U)VIC_DummyWDT;                   /* Set the vector address                                   */
    VICVectAddr2  = (CPU_INT32U)VIC_DummyTIMER0;
    VICVectAddr3  = (CPU_INT32U)VIC_DummyTIMER1;
    VICVectAddr4  = (CPU_INT32U)VIC_DummyUART0;
    VICVectAddr5  = (CPU_INT32U)VIC_DummyUART1;
    VICVectAddr6  = (CPU_INT32U)VIC_DummyPWM0;
    VICVectAddr7  = (CPU_INT32U)VIC_DummyI2C;
    VICVectAddr8  = (CPU_INT32U)VIC_DummySPI;
    VICVectAddr9  = (CPU_INT32U)VIC_DummyRTC;
    VICVectAddr10 = (CPU_INT32U)VIC_DummyEINT0;
    VICVectAddr11 = (CPU_INT32U)VIC_DummyEINT1;
    VICVectAddr12 = (CPU_INT32U)VIC_DummyEINT2;
}

static  void  VIC_Dummy (void)
{
    while (1) {
        (void)VIC_SpuriousInt;
    }
}

static  void  VIC_DummyWDT (void)
{
    VIC_SpuriousInt = VIC_WDT;
    VIC_Dummy();
}

static  void  VIC_DummyTIMER0 (void)
{
    VIC_SpuriousInt = VIC_TIMER0;
    VIC_Dummy();
}

static  void  VIC_DummyTIMER1 (void)
{
    VIC_SpuriousInt = VIC_TIMER1;
    VIC_Dummy();
}

static  void  VIC_DummyUART0 (void)
{
    VIC_SpuriousInt = VIC_UART0;
    VIC_Dummy();
}

static  void  VIC_DummyUART1 (void)
{
    VIC_SpuriousInt = VIC_UART1;
    VIC_Dummy();
}

static  void  VIC_DummyPWM0 (void)
{
    VIC_SpuriousInt = VIC_UART1;
    VIC_Dummy();
}

static  void  VIC_DummyI2C (void)
{
    VIC_SpuriousInt = VIC_I2C;
    VIC_Dummy();
}

static  void  VIC_DummySPI (void)
{
    VIC_SpuriousInt = VIC_SPI;
    VIC_Dummy();
}

static  void  VIC_DummyRTC (void)
{
    VIC_SpuriousInt = VIC_RTC;
    VIC_Dummy();
}

static  void  VIC_DummyEINT0 (void)
{
    VIC_SpuriousInt = VIC_EINT0;
    VIC_Dummy();
}

static  void  VIC_DummyEINT1 (void)
{
    VIC_SpuriousInt = VIC_EINT1;
    VIC_Dummy();
}

static  void  VIC_DummyEINT2 (void)
{
    VIC_SpuriousInt = VIC_EINT2;
    VIC_Dummy();
}

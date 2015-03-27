;******************************************************************************
;
;                             INTERRUPT VECTORS
;                                    ARM
;                             KEIL's uVision3 
;                   (RealView Microprocessor Developer Kit)
;
; Filename      : vectors.s
;******************************************************************************

                PRESERVE8
                AREA   VECT, CODE, READONLY                     ; Name this block of code                                   ;
                ARM
                ENTRY

;******************************************************************************
;                                  IMPORTS
;******************************************************************************

                IMPORT  OS_CPU_ARM_ExceptUndefInstrHndlr
                IMPORT  OS_CPU_ARM_ExceptSwiHndlr
                IMPORT  OS_CPU_ARM_ExceptPrefetchAbortHndlr
                IMPORT  OS_CPU_ARM_ExceptDataAbortHndlr
                IMPORT  OS_CPU_ARM_ExceptIrqHndlr
                IMPORT  OS_CPU_ARM_ExceptFiqHndlr
                IMPORT  ResetHndlr
                

;******************************************************************************
;                                  EXPORTS
;******************************************************************************


;******************************************************************************
;                                DEFINITIONS
;******************************************************************************


;******************************************************************************
;                      INITIALIZE EXCEPTION VECTORS
;******************************************************************************

Vectors
                ldr     pc, Reset_Addr
                ldr     pc, Undef_Addr
                ldr     pc, SWI_Addr
                ldr     pc, Prefetch_Addr
                ldr     pc, Abort_Addr
                nop
		        ldr	    pc, IRQ_Addr
		        ldr	    pc, FIQ_Addr

Reset_Addr      dcd     ResetHndlr
Undef_Addr      dcd     OS_CPU_ARM_ExceptUndefInstrHndlr
SWI_Addr        dcd     OS_CPU_ARM_ExceptSwiHndlr
Prefetch_Addr   dcd     OS_CPU_ARM_ExceptPrefetchAbortHndlr
Abort_Addr      dcd     OS_CPU_ARM_ExceptDataAbortHndlr
                nop
IRQ_Addr        dcd     OS_CPU_ARM_ExceptIrqHndlr
FIQ_Addr        dcd     OS_CPU_ARM_ExceptFiqHndlr


                END
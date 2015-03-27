;******************************************************************************
;
;                               STARTUP CODE
;                                  LPC2378
;                             KEIL's uVision3 
;                   (RealView Microprocessor Developer Kit)
;
; Filename      : init.s
;******************************************************************************

                PRESERVE8
                AREA   INIT, CODE, READONLY                     ; Name this block of code                                   ;
                ARM

;******************************************************************************
;                                  IMPORTS
;******************************************************************************
                                
                IMPORT  __main
                IMPORT  ||Image$$ARM_LIB_STACK$$ZI$$Limit||     ; Import stack limit from scatter-loading file              ;

;******************************************************************************
;                                  EXPORTS
;******************************************************************************

                EXPORT  ResetHndlr

;******************************************************************************
;                                DEFINITIONS
;******************************************************************************

MODE_BITS	    EQU	    0x1F		; Bit mask for mode bits in CPSR
USR_MODE	    EQU	    0x10		; User mode
FIQ_MODE	    EQU 	0x11		; Fast Interrupt Request mode
IRQ_MODE	    EQU	    0x12		; Interrupt Request mode
SVC_MODE	    EQU	    0x13		; Supervisor mode
ABT_MODE	    EQU	    0x17		; Abort mode
UND_MODE	    EQU	    0x1B		; Undefined Instruction mode
SYS_MODE        EQU 	0x1F		; System mode
	
I_BIT           EQU     0x80
F_BIT           EQU     0x40

                                                      	    ; Define stack sizes                                        ;
IRQ_STK_SIZE    EQU     0x00000200
FIQ_STK_SIZE    EQU     0x00000100
SVC_STK_SIZE    EQU     0x00000200
ABT_STK_SIZE    EQU     0x00000200
UND_STK_SIZE    EQU     0x00000200
SYS_STK_SIZE    EQU     0x00000200

MEMMAP          EQU     0xE01FC040

                                                         	; Define stack pointers                                     ;

;******************************************************************************
;                             PERFORM ROM/RAM REMAPPING
;******************************************************************************                

                ENTRY
ResetHndlr      
                                                      	    ; If interrupt vectors in RAM, then perform remap           ;
                IF :DEF: REMAP
                
                ldr     r0, =MEMMAP
                mov     r1, #2
                str     r1, [r0]
                
                ENDIF

;******************************************************************************
;                              SETUP STACK POINTERS
;******************************************************************************
                
                ldr     r1, =||Image$$ARM_LIB_STACK$$ZI$$Limit||
                
                mrs     r0,cpsr                             ; Original PSR value                                        ;
                bic     r0,r0,#MODE_BITS                    ; Clear the mode bits                                       ;
                orr     r0,r0,#IRQ_MODE                     ; Set IRQ mode bits                                         ;
                msr     cpsr_c,r0                           ; Change the mode                                           ;
                mov     sp, r1
                sub     r1, r1, #IRQ_STK_SIZE
                
                mrs     r0,cpsr                             ; Original PSR value                                        ;
                bic     r0,r0,#MODE_BITS                    ; Clear the mode bits                                       ;
                orr     r0,r0,#ABT_MODE                     ; Set IRQ mode bits                                         ;
                msr     cpsr_c,r0                           ; Change the mode                                           ;
                mov     sp, r1
                sub     r1, r1, #ABT_STK_SIZE
                
                mrs     r0,cpsr                             ; Original PSR value                                        ;
                bic     r0,r0,#MODE_BITS                    ; Clear the mode bits                                       ;
                orr     r0,r0,#UND_MODE                     ; Set IRQ mode bits                                         ;
                msr     cpsr_c,r0                           ; Change the mode                                           ;
                mov     sp, r1
                sub     r1, r1, #UND_STK_SIZE

                mrs     r0,cpsr                             ; Original PSR value                                        ;
                bic     r0,r0,#MODE_BITS                    ; Clear the mode bits                                       ;
                orr     r0,r0,#FIQ_MODE                     ; Set IRQ mode bits                                         ;
                msr     cpsr_c,r0                           ; Change the mode                                           ;
                mov     sp, r1
                sub     r1, r1, #FIQ_STK_SIZE
                
                mrs     r0,cpsr                             ; Original PSR value                                        ;
                bic     r0,r0,#MODE_BITS                    ; Clear the mode bits                                       ;
                orr     r0,r0,#SVC_MODE                     ; Set IRQ mode bits                                         ;
                msr     cpsr_c,r0                           ; Change the mode                                           ;
                mov     sp, r1
        
                msr     cpsr_c, #SVC_MODE:OR:F_BIT          ; Enable interrupts, if required                            ;

;******************************************************************************
;                                   MOVE TO MAIN
;******************************************************************************
                ldr     r0, =__main
                bx      r0                             	    ; Save this in register for possible long jump              ;

                LTORG

                END 
        

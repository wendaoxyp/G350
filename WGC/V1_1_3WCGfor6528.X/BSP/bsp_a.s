;
;********************************************************************************************************
;                                               uC/OS-II
;                                         The Real-Time Kernel
;
;                         (c) Copyright 2002, Jean J. Labrosse, Weston, FL
;                                          All Rights Reserved
;
;
;                                  dsPIC33FJ Board Support Package
;
;
; File         : bsp_a.s
; By           : Eric Shufro
;********************************************************************************************************
;

;
;********************************************************************************************************
;                                                CONSTANTS
;********************************************************************************************************
;
;
;********************************************************************************************************
;                                                INCLUDES
;********************************************************************************************************
;

.include "xc.inc"
.include "os_cpu_util_a.s"                    ; Include an assembly utility files with macros for saving and restoring the CPU registers

;
;********************************************************************************************************
;                                             LINKER SPECIFICS
;********************************************************************************************************
;

    .text                                                               ; Locate this file in the text region of the build

;
;********************************************************************************************************
;                                                 GLOBALS
;********************************************************************************************************
;

    .global __T2Interrupt
    .global __T4Interrupt

;
;********************************************************************************************************
;                                            OS Time Tick ISR Handler
;
; Description : This function services the OS Time Tick Interrupt when configured using Timer #2
;
; Notes       : All user interrupts should be defined as follows.
;********************************************************************************************************
;

__T2Interrupt:
    OS_REGS_SAVE                                                        ; 1) Save processor registers

    mov   #_OSIntNesting, w1
    inc.b [w1], [w1]                                                    ; 2) Call OSIntEnter() or increment OSIntNesting

    dec.b _OSIntNesting, wreg                                           ; 3) Check OSIntNesting. if OSIntNesting == 1, then save the stack pointer, otherwise jump to T2_Cont
    bra nz, T2_Cont
    mov _OSTCBCur, w0
    mov w15, [w0]

T2_Cont:
    call _OS_Tick_ISR_Handler                                           ; 4) Call YOUR ISR Handler (May be a C function). In this case, the OS Tick ISR Handler
    call _OSIntExit                                                     ; 5) Call OSIntExit() or decrement 1 from OSIntNesting

    OS_REGS_RESTORE                                                     ; 6) Restore registers

    retfie                                                              ; 7) Return from interrupt


;
;********************************************************************************************************
;                                            OS Time Tick ISR Handler
;
; Description : This function services the OS Time Tick Interrupt when configured using Timer #4
;
; Notes       : All user interrupts should be defined as follows.
;********************************************************************************************************
;

__T4Interrupt:
    OS_REGS_SAVE                                                        ; 1) Save processor registers

    mov   #_OSIntNesting, w1
    inc.b [w1], [w1]                                                    ; 2) Call OSIntEnter() or increment OSIntNesting

    dec.b _OSIntNesting, wreg                                           ; 3) Check OSIntNesting. if OSIntNesting == 1, then save the stack pointer, otherwise jump to T2_Cont
    bra nz, T4_Cont
    mov _OSTCBCur, w0
    mov w15, [w0]

T4_Cont:
    call _OS_Tick_ISR_Handler                                           ; 4) Call YOUR ISR Handler (May be a C function). In this case, the OS Tick ISR Handler
    call _OSIntExit                                                     ; 5) Call OSIntExit() or decrement 1 from OSIntNesting

    OS_REGS_RESTORE                                                     ; 6) Restore registers

    retfie                                                              ; 7) Return from interrupt



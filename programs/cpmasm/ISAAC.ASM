
; ASCII Characters
CR      EQU     0DH     ; Carriage Return
LF      EQU     0AH     ; Line Feed
CTRLZ   EQU     1AH     ; Operator Interrupt

; CP/M BDOS Functions
RCONIN  EQU     1       ; Read Console (into A)
WCONOUT EQU     2       ; Write (A) to Console
RBUF    EQU     10      ; Read Buffered Input

; CP/M Addresses
RBOOT   EQU     0       ; Reboot CP/M System
BDOS    EQU     5       ; System Call Entry
TPA     EQU     100H    ; Transient Program Area

        ORG     TPA     ; Assemble program for TPA

; Main Program Start
START:  LXI     SP,STAK ; Set up user's stack
        MVI     D, 0x0E        ; Load the device address for serial output (assumed address for terminal)
        MVI     R0, 3          ; Position of '*' is at index 2
 
        ; Main loop for user input and moving the '*'
START1: CALL    CCRLF   ; Start a new line
        LXI     H,SINON ; With sign-on message
START2: LXI     H,MSG1  ; MSG1 propts for first number
START3: LXI     H,MSG2  ; MSG2 PROPTS FOR SECOND NUMBER 
        ; Now get user input (LEFT, RIGHT, or E)
        CALL    CIMSG          ; Get user input into INBUF
        CALL    CCRLF          ; Print carriage return after input

        LDA     INBUF+2        ; Read the first character of input
        ANI     7FH            ; Mask to 7 bits (clear any high bits)
        CPI     'E'            ; Check if the input is 'E' (exit)
        JZ      EXIT_PROGRAM    ; If 'E', exit the program

        CPI     'L'            ; Check if the input is 'L'
        JZ      MOVE_LEFT      ; If 'L', move '*' left

        CPI     'R'            ; Check if the input is 'R'
        JZ      MOVE_RIGHT     ; If 'R', move '*' right

        JMP     START3      ; If invalid input, ask again

        

SINON:  DB      'Move the asterisk',CR,LF,0
MSG1:   DB      '000*000',CR,LF,0
MSG2:   DB      'LEFT or RIGHT',CR,LF,0


; Console Character Input Routine
CI:     PUSH    B       ; Save registers
        PUSH    D
        PUSH    H
        MVI     C,RCONIN ; Read function
        CALL    BDOS
        ANI     7FH      ; Mask to 7 bits
        POP     H        ; Restore registers
        POP     D
        POP     B
        RET

; Console Output Character Routine
CO:     PUSH    B       ; Save registers
        PUSH    D
        PUSH    H
        MVI     C,WCONOUT ; Select function
        MOV     E,A     ; Character to E
        CALL    BDOS    ; Output by CP/M
        POP     H       ; Restore registers
        POP     D
        POP     B
        RET


; Carriage Return and Line Feed Routine
CCRLF:  MVI     A,CR
        CALL    CO
        MVI     A,LF
        JMP     CO

; Print Message Pointed to by HL to Console
COMSG:  MOV     A,M     ; Get A character
        ORA     A       ; Check if zero
        RZ              ; Return on zero
        CALL    CO      ; Else output the character
        INX     H       ; Point to the next character
        JMP     COMSG   ; Repeat

MOVE_LEFT:
 ; Move '*' left: Update the position of '*' and reprint the string
        MVI     A, '0'         ; Print '0'
        CALL    CO
        MVI     A, '0'         ; Print '0'
        CALL    CO
        MVI     A, '0'         ; Print '0'
        CALL    CO

        ; Update the position of '*' (move left)
        MOV     A, R0
        DEC     A
        MOV     R0, A

        ; Print updated string with '*' moved left
        MVI     A, '0'         ; Print '0'
        CALL    CO
        MVI     A, '0'         ; Print '0'
        CALL    CO
        MVI     A, '*'         ; Print '*'
        CALL    CO
        MVI     A, '0'         ; Print '0'
        CALL    CO
        MVI     A, '0'         ; Print '0'
        CALL    CO
        MVI     A, '0'         ; Print '0'
        CALL    CO

        CALL    CCRLF          ; Print carriage return and line feed
        JMP     START3      ; Ask for input again


MOVE_RIGHT:
      ; Move '*' right: Update the position of '*' and reprint the string
        MVI     A, '0'         ; Print '0'
        CALL    CO
        MVI     A, '0'         ; Print '0'
        CALL    CO
        MVI     A, '0'         ; Print '0'
        CALL    CO

        ; Update the position of '*' (move right)
        MOV     A, R0
        INC     A
        MOV     R0, A

        ; Print updated string with '*' moved right
        MVI     A, '0'         ; Print '0'
        CALL    CO
        MVI     A, '0'         ; Print '0'
        CALL    CO
        MVI     A, '*'         ; Print '*'
        CALL    CO
        MVI     A, '0'         ; Print '0'
        CALL    CO
        MVI     A, '0'         ; Print '0'
        CALL    CO
        MVI     A, '0'         ; Print '0'
        CALL    CO

        CALL    CCRLF          ; Print carriage return and line feed
        JMP     START3      ; Ask for input again
 
EXIT_PROGRAM:
        HLT                     ; Halt the program when 'E' is input

; Subroutine to get user input (LEFT, RIGHT, or E)
GET_INPUT:
        IN      0x00            ; Read input from the terminal (I/O port 0x00)
        MOV     B, A           ; Store the input in register B
        RET                     ; Return to calling point

    
; Stack Setup
        DS      64      ; 40H locations for stack
STAK:   DB      0       ; Top of stack

        END
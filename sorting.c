DATA SEGMENT
    ARR DW 5 DUP(0)
    N EQU 5
    MSG1 DB 10,13, 'Enter 5 hexadecimal numbers (4 digits each): $'
    MSG2 DB 10,13, 'Before sorting: $'
    MSG3 DB 10,13, 'After sorting: $'
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA
    MOV DS, AX

    ; Ask user for input
    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    LEA SI, ARR
    MOV CX, N

READ_LOOP:
    CALL READ_HEX        ; Read one hex number
    MOV [SI], BX         ; Store it
    ADD SI, 2
    LOOP READ_LOOP

    ; Display before sorting
    LEA DX, MSG2
    MOV AH, 09H
    INT 21H
    CALL DISPLAY_ARRAY

    ; Bubble sort
    MOV CX, N
OUTER_LOOP:
    MOV BX, CX
    DEC BX
    JZ DONE_SORT
    LEA SI, ARR
INNER_LOOP:
    MOV AX, [SI]
    CMP AX, [SI+2]
    JBE NOSWAP
    XCHG AX, [SI+2]
    MOV [SI], AX
NOSWAP:
    ADD SI, 2
    DEC BX
    JNZ INNER_LOOP
    LOOP OUTER_LOOP

DONE_SORT:
    ; Display after sorting
    LEA DX, MSG3
    MOV AH, 09H
    INT 21H
    CALL DISPLAY_ARRAY

    ; Exit
    MOV AH, 4CH
    INT 21H

;-----------------------------------------------
; DISPLAY ARRAY
;-----------------------------------------------
DISPLAY_ARRAY PROC
    LEA SI, ARR
    MOV CX, N
PRINT_NEXT:
    MOV BX, [SI]
    CALL PRINT_HEX
    MOV DL, ' '
    MOV AH, 02H
    INT 21H
    ADD SI, 2
    LOOP PRINT_NEXT
    RET
DISPLAY_ARRAY ENDP

;-----------------------------------------------
; READ HEX NUMBER (4 digits)
;-----------------------------------------------
READ_HEX PROC
    MOV BX, 0
    MOV CX, 4
READ_NEXT_DIGIT:
    MOV AH, 01H
    INT 21H
    CMP AL, 0DH
    JE READ_END
    CMP AL, '0'
    JB READ_NEXT_DIGIT
    CMP AL, '9'
    JBE DIGIT
    CMP AL, 'A'
    JB READ_NEXT_DIGIT
    CMP AL, 'F'
    JBE LETTER
    CMP AL, 'a'
    JB READ_NEXT_DIGIT
    CMP AL, 'f'
    JBE LETTER_LOW
    JMP READ_NEXT_DIGIT

DIGIT:
    SUB AL, '0'
    JMP STORE
LETTER:
    SUB AL, 'A'
    ADD AL, 10
    JMP STORE
LETTER_LOW:
    SUB AL, 'a'
    ADD AL, 10
STORE:
    SHL BX, 4
    ADD BL, AL
    LOOP READ_NEXT_DIGIT
READ_END:
    RET
READ_HEX ENDP

;-----------------------------------------------
; PRINT HEX NUMBER
;-----------------------------------------------
PRINT_HEX PROC
    PUSH CX
    MOV CX, 4
NEXT_DIGIT:
    ROL BX, 4
    MOV AL, BL
    AND AL, 0FH
    ADD AL, 30H
    CMP AL, '9'
    JBE DISP
    ADD AL, 7
DISP:
    MOV DL, AL
    MOV AH, 02H
    INT 21H
    LOOP NEXT_DIGIT
    POP CX
    RET
PRINT_HEX ENDP

CODE ENDS
END START
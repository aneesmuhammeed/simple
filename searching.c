DATA SEGMENT
    ARR DW 10 DUP(?)              ; Array for up to 10 numbers
    MSG1 DB 10,13, 'Enter count (<=10): $'
    MSG2 DB 10,13, 'Enter each number (4-digit HEX): $'
    MSG3 DB 10,13, 'Enter number to search: $'
    FOUND_MSG DB 10,13, 'Number Found!$'
    NOT_FOUND_MSG DB 10,13, 'Number Not Found!$'
    N DB ?
    KEY DW ?
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA
    MOV DS, AX

    ; --- Ask for count ---
    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    CALL READ_HEX_BYTE
    MOV N, AL                     ; Store count

    ; --- Input array elements ---
    LEA DX, MSG2
    MOV AH, 09H
    INT 21H

    LEA SI, ARR
    MOV CL, N
    XOR CH, CH

INPUT_LOOP:
    CALL READ_HEX_WORD
    MOV [SI], AX
    ADD SI, 2
    LOOP INPUT_LOOP

    ; --- Ask for search key ---
    LEA DX, MSG3
    MOV AH, 09H
    INT 21H

    CALL READ_HEX_WORD
    MOV KEY, AX

    ; --- Search for key ---
    LEA SI, ARR
    MOV CL, N
    XOR CH, CH

SEARCH_LOOP:
    MOV AX, [SI]
    CMP AX, KEY
    JE FOUND
    ADD SI, 2
    LOOP SEARCH_LOOP

NOT_FOUND:
    LEA DX, NOT_FOUND_MSG
    MOV AH, 09H
    INT 21H
    JMP EXIT

FOUND:
    LEA DX, FOUND_MSG
    MOV AH, 09H
    INT 21H

EXIT:
    MOV AH, 4CH
    INT 21H

;----------------------------------------------------
; READ_HEX_BYTE → reads 2 hex digits (00–FF) into AL
;----------------------------------------------------
READ_HEX_BYTE PROC
    CALL READ_HEX_DIGIT
    MOV AH, AL
    CALL READ_HEX_DIGIT
    SHL AH, 4
    OR AL, AH
    RET
READ_HEX_BYTE ENDP

;----------------------------------------------------
; READ_HEX_WORD → reads 4 hex digits (0000–FFFF) into AX
;----------------------------------------------------
READ_HEX_WORD PROC
    XOR AX, AX
    MOV CX, 4
READ_DIG_LOOP:
    CALL READ_HEX_DIGIT
    SHL AX, 4
    OR AL, AL
    OR AX, AX
    OR AL, AL
    OR AX, AL
    CALL READ_HEX_DIGIT
    LOOP READ_DIG_LOOP
    RET
READ_HEX_WORD ENDP

;----------------------------------------------------
; READ_HEX_DIGIT → reads a single hex digit into AL
;----------------------------------------------------
READ_HEX_DIGIT PROC
    MOV AH, 01H
    INT 21H
    CMP AL, '0'
    JB READ_HEX_DIGIT
    CMP AL, '9'
    JBE NUM_OK
    CMP AL, 'A'
    JB READ_HEX_DIGIT
    CMP AL, 'F'
    JBE LET_OK
    JMP READ_HEX_DIGIT

NUM_OK:
    SUB AL, '0'
    RET
LET_OK:
    SUB AL, 55        ; 'A' = 65, 65-55 = 10
    RET
READ_HEX_DIGIT ENDP

CODE ENDS
END START
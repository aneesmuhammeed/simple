DATA SEGMENT
    MSG1    DB 10,13,'Enter first string:$'
    MSG2    DB 10,13,'Enter second string:$'
    MSG3    DB 10,13,'Concatenated string: $'
    MSG4    DB 10,13,'Length of concatenated string: $'
    STR1    DB 50 DUP(0)
    STR2    DB 50 DUP(0)
    CONCAT  DB 100 DUP(0)
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA
    MOV DS, AX

;--------------------------------------------
; INPUT FIRST STRING
;--------------------------------------------
    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    LEA DI, STR1
    MOV AH, 01H
READ1:
    INT 21H
    CMP AL, 0DH        ; Enter key pressed?
    JE DONE1
    MOV [DI], AL
    INC DI
    JMP READ1
DONE1:
    MOV AL, '$'
    MOV [DI], AL

;--------------------------------------------
; INPUT SECOND STRING
;--------------------------------------------
    LEA DX, MSG2
    MOV AH, 09H
    INT 21H

    LEA DI, STR2
    MOV AH, 01H
READ2:
    INT 21H
    CMP AL, 0DH
    JE DONE2
    MOV [DI], AL
    INC DI
    JMP READ2
DONE2:
    MOV AL, '$'
    MOV [DI], AL

;--------------------------------------------
; CONCATENATION
;--------------------------------------------
    LEA SI, STR1
    LEA DI, CONCAT

COPY1:
    MOV AL, [SI]
    CMP AL, '$'
    JE COPY2
    MOV [DI], AL
    INC SI
    INC DI
    JMP COPY1

COPY2:
    LEA SI, STR2
COPY2_LOOP:
    MOV AL, [SI]
    CMP AL, '$'
    JE DONECAT
    MOV [DI], AL
    INC SI
    INC DI
    JMP COPY2_LOOP

DONECAT:
    MOV AL, '$'
    MOV [DI], AL

;--------------------------------------------
; DISPLAY CONCATENATED STRING
;--------------------------------------------
    LEA DX, MSG3
    MOV AH, 09H
    INT 21H

    LEA DX, CONCAT
    MOV AH, 09H
    INT 21H

;--------------------------------------------
; COUNT CONCATENATED STRING
;--------------------------------------------
    LEA SI, CONCAT
    MOV CX, 0          ; Counter = 0

COUNT_LOOP:
    MOV AL, [SI]
    CMP AL, '$'        ; End of string?
    JE COUNT_DONE
    INC CX             ; Increment count
    INC SI
    JMP COUNT_LOOP

COUNT_DONE:
    LEA DX, MSG4
    MOV AH, 09H
    INT 21H

    MOV AX, CX
    CALL DISP_NUM

;--------------------------------------------
; EXIT
;--------------------------------------------
EXIT:
    MOV AH, 4CH
    INT 21H

;--------------------------------------------
; PROCEDURE TO DISPLAY DECIMAL NUMBER
;--------------------------------------------
DISP_NUM PROC
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX

    MOV BX, 10        ; Divisor for base 10
    MOV CX, 0         ; Initialize counter

DIV_LOOP:
    XOR DX, DX
    DIV BX            ; AX ÷ 10 → Quotient in AX, Remainder in DX
    PUSH DX           ; Save remainder
    INC CX
    CMP AX, 0
    JNE DIV_LOOP

PRINT_LOOP:
    POP DX
    ADD DL, 30H       ; Convert to ASCII
    MOV AH, 02H
    INT 21H
    LOOP PRINT_LOOP

    POP DX
    POP CX
    POP BX
    POP AX
    RET
DISP_NUM ENDP

CODE ENDS
END START

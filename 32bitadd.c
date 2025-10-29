ASSUME DS:DATA, CS:CODE

DATA SEGMENT
    MSG1 DB 0AH,0DH,'ENTER FIRST 32-BIT NUMBER:$'
    MSG2 DB 0AH,0DH,'ENTER SECOND 32-BIT NUMBER:$'
    MSG3 DB 0AH,0DH,'SUM IS: $'
    NUM1 DB 10 DUP(?)        ; buffer for first number
    NUM2 DB 10 DUP(?)        ; buffer for second number
    RESULT DB 12 DUP(?)      ; buffer for result
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX

    ;--- INPUT FIRST NUMBER ---
    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    LEA DI, NUM1
READ1:
    MOV AH, 01H
    INT 21H
    CMP AL, 0DH              ; ENTER pressed?
    JE DONE1
    STOSB
    JMP READ1
DONE1:

    ;--- INPUT SECOND NUMBER ---
    LEA DX, MSG2
    MOV AH, 09H
    INT 21H

    LEA DI, NUM2
READ2:
    MOV AH, 01H
    INT 21H
    CMP AL, 0DH
    JE DONE2
    STOSB
    JMP READ2
DONE2:

    ;--- CONVERT ASCII TO INTEGER (FIRST NUMBER) ---
    XOR AX, AX
    XOR BX, BX
    LEA SI, NUM1
CONV1:
    LODSB
    CMP AL, 0DH
    JE END_CONV1
    CMP AL, 0
    JE END_CONV1
    SUB AL, '0'
    MOV AH, 0
    MOV CX, 10
    MUL CX
    ADD BX, AX
    JMP CONV1
END_CONV1:

    MOV DX, BX          ; Store first number in DX

    ;--- CONVERT SECOND NUMBER ---
    XOR AX, AX
    XOR BX, BX
    LEA SI, NUM2
CONV2:
    LODSB
    CMP AL, 0DH
    JE END_CONV2
    CMP AL, 0
    JE END_CONV2
    SUB AL, '0'
    MOV AH, 0
    MOV CX, 10
    MUL CX
    ADD BX, AX
    JMP CONV2
END_CONV2:

    ;--- PERFORM 32-BIT ADDITION ---
    ADD BX, DX      ; (only low 16 bits)
    ADC AX, 0       ; carry if any (simulate 32-bit)

    ;--- DISPLAY RESULT ---
    LEA DX, MSG3
    MOV AH, 09H
    INT 21H

    ; Convert BX to ASCII decimal
    MOV AX, BX
    LEA DI, RESULT
    MOV CX, 0
CONVERT_DEC:
    XOR DX, DX
    MOV BX, 10
    DIV BX
    ADD DL, '0'
    PUSH DX
    INC CX
    CMP AX, 0
    JNE CONVERT_DEC

PRINT_DEC:
    POP DX
    MOV AH, 02H
    INT 21H
    LOOP PRINT_DEC

    MOV AH, 4CH
    INT 21H

CODE ENDS
END START
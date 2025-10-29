data SEGMENT
    MSG1 DB 10, 13, 'Enter the string:$'
    MSG2 DB 10, 13, 'String is Palindrome$'
    MSG3 DB 10, 13, 'String is not Palindrome$'
    MSG4 DB 10, 13, 'Number of characters: $'
    STR1 DB 50 DUP(0)
    COUNT DB 0
data ENDS

code SEGMENT
ASSUME CS:code, DS:data
START:
    MOV AX, data
    MOV DS, AX

    ; Prompt message
    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    ; Input string
    LEA SI, STR1
    LEA DI, STR1
    MOV AH, 01H
    MOV CL, 0            ; CL will hold count

READ_LOOP:
    INT 21H              ; Read a character
    CMP AL, 0DH          ; Enter key (Carriage Return)?
    JE END_INPUT
    MOV [DI], AL
    INC DI
    INC CL               ; Increment character count
    JMP READ_LOOP

END_INPUT:
    MOV AL, '$'
    MOV [DI], AL         ; End string with '$'
    DEC DI               ; DI points to last char
    MOV COUNT, CL        ; Save count

    ; Display character count
    LEA DX, MSG4
    MOV AH, 09H
    INT 21H

    MOV AL, COUNT        ; Convert count to ASCII
    AAM                  ; Split into AH=tens, AL=ones
    ADD AH, 30H
    ADD AL, 30H
    MOV DL, AH
    MOV AH, 02H
    INT 21H
    MOV DL, AL
    MOV AH, 02H
    INT 21H

    ; Palindrome checking
    LEA SI, STR1

CHECK_LOOP:
    MOV AL, [SI]
    CMP AL, [DI]
    JNE NOTPALINDROME
    INC SI
    DEC DI
    CMP SI, DI
    JLE CHECK_LOOP

PALINDROME:
    LEA DX, MSG2
    MOV AH, 09H
    INT 21H
    JMP EXIT

NOTPALINDROME:
    LEA DX, MSG3
    MOV AH, 09H
    INT 21H

EXIT:
    MOV AH, 4CH
    INT 21H

code ENDS
END START
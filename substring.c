data SEGMENT
    MSG1 DB 10,13,'Enter the main string:$'
    MSG2 DB 10,13,'Enter the substring:$'
    MSG3 DB 10,13,'Substring FOUND!$'
    MSG4 DB 10,13,'Substring NOT FOUND!$'
    MAINSTR DB 100 DUP(0)
    SUBSTR  DB 50 DUP(0)
data ENDS

code SEGMENT
ASSUME CS:code, DS:data
START:
    MOV AX, data
    MOV DS, AX

;--------------------------------------------
; INPUT MAIN STRING
;--------------------------------------------
    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    LEA DI, MAINSTR
    MOV AH, 01H
READ_MAIN:
    INT 21H
    CMP AL, 0DH          ; Enter pressed?
    JE END_MAIN
    MOV [DI], AL
    INC DI
    JMP READ_MAIN
END_MAIN:
    MOV AL, '$'
    MOV [DI], AL

;--------------------------------------------
; INPUT SUBSTRING
;--------------------------------------------
    LEA DX, MSG2
    MOV AH, 09H
    INT 21H

    LEA DI, SUBSTR
    MOV AH, 01H
READ_SUB:
    INT 21H
    CMP AL, 0DH
    JE END_SUB
    MOV [DI], AL
    INC DI
    JMP READ_SUB
END_SUB:
    MOV AL, '$'
    MOV [DI], AL

;--------------------------------------------
; CHECK IF SUBSTRING PRESENT
;--------------------------------------------
    LEA SI, MAINSTR        ; SI → main string
CHECK_NEXT:
    MOV AL, [SI]
    CMP AL, '$'            ; End of main string?
    JE NOT_FOUND

    PUSH SI                ; Save current main pointer
    LEA DI, SUBSTR         ; DI → substring
MATCH_LOOP:
    MOV AL, [SI]
    CMP AL, '$'
    JE NOT_FOUND
    MOV BL, [DI]
    CMP BL, '$'
    JE FOUND               ; All characters matched
    CMP AL, BL
    JNE MISMATCH
    INC SI
    INC DI
    JMP MATCH_LOOP

MISMATCH:
    POP SI
    INC SI
    JMP CHECK_NEXT

FOUND:
    LEA DX, MSG3
    MOV AH, 09H
    INT 21H
    JMP EXIT

NOT_FOUND:
    LEA DX, MSG4
    MOV AH, 09H
    INT 21H

;--------------------------------------------
; EXIT
;--------------------------------------------
EXIT:
    MOV AH, 4CH
    INT 21H

code ENDS
END START
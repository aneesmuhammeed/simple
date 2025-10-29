data SEGMENT
    MSG1 DB 10,13,'Enter first string:$'
    MSG2 DB 10,13,'Enter second string:$'
    MSG3 DB 10,13,'First string is palindrome$'
    MSG4 DB 10,13,'First string is not palindrome$'
    MSG5 DB 10,13,'Second string is palindrome$'
    MSG6 DB 10,13,'Second string is not palindrome$'
    MSG7 DB 10,13,'Concatenated string:$'
    STR1 DB 50 DUP(0)
    STR2 DB 50 DUP(0)
    CONCAT DB 100 DUP(0)
data ENDS

code SEGMENT
ASSUME CS:code, DS:data
START:
    MOV AX, data
    MOV DS, AX

;------------------------------------------------------
; INPUT FIRST STRING
;------------------------------------------------------
    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    LEA DI, STR1
    MOV AH, 01H
READ1:
    INT 21H
    CMP AL, 0DH
    JE DONE1
    MOV [DI], AL
    INC DI
    JMP READ1
DONE1:
    MOV AL, '$'
    MOV [DI], AL

;------------------------------------------------------
; INPUT SECOND STRING
;------------------------------------------------------
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

;------------------------------------------------------
; CHECK FIRST STRING PALINDROME
;------------------------------------------------------
    LEA SI, STR1
    LEA DI, STR1

F1_END:                 ; Find end of STR1
    CMP BYTE PTR [DI], '$'
    JE F1_FOUND
    INC DI
    JMP F1_END
F1_FOUND:
    DEC DI

F1_CHECK:
    MOV AL, [SI]
    CMP AL, [DI]
    JNE F1_NOTPAL
    INC SI
    DEC DI
    CMP SI, DI
    JLE F1_CHECK

F1_PAL:
    LEA DX, MSG3
    MOV AH, 09H
    INT 21H
    JMP SECOND_PAL

F1_NOTPAL:
    LEA DX, MSG4
    MOV AH, 09H
    INT 21H

;------------------------------------------------------
; CHECK SECOND STRING PALINDROME
;------------------------------------------------------
SECOND_PAL:
    LEA SI, STR2
    LEA DI, STR2

F2_END:
    CMP BYTE PTR [DI], '$'
    JE F2_FOUND
    INC DI
    JMP F2_END
F2_FOUND:
    DEC DI

F2_CHECK:
    MOV AL, [SI]
    CMP AL, [DI]
    JNE F2_NOTPAL
    INC SI
    DEC DI
    CMP SI, DI
    JLE F2_CHECK

F2_PAL:
    LEA DX, MSG5
    MOV AH, 09H
    INT 21H
    JMP CONCATENATE

F2_NOTPAL:
    LEA DX, MSG6
    MOV AH, 09H
    INT 21H

;------------------------------------------------------
; CONCATENATION
;------------------------------------------------------
CONCATENATE:
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

;------------------------------------------------------
; DISPLAY CONCATENATED STRING
;------------------------------------------------------
    LEA DX, MSG7
    MOV AH, 09H
    INT 21H

    LEA DX, CONCAT
    MOV AH, 09H
    INT 21H

;------------------------------------------------------
; EXIT
;------------------------------------------------------
EXIT:
    MOV AH, 4CH
    INT 21H

code ENDS
END START

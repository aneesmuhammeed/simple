DATA SEGMENT
    MSG1 DB 10,13,'Enter main string: $'
    MSG2 DB 10,13,'String IS a palindrome.$'
    MSG3 DB 10,13,'String is NOT a palindrome.$'
    MSG4 DB 10,13,'Enter substring to search: $'
    MSG5 DB 10,13,'Substring FOUND in main string.$'
    MSG6 DB 10,13,'Substring NOT FOUND in main string.$'

    MAINSTR DB 100 DUP(0)
    SUBSTR  DB 50 DUP(0)
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA
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
    CMP AL, 0DH
    JE DONE_MAIN
    MOV [DI], AL
    INC DI
    JMP READ_MAIN
DONE_MAIN:
    MOV AL, '$'
    MOV [DI], AL

;--------------------------------------------
; PALINDROME CHECK
;--------------------------------------------
    LEA SI, MAINSTR
    LEA DI, MAINSTR

; Find end of string (DI → last char before '$')
FIND_END:
    CMP BYTE PTR [DI], '$'
    JE GOT_END
    INC DI
    JMP FIND_END
GOT_END:
    DEC DI             ; point to last character

CHECK_LOOP:
    MOV AL, [SI]
    CMP AL, [DI]
    JNE NOT_PAL
    INC SI
    DEC DI
    CMP SI, DI
    JL CHECK_LOOP

PAL:
    LEA DX, MSG2
    MOV AH, 09H
    INT 21H
    JMP ASK_SUB

NOT_PAL:
    LEA DX, MSG3
    MOV AH, 09H
    INT 21H

;--------------------------------------------
; ASK FOR SUBSTRING AND SEARCH
;--------------------------------------------
ASK_SUB:
    LEA DX, MSG4
    MOV AH, 09H
    INT 21H

    LEA DI, SUBSTR
    MOV AH, 01H
READ_SUB:
    INT 21H
    CMP AL, 0DH
    JE DONE_SUB
    MOV [DI], AL
    INC DI
    JMP READ_SUB
DONE_SUB:
    MOV AL, '$'
    MOV [DI], AL

;--------------------------------------------
; SEARCH FOR SUBSTRING
;--------------------------------------------
    LEA SI, MAINSTR       ; SI → main string
SEARCH_NEXT:
    LEA DI, SUBSTR        ; DI → substring start
    MOV BX, SI            ; BX tracks current main position

COMPARE_LOOP:
    MOV AL, [BX]
    MOV DL, [DI]
    CMP DL, '$'
    JE FOUND              ; substring ended ⇒ match found
    CMP AL, '$'
    JE NOT_FOUND          ; main string ended ⇒ no match
    CMP AL, DL
    JNE NEXT_START
    INC BX
    INC DI
    JMP COMPARE_LOOP

NEXT_START:
    INC SI
    MOV AL, [SI]
    CMP AL, '$'
    JNE SEARCH_NEXT
    JMP NOT_FOUND

FOUND:
    LEA DX, MSG5
    MOV AH, 09H
    INT 21H
    JMP EXIT

NOT_FOUND:
    LEA DX, MSG6
    MOV AH, 09H
    INT 21H

;--------------------------------------------
; EXIT PROGRAM
;--------------------------------------------
EXIT:
    MOV AH, 4CH
    INT 21H

CODE ENDS
END START

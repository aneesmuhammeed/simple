#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
    int start, length, temp;
    char addr[10], label[10], opcode[10],
    operand[10];
    char mnemonic[10], code[10];
    char symbol[10], symaddr[10];

    FILE *inter, *optab, *symtab, *asml, *objc, *leng;
    inter = fopen("intermediate.txt", "r");
    optab = fopen("optab.txt", "r");
    symtab = fopen("symtab.txt", "r");
    asml = fopen("asml.txt", "w");
    objc = fopen("objc.txt", "w");
    leng = fopen("length.txt", "r");

    if (!inter || !optab || !symtab || !asml || !objc || !leng) {
        printf("Error: Could not open one or more files.\n");
        return 1;
    }

    fscanf(leng, "%d", &length);
    fscanf(inter, "%s %s %s %s", addr, label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%-10s\n", "~", label, opcode, operand, "~");
        fprintf(objc, "H^%-6s^%06X^%06X\n", label, start, length);
        fscanf(inter, "%s %s %s %s", addr, label, opcode, operand);
    } else {
        start = 0;
    }

    fprintf(objc, "T^%06X^", start);
    while (strcmp(opcode, "END") != 0) {
        int found = 0;
        rewind(optab);
        while (fscanf(optab, "%s %s", mnemonic, code) != EOF) {
            if (strcmp(mnemonic, opcode) == 0) {
                found = 1;
                rewind(symtab);
                int sym_found = 0;
                while (fscanf(symtab, "%s %s", symbol, symaddr) != EOF) {
                    if (strcmp(symbol, operand) == 0) {
                        fprintf(objc, "%s%s^", code, symaddr);
                        fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%-10s\n", addr, label, opcode, operand, strcat(strcpy(code, code), symaddr));
                        sym_found = 1;
                        break;
                    }
                }
                if (!sym_found) {
                    fprintf(objc, "%s0000^", code);
                    fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%-10s\n", addr, label, opcode, operand, strcat(strcpy(code, code), "0000"));
                }
                break;
            }
        }
        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                temp = atoi(operand);
                fprintf(objc, "%06X^", temp);
                fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%06X\n", addr, label, opcode, operand, temp);
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    for (int i = 2; i < (int)strlen(operand) - 1; i++) {
                        fprintf(objc, "%02X", operand[i]);
                    }
                    fprintf(objc, "^");
                    fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%s\n", addr, label, opcode, operand, operand);
                } else if (operand[0] == 'X') {
                    for (int i = 2; i < (int)strlen(operand) - 1; i++) {
                        fprintf(objc, "%c", operand[i]);
                    }
                    fprintf(objc, "^");
                    fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%s\n", addr, label, opcode, operand, operand);
                }
            } else {
                fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\n", addr, label, opcode, operand);
            }
        }
        fscanf(inter, "%s %s %s %s", addr, label, opcode, operand);
    }

    fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%-10s\n", "~", label, opcode, operand, "~");
    fprintf(objc, "\nE^%06X\n", start);

    fclose(optab);
    fclose(symtab);
    fclose(asml);
    fclose(objc);
    fclose(inter);
    fclose(leng);

    printf("Pass 2 completed successfully.\n");
    
    return 0;
}




//intermediate.txt
2000 PROG START 2000
2000 ~ LDA NUM1
2003 ~ ADD NUM2
2006 ~ STA RES
2009 NUM1 WORD 5
200C NUM2 WORD 7
200F RES RESW 1
2012 ~ END PROG


//optab.txt
LDA 00
ADD 18
STA 0C


//symtab.txt
NUM1 2009
NUM2 200C
RES 200F


//length.txt
12
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char bitmask[12];
char bit[50];

void convert(char h[12]);

int main() {
    char line[200], recordType[5], pn[10];
    int start, address, opcode, addr, actualadd, tlen;
    char relocbit;
    int orig_start, offset;
    FILE *fp1, *fp2;

    printf("Enter the actual starting address: ");
    scanf("%x", &start);

    fp1 = fopen("RLIN.txt", "r");
    if (fp1 == NULL) {
        printf("Error opening input file.\n");
        exit(1);
    }

    fp2 = fopen("RLOUT.txt", "w");
    if (fp2 == NULL) {
        printf("Error creating output file.\n");
        fclose(fp1);
        exit(1);
    }

    fprintf(fp2, " ----------------------------\n");
    fprintf(fp2, " ADDRESS\tCONTENT\n");
    fprintf(fp2, " ----------------------------\n");

    while (fgets(line, sizeof(line), fp1)) {
        // Remove trailing newline
        line[strcspn(line, "\n")] = '\0';

        // Split first token (record type)
        char *token = strtok(line, "^");
        if (!token) continue;
        strcpy(recordType, token);

        if (strcmp(recordType, "H") == 0) {
            // Header record: H^TEST^001000^00107A
            char progname[10], startAddrStr[10], lengthStr[10];
            token = strtok(NULL, "^");
            strcpy(progname, token);
            token = strtok(NULL, "^");
            strcpy(startAddrStr, token);
            token = strtok(NULL, "^");
            strcpy(lengthStr, token);

            sscanf(startAddrStr, "%x", &orig_start);
        } 
        else if (strcmp(recordType, "T") == 0) {
            // Text record: T^001000^1E^F1^141003^281030...
            char addressStr[10], lenStr[10];

            token = strtok(NULL, "^");
            strcpy(addressStr, token);
            sscanf(addressStr, "%x", &address);

            token = strtok(NULL, "^");
            strcpy(lenStr, token);
            sscanf(lenStr, "%x", &tlen);

            offset = start - orig_start;
            address += offset;

            // Next token is bitmask (e.g., "F1")
            token = strtok(NULL, "^");
            strcpy(bitmask, token);
            convert(bitmask);

            int i = 0;
            token = strtok(NULL, "^");

            while (token && i < strlen(bit)) {
                // Combine opcode and address (e.g., "141003")
                sscanf(token, "%2x%4x", &opcode, &addr);

                relocbit = bit[i];
                if (relocbit == '0')
                    actualadd = addr;
                else
                    actualadd = addr + offset;

                fprintf(fp2, "%04X\t\t%02X%04X\n", address, opcode, actualadd);
                address += 3;
                token = strtok(NULL, "^");
                i++;
            }
        } 
        else if (strcmp(recordType, "E") == 0) {
            break;
        }
    }

    fprintf(fp2, " ----------------------------\n");
    fclose(fp1);
    fclose(fp2);

    printf("Successfully implemented relocating loader.\n");
    return 0;
}

void convert(char h[12]) {
    int i, l;
    strcpy(bit, "");
    l = strlen(h);

    for (i = 0; i < l; i++) {
        switch (h[i]) {
            case '0': strcat(bit, "0000"); break;
            case '1': strcat(bit, "0001"); break;
            case '2': strcat(bit, "0010"); break;
            case '3': strcat(bit, "0011"); break;
            case '4': strcat(bit, "0100"); break;
            case '5': strcat(bit, "0101"); break;
            case '6': strcat(bit, "0110"); break;
            case '7': strcat(bit, "0111"); break;
            case '8': strcat(bit, "1000"); break;
            case '9': strcat(bit, "1001"); break;
            case 'A': strcat(bit, "1010"); break;
            case 'B': strcat(bit, "1011"); break;
            case 'C': strcat(bit, "1100"); break;
            case 'D': strcat(bit, "1101"); break;
            case 'E': strcat(bit, "1110"); break;
            case 'F': strcat(bit, "1111"); break;
        }
    }
}




//RLIN.txt
H^TEST^001000^00107A  
T^001000^1E^F1^141003^281030^301015^482039^3C1003  
E
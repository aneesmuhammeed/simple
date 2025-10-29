#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char line[100], name1[10];
    char startAddrStr[10], progLenStr[10];
    int startAddr, progLen, textAddr;

    fp = fopen("objectcode.txt", "r");
    if (fp == NULL) {
        printf("Error: Cannot open objectcode.txt\n");
        return 1;
    }

    // Read Header Record
    fscanf(fp, "%s", line);
    if (line[0] != 'H') {
        printf("Invalid object program format!\n");
        fclose(fp);
        return 1;
    }

    // Example Header: H^TEST^001000^00107A
    sscanf(line, "H^%[^'^']^%[^'^']^%s", name1, startAddrStr, progLenStr);
    startAddr = (int)strtol(startAddrStr, NULL, 16);
    progLen = (int)strtol(progLenStr, NULL, 16);

    printf("ABSOLUTE LOADER OUTPUT\n");
    printf("--------------------------------------\n");
    printf("Program Name: %s\n", name1);
    printf("Start Address: %04X\n", startAddr);
    printf("Program Length: %04X\n", progLen);
    printf("--------------------------------------\n");
    printf("Address\t\tByte\n");
    printf("--------------------------------------\n");

    // Process Text Records
    while (fscanf(fp, "%s", line) != EOF) {
        if (line[0] == 'T') {
            char tempAddrStr[10], lenStr[10];
            sscanf(line, "T^%[^'^']^%[^'^']", tempAddrStr, lenStr);
            textAddr = (int)strtol(tempAddrStr, NULL, 16);

            // Skip 3 fields (T, start, length)
            char *ptr = strchr(line + 1, '^');
            for (int i = 0; i < 2 && ptr; i++)
                ptr = strchr(ptr + 1, '^');
            if (!ptr) continue;
            ptr++;

            // Process object code bytes
            while (*ptr && *ptr != '$') {
                if (*ptr == '^') { ptr++; continue; }

                // Take two hex digits (one byte)
                char byte[3];
                byte[0] = *ptr++;
                byte[1] = *ptr++;
                byte[2] = '\0';

                printf("%04X\t\t%s\n", textAddr, byte);
                textAddr++;
            }
        } 
        else if (line[0] == 'E') {
            printf("--------------------------------------\n");
            printf("End of program.\n");
            break;
        }
    }

    fclose(fp);
    return 0;
}


//objectcode.txt
H^TEST^001000^000015
T^001000^06^141033^281030^301015$
E^001000
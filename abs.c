#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
    FILE *fp;
    int i, j, staddr1;
    char name[10], line[100], name1[10], staddr[10];

    printf("Enter program name: ");
    scanf("%s", name);

    fp = fopen("objectcode.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    fscanf(fp, "%s", line);
    if (line[0] != 'H') {
        printf("Invalid object program format.\n");
        fclose(fp);
        return;
    }

    i = 2;
    j = 0;
    while (line[i] != '^' && line[i] != '\0' && j < 6) {
        name1[j++] = line[i++];
    }
    name1[j] = '\0';

    printf("Program name from object file: %s\n", name1);

    if (strcmp(name, name1) == 0) {
        while (fscanf(fp, "%s", line) != EOF) {
            if (line[0] == 'T') {
                i = 2;
                j = 0;
                while (line[i] != '^' && line[i] != '\0' && j < 6)
                    staddr[j++] = line[i++];
                staddr[j] = '\0';

                staddr1 = (int)strtol(staddr, NULL, 16);

                int caretCount = 0;
                while (line[i] != '\0' && caretCount < 2) {
                    if (line[i] == '^')
                        caretCount++;
                    i++;
                }

                while (line[i] != '$' && line[i] != '\0') {
                    if (line[i] != '^') {
                        printf("00%04X\t%c%c\n", staddr1, line[i], line[i + 1]);
                        staddr1++;
                        i += 2;
                    } else {
                        i++;
                    }
                }
            } else if (line[0] == 'E') {
                printf("\nEnd of program.\n");
                break;
            }
        }
    } else {
        printf("Program name does not match.\n");
    }

    fclose(fp);
}



//objectcode.txt
H^TEST^001000^000015
T^001000^06^141033^281030^301015$
E^001000
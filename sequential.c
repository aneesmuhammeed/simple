#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, j, k;
    int fileCount = 0;
    int b[20], sb[20], mem[100], ch;

    // Initialize memory blocks (0 = free)
    for (i = 0; i < 100; i++)
        mem[i] = 0;

    do {
        fileCount++;
        printf("\nEnter the number of blocks occupied by file %d: ", fileCount);
        scanf("%d", &b[fileCount]);

        int valid = 0;
        while (!valid) {
            printf("Enter the starting block of file %d: ", fileCount);
            scanf("%d", &sb[fileCount]);

            // Check if starting block + length goes out of memory
            if (sb[fileCount] + b[fileCount] > 100) {
                printf("Not enough space from this starting block! Try again.\n");
                continue;
            }

            // Check if all required blocks are free
            valid = 1;
            for (j = sb[fileCount]; j < sb[fileCount] + b[fileCount]; j++) {
                if (mem[j] != 0) {
                    printf("Block %d is already allocated! Try a different starting block.\n", j);
                    valid = 0;
                    break;
                }
            }

            // If valid, allocate
            if (valid) {
                for (j = sb[fileCount]; j < sb[fileCount] + b[fileCount]; j++) {
                    mem[j] = fileCount; // mark block with file number
                    printf("Block %d allocated for file %d\n", j, fileCount);
                }
                printf("File %d allocated successfully!\n", fileCount);
            }
        }

        printf("\nPress 1 to continue allocation, 0 to stop: ");
        scanf("%d", &ch);

    } while (ch == 1);

    // Display final allocation table
    printf("\nFile\tStart\tLength\n");
    for (i = 1; i <= fileCount; i++)
        printf("%2d\t%5d\t%6d\n", i, sb[i], b[i]);

    printf("\nMemory Status (0 = Free, n = File number):\n");
    for (i = 0; i < 100; i++) {
        printf("%d ", mem[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }

    return 0;
}

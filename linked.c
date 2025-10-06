#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, j, k;
    int mem[100] = {0};   // memory blocks: 0 = free, non-zero = allocated
    int alloc[20] = {0};  // pre-allocated blocks
    int sb[20] = {0};     // starting block for each file
    int b[20] = {0};      // number of blocks per file
    int count = 0, ch;
    int n;

    // Input already allocated blocks
    printf("\nEnter the number of blocks already allocated: ");
    scanf("%d", &n);

    if (n > 0) {
        printf("\nEnter the already allocated block numbers:\n");
        for (i = 0; i < n; i++) {
            scanf("%d", &alloc[i]);
            if (alloc[i] >= 0 && alloc[i] < 100)
                mem[alloc[i]] = 1;
        }
    }

    do {
        count++;
        printf("\nEnter the number of blocks occupied by file %d: ", count);
        scanf("%d", &b[count]);

        printf("Enter the starting block of file %d: ", count);
        scanf("%d", &sb[count]);

        int success = 0;
        k = sb[count];

        while (success < b[count]) {
            if (k >= 100) {
                printf("Memory limit reached! File %d not fully allocated.\n", count);
                break;
            }

            if (mem[k] == 0) {
                mem[k] = count; // mark block with file number
                printf("Block %d allocated for file %d\n", k, count);
                success++;
            } else {
                printf("Block %d is already allocated. Skipping...\n", k);
            }

            k++;
        }

        if (success == b[count])
            printf("File %d allocated successfully!\n", count);
        else
            printf("File %d only partially allocated (%d/%d blocks).\n", count, success, b[count]);

        printf("\nPress 1 to continue allocation, 0 to stop: ");
        scanf("%d", &ch);

    } while (ch == 1);

    // Display final allocation table
    printf("\nFile\tStart\tLength\n");
    for (j = 1; j <= count; j++)
        printf("%2d\t%5d\t%6d\n", j, sb[j], b[j]);

    // Display memory map
    printf("\nMemory Status (0 = Free, n = File number):\n");
    for (i = 0; i < 100; i++) {
        printf("%d ", mem[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }

    return 0;
}

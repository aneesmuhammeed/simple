//sequential
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

//indexed
#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, j;
    int mem[100] = {0};     // memory blocks (0 = free, 1 = allocated)
    int ib[20] = {0};       // index block of each file
    int b[20] = {0};        // number of data blocks for each file
    int blocks[20][20];     // data blocks per file
    int count = 0, ch;

    do {
        count++;
        int indexBlock;

        // Input index block
        while (1) {
            printf("\nEnter the index block for file %d: ", count);
            scanf("%d", &indexBlock);

            if (indexBlock < 0 || indexBlock >= 100) {
                printf("Invalid block number! Must be between 0 and 99.\n");
                continue;
            }

            if (mem[indexBlock] == 0) {
                mem[indexBlock] = 1;
                ib[count] = indexBlock;
                printf("Block %d allocated as index block for file %d.\n", indexBlock, count);
                break;
            } else {
                printf("Block %d is already allocated. Try another block.\n", indexBlock);
            }
        }

        // Input number of data blocks
        printf("Enter the number of blocks occupied by file %d: ", count);
        scanf("%d", &b[count]);

        // Input and allocate each data block
        printf("Enter the block numbers for file %d:\n", count);
        for (i = 0; i < b[count]; i++) {
            int blk;
            while (1) {
                scanf("%d", &blk);

                if (blk < 0 || blk >= 100) {
                    printf("Invalid block number! Must be between 0 and 99.\n");
                    continue;
                }

                if (mem[blk] == 0) {
                    mem[blk] = count;  // mark block as allocated to file number
                    blocks[count][i] = blk;
                    printf("Block %d allocated for file %d.\n", blk, count);
                    break;
                } else {
                    printf("Block %d is already allocated. Enter another block: ", blk);
                }
            }
        }

        printf("\nFile %d Allocation Successful!\n", count);

        printf("\nPress 1 to continue allocation, 0 to stop: ");
        scanf("%d", &ch);

    } while (ch == 1);

    // Display allocation table
    printf("\nFile\tIndex\tLength\tBlocks\n");
    for (j = 1; j <= count; j++) {
        printf("%2d\t%5d\t%6d\t", j, ib[j], b[j]);
        for (i = 0; i < b[j]; i++)
            printf("%d ", blocks[j][i]);
        printf("\n");
    }

    // Display memory map
    printf("\nMemory Status (0 = Free, n = File number or 1 for index block):\n");
    for (i = 0; i < 100; i++) {
        printf("%d ", mem[i]);
        if ((i + 1) % 10 == 0)
            printf("\n");
    }

    return 0;
}

//linked

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

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

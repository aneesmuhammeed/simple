#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 10

int frames[MAX_FRAMES]; 
int front = 0; 
int rear = -1; 

void initialize() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1; 
    }
}

void displayFrames() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

void FIFO(int pages[], int n) {
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                printf("Page %d already in frame\n", page);
                break;
            }
        }

        if (!found) {
            page_faults++;

            if (rear < MAX_FRAMES - 1) {
                rear++;
            } else {
                rear = 0; 
                front = (front + 1) % MAX_FRAMES;
            }
            frames[rear] = page;
            printf("Page %d loaded in frame %d\n", page, rear);
        }
        displayFrames();
    }
    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES]; 
    int n;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    initialize();
    FIFO(pages, n); 
    return 0;
}

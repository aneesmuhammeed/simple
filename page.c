//fifo
#include <stdio.h>

#define MAX_FRAMES 3 

int frames[MAX_FRAMES];
int rear = -1;

void init() {
    for (int i=0; i<MAX_FRAMES; i++) {
        frames[i] = -1;
    }
}

void display() {
    for (int i=0; i<MAX_FRAMES; i++) {
        if (frames[i] != -1) {
            printf("%d ", frames[i]);
        } else {
            printf("-");
        }
    }
    printf("\n");
}

void fifo(int pages[], int n) {
    int page_fault = 0;
    // int front = 0;

    for (int i=0; i<n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j=0; j<MAX_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                printf("page %d already there at %d\n", page, j);
                break;
            }
        }

        if (!found) {
            rear = (rear + 1) % MAX_FRAMES;
            frames[rear] = page;
            page_fault++;
            printf("page %d loaded to frame %d\n", page, rear);
        }

        display();
    }
    printf("total page faults: %d\n", page_fault);
}

void main() {
    int n;
    printf("Enter no: of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter page sequence: ");
    for (int i=0; i<n; i++) {
        scanf("%d", &pages[i]);
    }
    init();
    fifo(pages, n);
}

//lru
#include <stdio.h>

#define MAX_FRAMES 3

int frames[MAX_FRAMES];
int counter[MAX_FRAMES];

void init() {
    for (int i=0; i<MAX_FRAMES; i++) {
        frames[i] = -1;
        counter[i] = 0;
    }
}

void display() {
    for (int i=0; i<MAX_FRAMES; i++) {
        if (frames[i] != -1) {
            printf("%d", frames[i]);
        } else {
            printf("-");
        }
    }
    printf("\n");

    // ------displaying counter values-------
    // for (int j=0; j<MAX_FRAMES; j++) {
    //     printf("%d", counter[j]);
    // }
    // printf("\n");
}

int findLRU() {
    int max = counter[0];
    int lru_frame = 0;

    for (int i=1; i<MAX_FRAMES; i++) {
        if (counter[i] > max) {
            max = counter[i];
            lru_frame = i;
        }
    }

    return lru_frame;
}

void lru(int pages[], int n) {
    int page_faults = 0;

    for (int i=0; i<n; i++) {
        int page = pages[i];
        int found = 0;
        
        for (int j=0; j<MAX_FRAMES; j++) {
            counter[j]++;
        }

        for (int j=0; j<MAX_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                printf("page %d already in frame %d\n", page, j);
                counter[j] = 0;
                break;
            }
        }

        if (!found) {
            int lru_frame = findLRU();
            frames[lru_frame] = page;
            printf("page %d loaded into frame %d\n", page, lru_frame);
            page_faults++;
            counter[lru_frame] = 0;
        }
        display();
    }
    printf("total page faults: %d", page_faults);
}

void main() {
    int n;
    printf("Enter no: of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter page sequence: ");
    for (int i=0; i<n; i++) {
        scanf("%d", &pages[i]);
    }
    init();
    lru(pages, n);
}

//lfu
#include <stdio.h>

#define MAX_FRAMES 3

int frames[MAX_FRAMES];
int count[MAX_FRAMES];

void init() {
    for (int i=0; i<MAX_FRAMES; i++) {
        frames[i] = -1;
        count[i] = 0;
    }
}

void display() {
    for (int i=0; i<MAX_FRAMES; i++) {
        if (frames[i] != -1) {
            printf("%d", frames[i]);
        } else {
            printf("-");
        }
    }
    printf("\n");

    // ----displaying counter values-----
    // for (int i=0; i<MAX_FRAMES; i++) {
    //     printf("%d", count[i]);
    // }
    // printf("\n");
}

int findLFU() {
    int min = count[0];
    int lfu_frame = 0;

    for (int i=0; i<MAX_FRAMES; i++) {
        if (count[i] < min) {
            min = count[i];
            lfu_frame = i;
        }
    }
    return lfu_frame;
}

void lfu(int pages[], int n) {
    int page_fault = 0;
    
    for (int i=0; i<n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j=0; j<MAX_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                count[j]++;
                printf("page %d found in frame %d\n", page, j);
                break;
            }
        }

        if (!found) {
            int lfu_frame = findLFU();
            frames[lfu_frame] = page;
            count[lfu_frame] = 1;
            page_fault++;
            printf("page %d loaded in frame %d\n", page, lfu_frame);
        }
        display();
    }

    printf("total page faults: %d\n", page_fault);
}

void main() {
    int n;
    printf("Enter no: of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter page sequence: ");
    for (int i=0; i<n; i++) {
        scanf("%d", &pages[i]);
    }
    init();
    lfu(pages, n);
}


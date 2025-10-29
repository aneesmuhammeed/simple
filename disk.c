//fcfs
#include <stdio.h>
#include <stdlib.h>

// #define MAX_REQUESTS 20

int fcfs_disk(int requests[], int n, int pos) {
    int total_seek_time = 0;
    int cur_pos = pos;

    for (int i=0; i<n; i++) {
        total_seek_time += abs(cur_pos - requests[i]);
        cur_pos = requests[i];
    }

    return total_seek_time;
}

void main() {
    int n;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int requests[n];
    for (int i=0; i<n; i++) {
        printf("Enter request %d: ", i+1);
        scanf("%d", &requests[i]);
    }
    int pos;
    printf("Enter starting position of head: ");
    scanf("%d", &pos);
    int total_seek_time = fcfs_disk(requests, n, pos);
    printf("Total seek time: %d\n", total_seek_time);
}

//scan
#include <stdio.h>
#include <stdlib.h>

#define MAX_TRACK 199  // max track number (you can adjust)

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int scan(int requests[], int n, int head, int direction) {
    int total_seek_time = 0;
    int distance, cur_track;
    int i, j;
    
    // Sort the request array
    qsort(requests, n, sizeof(int), compare);

    // Find position of head in sorted order
    int pos;
    for (i = 0; i < n; i++) {
        if (head < requests[i]) {
            pos = i;
            break;
        }
    }

    printf("\nHead movement sequence:\n");
    printf("%d", head);

    if (direction == 1) { // moving toward higher end
        // Move toward MAX_TRACK
        for (i = pos; i < n; i++) {
            distance = abs(head - requests[i]);
            total_seek_time += distance;
            head = requests[i];
            printf(" -> %d", head);
        }
        // Go to end, then reverse
        if (head != MAX_TRACK) {
            total_seek_time += abs(MAX_TRACK - head);
            head = MAX_TRACK;
        }

        // Now move to beginning direction
        for (i = pos - 1; i >= 0; i--) {
            distance = abs(head - requests[i]);
            total_seek_time += distance;
            head = requests[i];
            printf(" -> %d", head);
        }
    } else { // moving toward lower end
        // Move toward 0
        for (i = pos - 1; i >= 0; i--) {
            distance = abs(head - requests[i]);
            total_seek_time += distance;
            head = requests[i];
            printf(" -> %d", head);
        }

        if (head != 0) {
            total_seek_time += abs(head - 0);
            head = 0;
        }

        // Now move toward higher end
        for (i = pos; i < n; i++) {
            distance = abs(head - requests[i]);
            total_seek_time += distance;
            head = requests[i];
            printf(" -> %d", head);
        }
    }

    printf("\n");
    return total_seek_time;
}

int main() {
    int n, head, direction;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter head direction (1 = high, 0 = low): ");
    scanf("%d", &direction);

    int total_seek_time = scan(requests, n, head, direction);
    printf("\nTotal seek time: %d\n", total_seek_time);

    return 0;
}

//cscan
#include <stdio.h>
#include <stdlib.h>

#define MAX_TRACK 199  // Last track (can change as needed)

// Comparison function for sorting
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int cscan(int requests[], int n, int head) {
    int total_seek_time = 0;
    int i;

    // Sort the requests in ascending order
    qsort(requests, n, sizeof(int), compare);

    // Find index of first request greater than head
    int start = 0;
    for (i = 0; i < n; i++) {
        if (requests[i] > head) {
            start = i;
            break;
        }
    }

    printf("\nHead movement sequence:\n");
    printf("%d", head);

    // Service requests to the right of head
    for (i = start; i < n; i++) {
        total_seek_time += abs(head - requests[i]);
        head = requests[i];
        printf(" -> %d", head);
    }

    // Go to the end of the disk
    if (head != MAX_TRACK) {
        total_seek_time += abs(MAX_TRACK - head);
        head = MAX_TRACK;
        printf(" -> %d", head);
    }

    // Jump from end to 0 (circular move)
    total_seek_time += MAX_TRACK;
    head = 0;
    printf(" -> %d", head);

    // Service the remaining requests (left side)
    for (i = 0; i < start; i++) {
        total_seek_time += abs(head - requests[i]);
        head = requests[i];
        printf(" -> %d", head);
    }

    printf("\n");
    return total_seek_time;
}

int main() {
    int n, head;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    int total_seek_time = cscan(requests, n, head);
    printf("\nTotal seek time: %d\n", total_seek_time);

    return 0;
}
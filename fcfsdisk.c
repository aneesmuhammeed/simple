#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

int calculateTotalSeekTime(int *requests, int numRequests) {
    int totalSeekTime = 0;
    int currentTrack = 0;
    for (int i = 0; i < numRequests; i++) {
        int seekTime = abs(currentTrack - requests[i]);
        currentTrack = requests[i];
        totalSeekTime += seekTime;
    }
    return totalSeekTime;
}

int main() {
    int requests[MAX_REQUESTS];
    int numRequests;
    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);
    if (numRequests <= 0 || numRequests > MAX_REQUESTS) {
        printf("Invalid number of requests.\n");
        return 1;
    }
    printf("Enter the disk requests (track numbers):\n");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }
    int totalSeekTime = calculateTotalSeekTime(requests, numRequests);
    printf("Total seek time using FCFS: %d\n", totalSeekTime);
    return 0;
}

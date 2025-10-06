#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

int calculateTotalSeekTime(int *requests, int numRequests) {
    int totalSeekTime = 0;
    int currentTrack = 0; 
    int direction = 1; 
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = 0; j < numRequests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < numRequests; i++) {
        while (currentTrack >= 0 && currentTrack <= 199) {
            if (requests[i] == currentTrack) {
                totalSeekTime += abs(currentTrack - requests[i]); // Add seek time
                requests[i] = -1; 
                break; 
            }
            currentTrack += direction;
            totalSeekTime++; 
        }
        if (currentTrack == 200) {
            currentTrack = 0;
            direction = 1; 
        }
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
    printf("Total seek time using C-SCAN: %d\n", totalSeekTime);
    return 0;
}

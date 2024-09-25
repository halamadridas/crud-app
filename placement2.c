#include <stdio.h>

int circularArrayLoop(int* res, int resSize, int* cost, int costSize) {
    for (int i = 0; i < resSize; i++) {
        int curr = i;
        int sum = 0; // Track resource accumulation

        // Loop to check if a cycle exists starting from the current checkpoint
        do {
            sum += res[curr];
            curr = (curr + 1) % resSize; // Move to the next checkpoint (circular fashion)
        } while (curr != i && sum >= cost[curr]);

        // If the loop stops because we reached the starting point (curr == i)
        // and the accumulated resources are sufficient (sum >= cost[curr]),
        // then this is the starting checkpoint for a successful journey.
        if (curr == i && sum >= cost[curr]) {
            return i;
        }
    }

    // No starting checkpoint found for a successful journey
    return -1;
}

int main() {
    int res[] = {1, 2, 3, 4, 5};
    int cost[] = {3, 4, 5, 1, 2};
    int resSize = sizeof(res) / sizeof(res[0]);
    int costSize = sizeof(cost) / sizeof(cost[0]);

    int start = circularArrayLoop(res, resSize, cost, costSize);

    if (start == -1) {
        printf("No starting checkpoint found for a successful journey.\n");
    } else {
        printf("Starting checkpoint: %d\n", start);
    }

    return 0;
}

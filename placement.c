#include <stdio.h>

int findUnsortedSubarray(int nums[], int n) {
    int i = 0, j = n - 1;

    // Find the first element that breaks the increasing order from the left.
    while (i < n - 1 && nums[i] <= nums[i + 1]) {
        i++;
    }

    // If the list is already sorted, return 0.
    if (i == n - 1) {
        return 0;
    }

    // Find the last element that breaks the decreasing order from the right.
    while (j > 0 && nums[j] >= nums[j - 1]) {
        j--;
    }

    return j + 1; // Return the ending index (inclusive)
}

int main() {
    int nums[] = {2, 6, 4, 8, 10, 9, 15};
    int n = sizeof(nums) / sizeof(nums[0]);

    int start = findUnsortedSubarray(nums, n);

    if (start == 0) {
        printf("The array is already sorted.\n");
    } else {
        printf("Subarray to be rearranged: starts at index %d\n", start);
    }

return 0;
}
